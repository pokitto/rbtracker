#include "rbtrackerMain.h"
#include <wx/msgdlg.h>
#include <wx/wxprec.h>
#include <wx/filename.h>
#include <wx/textfile.h>
#include "synth.h"
#include "Utilities.h"


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
