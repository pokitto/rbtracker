#ifndef UTILITIES_H
#define UTILITIES_H

#include  <wx/string.h>

extern wxString KeyToNote(wxString, int);
extern uint8_t KeyToNumber(wxString, int);
extern uint16_t NoteToFreq(wxString);
extern uint16_t freqs[];
extern uint16_t cincs[];
extern wxString NoteNames[];

#endif // UTILITIES_H
