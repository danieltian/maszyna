#include "stdafx.h"
#include "uitranscripts.h"

#include "Globals.h"
#include "parser.h"
#include "utilities.h"
#include "Logs.h"
#include "Timer.h"
#include "simulationtime.h"

namespace ui {

TTranscripts Transcripts;

// dodanie linii do tabeli, (show) i (hide) w [s] od aktualnego czasu
void
TTranscripts::AddLine( std::string const &txt, float show, float hide, bool it ) {
    if( show == hide ) { return; } // komentarz jest ignorowany

    TTranscript transcript;
    transcript.asText = ExchangeCharInString( txt, '|', ' ' ); // NOTE: legacy transcript lines use | as new line mark
    transcript.fShowTime = Timer::GetTime() + show;
    transcript.fHideTime = Timer::GetTime() + hide;
    aQueuedLines.emplace_back( transcript );
}

// dodanie tekstów, długość dźwięku, czy istotne
void
TTranscripts::Add( std::string const &txt, bool background ) {
    if( true == txt.empty() ) { return; }

    std::string asciitext{ txt }; win1250_to_ascii( asciitext ); // TODO: launch relevant conversion table based on language
    cParser parser( asciitext );
    while( true == parser.getTokens( 3, false, "[]\n" ) ) {

        float begin, end;
        std::string transcript;
        parser
            >> begin
            >> end
            >> transcript;
        AddLine( transcript, 0.10 * begin, 0.12 * end, false );
    }
    // try to handle malformed(?) cases with no show/hide times
    std::string transcript; parser >> transcript;
    while( false == transcript.empty() ) {

        //        WriteLog( "Transcript text with no display/hide times: \"" + transcript + "\"" );
        AddLine( transcript, 0.0, 0.12 * transcript.size(), false );
        transcript = ""; parser >> transcript;
    }
}

// usuwanie niepotrzebnych (nie częściej niż 10 razy na sekundę)
void
TTranscripts::Update() {
    // We maintain two different lists: aQueuedLines for transcript lines that are scheduled to be shown, and aLines
    // for lines that are shown. In this loop, we check if the lines in aQueuedLines are ready to be shown, and if so,
    // move them to aLines.
    for (auto i = 0; i < aQueuedLines.size(); i++) {
        auto &transcript = aQueuedLines[i];
        
        if ( Timer::GetTime() >= transcript.fShowTime ) {
            transcript.bActive = true;
            transcript.fTimestamp = simulation::Time.to_string(); // Set to the time the line is shown, not when it was queued.
            aLines.emplace_back( transcript );
            aQueuedLines.erase( aQueuedLines.begin() + i );
        }
    }

    bool isAllLinesInactive = true;
    // Go through each line in aLines and check if each line is still active (the audio for it is still playing). We
    // start from the index of the last inactive line so that we don't process every inactive line.
    for (auto i = mLastCompleteIndex; i < aLines.size(); i++) {
        TTranscript &transcript = aLines[i];
        // If the line is past its hide time, mark it as inactive. Don't remove it so that we can still show it in the
        // transcript window.
        if ( Timer::GetTime() >= transcript.fHideTime ) {
            aLines[i].bActive = false;
        }
        // If there was an an active line in this batch, mark the batch as still active.
        else if ( true == transcript.bActive ) {
            isAllLinesInactive = false;
        }
    }
    // New lines are added in the order that they're shown in, but can go inactive at different times. This means that
    // it's possible for a later line to go inactive while a line before it is still active, for example doing a radio
    // check while a station announcement is playing. Thus, in the above loop, we can't go backwards in the list and
    // stop when we hit an inactive line, because there can still be active lines above it. Instead, we'll process it in
    // batches; if there's at least one active line, we'll keep processing all the lines until none of them are active
    // anymore. Then we save the index+1 of the last line in the list, so that the next time we go through the loop, it
    // starts from the newly-added lines rather than go through the entire list.
    if ( isAllLinesInactive ) {
        mLastCompleteIndex = aLines.size();
    }
}

bool
TTranscripts::HasActiveLines()  {
    return mLastCompleteIndex < aLines.size();
}

} // namespace ui
