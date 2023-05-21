
#pragma once

#include <deque>
#include <string>

namespace ui {

// klasa obsługująca linijkę napisu do dźwięku
struct TTranscript {

    float fShowTime; // czas pokazania
    float fHideTime; // czas ukrycia/usunięcia
    std::string fTimestamp; // Game time that the message was shown at.
    std::string asText; // tekst gotowy do wyświetlenia (usunięte znaczniki czasu)
    bool bItalic; // czy kursywa (dźwięk nieistotny dla prowadzącego)
    bool bShow = false; // Whether the transcript should be shown. Transcripts can be added before their show time.
    bool bActive = true; // Whether the transcript is scheduled to be shown, or is currently 
};

// klasa obsługująca napisy do dźwięków
class TTranscripts { 

public:
// constructors
    TTranscripts() = default;
// methods
    void AddLine( std::string const &txt, float show, float hide, bool it );
    // dodanie tekstów, długość dźwięku, czy istotne
    void Add( std::string const &txt, bool background = false );
    // usuwanie niepotrzebnych (ok. 10 razy na sekundę)
    void Update();
    bool HasActiveLines();
// members
    std::deque<TTranscript> aLines;

private:
// members
    std::vector <TTranscript> aQueuedLines;
    size_t mLastCompleteIndex { 0 };
};

extern TTranscripts Transcripts;

} // namespace ui