#include "rbtrackerMain.h"
#include <wx/msgdlg.h>
#include <wx/wxprec.h>
#include <wx/filename.h>
#include <wx/textfile.h>
#include "synth.h"





void rbtrackerFrame::OnExportCPatchClick(wxCommandEvent& event)
{
    wxString defname;
    defname = InstName->GetValue();
    defname.Append(wxT(".c"));
    ExportPatchDialog->SetFilename(defname);
    int dlg=ExportPatchDialog->ShowModal();

    if(dlg==wxID_OK)
    {
        defname = ExportPatchDialog->GetPath();
        wxTextFile file(defname);
        if(file.Exists()) file.Open(defname); else file.Create(defname);

        file.Clear();
        file.AddLine( (wxString)"// Rboy Tracker patch .c export file");
        file.AddLine( (wxString)"#include <Arduino.h>");
        file.AddLine( (wxString)"#include <patches.h>");
        file.AddLine( (wxString)"");
        wxString temp;
        temp << "// " << Patch->GetValue() << " " << InstName->GetValue();
        file.AddLine(temp);
        temp = "const prog_uchar ";
        temp << InstName->GetValue() << "[13] PROGMEM = {";
        file.AddLine(temp);
        exportPatchToFile(file);
        file.AddLine( (wxString)"};");
        wxRemoveFile(defname);
        file.Create(defname);

        file.Write();
        file.Close();
    }
}

void rbtrackerFrame::OnKickClick(wxCommandEvent& event)
{
    int i = Patch->GetValue();
    patch[i].kick = Kick->GetValue();
}

void rbtrackerFrame::OnOverdriveClick(wxCommandEvent& event)
{
    int i = Patch->GetValue();
    patch[i].overdrive = Overdrive->GetValue();
}

void rbtrackerFrame::OnInstNameTextEnter(wxCommandEvent& event)
{
    int i = Patch->GetValue();
    iNames[i] = InstName->GetValue();
    if (Patch->GetValue()>instedited) {instedited = Patch->GetValue(); NumInstruments->SetValue(instedited);}  //ensure instruments are saved correctly
}

void rbtrackerFrame::OnPatchChange(wxSpinEvent& event)
{
    int i = Patch->GetValue();
    getPatch(i);
}

void rbtrackerFrame::OnAttackChange(wxSpinEvent& event)
{
    patch[Patch->GetValue()].attack = Attack->GetValue();
    patch[Patch->GetValue()].decay = Decay->GetValue();
    patch[Patch->GetValue()].sustain = Sustain->GetValue()<<8; // sustain is a volume level, not a rate
    patch[Patch->GetValue()].release = Release->GetValue();
    if (Patch->GetValue()>instedited) {instedited = Patch->GetValue(); NumInstruments->SetValue(instedited);}  //ensure instruments are saved correctly
}

void rbtrackerFrame::OnWaveSelect(wxCommandEvent& event)
{
    patch[Patch->GetValue()].wave = Wave->GetSelection();
    if (Patch->GetValue()>instedited) {instedited = Patch->GetValue(); NumInstruments->SetValue(instedited);}  //ensure instruments are saved correctly
}

void rbtrackerFrame::OnLoopClick(wxCommandEvent& event)
{
    patch[Patch->GetValue()].loop = Loop->IsChecked();
    if (Patch->GetValue()>instedited) {instedited = Patch->GetValue(); NumInstruments->SetValue(instedited);}  //ensure instruments are saved correctly
}

void rbtrackerFrame::OnEchoClick(wxCommandEvent& event)
{
    patch[Patch->GetValue()].echo = Echo->IsChecked();
     if (Patch->GetValue()>instedited) {instedited = Patch->GetValue(); NumInstruments->SetValue(instedited);}
}

void rbtrackerFrame::OnADSRClick(wxCommandEvent& event)
{
    patch[Patch->GetValue()].adsr = ADSR->IsChecked();
     if (Patch->GetValue()>instedited) {instedited = Patch->GetValue(); NumInstruments->SetValue(instedited);}
}

void rbtrackerFrame::OnInstVolChange(wxSpinEvent& event)
{
    patch[Patch->GetValue()].vol = InstVol->GetValue();
     if (Patch->GetValue()>instedited) {instedited = Patch->GetValue(); NumInstruments->SetValue(instedited);}
}

void rbtrackerFrame::OnPitchBendChange(wxSpinEvent& event)
{
    patch[Patch->GetValue()].maxbend = MaxBend->GetValue();
     if (Patch->GetValue()>instedited) {instedited = Patch->GetValue(); NumInstruments->SetValue(instedited);}
}

void rbtrackerFrame::OnInstTuneChange(wxSpinEvent& event)
{
    patch[Patch->GetValue()].bendrate = BendRate->GetValue();
     if (Patch->GetValue()>instedited) {instedited = Patch->GetValue(); NumInstruments->SetValue(instedited);}
}

void rbtrackerFrame::OnArpModeSelect(wxCommandEvent& event)
{
    patch[Patch->GetValue()].arpmode = ArpMode->GetSelection();
}

void rbtrackerFrame::setPatch(int i)
{
    iNames[i] = InstName->GetValue();
    patch[i].adsr = ADSR->IsChecked();
    patch[i].vol = InstVol->GetValue();
    patch[i].bendrate = BendRate->GetValue();
    patch[i].maxbend = MaxBend->GetValue();
    patch[i].echo = Echo->IsChecked(); // echo loops maximum 16 times
    patch[i].loop = Loop->IsChecked();
    patch[i].wave = Wave->GetSelection();
    patch[i].attack = Attack->GetValue();
    patch[i].decay = Decay->GetValue();
    patch[i].sustain = Sustain->GetValue()<<8; // sustain is a volume level, not a rate
    patch[i].release = Release->GetValue();
    patch[i].arpmode = ArpMode->GetSelection();
    patch[i].overdrive = Overdrive->GetValue();
    patch[i].kick = Kick->GetValue();
}

void rbtrackerFrame::getPatch(int i) {
    Patch->SetValue(i);
    InstName->SetValue(iNames[i]);
    Wave->SetSelection(patch[i].wave);
    InstVol->SetValue(patch[i].vol);
    BendRate->SetValue(patch[i].bendrate);
    MaxBend->SetValue(patch[i].maxbend);
    VibRate->SetValue(patch[i].vibrate);
    ArpMode->SetSelection(patch[i].arpmode);

    ADSR->SetValue(patch[i].adsr);
    Attack->SetValue(patch[i].attack);
    Decay->SetValue(patch[i].decay);
    Sustain->SetValue(patch[i].sustain>>8); // sustain is a volume level, not a rate
    Release->SetValue(patch[i].release);

    Loop->SetValue(patch[i].loop);
    Echo->SetValue(patch[i].echo);
    Overdrive->SetValue(patch[i].overdrive);
    Kick->SetValue(patch[i].kick);
}
