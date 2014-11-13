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
#include <wx/button.h>
#include <wx/frame.h>
//*)

#include <wx/timer.h>

class rbtrackerFrame: public wxFrame
{
    public:

        rbtrackerFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~rbtrackerFrame();
        void playNote(uint8_t);

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
        static const long ID_SPINCTRL11;
        static const long ID_SPINCTRL12;
        static const long ID_SPINCTRL4;
        static const long ID_STATICTEXT11;
        static const long ID_STATICTEXT12;
        static const long ID_STATICTEXT4;
        static const long ID_STATICTEXT5;
        static const long ID_SPINCTRL19;
        static const long ID_SPINCTRL5;
        static const long ID_STATICTEXT21;
        static const long ID_STATICTEXT6;
        static const long ID_STATICTEXT20;
        static const long ID_SPINCTRL6;
        static const long ID_STATICTEXT7;
        static const long ID_CHECKBOX3;
        static const long ID_SPINCTRL8;
        static const long ID_SPINCTRL9;
        static const long ID_SPINCTRL10;
        static const long ID_SPINCTRL7;
        static const long ID_STATICTEXT9;
        static const long ID_STATICTEXT10;
        static const long ID_STATICTEXT8;
        static const long ID_BUTTON9;
        static const long ID_GRID2;
        static const long ID_PANEL5;
        static const long ID_PANEL1;
        static const long ID_GRID1;
        static const long ID_PANEL2;
        static const long ID_TEXTCTRL2;
        static const long ID_STATICTEXT14;
        static const long ID_STATICTEXT19;
        static const long ID_STATICTEXT15;
        static const long ID_SPINCTRL15;
        static const long ID_SPINCTRL16;
        static const long ID_SPINCTRL14;
        static const long ID_STATICTEXT16;
        static const long ID_BUTTON6;
        static const long ID_BUTTON8;
        static const long ID_BUTTON7;
        static const long ID_BUTTON4;
        static const long ID_CHECKBOX7;
        static const long ID_PANEL3;
        static const long ID_BUTTON5;
        static const long ID_BUTTON2;
        static const long ID_BUTTON3;
        static const long ID_BUTTON1;
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
        wxButton* Pause;
        wxStaticText* StaticText20;
        wxCheckBox* Echo;
        wxCheckBox* InstAudible;
        wxSpinCtrl* VibAmount;
        wxCheckBox* Ch3;
        wxSpinCtrl* Arp2;
        wxStaticText* StaticText13;
        wxStaticText* StaticText2;
        wxSpinCtrl* InstNum;
        wxStaticText* StaticText14;
        wxStaticText* StaticText6;
        wxSpinCtrl* InstTune;
        wxSpinCtrl* InstBend;
        wxStaticText* StaticText19;
        wxSpinCtrl* Position;
        wxStaticText* StaticText8;
        wxStaticText* StaticText11;
        wxStaticText* StaticText18;
        wxCheckBox* Ch2;
        wxPanel* Panel1;
        wxStaticText* StaticText1;
        wxButton* PlayPattern;
        wxStaticText* StaticText3;
        wxButton* Save;
        wxTextCtrl* InstName;
        wxStaticText* StaticText21;
        wxSpinCtrl* Pattern;
        wxRadioBox* Wave;
        wxButton* Rewind;
        wxSpinCtrl* NumInstruments;
        wxSpinCtrl* Decay;
        wxCheckBox* Ch1;
        wxStaticText* StaticText5;
        wxStaticText* StaticText7;
        wxSpinCtrl* InstVol;
        wxButton* PlaySong;
        wxSpinCtrl* Pitch;
        wxPanel* Instrument;
        wxGrid* TestGrid;
        wxPanel* Tracks;
        wxStaticText* StaticText15;
        wxStaticText* StaticText12;
        wxSpinCtrl* Sustain;
        wxPanel* Panel2;
        wxTextCtrl* SongName;
        wxSpinCtrl* Tempo;
        wxCheckBox* ADSR;
        wxSpinCtrl* VibSpeed;
        wxButton* New;
        wxSpinCtrl* Release;
        wxStaticText* StaticText17;
        wxStaticText* StaticText4;
        wxSpinCtrl* Attack;
        wxButton* Export;
        wxSpinCtrl* Octave;
        wxGrid* Grid;
        wxButton* Test;
        wxPanel* Control;
        wxButton* Load;
        wxStaticText* StaticText16;
        wxSpinCtrl* NumPatterns;
        wxSpinCtrl* Arp1;
        wxCheckBox* Loop;
        //*)

        wxTimer* timer;

        DECLARE_EVENT_TABLE()
};

#endif // RBTRACKERMAIN_H
