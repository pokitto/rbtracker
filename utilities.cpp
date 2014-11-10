#include "rbtrackerMain.h"
#include "utilities.h"
#include "notes.h"

wxString KeyToNote(wxString iText, int oct)
{
    switch (iText[0].GetValue()) {
    case 'X':
        iText = "B-"; oct-- ; break;
    case 'S':
        iText = "A#"; oct-- ; break;
    case 'Z':
        iText = "A-"; oct-- ; break;
    case 'A':
        iText = "G#"; oct-- ; break;
    case 'C':
        iText = "C-"; break;
    case 'F':
        iText = "C#"; break;
    case 'V':
        iText = "D-"; break;
    case 'G':
        iText = "D#"; break;
    case 'B':
        iText = "E-"; break;
    case 'N':
        iText = "F-"; break;
    case 'J':
        iText = "F#"; break;
    case 'M':
        iText = "G-"; break;
    case 'K':
        iText = "G#"; break;
    case ',':
        iText = "A-"; break;
    case 'L':
        iText = "A#"; break;
    case '.':
        iText = "B-"; break;
    case 'Q':
        iText = "C-"; oct++; break;
    case '2':
        iText = "C#"; oct++; break;
    case 'W':
        iText = "D-"; oct++; break;
    case '3':
        iText = "D#"; oct++; break;
    case 'E':
        iText = "E-"; oct++; break;
    case 'R':
        iText = "F-"; oct++; break;
    case '5':
        iText = "F#"; oct++; break;
    case 'T':
        iText = "G-"; oct++; break;
    case '6':
        iText = "G#"; oct++; break;
    case 'Y':
        iText = "A-"; oct++; break;
    case '7':
        iText = "A#"; oct++; break;
    case 'U':
        iText = "B-"; oct++; break;
    case 'I':
        iText = "C-"; oct++; oct++; break;
    case '9':
        iText = "C#"; oct++; oct++; break;
    case 'O':
        iText = "D-"; oct++; oct++; break;
    case '0':
        iText = "D#"; oct++; oct++; break;
    case 'P':
        iText = "E-"; oct++; oct++; break;
    case '+':
        iText = "F-"; oct++; oct++; break;
    case 'Å':
        iText = "G-"; oct++; oct++; break;
    default:
        iText ="";
    }
    if (iText != "") iText << oct;
    return iText;
}

uint16_t NoteToFreq(wxString iText) {
    uint16_t freq;
    if (iText == "C-1") freq = NOTE_C1;
    else if (iText == "C-2") freq = NOTE_C2;
    else if (iText == "C-3") freq = NOTE_C3;
    else if (iText == "C-4") freq = NOTE_C4;
    else if (iText == "C-5") freq = NOTE_C5;
    else if (iText == "C-6") freq = NOTE_C6;
    else if (iText == "C-7") freq = NOTE_C7;

    else if (iText == "C#1") freq = NOTE_CS1;
    else if (iText == "C#2") freq = NOTE_CS2;
    else if (iText == "C#3") freq = NOTE_CS3;
    else if (iText == "C#4") freq = NOTE_CS4;
    else if (iText == "C#5") freq = NOTE_CS5;
    else if (iText == "C#6") freq = NOTE_CS6;
    else if (iText == "C#7") freq = NOTE_CS7;

    else if (iText == "D-1") freq = NOTE_D1;
    else if (iText == "D-2") freq = NOTE_D2;
    else if (iText == "D-3") freq = NOTE_D3;
    else if (iText == "D-4") freq = NOTE_D4;
    else if (iText == "D-5") freq = NOTE_D5;
    else if (iText == "D-6") freq = NOTE_D6;
    else if (iText == "D-7") freq = NOTE_D7;

    else if (iText == "D#1") freq = NOTE_DS1;
    else if (iText == "D#2") freq = NOTE_DS2;
    else if (iText == "D#3") freq = NOTE_DS3;
    else if (iText == "D#4") freq = NOTE_DS4;
    else if (iText == "D#5") freq = NOTE_DS5;
    else if (iText == "D#6") freq = NOTE_DS6;
    else if (iText == "D#7") freq = NOTE_DS7;

    else if (iText == "E-1") freq = NOTE_E1;
    else if (iText == "E-2") freq = NOTE_E2;
    else if (iText == "E-3") freq = NOTE_E3;
    else if (iText == "E-4") freq = NOTE_E4;
    else if (iText == "E-5") freq = NOTE_E5;
    else if (iText == "E-6") freq = NOTE_E6;
    else if (iText == "E-7") freq = NOTE_E7;

    else if (iText == "F-1") freq = NOTE_F1;
    else if (iText == "F-2") freq = NOTE_F2;
    else if (iText == "F-3") freq = NOTE_F3;
    else if (iText == "F-4") freq = NOTE_F4;
    else if (iText == "F-5") freq = NOTE_F5;
    else if (iText == "F-6") freq = NOTE_F6;
    else if (iText == "F-7") freq = NOTE_F7;

    else if (iText == "G-1") freq = NOTE_G1;
    else if (iText == "G-2") freq = NOTE_G2;
    else if (iText == "G-3") freq = NOTE_G3;
    else if (iText == "G-4") freq = NOTE_G4;
    else if (iText == "G-5") freq = NOTE_G5;
    else if (iText == "G-6") freq = NOTE_G6;
    else if (iText == "G-7") freq = NOTE_G7;

    else if (iText == "G#1") freq = NOTE_GS1;
    else if (iText == "G#2") freq = NOTE_GS2;
    else if (iText == "G#3") freq = NOTE_GS3;
    else if (iText == "G#4") freq = NOTE_GS4;
    else if (iText == "G#5") freq = NOTE_GS5;
    else if (iText == "G#6") freq = NOTE_GS6;
    else if (iText == "G#7") freq = NOTE_GS7;

    else if (iText == "A-1") freq = NOTE_A1;
    else if (iText == "A-2") freq = NOTE_A2;
    else if (iText == "A-3") freq = NOTE_A3;
    else if (iText == "A-4") freq = NOTE_A4;
    else if (iText == "A-5") freq = NOTE_A5;
    else if (iText == "A-6") freq = NOTE_A6;
    else if (iText == "A-7") freq = NOTE_A7;

    else if (iText == "A#1") freq = NOTE_AS1;
    else if (iText == "A#2") freq = NOTE_AS2;
    else if (iText == "A#3") freq = NOTE_AS3;
    else if (iText == "A#4") freq = NOTE_AS4;
    else if (iText == "A#5") freq = NOTE_AS5;
    else if (iText == "A#6") freq = NOTE_AS6;
    else if (iText == "A#7") freq = NOTE_AS7;

    else if (iText == "B-1") freq = NOTE_B1;
    else if (iText == "B-2") freq = NOTE_B2;
    else if (iText == "B-3") freq = NOTE_B3;
    else if (iText == "B-4") freq = NOTE_B4;
    else if (iText == "B-5") freq = NOTE_B5;
    else if (iText == "B-6") freq = NOTE_B6;
    else if (iText == "B-7") freq = NOTE_B7;

    return freq;
}
