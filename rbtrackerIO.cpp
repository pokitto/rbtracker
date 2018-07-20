#include "rbtrackerMain.h"
#include <wx/msgdlg.h>
#include <wx/wxprec.h>
#include <wx/filename.h>
#include <wx/textfile.h>
#include <wx/grid.h>
#include "Synth.h"
#include "utilities.h"

void rbtrackerFrame::OnExportCSongClick(wxCommandEvent& event)
{
    wxString defname;
    defname = "Song";
    defname.Append(wxT(".c"));
    ExportPatchDialog->SetFilename(defname);
    int dlg=ExportPatchDialog->ShowModal();

    if(dlg==wxID_OK)
    {
        defname = ExportPatchDialog->GetPath();
        wxTextFile file(defname);
        if(file.Exists()) file.Open(defname); else file.Create(defname);

        file.Clear();
        wxString temp;
        file.AddLine( (wxString)"// Rboy Tracker song .c export file");
        temp << "// Rbtracker version :" << RBTRACKER_VERSION;
        file.AddLine(temp);
        file.AddLine( (wxString)"#include <Arduino.h>");
        file.AddLine( (wxString)"#include <songs.h>");
        file.AddLine( (wxString)"");
        file.AddLine( (wxString)"// Song data");
        temp = "const prog_uchar ";
        temp << "Song[";
        temp << 5 + 3 * (SongLength->GetValue()+1) + 64 * NumBlocks->GetValue();
        temp << "] PROGMEM = {";
        file.AddLine(temp);
        file.AddLine(wxString::Format("%d, // Song length",SongLength->GetValue()));
        file.AddLine(wxString::Format("%d, // Loop to",LoopTo->GetValue()));
        file.AddLine(wxString::Format("%d, // Number of blocks used",NumBlocks->GetValue()));
        file.AddLine(wxString::Format("%d, // Number of patches used",NumInstruments->GetValue()));
        file.AddLine(wxString::Format("%d, // BPM",Tempo->GetValue()));

        /** Write Sequence to file **/
        file.AddLine( (wxString)"// Sequence");
        for (int i=0; i <= SongLength->GetValue(); i++) {
            temp = "";
            temp.Append(wxString::Format("%d,%d,%d,",song.block_sequence[0][i],song.block_sequence[1][i],song.block_sequence[2][i]));
            temp.Append(wxString::Format("// Pattern %d ",i));
            file.AddLine(temp);
        }
        /** Write Blocks to file **/
        file.AddLine( (wxString)"// Block data");
        for (int i=0; i<NumBlocks->GetValue(); i++)
            {
            temp="";
            for (int j=0; j < PATTERNLENGTH; j++) {
                temp.Append(wxString::Format("%d,%d,",block[i].notenumber[j],block[i].instrument[j]));
                if (j == 15 || j == 31 || j == 47 || j==63) {
                        temp.Append(wxString::Format("// Block %d phrase %d",i,j/15));
                        file.AddLine(temp);
                        temp="";
                        }
                }
            file.AddLine( (wxString)"//");
            }
        file.AddLine( (wxString)"}; // end of song data");

        /** Write Patches to file **/
        //exportPatchToFile(file);

        file.AddLine( (wxString)"");
        file.AddLine( (wxString)"// Patches data");

        temp = "const prog_uchar ";
        temp << "Patches" << "[";
        temp << 13 * (NumInstruments->GetValue());
        temp << "] PROGMEM = {";
        file.AddLine(temp);

        for (int i=1; i<=NumInstruments->GetValue(); i++) {
            getPatch(i);
            temp = "// Patch " ;
            temp << i;
            file.AddLine(temp);
            exportPatchToFile(file);
        }

        file.AddLine( (wxString)"}; // end of patches data");

        wxRemoveFile(defname);
        file.Create(defname);

        file.Write();
        file.Close();
    }
}




void rbtrackerFrame::exportPatchToFile(wxTextFile &file)
{
        file.AddLine(wxString::Format("%d, // Waveform ",Wave->GetSelection()));
        file.AddLine(wxString::Format("%d, // Volume",InstVol->GetValue()));
        file.AddLine(wxString::Format("0x%x, // Pitch bend rate UPPER BYTE",(uint8_t)(BendRate->GetValue()>>8)));
        file.AddLine(wxString::Format("0x%x, // Pitch bend rate LOWER BYTE",(uint8_t)(BendRate->GetValue())));
        file.AddLine(wxString::Format("0x%x, // Pitch bend max UPPER BYTE",(uint8_t)(MaxBend->GetValue()>>8)));
        file.AddLine(wxString::Format("0x%x, // Pitch bend max LOWER BYTE",(uint8_t)(MaxBend->GetValue())));
        file.AddLine(wxString::Format("%d, // Transpose",VibRate->GetValue()));
        file.AddLine(wxString::Format("%d, // Arp mode ", ArpMode->GetSelection()));
        uint8_t options=0;
        wxString optstring;
        options = (ADSR->IsChecked()) << OPT_ADSR ;
        if (ADSR->IsChecked()) optstring << "ADSR on ";
        else optstring << "ADSR off ";
        options |= (Loop->IsChecked()) << OPT_LOOP ;
        if (Loop->IsChecked()) optstring << "LOOP on ";
        else optstring << "LOOP off ";
        options |= (Echo->IsChecked()) << OPT_ECHO ;
        if (Echo->IsChecked()) optstring << "ECHO on ";
        else optstring << "ECHO off ";
        options |= (Overdrive->IsChecked()) << OPT_OVERDRIVE ;
        if (Overdrive->IsChecked()) optstring << "OVERDRIVE on ";
        else optstring << "OVERDRIVE off ";
        options |= (Kick->IsChecked()) << OPT_NORMALIZE ;
        if (Kick->IsChecked()) optstring << "NORMALIZE on ";
        else optstring << "NORMALIZE off ";
        file.AddLine(wxString::Format("%d, // Options ", options) << optstring);
        file.AddLine(wxString::Format("%d, // Attack ", Attack->GetValue()));
        file.AddLine(wxString::Format("%d, // Decay", Decay->GetValue()));
        file.AddLine(wxString::Format("%d, // Sustain", Sustain->GetValue()));
        file.AddLine(wxString::Format("%d, // Release", Release->GetValue()));
}

void rbtrackerFrame::instrumentsToPatches()
{
   //make sure Synth song structure instruments match the wxwidgets values
   for (int i=1; i<=15; i++) {
                    Patch->SetValue(i);
                    setPatch(i);
                    //getPatch(i);
  }
}

void rbtrackerFrame::blocksetsToBlocks()
{
   //make sure Synth song blocks match the wxwidgets values
   for (int i=0; i<=10; i++) {
                    Position->SetValue(i);
                    song.block_sequence[0][i]=Block1->GetValue();
                    song.block_sequence[1][i]=Block2->GetValue();
                    song.block_sequence[2][i]=Block3->GetValue();
  }
}


void rbtrackerFrame::OnSaveSongBtnClick(wxCommandEvent& event)
{
    wxString defname, str;
    int dlg=SaveSongDialog->ShowModal();

    if(dlg==wxID_OK)
    {
        defname = SaveSongDialog->GetPath();
        wxTextFile file(defname);
        if(file.Exists()) file.Open(defname); else file.Create(defname);

        file.Clear();
        str << RBTRACKER_VERSION;
        file.AddLine( (wxString)"Rboy Tracker song file");
        file.AddLine(str);
        file.AddLine(wxString::Format("BPM=%d",Tempo->GetValue()));
        file.AddLine(wxString::Format("Last pattern=%d",SongLength->GetValue()));
        file.AddLine(wxString::Format("Loop to=%d",LoopTo->GetValue()));
        file.AddLine(wxString::Format("Patches=%d",NumInstruments->GetValue()));

        /** Write Sequence to file **/

        str="";
        for (int i=0; i <= SongLength->GetValue(); i++) {
            str << "Block sequence " << i << " ";
            str.Append(wxString::Format(",%d,%d,%d",song.block_sequence[0][i],song.block_sequence[1][i],song.block_sequence[2][i]));
            file.AddLine(str);
            str="";
        }

        writeBlocksToFile(file);

        for (int i=1; i<=NumInstruments->GetValue(); i++) {
            getPatch(i);
            file.AddLine(InstName->GetValue());
            writePatchToFile(file);
        }

        wxRemoveFile(defname);
        file.Create(defname);

        file.Write();
        file.Close();
    }
}

void rbtrackerFrame::OnLoadSongBtnClick(wxCommandEvent& event)
{
        wxString defname; int numinst=1; int numpat=1;
        int dlg=LoadSongDialog->ShowModal();
        if (dlg == wxID_OK)
        {
            defname = LoadSongDialog->GetPath();
            wxTextFile file(defname);
            if (file.Open()) {
                wxString str;
                str = file.GetFirstLine(); // vanity text only
                str = file.GetFirstLine(); // version number
                str = file.GetNextLine();
                str = file.GetNextLine();

                Tempo->SetValue(wxAtoi(str.AfterLast((wxUniChar)'=')));
                song.song_bpm = Tempo->GetValue();

                str = file.GetNextLine();
                numpat = wxAtoi(str.AfterLast((wxUniChar)'='));
                SongLength->SetValue(numpat);
                song.song_end = numpat;

                str = file.GetNextLine();
                numpat = wxAtoi(str.AfterLast((wxUniChar)'='));
                LoopTo->SetValue(numpat);
                song.song_loop = numpat;

                str = file.GetNextLine();
                numinst = wxAtoi(str.AfterLast((wxUniChar)'='));
                NumInstruments->SetValue(numinst);
                song.num_patches = numinst;

                /** Read Block Sequence from file **/

                str="";
                for (int i=0; i <= SongLength->GetValue(); i++) {
                    int val;
                    str = file.GetNextLine(); //
                    val = wxAtoi(str.AfterLast((wxUniChar)','));
                    song.block_sequence[2][i]=val;
                    str = str.BeforeLast((wxUniChar)','); //chop 1
                    val = wxAtoi(str.AfterLast((wxUniChar)','));
                    song.block_sequence[1][i]=val;
                    str = str.BeforeLast((wxUniChar)','); //chop 2
                    val = wxAtoi(str.AfterLast((wxUniChar)','));
                    song.block_sequence[0][i]=val;
                }

                Block1->SetValue(song.block_sequence[0][0]);
                Block2->SetValue(song.block_sequence[1][0]);
                Block3->SetValue(song.block_sequence[2][0]);

                readBlocksFromFile(file);

                // Read instruments
                for (int i=1; i<=numinst; i++) {
                    Patch->SetValue(i);
                    readPatchFromFile(file);
                    iNames[i].clear();
                    iNames[i].Append(InstName->GetValue()); //= InstName->GetValue();
                    setPatch(i);
                    getPatch(i);
                }
                file.Close();
            }

        }
}

void rbtrackerFrame::OnSavePatchBtnClick(wxCommandEvent& event)
{
    wxString defname;
    defname = InstName->GetValue();
    defname.Append(wxT(".rbp"));
    SavePatchDialog->SetFilename(defname);
    int dlg=SavePatchDialog->ShowModal();

    if(dlg==wxID_OK)
    {
        defname = SavePatchDialog->GetPath();
        wxTextFile file(defname);
        if(file.Exists()) file.Open(defname); else file.Create(defname);

        file.Clear();
        file.AddLine( (wxString)"Rboy Tracker patch file");
        file.AddLine(InstName->GetValue());
        writePatchToFile(file);
        wxRemoveFile(defname);
        file.Create(defname);

        file.Write();
        file.Close();
    }
}

void rbtrackerFrame::OnLoadPatchBtnClick(wxCommandEvent& event)
{
        wxString defname;
        defname = InstName->GetValue();
        defname.Append(wxT(".rbp"));
        LoadPatchDialog->SetFilename(defname);
        int dlg=LoadPatchDialog->ShowModal();
        if (dlg == wxID_OK)
        {
            defname = LoadPatchDialog->GetPath();
            wxTextFile file(defname);
            if (file.Open()) {
                wxString str;
                str = file.GetFirstLine();
                readPatchFromFile(file);
                setPatch(Patch->GetValue());
                file.Close();
            }

        }
}

void rbtrackerFrame::writePatchToFile(wxTextFile &file)
{
        file.AddLine(wxString::Format("Waveform=%d",Wave->GetSelection()));
        file.AddLine(wxString::Format("Volume=%d",InstVol->GetValue()));
        file.AddLine(wxString::Format("Pitch bend rate=%d",BendRate->GetValue()));
        file.AddLine(wxString::Format("Pitch bend max=%d",MaxBend->GetValue()));
        file.AddLine(wxString::Format("Vibrato rate=%d",VibRate->GetValue()));
        file.AddLine(wxString::Format("Arpeggio mode=%d", ArpMode->GetSelection()));
        file.AddLine(wxString::Format("ADSR=%d", ADSR->IsChecked()));
        file.AddLine(wxString::Format("Attack=%d", Attack->GetValue()));
        file.AddLine(wxString::Format("Decay=%d", Decay->GetValue()));
        file.AddLine(wxString::Format("Sustain=%d", Sustain->GetValue()));
        file.AddLine(wxString::Format("Release=%d", Release->GetValue()));
        file.AddLine(wxString::Format("Loop=%d", Loop->IsChecked()));
        file.AddLine(wxString::Format("Echo=%d", Echo->IsChecked()));
        file.AddLine(wxString::Format("Overdrive=%d", Overdrive->IsChecked()));
        file.AddLine(wxString::Format("Drum kick=%d", Kick->IsChecked()));
}


void rbtrackerFrame::readPatchFromFile(wxTextFile &file)
{
        wxString str;
        str = file.GetNextLine();
        InstName->SetValue(str);
        str = file.GetNextLine(); // wave type
        Wave->SetSelection(wxAtoi(str.AfterLast((wxUniChar)'=')));
        str = file.GetNextLine(); // instrument volume
        InstVol->SetValue(wxAtoi(str.AfterLast((wxUniChar)'=')));
        str = file.GetNextLine(); // pitch bend rate
        BendRate->SetValue(wxAtoi(str.AfterLast((wxUniChar)'=')));
        str = file.GetNextLine(); // pitch bend max
        MaxBend->SetValue(wxAtoi(str.AfterLast((wxUniChar)'=')));
        str = file.GetNextLine(); // vibrato rate
        VibRate->SetValue(wxAtoi(str.AfterLast((wxUniChar)'=')));
        str = file.GetNextLine(); // Arpeggio mode
        ArpMode->SetSelection(wxAtoi(str.AfterLast((wxUniChar)'=')));
        str = file.GetNextLine(); // ADSR toggle
        ADSR->SetValue(wxAtoi(str.AfterLast((wxUniChar)'=')));
        str = file.GetNextLine(); // Attack
        Attack->SetValue(wxAtoi(str.AfterLast((wxUniChar)'=')));
        str = file.GetNextLine(); // Decay
        Decay->SetValue(wxAtoi(str.AfterLast((wxUniChar)'=')));
        str = file.GetNextLine(); // Sustain
        Sustain->SetValue(wxAtoi(str.AfterLast((wxUniChar)'=')));
        str = file.GetNextLine(); // Release
        Release->SetValue(wxAtoi(str.AfterLast((wxUniChar)'=')));
        str = file.GetNextLine(); // Loop toggle
        Loop->SetValue(wxAtoi(str.AfterLast((wxUniChar)'=')));
        str = file.GetNextLine(); // Echo toggle
        Echo->SetValue(wxAtoi(str.AfterLast((wxUniChar)'=')));
        str = file.GetNextLine(); // Overdrive toggle
        Overdrive->SetValue(wxAtoi(str.AfterLast((wxUniChar)'=')));
        str = file.GetNextLine(); // Drum kick toggle
        Kick->SetValue(wxAtoi(str.AfterLast((wxUniChar)'=')));
}

void rbtrackerFrame::writePatternToFile(wxTextFile &file)
{
        for (int i=0; i<64; i++)
            {
            wxString str;
            //str.Append(wxString::Format("%d,%d,",track[0].notenumber[i],track[0].instrument[i]));
            //str.Append(wxString::Format("%d,%d,",track[1].notenumber[i],track[1].instrument[i]));
            //str.Append(wxString::Format("%d,%d ",track[2].notenumber[i],track[2].instrument[i]));

            file.AddLine(str);
            }
}

void rbtrackerFrame::writeBlocksToFile(wxTextFile &file)
{
        for (int i=0; i<MAXBLOCKS; i++)
            {
            for (int j=0; j < PATTERNLENGTH; j++) {
                wxString str;
                str << "Block " << i << " row " << j << " ";
                str.Append(wxString::Format(",%d,%d",block[i].notenumber[j],block[i].instrument[j]));
                file.AddLine(str);
                }
            }
}

void rbtrackerFrame::readBlocksFromFile(wxTextFile &file)
{
    for (int i=0; i<MAXBLOCKS; i++)
            {
            for (int j=0; j<PATTERNLENGTH; j++)
            {
                    wxString str; int val,inst;
                    wxString iText;
                    str = file.GetNextLine();

                    inst = wxAtoi(str.AfterLast((wxUniChar)','));
                    block[i].instrument[j]=(uint8_t)inst;
                    str = str.BeforeLast((wxUniChar)','); //chop 1
                    val = wxAtoi(str.AfterLast((wxUniChar)','));
                    block[i].notenumber[j]=(uint8_t)val;
                    str = str.BeforeLast((wxUniChar)','); //chop 2
            }
        }
    sequencepos=0;
    readBlocksToAllTracks(sequencepos); // refresh display
}


void rbtrackerFrame::readPatternFromFile(wxTextFile &file)
{
    for (int i=0; i<64; i++)
            {
            wxString str; int val,inst;
            wxString iText;
            str = file.GetNextLine();

            inst = wxAtoi(str.AfterLast((wxUniChar)','));
            str = str.BeforeLast((wxUniChar)','); //chop 1
            val = wxAtoi(str.AfterLast((wxUniChar)','));
            str = str.BeforeLast((wxUniChar)','); //chop 2

            iText = "";
            if (val!=255) {
                    if (val>88) {
                        while(1){
                            iText="";
                        }; //error!
                    }
                    iText.Append(NoteNames[val]);
                    iText.Append(" ");
                    if (inst<10) iText.Append(wxString::Format("0%d",inst));
                    else iText.Append(wxString::Format("%d",inst));
                    iText.Append(" ");
                    if (val<10) iText.Append(wxString::Format("0%d",val));
                    else iText.Append(wxString::Format("%d",val));
            } else iText = "--- 00 --";

            Grid->SetCellValue(i,2,iText);

            inst = wxAtoi(str.AfterLast((wxUniChar)','));
            str = str.BeforeLast((wxUniChar)','); //chop 3
            val = wxAtoi(str.AfterLast((wxUniChar)','));
            str = str.BeforeLast((wxUniChar)','); //chop 4

            iText = "";
            if (val!=255) {
                    iText.Append(NoteNames[val]);
                    iText.Append(" ");
                    if (inst<10) iText.Append(wxString::Format("0%d",inst));
                    else iText.Append(wxString::Format("%d",inst));
                    iText.Append(" ");
                    if (val<10) iText.Append(wxString::Format("0%d",val));
                    else iText.Append(wxString::Format("%d",val));
            } else iText = "--- 00 --";

            Grid->SetCellValue(i,1,iText);

            inst = wxAtoi(str.AfterLast((wxUniChar)','));
            str = str.BeforeLast((wxUniChar)','); //chop 5
            val = wxAtoi(str);

            iText = "";
            if (val!=255) {
                    iText.Append(NoteNames[val]);
                    iText.Append(" ");
                    if (inst<10) iText.Append(wxString::Format("0%d",inst));
                    else iText.Append(wxString::Format("%d",inst));
                    iText.Append(" ");
                    if (val<10) iText.Append(wxString::Format("0%d",val));
                    else iText.Append(wxString::Format("%d",val));
            } else iText = "--- 00 --";

            Grid->SetCellValue(i,0,iText);

            }
}
