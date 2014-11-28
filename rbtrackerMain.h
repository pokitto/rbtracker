/***************************************************************
 * Name:      rbtrackerMain.h
 * Purpose:   Defines Application Frame
 * Author:    Jonne Valola (jonnev@gmail.com)
 * Created:   2014-11-09
 * Copyright: Jonne Valola ()
 * License:
 **************************************************************/

#ifndef RBTRACKERMAIN_H
#define RBTRACKERMAIN_H

//(*Headers(rbtrackerFrame)
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/spinctrl.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/filedlg.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/frame.h>
//*)

#include <wx/timer.h>
#include <wx/textfile.h>

extern wxString iNames[];
extern uint16_t instedited;

class rbtrackerFrame: public wxFrame
{
    public:

        rbtrackerFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~rbtrackerFrame();
        void playNote(uint8_t);
        void playPtn();
        void setPatch(int);
        void getPatch(int);
        void writePatchToFile(wxTextFile &);
        void readPatchFromFile(wxTextFile &);
        void writePatternToFile(wxTextFile &);
        void readPatternFromFile(wxTextFile &);


    private:

        void OnTimer(wxTimerEvent& event);

        //(*Handlers(rbtrackerFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnGrid1CellLeftClick(wxGridEvent& event);
        void OnPlaySongClick(wxCommandEvent& event);
        void OnPauseClick(wxCommandEvent& event);
        void OnCh1Click(wxCommandEvent& event);
        void OnCh2Click(wxCommandEvent& event);
        void OnCh3Click(wxCommandEvent& event);
        void OnTracksKeyDown(wxKeyEvent& event);
        void OnTestClick(wxCommandEvent& event);
        void OnTestNoteText(wxCommandEvent& event);
        void OnTestGridLeftClick(wxMouseEvent& event);
        void OnTestGridKeyDown(wxKeyEvent& event);
        void OnTestGridLeftDown(wxMouseEvent& event);
        void OnTestGridCellLeftClick(wxGridEvent& event);
        void OnAttackChange(wxSpinEvent& event);
        void OnPatchChange(wxSpinEvent& event);
        void OnWaveSelect(wxCommandEvent& event);
        void OnLoopClick(wxCommandEvent& event);
        void OnEchoClick(wxCommandEvent& event);
        void OnADSRClick(wxCommandEvent& event);
        void OnInstVolChange(wxSpinEvent& event);
        void OnPitchBendChange(wxSpinEvent& event);
        void OnInstTuneChange(wxSpinEvent& event);
        void OnButton2Click(wxCommandEvent& event);
        void OnSaveSongBtnClick(wxCommandEvent& event);
        void OnLoadSongBtnClick(wxCommandEvent& event);
        void OnButton5Click(wxCommandEvent& event);
        void OnLoadPatchBtnClick(wxCommandEvent& event);
        void OnSavePatchBtnClick(wxCommandEvent& event);
        void OnInstNameTextEnter(wxCommandEvent& event);
        //*)

        //(*Identifiers(rbtrackerFrame)
        static const long ID_RADIOBOX1;
        static const long ID_SPINCTRL2;
        static const long ID_SPINCTRL3;
        static const long ID_SPINCTRL1;
        static const long ID_STATICTEXT2;
        static const long ID_STATICTEXT3;
        static const long ID_STATICTEXT1;
        static const long ID_TEXTCTRL1;
        static const long ID_CHECKBOX1;
        static const long ID_CHECKBOX2;
        static const long ID_STATICTEXT12;
        static const long ID_STATICTEXT5;
        static const long ID_SPINCTRL5;
        static const long ID_STATICTEXT21;
        static const long ID_SPINCTRL6;
        static const long ID_STATICTEXT4;
        static const long ID_STATICTEXT7;
        static const long ID_CHECKBOX3;
        static const long ID_SPINCTRL8;
        static const long ID_SPINCTRL9;
        static const long ID_SPINCTRL10;
        static const long ID_SPINCTRL7;
        static const long ID_STATICTEXT9;
        static const long ID_STATICTEXT10;
        static const long ID_STATICTEXT8;
        static const long ID_CHOICE1;
        static const long ID_CHECKBOX8;
        static const long ID_CHECKBOX7;
        static const long ID_BUTTON7;
        static const long ID_BUTTON8;
        static const long ID_BUTTON9;
        static const long ID_PANEL1;
        static const long ID_GRID1;
        static const long ID_PANEL2;
        static const long ID_STATICTEXT19;
        static const long ID_STATICTEXT15;
        static const long ID_SPINCTRL15;
        static const long ID_SPINCTRL16;
        static const long ID_SPINCTRL14;
        static const long ID_STATICTEXT16;
        static const long ID_BUTTON3;
        static const long ID_BUTTON4;
        static const long ID_BUTTON6;
        static const long ID_BUTTON1;
        static const long ID_PANEL3;
        static const long ID_BUTTON5;
        static const long ID_BUTTON2;
        static const long ID_STATICTEXT18;
        static const long ID_STATICTEXT17;
        static const long ID_STATICTEXT13;
        static const long ID_SPINCTRL18;
        static const long ID_SPINCTRL17;
        static const long ID_SPINCTRL13;
        static const long ID_CHECKBOX5;
        static const long ID_CHECKBOX6;
        static const long ID_CHECKBOX4;
        static const long ID_PANEL4;
        static const long idMenuQuit;
        static const long idMenuAbout;
        //*)

        //(*Declarations(rbtrackerFrame)
        wxStaticText* StaticText10;
        wxStaticText* StaticText9;
        wxCheckBox* Echo;
        wxFileDialog* LoadSongDialog;
        wxCheckBox* Ch3;
        wxButton* LoadSongBtn;
        wxFileDialog* SaveSongDialog;
        wxButton* Button4;
        wxStaticText* StaticText13;
        wxStaticText* StaticText2;
        wxButton* Button1;
        wxStaticText* Pitchbendrate;
        wxStaticText* StaticText19;
        wxStaticText* asdff;
        wxSpinCtrl* Position;
        wxStaticText* StaticText8;
        wxStaticText* StaticText18;
        wxCheckBox* Ch2;
        wxCheckBox* Overdrive;
        wxPanel* Panel1;
        wxStaticText* StaticText1;
        wxButton* SaveSongBtn;
        wxButton* PlayPattern;
        wxStaticText* StaticText3;
        wxChoice* ArpMode;
        wxTextCtrl* InstName;
        wxStaticText* StaticText21;
        wxSpinCtrl* Pattern;
        wxRadioBox* Wave;
        wxButton* SavePatchBtn;
        wxSpinCtrl* NumInstruments;
        wxSpinCtrl* Patch;
        wxSpinCtrl* Decay;
        wxCheckBox* Ch1;
        wxButton* Button7;
        wxButton* LoadPatchBtn;
        wxCheckBox* Kick;
        wxStaticText* StaticText7;
        wxSpinCtrl* InstVol;
        wxButton* PlaySong;
        wxSpinCtrl* BendRate;
        wxPanel* Instrument;
        wxPanel* Tracks;
        wxStaticText* StaticText15;
        wxStaticText* StaticText12;
        wxSpinCtrl* Sustain;
        wxFileDialog* LoadPatchDialog;
        wxSpinCtrl* VibRate;
        wxFileDialog* SavePatchDialog;
        wxSpinCtrl* Tempo;
        wxCheckBox* ADSR;
        wxSpinCtrl* MaxBend;
        wxSpinCtrl* Release;
        wxStaticText* StaticText17;
        wxSpinCtrl* Attack;
        wxSpinCtrl* Octave;
        wxGrid* Grid;
        wxPanel* Control;
        wxStaticText* StaticText16;
        wxSpinCtrl* NumPatterns;
        wxCheckBox* Loop;
        //*)

        wxTimer* timer;
        DECLARE_EVENT_TABLE()
};

#endif // RBTRACKERMAIN_H
