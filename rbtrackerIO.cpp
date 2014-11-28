#include "rbtrackerMain.h"
#include <wx/msgdlg.h>
#include <wx/wxprec.h>
#include <wx/filename.h>
#include <wx/textfile.h>
#include "synth.h"
#include "utilities.h"

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
        file.AddLine( (wxString)"Rboy Tracker song file");
        file.AddLine(wxString::Format("BPM=%d",Tempo->GetValue()));
        file.AddLine(wxString::Format("Patterns=%d",NumPatterns->GetValue()));
        file.AddLine(wxString::Format("Instruments=%d",NumInstruments->GetValue()));
        // Write patterns
        for (int i=1; i<=NumPatterns->GetValue(); i++) {
            Pattern->SetValue(i);
            writePatternToFile(file);
        }
        // Write instruments
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
                str = file.GetNextLine();

                Tempo->SetValue(wxAtoi(str.AfterLast((wxUniChar)'=')));

                str = file.GetNextLine();
                numpat = wxAtoi(str.AfterLast((wxUniChar)'='));
                NumPatterns->SetValue(numpat);

                str = file.GetNextLine();
                numinst = wxAtoi(str.AfterLast((wxUniChar)'='));
                NumInstruments->SetValue(numinst);

                // Read patterns
                for (int i=1; i<=NumPatterns->GetValue(); i++) {
                    Pattern->SetValue(i);
                    readPatternFromFile(file);
                }

                // Read instruments
                for (int i=1; i<=NumInstruments->GetValue(); i++) {
                    readPatchFromFile(file);
                    setPatch(i);
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
            str.Append(wxString::Format("%d,%d,",track[0].notenumber[i],track[0].instrument[i]));
            str.Append(wxString::Format("%d,%d,",track[1].notenumber[i],track[1].instrument[i]));
            str.Append(wxString::Format("%d,%d ",track[2].notenumber[i],track[2].instrument[i]));
            file.AddLine(str);
            }
}

void rbtrackerFrame::readPatternFromFile(wxTextFile &file)
{
    for (int i=0; i<64; i++)
            {
            wxString str; int val,inst;
            wxString iText;
            str = file.GetNextLine();

            inst = wxAtoi(str.AfterLast((wxUniChar)','));
            track[2].instrument[i]=inst;
            str = str.BeforeLast((wxUniChar)','); //chop 1
            val = wxAtoi(str.AfterLast((wxUniChar)','));
            track[2].notenumber[i]=val;
            str = str.BeforeLast((wxUniChar)','); //chop 2

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

            Grid->SetCellValue(i,2,iText);

            inst = wxAtoi(str.AfterLast((wxUniChar)','));
            track[1].instrument[i]=inst;
            str = str.BeforeLast((wxUniChar)','); //chop 3
            val = wxAtoi(str.AfterLast((wxUniChar)','));
            track[1].notenumber[i]=val;
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
            track[0].instrument[i]=inst;
            str = str.BeforeLast((wxUniChar)','); //chop 5
            val = wxAtoi(str);
            track[0].notenumber[i]=val;

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
