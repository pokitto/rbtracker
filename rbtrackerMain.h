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
#include <wx/msgdlg.h>
#include <wx/checkbox.h>
#include <wx/spinctrl.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/filedlg.h>
#include <wx/choice.h>
#include <wx/statbmp.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

#include <wx/timer.h>
#include <wx/textfile.h>
#include "oscillator.h"

extern wxString iNames[16];
extern uint16_t instedited;
extern BLOCK clipboard[3];
extern int clipwidth, clipheight, cliprow, clipcol;

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
        void writeBlocksToFile(wxTextFile &);
        void readPatternFromFile(wxTextFile &);
        void readBlocksFromFile(wxTextFile &);
        void readPatternToTable(uint8_t);
        void readBlockToTrack(uint8_t, uint8_t);
        void readBlocksToAllTracks(uint8_t);
        void copyToClipboard(int,int,int,int);
        void pasteFromClipboard(int,int);
        void transposeSelection(int);
        void exportPatchToFile(wxTextFile &);

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
        void OnArpModeSelect(wxCommandEvent& event);
        void OnPanel1Paint(wxPaintEvent& event);
        void OnPatternChange(wxSpinEvent& event);
        void OnSongLengthChange(wxSpinEvent& event);
        void OnPositionChange(wxSpinEvent& event);
        void OnBlock1Change(wxSpinEvent& event);
        void OnBlock2Change(wxSpinEvent& event);
        void OnBlock3Change(wxSpinEvent& event);
        void OnLoopToChange(wxSpinEvent& event);
        void OnNewSongClick(wxCommandEvent& event);
        void OnOverdriveClick(wxCommandEvent& event);
        void OnKickClick(wxCommandEvent& event);
        void OnExportCPatchClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(rbtrackerFrame)
        static const long ID_STATICBITMAP1;
        static const long ID_BUTTON5;
        static const long ID_STATICTEXT13;
        static const long ID_SPINCTRL18;
        static const long ID_STATICTEXT19;
        static const long ID_SPINCTRL15;
        static const long ID_STATICTEXT6;
        static const long ID_STATICTEXT15;
        static const long ID_SPINCTRL13;
        static const long ID_SPINCTRL14;
        static const long ID_BUTTON3;
        static const long ID_BUTTON4;
        static const long ID_BUTTON13;
        static const long ID_BUTTON6;
        static const long ID_STATICTEXT18;
        static const long ID_SPINCTRL4;
        static const long ID_STATICTEXT11;
        static const long ID_SPINCTRL17;
        static const long ID_STATICTEXT22;
        static const long ID_SPINCTRL16;
        static const long ID_STATICTEXT16;
        static const long ID_SPINCTRL20;
        static const long ID_PANEL4;
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
        static const long ID_SPINCTRL12;
        static const long ID_SPINCTRL11;
        static const long ID_STATICTEXT20;
        static const long ID_STATICTEXT17;
        static const long ID_STATICTEXT14;
        static const long ID_CHECKBOX5;
        static const long ID_CHECKBOX4;
        static const long ID_SPINCTRL19;
        static const long ID_CHECKBOX6;
        static const long ID_PANEL2;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        static const long ID_MESSAGEDIALOG1;
        //*)

        //(*Declarations(rbtrackerFrame)
        wxStaticText* StaticText10;
        wxStaticText* StaticText9;
        wxButton* NewSong;
        wxCheckBox* Echo;
        wxFileDialog* LoadSongDialog;
        wxSpinCtrl* Block2;
        wxCheckBox* Ch3;
        wxButton* LoadSongBtn;
        wxFileDialog* SaveSongDialog;
        wxButton* Button4;
        wxStaticText* StaticText13;
        wxStaticText* StaticText2;
        wxStaticText* StaticText14;
        wxStaticText* StaticText6;
        wxStaticBitmap* StaticBitmap1;
        wxStaticText* Pitchbendrate;
        wxStaticText* asdff;
        wxStaticText* StaticText19;
        wxStaticText* StaticText8;
        wxSpinCtrl* Position;
        wxStaticText* StaticText11;
        wxStaticText* StaticText18;
        wxCheckBox* Ch2;
        wxCheckBox* Overdrive;
        wxPanel* Panel1;
        wxStaticText* StaticText1;
        wxButton* SaveSongBtn;
        wxStaticText* StaticText3;
        wxChoice* ArpMode;
        wxMessageDialog* NewSongDialog;
        wxTextCtrl* InstName;
        wxStaticText* StaticText21;
        wxRadioBox* Wave;
        wxButton* SavePatchBtn;
        wxSpinCtrl* NumInstruments;
        wxSpinCtrl* Patch;
        wxSpinCtrl* Decay;
        wxCheckBox* Ch1;
        wxSpinCtrl* Block3;
        wxStaticText* StaticText5;
        wxButton* LoadPatchBtn;
        wxCheckBox* Kick;
        wxSpinCtrl* InstVol;
        wxStatusBar* StatusBar1;
        wxFileDialog* ExportPatchDialog;
        wxButton* PlaySong;
        wxSpinCtrl* BendRate;
        wxPanel* Instrument;
        wxPanel* Tracks;
        wxSpinCtrl* SongLength;
        wxSpinCtrl* RowJump;
        wxStaticText* StaticText15;
        wxStaticText* StaticText12;
        wxSpinCtrl* Sustain;
        wxFileDialog* LoadPatchDialog;
        wxSpinCtrl* VibRate;
        wxSpinCtrl* Block1;
        wxFileDialog* SavePatchDialog;
        wxButton* ExportCPatch;
        wxSpinCtrl* Tempo;
        wxCheckBox* ADSR;
        wxSpinCtrl* MaxBend;
        wxSpinCtrl* Release;
        wxStaticText* StaticText17;
        wxStaticText* StaticText4;
        wxSpinCtrl* Attack;
        wxSpinCtrl* Octave;
        wxSpinCtrl* LoopTo;
        wxGrid* Grid;
        wxStaticText* StaticText16;
        wxSpinCtrl* NumPatterns;
        wxCheckBox* Loop;
        //*)

        wxTimer* timer;
        DECLARE_EVENT_TABLE()
};

#endif // RBTRACKERMAIN_H
