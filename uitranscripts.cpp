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
    for ( size_t i = 0; i < aQueuedLines.size(); i++ ) {
        auto &transcript = aQueuedLines[i];

        if ( Timer::GetTime() >= transcript.fShowTime ) {
            transcript.bActive = true;
            transcript.fTimestamp = simulation::Time.to_string();
            aLines.emplace_back( transcript );
            aQueuedLines.erase( aQueuedLines.begin() + i );
        }
    }

    if (!HasActiveLines()) return;

    bool isAllLinesInactive = true;

    for (size_t i = mLastCompleteIndex; i < aLines.size(); i++) {
        TTranscript &transcript = aLines[i];

        if ( true == transcript.bActive ) {
            isAllLinesInactive = false;
        }
        if ( Timer::GetTime() >= transcript.fHideTime ) {
            aLines[i].bActive = false;
        }
    }

    if ( isAllLinesInactive ) {
        mLastCompleteIndex = aLines.size();
    }
}

bool
TTranscripts::HasActiveLines()  {
    return mLastCompleteIndex < aLines.size();
}

} // namespace ui
