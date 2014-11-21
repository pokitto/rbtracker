#include "rbtrackerMain.h"
#include <wx/msgdlg.h>
#include <wx/wxprec.h>
#include <wx/filename.h>
#include <wx/textfile.h>
#include "synth.h"



void rbtrackerFrame::OnInstNameTextEnter(wxCommandEvent& event)
{
    int i = Patch->GetValue();
    iNames[i] = InstName->GetValue();
}


void rbtrackerFrame::OnPatchChange(wxSpinEvent& event)
{
    int i = Patch->GetValue();
    InstName->SetValue(iNames[i]);
    Wave->SetSelection(patch[i].wave);
    Loop->SetValue(patch[i].loop);
    Echo->SetValue(patch[i].echo);
    ADSR->SetValue(patch[i].adsr);
    InstVol->SetValue(patch[i].vol);
    Attack->SetValue(patch[i].attack);
    Decay->SetValue(patch[i].decay);
    Sustain->SetValue(patch[i].sustain>>8); // sustain is a volume level, not a rate
    Release->SetValue(patch[i].release);
    MaxBend->SetValue(patch[i].maxbend);
    BendRate->SetValue(patch[i].bendrate);
}

void rbtrackerFrame::OnAttackChange(wxSpinEvent& event)
{
    patch[Patch->GetValue()].attack = Attack->GetValue();
    patch[Patch->GetValue()].decay = Decay->GetValue();
    patch[Patch->GetValue()].sustain = Sustain->GetValue()<<8; // sustain is a volume level, not a rate
    patch[Patch->GetValue()].release = Release->GetValue();
}

void rbtrackerFrame::OnWaveSelect(wxCommandEvent& event)
{
    patch[Patch->GetValue()].wave = Wave->GetSelection();
}

void rbtrackerFrame::OnLoopClick(wxCommandEvent& event)
{
    patch[Patch->GetValue()].loop = Loop->IsChecked();
}

void rbtrackerFrame::OnEchoClick(wxCommandEvent& event)
{
    patch[Patch->GetValue()].echo = Echo->IsChecked() * 16; // echo loops maximum 16 times
}

void rbtrackerFrame::OnADSRClick(wxCommandEvent& event)
{
    patch[Patch->GetValue()].adsr = ADSR->IsChecked();
}

void rbtrackerFrame::OnInstVolChange(wxSpinEvent& event)
{
    patch[Patch->GetValue()].vol = InstVol->GetValue();
}

void rbtrackerFrame::OnPitchBendChange(wxSpinEvent& event)
{
    patch[Patch->GetValue()].maxbend = MaxBend->GetValue();
}

void rbtrackerFrame::OnInstTuneChange(wxSpinEvent& event)
{
    patch[Patch->GetValue()].bendrate = BendRate->GetValue();
}

void rbtrackerFrame::setPatch()
{
    int i = Patch->GetValue();
    iNames[i] = InstName->GetValue();
    patch[i].adsr = ADSR->IsChecked();
    patch[i].vol = InstVol->GetValue();
    patch[i].bendrate = BendRate->GetValue();
    patch[i].maxbend = MaxBend->GetValue();
    patch[i].echo = Echo->IsChecked() * 16; // echo loops maximum 16 times
    patch[i].loop = Loop->IsChecked();
    patch[i].wave = Wave->GetSelection();
    patch[i].attack = Attack->GetValue();
    patch[i].decay = Decay->GetValue();
    patch[i].sustain = Sustain->GetValue()<<8; // sustain is a volume level, not a rate
    patch[i].release = Release->GetValue();
}
