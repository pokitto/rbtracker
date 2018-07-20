#include "rbtrackerMain.h"
#include "utilities.h"
#include "Synth.h"
#include "notes.h"

uint16_t freqs[] = {
31,  // 0 - NOTE_B0
33,  // 1 - NOTE_C1
35,  // 2 - NOTE_CS1
37,  // 3 - NOTE_D1
39,  // 4 - NOTE_DS1
41,  // 5 - NOTE_E1
44,  // 6 - NOTE_F1
46,  // 7 - NOTE_FS1
49,  // 8 - NOTE_G1
52,  // 9 - NOTE_GS1
55,  // 10 - NOTE_A1
58,  // 11 - NOTE_AS1
62,  // 12 - NOTE_B1
65,  // 13 - NOTE_C2
69,  // 14 - NOTE_CS2
73,  // 15 - NOTE_D2
78,  // 16 - NOTE_DS2
82,  // 17 - NOTE_E2
87,  // 18 - NOTE_F2
93,  // 19 - NOTE_FS2
98,  // 20 - NOTE_G2
104,  // 21 - NOTE_GS2
110,  // 22 - NOTE_A2
117,  // 23 - NOTE_AS2
123,  // 24 - NOTE_B2
131,  // 25 - NOTE_C3
139,  // 26 - NOTE_CS3
147,  // 27 - NOTE_D3
156,  // 28 - NOTE_DS3
165,  // 29 - NOTE_E3
175,  // 30 - NOTE_F3
185,  // 31 - NOTE_FS3
196,  // 32 - NOTE_G3
208,  // 33 - NOTE_GS3
220,  // 34 - NOTE_A3
233,  // 35 - NOTE_AS3
247,  // 36 - NOTE_B3
262,  // 37 - NOTE_C4
277,  // 38 - NOTE_CS4
294,  // 39 - NOTE_D4
311,  // 40 - NOTE_DS4
330,  // 41 - NOTE_E4
349,  // 42 - NOTE_F4
370,  // 43 - NOTE_FS4
392,  // 44 - NOTE_G4
415,  // 45 - NOTE_GS4
440,  // 46 - NOTE_A4
466,  // 47 - NOTE_AS4
494,  // 48 - NOTE_B4
523,  // 49 - NOTE_C5
554,  // 50 - NOTE_CS5
587,  // 51 - NOTE_D5
622,  // 52 - NOTE_DS5
659,  // 53 - NOTE_E5
698,  // 54 - NOTE_F5
740,  // 55 - NOTE_FS5
784,  // 56 - NOTE_G5
831,  // 57 - NOTE_GS5
880,  // 58 - NOTE_A5
932,  // 59 - NOTE_AS5
988,  // 60 - NOTE_B5
1047,  // 61 - NOTE_C6
1109,  // 62 - NOTE_CS6
1175,  // 63 - NOTE_D6
1245,  // 64 - NOTE_DS6
1319,  // 65 - NOTE_E6
1397,  // 66 - NOTE_F6
1480,  // 67 - NOTE_FS6
1568,  // 68 - NOTE_G6
1661,  // 69 - NOTE_GS6
1760,  // 70 - NOTE_A6
1865,  // 71 - NOTE_AS6
1976,  // 72 - NOTE_B6
2093,  // 73 - NOTE_C7
2217,  // 74 - NOTE_CS7
2349,  // 75 - NOTE_D7
2489,  // 76 - NOTE_DS7
2637,  // 77 - NOTE_E7
2794,  // 78 - NOTE_F7
2960,  // 79 - NOTE_FS7
3136,  // 80 - NOTE_G7
3322,  // 81 - NOTE_GS7
3520,  // 82 - NOTE_A7
3729,  // 83 - NOTE_AS7
3951,  // 84 - NOTE_B7
4186,  // 85 - NOTE_C8
4435,  // 86 - NOTE_CS8
4699,  // 87 - NOTE_D8
4978  // 88 - NOTE_DS8
};

uint8_t KeyToNumber(wxString iText, int oct)
{
   oct = (oct-1)*12; // shift index by octave

   switch (iText[0].GetValue()) {
    case 'X':
        break;
    case 'S':
        oct -=1; break;
    case 'Z':
        oct -=2; break;
    case 'A':
        oct -=3; break;
    case 'C':
        oct +=1; break;
    case 'F':
        oct +=2; break;
    case 'V':
        oct +=3; break;
    case 'G':
        oct +=4; break;
    case 'B':
        oct +=5; break;
    case 'N':
        oct +=6; break;
    case 'J':
        oct +=7; break;
    case 'M':
        oct +=8; break;
    case 'K':
        oct +=9; break;
    case ',':
        oct +=10; break;
    case 'L':
        oct +=11; break;
    case '.':
        oct +=12; break;
    case 'Q':
        oct +=13; break;
    case '2':
        oct +=14; break;
    case 'W':
        oct +=15; break;
    case '3':
        oct +=16; break;
    case 'E':
        oct +=17; break;
    case 'R':
        oct +=18; break;
    case '5':
        oct +=19; break;
    case 'T':
        oct +=20; break;
    case '6':
        oct +=21; break;
    case 'Y':
        oct +=22; break;
    case '7':
        oct +=23; break;
    case 'U':
        oct +=24; break;
    case 'I':
        oct +=25; break;
    case '9':
        oct +=26; break;
    case 'O':
        oct +=27; break;
    case '0':
        oct +=28; break;
    case 'P':
        oct +=29; break;
    case '+':
        oct +=30; break;
    case '�':
        oct +=31; break;
    default:
        return 255; //error
    }

    if (oct > 88) return 255; // error
    return oct; // valid note index
}

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
    case '�':
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

    else if (iText == "F#1") freq = NOTE_FS1;
    else if (iText == "F#2") freq = NOTE_FS2;
    else if (iText == "F#3") freq = NOTE_FS3;
    else if (iText == "F#4") freq = NOTE_FS4;
    else if (iText == "F#5") freq = NOTE_FS5;
    else if (iText == "F#6") freq = NOTE_FS6;
    else if (iText == "F#7") freq = NOTE_FS7;

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

