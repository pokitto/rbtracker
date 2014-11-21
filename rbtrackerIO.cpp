#include "rbtrackerMain.h"
#include <wx/msgdlg.h>
#include <wx/wxprec.h>
#include <wx/filename.h>
#include <wx/textfile.h>

void rbtrackerFrame::OnSaveSongBtnClick(wxCommandEvent& event)
{
    int dlg=SaveSongDialog->ShowModal();
    if(dlg==wxID_OK)
    {
        wxFileName my_file(SaveSongDialog->GetPath());
        wxString my_file_ext=my_file.GetExt().Lower();
    }
}

void rbtrackerFrame::OnLoadSongBtnClick(wxCommandEvent& event)
{
        int dlg=LoadSongDialog->ShowModal();
        if (dlg == wxID_OK)
        {
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
                setPatch();
                file.Close();
            }

        }
}
