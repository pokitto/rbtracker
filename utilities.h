#ifndef UTILITIES_H
#define UTILITIES_H

#include  <wx/string.h>

extern wxString KeyToNote(wxString, int);
extern uint8_t KeyToNumber(wxString, int);
extern uint16_t NoteToFreq(wxString);

#endif // UTILITIES_H
