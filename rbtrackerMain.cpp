/***************************************************************
 * Name:      rbtrackerMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Jonne Valola (jonnev@gmail.com)
 * Created:   2014-11-09
 * Copyright: Jonne Valola ()
 * License:
 **************************************************************/

#include "rbtrackerMain.h"
#include <wx/msgdlg.h>
#include <wx/wxprec.h>
#include "led.h"
#include "Synth.h"
#include "oscillator.h"
#include "utilities.h"

//(*InternalHeaders(rbtrackerFrame)
#include <wx/settings.h>
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

uint8_t ticks=0;
uint16_t period=100;


//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(rbtrackerFrame)
const long rbtrackerFrame::ID_RADIOBOX1 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL2 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL3 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL1 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT2 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT3 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT1 = wxNewId();
const long rbtrackerFrame::ID_TEXTCTRL1 = wxNewId();
const long rbtrackerFrame::ID_CHECKBOX1 = wxNewId();
const long rbtrackerFrame::ID_CHECKBOX2 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL11 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL12 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL4 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT11 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT12 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT4 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT5 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL19 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL5 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT21 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT6 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT20 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL6 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT7 = wxNewId();
const long rbtrackerFrame::ID_CHECKBOX3 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL8 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL9 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL10 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL7 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT9 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT10 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT8 = wxNewId();
const long rbtrackerFrame::ID_BUTTON9 = wxNewId();
const long rbtrackerFrame::ID_GRID2 = wxNewId();
const long rbtrackerFrame::ID_PANEL5 = wxNewId();
const long rbtrackerFrame::ID_PANEL1 = wxNewId();
const long rbtrackerFrame::ID_GRID1 = wxNewId();
const long rbtrackerFrame::ID_PANEL2 = wxNewId();
const long rbtrackerFrame::ID_TEXTCTRL2 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT14 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT19 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT15 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL15 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL16 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL14 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT16 = wxNewId();
const long rbtrackerFrame::ID_BUTTON6 = wxNewId();
const long rbtrackerFrame::ID_BUTTON8 = wxNewId();
const long rbtrackerFrame::ID_BUTTON7 = wxNewId();
const long rbtrackerFrame::ID_BUTTON4 = wxNewId();
const long rbtrackerFrame::ID_CHECKBOX7 = wxNewId();
const long rbtrackerFrame::ID_PANEL3 = wxNewId();
const long rbtrackerFrame::ID_BUTTON5 = wxNewId();
const long rbtrackerFrame::ID_BUTTON2 = wxNewId();
const long rbtrackerFrame::ID_BUTTON3 = wxNewId();
const long rbtrackerFrame::ID_BUTTON1 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT18 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT17 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT13 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL18 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL17 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL13 = wxNewId();
const long rbtrackerFrame::ID_CHECKBOX5 = wxNewId();
const long rbtrackerFrame::ID_CHECKBOX6 = wxNewId();
const long rbtrackerFrame::ID_CHECKBOX4 = wxNewId();
const long rbtrackerFrame::ID_PANEL4 = wxNewId();
const long rbtrackerFrame::idMenuQuit = wxNewId();
const long rbtrackerFrame::idMenuAbout = wxNewId();
//*)

BEGIN_EVENT_TABLE(rbtrackerFrame,wxFrame)
    //(*EventTable(rbtrackerFrame)
    //*)
END_EVENT_TABLE()

rbtrackerFrame::rbtrackerFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(rbtrackerFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, _("Rboy Tracker - Copyright 2014 Jonne Valola"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(824,640));
    SetMinSize(wxSize(-1,-1));
    SetMaxSize(wxSize(-1,-1));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_GRADIENTACTIVECAPTION));
    Instrument = new wxPanel(this, ID_PANEL1, wxPoint(8,288), wxSize(304,328), wxSIMPLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    Instrument->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));
    wxString __wxRadioBoxChoices_1[6] =
    {
    	_("OFF"),
    	_("SQUARE"),
    	_("SAW"),
    	_("TRIANGLE"),
    	_("NOISE"),
    	_("TONE NOISE")
    };
    Wave = new wxRadioBox(Instrument, ID_RADIOBOX1, wxEmptyString, wxPoint(10,24), wxSize(128,151), 6, __wxRadioBoxChoices_1, 1, wxNO_BORDER, wxDefaultValidator, _T("ID_RADIOBOX1"));
    Wave->SetSelection(1);
    BendRate = new wxSpinCtrl(Instrument, ID_SPINCTRL2, _T("0"), wxPoint(232,64), wxSize(64,21), 0, -1000, 1000, 0, _T("ID_SPINCTRL2"));
    BendRate->SetValue(_T("0"));
    InstVol = new wxSpinCtrl(Instrument, ID_SPINCTRL3, _T("127"), wxPoint(232,40), wxSize(64,21), 0, 0, 300, 127, _T("ID_SPINCTRL3"));
    InstVol->SetValue(_T("127"));
    Patch = new wxSpinCtrl(Instrument, ID_SPINCTRL1, _T("1"), wxPoint(80,8), wxSize(56,21), 0, 1, 15, 1, _T("ID_SPINCTRL1"));
    Patch->SetValue(_T("1"));
    StaticText2 = new wxStaticText(Instrument, ID_STATICTEXT2, _("Patch"), wxPoint(8,8), wxSize(64,24), 0, _T("ID_STATICTEXT2"));
    StaticText3 = new wxStaticText(Instrument, ID_STATICTEXT3, _("Volume"), wxPoint(144,40), wxSize(64,16), 0, _T("ID_STATICTEXT3"));
    Pitchbendrate = new wxStaticText(Instrument, ID_STATICTEXT1, _("Pitch bend rate"), wxPoint(144,64), wxSize(87,16), 0, _T("ID_STATICTEXT1"));
    InstName = new wxTextCtrl(Instrument, ID_TEXTCTRL1, _("Description"), wxPoint(144,8), wxSize(152,24), wxTE_NO_VSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    InstName->SetMaxLength(20);
    Loop = new wxCheckBox(Instrument, ID_CHECKBOX1, _("Loop"), wxPoint(16,192), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    Loop->SetValue(false);
    Echo = new wxCheckBox(Instrument, ID_CHECKBOX2, _("Echo"), wxPoint(96,192), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    Echo->SetValue(false);
    VibAmount = new wxSpinCtrl(Instrument, ID_SPINCTRL11, _T("0"), wxPoint(96,240), wxSize(64,21), 0, 0, 255, 0, _T("ID_SPINCTRL11"));
    VibAmount->SetValue(_T("0"));
    Arp1 = new wxSpinCtrl(Instrument, ID_SPINCTRL12, _T("0"), wxPoint(96,264), wxSize(64,21), 0, -10, 10, 0, _T("ID_SPINCTRL12"));
    Arp1->SetValue(_T("0"));
    Arp2 = new wxSpinCtrl(Instrument, ID_SPINCTRL4, _T("0"), wxPoint(96,288), wxSize(64,21), 0, -10, 10, 0, _T("ID_SPINCTRL4"));
    Arp2->SetValue(_T("0"));
    StaticText11 = new wxStaticText(Instrument, ID_STATICTEXT11, _("Vibrato amount"), wxPoint(16,240), wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    StaticText12 = new wxStaticText(Instrument, ID_STATICTEXT12, _("Arpeggio 1"), wxPoint(16,264), wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    StaticText4 = new wxStaticText(Instrument, ID_STATICTEXT4, _("Arpeggio 2"), wxPoint(16,288), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    StaticText5 = new wxStaticText(Instrument, ID_STATICTEXT5, _("Vibrato speed"), wxPoint(16,216), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    Pitch = new wxSpinCtrl(Instrument, ID_SPINCTRL19, _T("100"), wxPoint(200,120), wxSize(64,21), 0, 1, 3000, 100, _T("ID_SPINCTRL19"));
    Pitch->SetValue(_T("100"));
    MaxBend = new wxSpinCtrl(Instrument, ID_SPINCTRL5, _T("0"), wxPoint(232,88), wxSize(64,21), 0, -30000, 30000, 0, _T("ID_SPINCTRL5"));
    MaxBend->SetValue(_T("0"));
    StaticText21 = new wxStaticText(Instrument, ID_STATICTEXT21, _("Pitch bend max"), wxPoint(144,88), wxDefaultSize, 0, _T("ID_STATICTEXT21"));
    StaticText6 = new wxStaticText(Instrument, ID_STATICTEXT6, _("Note"), wxPoint(152,152), wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    StaticText20 = new wxStaticText(Instrument, ID_STATICTEXT20, _("Hz"), wxPoint(270,124), wxSize(13,22), 0, _T("ID_STATICTEXT20"));
    VibSpeed = new wxSpinCtrl(Instrument, ID_SPINCTRL6, _T("0"), wxPoint(96,216), wxSize(64,21), 0, 0, 255, 0, _T("ID_SPINCTRL6"));
    VibSpeed->SetValue(_T("0"));
    StaticText7 = new wxStaticText(Instrument, ID_STATICTEXT7, _("Attack"), wxPoint(184,216), wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    ADSR = new wxCheckBox(Instrument, ID_CHECKBOX3, _("ADSR"), wxPoint(184,192), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
    ADSR->SetValue(false);
    Attack = new wxSpinCtrl(Instrument, ID_SPINCTRL8, _T("0"), wxPoint(232,216), wxSize(64,21), 0, 0, 255, 0, _T("ID_SPINCTRL8"));
    Attack->SetValue(_T("0"));
    Decay = new wxSpinCtrl(Instrument, ID_SPINCTRL9, _T("0"), wxPoint(232,240), wxSize(64,21), 0, 0, 255, 0, _T("ID_SPINCTRL9"));
    Decay->SetValue(_T("0"));
    Sustain = new wxSpinCtrl(Instrument, ID_SPINCTRL10, _T("0"), wxPoint(232,264), wxSize(64,21), 0, 0, 255, 0, _T("ID_SPINCTRL10"));
    Sustain->SetValue(_T("0"));
    Release = new wxSpinCtrl(Instrument, ID_SPINCTRL7, _T("0"), wxPoint(232,288), wxSize(64,21), 0, 0, 255, 0, _T("ID_SPINCTRL7"));
    Release->SetValue(_T("0"));
    StaticText9 = new wxStaticText(Instrument, ID_STATICTEXT9, _("Decay"), wxPoint(184,240), wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    StaticText10 = new wxStaticText(Instrument, ID_STATICTEXT10, _("Sustain"), wxPoint(184,264), wxDefaultSize, 0, _T("ID_STATICTEXT10"));
    StaticText8 = new wxStaticText(Instrument, ID_STATICTEXT8, _("Release"), wxPoint(184,288), wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    Test = new wxButton(Instrument, ID_BUTTON9, _("TEST"), wxPoint(144,119), wxSize(47,23), 0, wxDefaultValidator, _T("ID_BUTTON9"));
    Panel2 = new wxPanel(Instrument, ID_PANEL5, wxPoint(201,152), wxSize(62,20), wxTAB_TRAVERSAL, _T("ID_PANEL5"));
    TestGrid = new wxGrid(Panel2, ID_GRID2, wxPoint(-80,-32), wxSize(158,72), 0, _T("ID_GRID2"));
    TestGrid->CreateGrid(1,1);
    TestGrid->EnableEditing(true);
    TestGrid->EnableGridLines(false);
    TestGrid->SetDefaultColSize(60, true);
    TestGrid->SetDefaultCellFont( TestGrid->GetFont() );
    TestGrid->SetDefaultCellTextColour( TestGrid->GetForegroundColour() );
    Tracks = new wxPanel(this, ID_PANEL2, wxPoint(328,8), wxSize(480,608), wxSIMPLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    Grid = new wxGrid(Tracks, ID_GRID1, wxPoint(0,0), wxSize(472,595), 0, _T("ID_GRID1"));
    Grid->CreateGrid(64,3);
    wxFont GridFont(10,wxTELETYPE,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    Grid->SetFont(GridFont);
    Grid->EnableEditing(false);
    Grid->EnableGridLines(true);
    Grid->SetColLabelSize(17);
    Grid->SetRowLabelSize(30);
    Grid->SetDefaultRowSize(17, true);
    Grid->SetDefaultColSize(140, true);
    wxFont GridLabelFont_2(10,wxTELETYPE,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    Grid->SetLabelFont(GridLabelFont_2);
    Grid->SetColLabelValue(0, _("Track 1"));
    Grid->SetColLabelValue(1, _("Track 2"));
    Grid->SetColLabelValue(2, _("Track 3"));
    Grid->SetCellValue(0, 0, _("--- 00"));
    Grid->SetDefaultCellFont( Grid->GetFont() );
    Grid->SetDefaultCellTextColour( Grid->GetForegroundColour() );
    Control = new wxPanel(this, ID_PANEL3, wxPoint(8,136), wxSize(304,144), wxSIMPLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    Control->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));
    SongName = new wxTextCtrl(Control, ID_TEXTCTRL2, _("Song name"), wxPoint(64,8), wxSize(232,24), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    SongName->SetMaxLength(20);
    StaticText14 = new wxStaticText(Control, ID_STATICTEXT14, _("SONG"), wxPoint(8,8), wxDefaultSize, 0, _T("ID_STATICTEXT14"));
    StaticText19 = new wxStaticText(Control, ID_STATICTEXT19, _("Instruments"), wxPoint(8,40), wxDefaultSize, 0, _T("ID_STATICTEXT19"));
    StaticText15 = new wxStaticText(Control, ID_STATICTEXT15, _("BPM"), wxPoint(176,64), wxDefaultSize, 0, _T("ID_STATICTEXT15"));
    NumInstruments = new wxSpinCtrl(Control, ID_SPINCTRL15, _T("1"), wxPoint(80,40), wxSize(72,21), 0, 1, 15, 1, _T("ID_SPINCTRL15"));
    NumInstruments->SetValue(_T("1"));
    NumPatterns = new wxSpinCtrl(Control, ID_SPINCTRL16, _T("1"), wxPoint(232,40), wxSize(64,21), 0, 1, 10, 1, _T("ID_SPINCTRL16"));
    NumPatterns->SetValue(_T("1"));
    Tempo = new wxSpinCtrl(Control, ID_SPINCTRL14, _T("120"), wxPoint(232,64), wxSize(64,21), 0, 1, 300, 120, _T("ID_SPINCTRL14"));
    Tempo->SetValue(_T("120"));
    StaticText16 = new wxStaticText(Control, ID_STATICTEXT16, _("Patterns"), wxPoint(176,40), wxDefaultSize, 0, _T("ID_STATICTEXT16"));
    Save = new wxButton(Control, ID_BUTTON6, _("SAVE"), wxPoint(8,104), wxSize(64,23), 0, wxDefaultValidator, _T("ID_BUTTON6"));
    New = new wxButton(Control, ID_BUTTON8, _("NEW"), wxPoint(152,104), wxSize(64,23), 0, wxDefaultValidator, _T("ID_BUTTON8"));
    Export = new wxButton(Control, ID_BUTTON7, _("EXPORT"), wxPoint(224,104), wxSize(64,23), 0, wxDefaultValidator, _T("ID_BUTTON7"));
    Load = new wxButton(Control, ID_BUTTON4, _("LOAD"), wxPoint(80,104), wxSize(64,23), 0, wxDefaultValidator, _T("ID_BUTTON4"));
    InstAudible = new wxCheckBox(Control, ID_CHECKBOX7, _("Audible in track editor"), wxPoint(8,72), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
    InstAudible->SetValue(true);
    Panel1 = new wxPanel(this, ID_PANEL4, wxPoint(8,8), wxSize(304,120), wxSIMPLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL4"));
    Panel1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));
    PlaySong = new wxButton(Panel1, ID_BUTTON5, _("Play SONG"), wxPoint(8,8), wxSize(71,23), 0, wxDefaultValidator, _T("ID_BUTTON5"));
    PlayPattern = new wxButton(Panel1, ID_BUTTON2, _("Play PTN"), wxPoint(88,8), wxSize(71,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    Rewind = new wxButton(Panel1, ID_BUTTON3, _("REWIND"), wxPoint(88,40), wxSize(71,23), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    Pause = new wxButton(Panel1, ID_BUTTON1, _("PAUSE"), wxPoint(8,40), wxSize(71,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    StaticText18 = new wxStaticText(Panel1, ID_STATICTEXT18, _("PATTERN"), wxPoint(176,8), wxDefaultSize, 0, _T("ID_STATICTEXT18"));
    StaticText17 = new wxStaticText(Panel1, ID_STATICTEXT17, _("POSITION"), wxPoint(176,32), wxDefaultSize, 0, _T("ID_STATICTEXT17"));
    StaticText13 = new wxStaticText(Panel1, ID_STATICTEXT13, _("OCTAVE"), wxPoint(176,56), wxDefaultSize, 0, _T("ID_STATICTEXT13"));
    Octave = new wxSpinCtrl(Panel1, ID_SPINCTRL18, _T("3"), wxPoint(240,56), wxSize(49,21), 0, 0, 7, 3, _T("ID_SPINCTRL18"));
    Octave->SetValue(_T("3"));
    Position = new wxSpinCtrl(Panel1, ID_SPINCTRL17, _T("0"), wxPoint(240,32), wxSize(49,21), 0, 0, 63, 0, _T("ID_SPINCTRL17"));
    Position->SetValue(_T("0"));
    Pattern = new wxSpinCtrl(Panel1, ID_SPINCTRL13, _T("1"), wxPoint(240,8), wxSize(49,21), 0, 1, 10, 1, _T("ID_SPINCTRL13"));
    Pattern->SetValue(_T("1"));
    Ch1 = new wxCheckBox(Panel1, ID_CHECKBOX5, _("TRACK 1"), wxPoint(16,88), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
    Ch1->SetValue(true);
    Ch3 = new wxCheckBox(Panel1, ID_CHECKBOX6, _("TRACK 3"), wxPoint(208,88), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
    Ch3->SetValue(true);
    Ch2 = new wxCheckBox(Panel1, ID_CHECKBOX4, _("TRACK 2"), wxPoint(112,88), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
    Ch2->SetValue(true);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    Center();

    Connect(ID_RADIOBOX1,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&rbtrackerFrame::OnWaveSelect);
    Connect(ID_SPINCTRL2,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&rbtrackerFrame::OnInstTuneChange);
    Connect(ID_SPINCTRL3,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&rbtrackerFrame::OnInstVolChange);
    Connect(ID_SPINCTRL1,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&rbtrackerFrame::OnPatchChange);
    Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&rbtrackerFrame::OnLoopClick);
    Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&rbtrackerFrame::OnEchoClick);
    Connect(ID_SPINCTRL5,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&rbtrackerFrame::OnPitchBendChange);
    Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&rbtrackerFrame::OnADSRClick);
    Connect(ID_SPINCTRL8,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&rbtrackerFrame::OnAttackChange);
    Connect(ID_SPINCTRL9,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&rbtrackerFrame::OnAttackChange);
    Connect(ID_SPINCTRL10,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&rbtrackerFrame::OnAttackChange);
    Connect(ID_SPINCTRL7,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&rbtrackerFrame::OnAttackChange);
    Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&rbtrackerFrame::OnTestClick);
    Connect(ID_GRID2,wxEVT_GRID_CELL_LEFT_CLICK,(wxObjectEventFunction)&rbtrackerFrame::OnTestGridCellLeftClick);
    TestGrid->Connect(wxEVT_KEY_DOWN,(wxObjectEventFunction)&rbtrackerFrame::OnTestGridKeyDown,0,this);
    Connect(ID_GRID1,wxEVT_GRID_CELL_LEFT_CLICK,(wxObjectEventFunction)&rbtrackerFrame::OnGrid1CellLeftClick);
    Tracks->Connect(wxEVT_KEY_DOWN,(wxObjectEventFunction)&rbtrackerFrame::OnTracksKeyDown,0,this);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&rbtrackerFrame::OnPlaySongClick);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&rbtrackerFrame::OnPauseClick);
    Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&rbtrackerFrame::OnCh1Click);
    Connect(ID_CHECKBOX6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&rbtrackerFrame::OnCh3Click);
    Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&rbtrackerFrame::OnCh2Click);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&rbtrackerFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&rbtrackerFrame::OnAbout);
    //*)

    Grid->SetDefaultCellAlignment (wxALIGN_CENTER,wxALIGN_CENTER);
    for (int row = 0; row <= 63 ; row ++)
    {
        Grid->SetCellValue(row,0,wxString("--- 00 --"));
        Grid->SetCellValue(row,1,wxString("--- 00 --"));
        Grid->SetCellValue(row,2,wxString("--- 00 --"));
        if (!(row%4)) {
            Grid->SetCellBackgroundColour(row,0,wxColor(200,200,255));
            Grid->SetCellBackgroundColour(row,1,wxColor(200,200,255));
            Grid->SetCellBackgroundColour(row,2,wxColor(200,200,255));
        }
    }

    timer = new wxTimer(this, 1);
    Connect(wxEVT_TIMER, wxTimerEventHandler(rbtrackerFrame::OnTimer));
    initSound();
    //timer->Start(50);
}

rbtrackerFrame::~rbtrackerFrame()
{
    //(*Destroy(rbtrackerFrame)
    //*)
}

void rbtrackerFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void rbtrackerFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void rbtrackerFrame::OnTimer(wxTimerEvent& event)
{
        if (playing) {
            if (playerpos==64) Grid->MakeCellVisible(0,0);
            if (playerpos==31) Grid->MakeCellVisible(63,0);
            Grid->SelectRow(playerpos);
        }
        //timer->Start(-1,wxTIMER_ONE_SHOT);
}

void rbtrackerFrame::OnPlaySongClick(wxCommandEvent& event)
{
    if (!playing) {
        long per = 1000*60; // ms per minute was 1000*60
        per /= Tempo->GetValue(); // beats per minute
        per /= 4; // 4 ticks per beat
        period = (uint16_t) per;
        // at 57000 thousand samples per second
        // period gives ms of 1 tick
        // therefore samples per tick = period ms / 1000 * 57000
        samplespertick = period*57;
        samplesperpattern = samplespertick * 64;
        playerpos=0;
        Position->SetValue(playerpos);
        priming = true;
        playPtn();
    } else playing = false;
}

void rbtrackerFrame::OnPauseClick(wxCommandEvent& event)
{
    playing=false;
    timer->Stop();
}

void rbtrackerFrame::OnCh1Click(wxCommandEvent& event)
{
    if (Ch1->IsChecked()) for (int row = 0; row <64 ; row++) Grid->SetCellTextColour(row,0,wxColor(0,0,0));
    else for (int row = 0; row <64 ; row++) Grid->SetCellTextColour(row,0,wxColor(170,170,170));
    Grid->Refresh();
}

void rbtrackerFrame::OnCh2Click(wxCommandEvent& event)
{
    if (Ch2->IsChecked()) for (int row = 0; row <64 ; row++) Grid->SetCellTextColour(row,1,wxColor(0,0,0));
    else for (int row = 0; row <64 ; row++) Grid->SetCellTextColour(row,1,wxColor(170,170,170));
    Grid->Refresh();
}

void rbtrackerFrame::OnCh3Click(wxCommandEvent& event)
{
    if (Ch3->IsChecked()) for (int row = 0; row <64 ; row++) Grid->SetCellTextColour(row,2,wxColor(0,0,0));
    else for (int row = 0; row <64 ; row++) Grid->SetCellTextColour(row,2,wxColor(170,170,170));
    Grid->Refresh();
}

void rbtrackerFrame::OnGrid1CellLeftClick(wxGridEvent& event)
{
    Grid->SetGridCursor(event.GetRow(),event.GetCol());
}

void rbtrackerFrame::OnTracksKeyDown(wxKeyEvent& event)
{
    wxString iText; int num=0;
    uint8_t tracknum = Grid->GetCursorColumn();
    uint8_t trackpos = Grid->GetCursorRow();
    int instrument = Patch->GetValue();
    if (event.GetKeyCode()==WXK_LEFT) { Grid->MoveCursorLeft(false); return; }
    if (event.GetKeyCode()==WXK_RIGHT) { Grid->MoveCursorRight(false); return; }
    if (event.GetKeyCode()==WXK_UP) { Grid->MoveCursorUp(false); return; }
    if (event.GetKeyCode()==WXK_DOWN) { Grid->MoveCursorDown(false); return; }
    iText = event.GetUnicodeKey();
    iText = iText.Upper();
    num = KeyToNumber(iText, Octave->GetValue());
    iText = KeyToNote(iText, Octave->GetValue());

    if (iText == "" || num == 255) {
        iText = "--- 00 --";
        Grid->SetCellValue(trackpos,tracknum,iText);

        track[tracknum].notenumber[trackpos] = 255;
        track[tracknum].instrument[trackpos] = 0;
        return;
    }
    track[tracknum].notenumber[trackpos] = num;
    track[tracknum].instrument[trackpos] = instrument;
    if (InstAudible->IsChecked()) playNote(num);
    if (instrument < 10) iText << " 0" << instrument;
    else iText << " " << instrument;
    if (num < 10) iText << " 0" << num;
    else iText << " " << num;
    Grid->SetCellValue(trackpos,tracknum,iText);
}

void rbtrackerFrame::OnTestGridCellLeftClick(wxGridEvent& event)
{
    TestGrid->SetGridCursor(0,0);
}

void rbtrackerFrame::OnTestGridKeyDown(wxKeyEvent& event)
{
    wxString iText; int num;
    iText = event.GetUnicodeKey();
    num = KeyToNumber(iText, Octave->GetValue());
    iText = KeyToNote(iText, Octave->GetValue());
    TestGrid->SetCellValue(0,0,iText);
    playNote(num);
}

void rbtrackerFrame::OnTestClick(wxCommandEvent& event)
{
    setOSC(&osc1,1,Wave->GetSelection(),Loop->IsChecked(), Echo->IsChecked(), ADSR->IsChecked(),
           25,InstVol->GetValue(), Attack->GetValue(), Decay->GetValue(), Sustain->GetValue(),
           Release->GetValue(), MaxBend->GetValue(), BendRate->GetValue());
}

void rbtrackerFrame::playNote(uint8_t notenum)
{
    //stopSound();
    Pitch->SetValue(freqs[notenum]);
    setOSC(&osc1,1,Wave->GetSelection(),Loop->IsChecked(), Echo->IsChecked(), ADSR->IsChecked(),
           notenum,InstVol->GetValue(), Attack->GetValue(), Decay->GetValue(), Sustain->GetValue()<<8,
           Release->GetValue(), MaxBend->GetValue(), BendRate->GetValue());
    //startSound();
}


void rbtrackerFrame::OnPatchChange(wxSpinEvent& event)
{
    int i = Patch->GetValue();
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
    patch[Patch->GetValue()].echo = Echo->IsChecked();
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

void rbtrackerFrame::playPtn() {
    uint16_t h = samplespertick; // Initiate samples per tick counter, force first SetOsc
    uint8_t patternpos=0;
    uint8_t i=0;
    tick=3;

    // Zero all oscillators
    setOSC(&osc1,0,0,0,0,0,0,0,0,0,0,0,0,0);
    setOSC(&osc2,0,0,0,0,0,0,0,0,0,0,0,0,0);
    setOSC(&osc3,0,0,0,0,0,0,0,0,0,0,0,0,0);

    for (writeindex=0; writeindex < samplesperpattern; writeindex++) // Fill the buffer
    {
        if (h == samplespertick) {
            // TRACK 1
            if (track[0].on) i = track[0].instrument[patternpos];
            else i = 0;
            if (i) {
                setOSC(&osc1,1,patch[i].wave,patch[i].loop, patch[i].echo, patch[i].adsr,
                track[0].notenumber[patternpos],patch[i].vol,
                patch[i].attack, patch[i].decay, patch[i].sustain,patch[i].release,
                patch[i].maxbend, patch[i].bendrate );
                }
            // TRACK 2
            if (track[1].on) i = track[1].instrument[patternpos];
            else i = 0;
            if (i) {
                setOSC(&osc2,1,patch[i].wave,patch[i].loop, patch[i].echo, patch[i].adsr,
                track[1].notenumber[patternpos],patch[i].vol,
                patch[i].attack, patch[i].decay, patch[i].sustain,patch[i].release,
                patch[i].maxbend, patch[i].bendrate );
                }
            // TRACK 3
            if (track[2].on) i = track[2].instrument[patternpos];
            else i = 0;
            if (i) {
                setOSC(&osc3,1,patch[i].wave,patch[i].loop, patch[i].echo, patch[i].adsr,
                track[2].notenumber[patternpos],patch[i].vol,
                patch[i].attack, patch[i].decay, patch[i].sustain,patch[i].release,
                patch[i].maxbend, patch[i].bendrate );
                }
            patternpos++;
            if (patternpos == 64) patternpos = 0;
            h =0;
            } else h++; // else count away
            // Generate sample into buffer
            fakeISR();
        } // end of fill buffer
    priming = false; playing=true;
}
