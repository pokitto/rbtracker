#include "rbtrackerMain.h"
#include <wx/msgdlg.h>
#include <wx/wxprec.h>
#include <wx/filename.h>
#include <wx/textfile.h>
#include "synth.h"
#include "Utilities.h"

wxString NoteNames[] = {
"B-0",  // 0 - NOTE_B0
"C-1",  // 1 - NOTE_C1
"C#1",  // 2 - NOTE_CS1
"D-1",  // 3 - NOTE_D1
"D#1",  // 4 - NOTE_DS1
"E-1",  // 5 - NOTE_E1
"F-1",  // 6 - NOTE_F1
"F#1",  // 7 - NOTE_FS1
"G-1",  // 8 - NOTE_G1
"G#1",  // 9 - NOTE_GS1
"A-1",  // 10 - NOTE_A1
"A#1",  // 11 - NOTE_AS1
"B-1",  // 12 - NOTE_B1
"C-2",  // 13 - NOTE_C2
"C#2",  // 14 - NOTE_CS2
"D-2",  // 15 - NOTE_D2
"D#2",  // 16 - NOTE_DS2
"E-2",  // 17 - NOTE_E2
"F-2",  // 18 - NOTE_F2
"F#2",  // 19 - NOTE_FS2
"G-2",  // 20 - NOTE_G2
"G#2",  // 21 - NOTE_GS2
"A-2",  // 22 - NOTE_A2
"A#2",  // 23 - NOTE_AS2
"B-2",  // 24 - NOTE_B2
"C-3",  // 25 - NOTE_C3
"C#3",  // 26 - NOTE_CS3
"D-3",  // 27 - NOTE_D3
"D#3",  // 28 - NOTE_DS3
"E-3",  // 29 - NOTE_E3
"F-3",  // 30 - NOTE_F3
"F#3",  // 31 - NOTE_FS3
"G-3",  // 32 - NOTE_G3
"G#3",  // 33 - NOTE_GS3
"A-3",  // 34 - NOTE_A3
"A#3",  // 35 - NOTE_AS3
"B-3",  // 36 - NOTE_B3
"C-4",  // 37 - NOTE_C4
"C#4",  // 38 - NOTE_CS4
"D-4",  // 39 - NOTE_D4
"D#4",  // 40 - NOTE_DS4
"E-4",  // 41 - NOTE_E4
"F-4",  // 42 - NOTE_F4
"F#4",  // 43 - NOTE_FS4
"G-4",  // 44 - NOTE_G4
"G#4",  // 45 - NOTE_GS4
"A-4",  // 46 - NOTE_A4
"A#4",  // 47 - NOTE_AS4
"B-4",  // 48 - NOTE_B4
"C-5",  // 49 - NOTE_C5
"C#5",  // 50 - NOTE_CS5
"D-5",  // 51 - NOTE_D5
"D#5",  // 52 - NOTE_DS5
"E-5",  // 53 - NOTE_E5
"F-5",  // 54 - NOTE_F5
"F#5",  // 55 - NOTE_FS5
"G-5",  // 56 - NOTE_G5
"G#5",  // 57 - NOTE_GS5
"A-5",  // 58 - NOTE_A5
"A#5",  // 59 - NOTE_AS5
"B-5",  // 60 - NOTE_B5
"C-6",  // 61 - NOTE_C6
"C#6",  // 62 - NOTE_CS6
"D-6",  // 63 - NOTE_D6
"D#6",  // 64 - NOTE_DS6
"E-6",  // 65 - NOTE_E6
"F-6",  // 66 - NOTE_F6
"F#6",  // 67 - NOTE_FS6
"G-6",  // 68 - NOTE_G6
"G#6",  // 69 - NOTE_GS6
"A-6",  // 70 - NOTE_A6
"A#6",  // 71 - NOTE_AS6
"B-6",  // 72 - NOTE_B6
"C-7",  // 73 - NOTE_C7
"C#7",  // 74 - NOTE_CS7
"D-7",  // 75 - NOTE_D7
"D#7",  // 76 - NOTE_DS7
"E-7",  // 77 - NOTE_E7
"F-7",  // 78 - NOTE_F7
"F#7",  // 79 - NOTE_FS7
"G-7",  // 80 - NOTE_G7
"G#7",  // 81 - NOTE_GS7
"A-7",  // 82 - NOTE_A7
"A#7",  // 83 - NOTE_AS7
"B-7",  // 84 - NOTE_B7
"C-8",  // 85 - NOTE_C8
"C#8",  // 86 - NOTE_CS8
"D-8",  // 87 - NOTE_D8
"D#8"  // 88 - NOTE_DS8
};

void rbtrackerFrame::copyToClipboard(int tc,int tr, int bc, int br)
{
    int destcol=0, destrow=0; // clipboard always begins at 0,0
    //Copy entries to clipboard
    for (int cols=tc; cols <=bc; cols++, destcol++)
    {
          for (int rows = tr; rows <= br; rows++, destrow++) {
          int note, instr, blockn;
          // select block according to the column pointed to at the moment
          if (cols == 0) blockn = Block1->GetValue();
          else if (cols == 1) blockn = Block2->GetValue();
          else blockn = Block3->GetValue();
          note = block[blockn].notenumber[rows];
          instr = block[blockn].instrument[rows];
          // copy to clipboard
          clipboard[destcol].notenumber[destrow]=note;
          clipboard[destcol].instrument[destrow]=instr;
          }
     }
}

void rbtrackerFrame::pasteFromClipboard(int tracknum,int trackpos)
{
    //Copy from clipboard to current location at tracknum, trackpos
    int sourcecol = 0, sourcerow = 0; // clipboard data always begins at 0,0

    for (int cols=tracknum; cols <=tracknum+clipwidth; cols++, sourcecol++)
    {
         for (int rows = trackpos; rows <= trackpos+clipheight; rows++, sourcerow++) {
         int note, instr, blockn;
         // get a cell of data from the clipboard
         note = clipboard[sourcecol].notenumber[sourcerow];
         instr = clipboard[sourcecol].instrument[sourcerow];
         // copy to active pattern
         if (cols == 0) blockn = Block1->GetValue();
         else if (cols == 1) blockn = Block2->GetValue();
         else blockn = Block3->GetValue();
         // paste only if within legal bounds
         if (cols < 3 && rows < PATTERNLENGTH) {
            block[blockn].notenumber[rows]=note;
            block[blockn].instrument[rows]=instr;
         }
         }
     }
    // Refresh the table
    readBlocksToAllTracks(sequencepos);
}

void rbtrackerFrame::transposeSelection(int tval)
{
    for (int i = 0; i<3; i++) {
        for (int j =0; j<PATTERNLENGTH; j++)
        {
            int notenum = clipboard[i].notenumber[j];
            int instr = clipboard[i].instrument[j]; // only transpose notes with active instruments !!!
            if (instr) {
                notenum += tval;
                if (notenum < 0) notenum=0; // prevent transposing past 0
                if (notenum > 88) notenum = 88; // prevent transposing past cincs table
                clipboard[i].notenumber[j] = notenum;
            }
        }
    }
}

void rbtrackerFrame::OnLoopToChange(wxSpinEvent& event)
{
    if (Loop->GetValue() > song.song_end ) Loop->SetValue(song.song_end);
    song.song_loop = Loop->GetValue();
}

void rbtrackerFrame::OnPositionChange(wxSpinEvent& event)
{
    sequencepos = Position->GetValue();
    Block1->SetValue(song.block_sequence[0][sequencepos]);
    Block2->SetValue(song.block_sequence[1][sequencepos]);
    Block3->SetValue(song.block_sequence[2][sequencepos]);
    readBlocksToAllTracks(sequencepos);
}

void rbtrackerFrame::OnBlock1Change(wxSpinEvent& event)
{
    uint8_t newblock = Block1->GetValue();
    song.block_sequence[0][sequencepos] = newblock;
    readBlockToTrack(0,newblock);
}

void rbtrackerFrame::OnBlock2Change(wxSpinEvent& event)
{
    uint8_t newblock = Block2->GetValue();
    song.block_sequence[1][sequencepos] = newblock;
    readBlockToTrack(1,newblock);
}

void rbtrackerFrame::OnBlock3Change(wxSpinEvent& event)
{
    uint8_t newblock = Block3->GetValue();
    song.block_sequence[2][sequencepos] = newblock;
    readBlockToTrack(2,newblock);
}


void rbtrackerFrame::OnPatternChange(wxSpinEvent& event)
{
    //if (NumPatterns->GetValue()<=Pattern->GetValue()) NumPatterns->SetValue(Pattern->GetValue()+1);
    //readPatternToTable(Pattern->GetValue());
}

void rbtrackerFrame::OnSongLengthChange(wxSpinEvent& event)
{
    // nothing needs to be done here, its just a shorter song now
   song.song_end = SongLength->GetValue(); // set the song data struct correct as well
   if (song.song_loop > song.song_end ) song.song_loop = song.song_end; // avoid errors
}

void rbtrackerFrame::readBlocksToAllTracks(uint8_t seqpos)
{
    readBlockToTrack(0,song.block_sequence[0][seqpos]); // show new blocks
    readBlockToTrack(1,song.block_sequence[1][seqpos]); // show new blocks
    readBlockToTrack(2,song.block_sequence[2][seqpos]); // show new blocks
}


void rbtrackerFrame::readBlockToTrack(uint8_t tr, uint8_t bl)
{
        wxString str; int val,inst;
        wxString iText;

        for (uint8_t j=0; j<PATTERNLENGTH;j++)
            {
            iText = "";
            val = block[bl].notenumber[j];
            inst = block[bl].instrument[j];
            if (val!=255) {
                iText.Append(NoteNames[val]);
                iText.Append(" ");
                if (inst<10) iText.Append(wxString::Format("0%d",inst));
                else iText.Append(wxString::Format("%d",inst));
                iText.Append(" ");
                if (val<10) iText.Append(wxString::Format("0%d",val));
                else iText.Append(wxString::Format("%d",val));
            } else iText = "--- 00 --";
            Grid->SetCellValue(j,tr,iText);
            }
}


void rbtrackerFrame::readPatternToTable(uint8_t i)
{
            wxString str; int val,inst,loc=0;
            wxString iText;


            for (uint8_t k=0; k<3; k++) {
                for (uint16_t j=i*PATTERNLENGTH; j<(i+1)*PATTERNLENGTH;j++)
                {
                iText = "";
                //val = track[k].notenumber[j];
                //inst = track[k].instrument[j];
                if (val!=255) {
                    iText.Append(NoteNames[val]);
                    iText.Append(" ");
                    if (inst<10) iText.Append(wxString::Format("0%d",inst));
                    else iText.Append(wxString::Format("%d",inst));
                    iText.Append(" ");
                    if (val<10) iText.Append(wxString::Format("0%d",val));
                    else iText.Append(wxString::Format("%d",val));
                } else iText = "--- 00 --";
                Grid->SetCellValue(loc,k,iText);
                loc++;
                }
                loc=0;
            }

}
