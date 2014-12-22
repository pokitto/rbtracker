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
#include <wx/filename.h>
#include <wx/textfile.h>
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
uint16_t period=100, instedited=1;

wxString iNames[16];

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
const long rbtrackerFrame::ID_BUTTON5 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT18 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT17 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT13 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL18 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL17 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL13 = wxNewId();
const long rbtrackerFrame::ID_CHECKBOX5 = wxNewId();
const long rbtrackerFrame::ID_CHECKBOX6 = wxNewId();
const long rbtrackerFrame::ID_CHECKBOX4 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT19 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL15 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT16 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL16 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT15 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL14 = wxNewId();
const long rbtrackerFrame::ID_BUTTON3 = wxNewId();
const long rbtrackerFrame::ID_BUTTON4 = wxNewId();
const long rbtrackerFrame::ID_BUTTON13 = wxNewId();
const long rbtrackerFrame::ID_BUTTON14 = wxNewId();
const long rbtrackerFrame::ID_BUTTON1 = wxNewId();
const long rbtrackerFrame::ID_BUTTON6 = wxNewId();
const long rbtrackerFrame::ID_BUTTON2 = wxNewId();
const long rbtrackerFrame::ID_BUTTON12 = wxNewId();
const long rbtrackerFrame::ID_BUTTON10 = wxNewId();
const long rbtrackerFrame::ID_BUTTON18 = wxNewId();
const long rbtrackerFrame::ID_BUTTON19 = wxNewId();
const long rbtrackerFrame::ID_BUTTON11 = wxNewId();
const long rbtrackerFrame::ID_BUTTON20 = wxNewId();
const long rbtrackerFrame::ID_BUTTON21 = wxNewId();
const long rbtrackerFrame::ID_BUTTON15 = wxNewId();
const long rbtrackerFrame::ID_BUTTON22 = wxNewId();
const long rbtrackerFrame::ID_BUTTON25 = wxNewId();
const long rbtrackerFrame::ID_BUTTON17 = wxNewId();
const long rbtrackerFrame::ID_BUTTON23 = wxNewId();
const long rbtrackerFrame::ID_BUTTON26 = wxNewId();
const long rbtrackerFrame::ID_BUTTON16 = wxNewId();
const long rbtrackerFrame::ID_BUTTON27 = wxNewId();
const long rbtrackerFrame::ID_STATICLINE1 = wxNewId();
const long rbtrackerFrame::ID_PANEL4 = wxNewId();
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
const long rbtrackerFrame::ID_STATICTEXT12 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT5 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL5 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT21 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL6 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT4 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT7 = wxNewId();
const long rbtrackerFrame::ID_CHECKBOX3 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL8 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL9 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL10 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL7 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT9 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT10 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT8 = wxNewId();
const long rbtrackerFrame::ID_CHOICE1 = wxNewId();
const long rbtrackerFrame::ID_CHECKBOX8 = wxNewId();
const long rbtrackerFrame::ID_CHECKBOX7 = wxNewId();
const long rbtrackerFrame::ID_BUTTON7 = wxNewId();
const long rbtrackerFrame::ID_BUTTON8 = wxNewId();
const long rbtrackerFrame::ID_BUTTON9 = wxNewId();
const long rbtrackerFrame::ID_PANEL1 = wxNewId();
const long rbtrackerFrame::ID_GRID1 = wxNewId();
const long rbtrackerFrame::ID_PANEL2 = wxNewId();
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
    Panel1 = new wxPanel(this, ID_PANEL4, wxPoint(8,8), wxSize(304,240), wxSIMPLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL4"));
    Panel1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));
    PlaySong = new wxButton(Panel1, ID_BUTTON5, _("Play SONG"), wxPoint(8,8), wxSize(71,23), 0, wxDefaultValidator, _T("ID_BUTTON5"));
    StaticText18 = new wxStaticText(Panel1, ID_STATICTEXT18, _("PATTERN"), wxPoint(168,144), wxDefaultSize, 0, _T("ID_STATICTEXT18"));
    StaticText17 = new wxStaticText(Panel1, ID_STATICTEXT17, _("POSITION"), wxPoint(96,144), wxDefaultSize, 0, _T("ID_STATICTEXT17"));
    StaticText13 = new wxStaticText(Panel1, ID_STATICTEXT13, _("OCTAVE"), wxPoint(96,184), wxDefaultSize, 0, _T("ID_STATICTEXT13"));
    Octave = new wxSpinCtrl(Panel1, ID_SPINCTRL18, _T("3"), wxPoint(96,200), wxSize(49,21), 0, 0, 7, 3, _T("ID_SPINCTRL18"));
    Octave->SetValue(_T("3"));
    Position = new wxSpinCtrl(Panel1, ID_SPINCTRL17, _T("0"), wxPoint(96,160), wxSize(49,21), 0, 0, 63, 0, _T("ID_SPINCTRL17"));
    Position->SetValue(_T("0"));
    Pattern = new wxSpinCtrl(Panel1, ID_SPINCTRL13, _T("1"), wxPoint(168,160), wxSize(49,21), 0, 1, 10, 1, _T("ID_SPINCTRL13"));
    Pattern->SetValue(_T("1"));
    Ch1 = new wxCheckBox(Panel1, ID_CHECKBOX5, _("Track 1"), wxPoint(88,16), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
    Ch1->SetValue(true);
    Ch3 = new wxCheckBox(Panel1, ID_CHECKBOX6, _("Track 3"), wxPoint(232,16), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
    Ch3->SetValue(true);
    Ch2 = new wxCheckBox(Panel1, ID_CHECKBOX4, _("Track 2"), wxPoint(160,16), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
    Ch2->SetValue(true);
    StaticText19 = new wxStaticText(Panel1, ID_STATICTEXT19, _("PATCHES"), wxPoint(240,184), wxDefaultSize, 0, _T("ID_STATICTEXT19"));
    NumInstruments = new wxSpinCtrl(Panel1, ID_SPINCTRL15, _T("1"), wxPoint(240,200), wxSize(50,21), 0, 1, 15, 1, _T("ID_SPINCTRL15"));
    NumInstruments->SetValue(_T("1"));
    StaticText16 = new wxStaticText(Panel1, ID_STATICTEXT16, _("LOOP AT"), wxPoint(240,144), wxDefaultSize, 0, _T("ID_STATICTEXT16"));
    NumPatterns = new wxSpinCtrl(Panel1, ID_SPINCTRL16, _T("1"), wxPoint(240,160), wxSize(49,21), 0, 1, 10, 1, _T("ID_SPINCTRL16"));
    NumPatterns->SetValue(_T("1"));
    StaticText15 = new wxStaticText(Panel1, ID_STATICTEXT15, _("BPM"), wxPoint(168,184), wxDefaultSize, 0, _T("ID_STATICTEXT15"));
    Tempo = new wxSpinCtrl(Panel1, ID_SPINCTRL14, _T("120"), wxPoint(168,200), wxSize(49,21), 0, 1, 300, 120, _T("ID_SPINCTRL14"));
    Tempo->SetValue(_T("120"));
    SaveSongBtn = new wxButton(Panel1, ID_BUTTON3, _("SAVE AS..."), wxPoint(8,40), wxSize(72,23), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    LoadSongBtn = new wxButton(Panel1, ID_BUTTON4, _("LOAD"), wxPoint(8,64), wxSize(72,23), 0, wxDefaultValidator, _T("ID_BUTTON4"));
    Button5 = new wxButton(Panel1, ID_BUTTON13, _("NEW SONG"), wxPoint(8,88), wxSize(71,23), 0, wxDefaultValidator, _T("ID_BUTTON13"));
    Button6 = new wxButton(Panel1, ID_BUTTON14, _("Copy PTN"), wxPoint(8,152), wxSize(71,23), 0, wxDefaultValidator, _T("ID_BUTTON14"));
    Button1 = new wxButton(Panel1, ID_BUTTON1, _("Paste PTN"), wxPoint(8,176), wxSize(71,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    Button4 = new wxButton(Panel1, ID_BUTTON6, _("EXPORT .C"), wxPoint(8,112), wxSize(72,23), 0, wxDefaultValidator, _T("ID_BUTTON6"));
    CopyTr1 = new wxButton(Panel1, ID_BUTTON2, _("Copy Tr1"), wxPoint(88,40), wxSize(63,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    CopyTr3 = new wxButton(Panel1, ID_BUTTON12, _("Copy Tr3"), wxPoint(232,40), wxSize(63,23), 0, wxDefaultValidator, _T("ID_BUTTON12"));
    CopyTr2 = new wxButton(Panel1, ID_BUTTON10, _("Copy Tr2"), wxPoint(160,40), wxSize(63,23), 0, wxDefaultValidator, _T("ID_BUTTON10"));
    Button2 = new wxButton(Panel1, ID_BUTTON18, _("Paste Tr1"), wxPoint(88,64), wxSize(63,23), 0, wxDefaultValidator, _T("ID_BUTTON18"));
    Button3 = new wxButton(Panel1, ID_BUTTON19, _("Paste Tr1"), wxPoint(232,64), wxSize(63,23), 0, wxDefaultValidator, _T("ID_BUTTON19"));
    PastePtn = new wxButton(Panel1, ID_BUTTON11, _("Paste Tr1"), wxPoint(160,64), wxSize(63,23), 0, wxDefaultValidator, _T("ID_BUTTON11"));
    Button11 = new wxButton(Panel1, ID_BUTTON20, _("Clear Tr1"), wxPoint(88,88), wxSize(63,23), 0, wxDefaultValidator, _T("ID_BUTTON20"));
    Button12 = new wxButton(Panel1, ID_BUTTON21, _("Clear Tr1"), wxPoint(160,88), wxSize(63,23), 0, wxDefaultValidator, _T("ID_BUTTON21"));
    Button8 = new wxButton(Panel1, ID_BUTTON15, _("Clear Tr1"), wxPoint(232,88), wxSize(63,23), 0, wxDefaultValidator, _T("ID_BUTTON15"));
    Button13 = new wxButton(Panel1, ID_BUTTON22, _("/\\"), wxPoint(88,112), wxSize(31,23), 0, wxDefaultValidator, _T("ID_BUTTON22"));
    Button16 = new wxButton(Panel1, ID_BUTTON25, _("/\\"), wxPoint(160,112), wxSize(31,23), 0, wxDefaultValidator, _T("ID_BUTTON25"));
    Button10 = new wxButton(Panel1, ID_BUTTON17, _("/\\"), wxPoint(232,112), wxSize(31,23), 0, wxDefaultValidator, _T("ID_BUTTON17"));
    Button14 = new wxButton(Panel1, ID_BUTTON23, _("\\/"), wxPoint(120,112), wxSize(31,23), 0, wxDefaultValidator, _T("ID_BUTTON23"));
    Button17 = new wxButton(Panel1, ID_BUTTON26, _("\\/"), wxPoint(192,112), wxSize(31,23), 0, wxDefaultValidator, _T("ID_BUTTON26"));
    Button9 = new wxButton(Panel1, ID_BUTTON16, _("\\/"), wxPoint(264,112), wxSize(31,23), 0, wxDefaultValidator, _T("ID_BUTTON16"));
    Button18 = new wxButton(Panel1, ID_BUTTON27, _("Clear PTN"), wxPoint(8,200), wxSize(71,23), 0, wxDefaultValidator, _T("ID_BUTTON27"));
    StaticLine1 = new wxStaticLine(Panel1, ID_STATICLINE1, wxPoint(83,8), wxSize(1,225), wxLI_VERTICAL, _T("ID_STATICLINE1"));
    Instrument = new wxPanel(this, ID_PANEL1, wxPoint(8,256), wxSize(304,360), wxSIMPLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL1"));
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
    BendRate = new wxSpinCtrl(Instrument, ID_SPINCTRL2, _T("0"), wxPoint(232,72), wxSize(64,21), 0, -1000, 1000, 0, _T("ID_SPINCTRL2"));
    BendRate->SetValue(_T("0"));
    InstVol = new wxSpinCtrl(Instrument, ID_SPINCTRL3, _T("127"), wxPoint(232,40), wxSize(64,21), 0, 0, 300, 127, _T("ID_SPINCTRL3"));
    InstVol->SetValue(_T("127"));
    Patch = new wxSpinCtrl(Instrument, ID_SPINCTRL1, _T("1"), wxPoint(80,8), wxSize(56,21), 0, 1, 15, 1, _T("ID_SPINCTRL1"));
    Patch->SetValue(_T("1"));
    StaticText2 = new wxStaticText(Instrument, ID_STATICTEXT2, _("Patch"), wxPoint(8,8), wxSize(64,24), 0, _T("ID_STATICTEXT2"));
    StaticText3 = new wxStaticText(Instrument, ID_STATICTEXT3, _("Volume"), wxPoint(144,40), wxSize(64,16), 0, _T("ID_STATICTEXT3"));
    Pitchbendrate = new wxStaticText(Instrument, ID_STATICTEXT1, _("Pitch bend rate"), wxPoint(144,72), wxSize(87,16), 0, _T("ID_STATICTEXT1"));
    InstName = new wxTextCtrl(Instrument, ID_TEXTCTRL1, _("Patchname"), wxPoint(144,8), wxSize(152,24), wxTE_NO_VSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    InstName->SetMaxLength(20);
    Loop = new wxCheckBox(Instrument, ID_CHECKBOX1, _("Loop"), wxPoint(16,216), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    Loop->SetValue(false);
    Echo = new wxCheckBox(Instrument, ID_CHECKBOX2, _("Echo"), wxPoint(16,240), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    Echo->SetValue(false);
    StaticText12 = new wxStaticText(Instrument, ID_STATICTEXT12, _("Arpeggio mode"), wxPoint(144,144), wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    asdff = new wxStaticText(Instrument, ID_STATICTEXT5, _("Vibrato rate"), wxPoint(144,120), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    MaxBend = new wxSpinCtrl(Instrument, ID_SPINCTRL5, _T("0"), wxPoint(232,96), wxSize(64,21), 0, -30000, 30000, 0, _T("ID_SPINCTRL5"));
    MaxBend->SetValue(_T("0"));
    StaticText21 = new wxStaticText(Instrument, ID_STATICTEXT21, _("Pitch bend max"), wxPoint(144,96), wxDefaultSize, 0, _T("ID_STATICTEXT21"));
    VibRate = new wxSpinCtrl(Instrument, ID_SPINCTRL6, _T("0"), wxPoint(232,120), wxSize(64,21), 0, 0, 255, 0, _T("ID_SPINCTRL6"));
    VibRate->SetValue(_T("0"));
    StaticText1 = new wxStaticText(Instrument, ID_STATICTEXT4, _("Attack"), wxPoint(144,216), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    StaticText7 = new wxStaticText(Instrument, ID_STATICTEXT7, _("Effects"), wxPoint(16,184), wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    ADSR = new wxCheckBox(Instrument, ID_CHECKBOX3, _("ADSR"), wxPoint(88,216), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
    ADSR->SetValue(false);
    Attack = new wxSpinCtrl(Instrument, ID_SPINCTRL8, _T("0"), wxPoint(232,216), wxSize(64,21), 0, 0, 255, 0, _T("ID_SPINCTRL8"));
    Attack->SetValue(_T("0"));
    Decay = new wxSpinCtrl(Instrument, ID_SPINCTRL9, _T("0"), wxPoint(232,240), wxSize(64,21), 0, 0, 255, 0, _T("ID_SPINCTRL9"));
    Decay->SetValue(_T("0"));
    Sustain = new wxSpinCtrl(Instrument, ID_SPINCTRL10, _T("0"), wxPoint(232,264), wxSize(64,21), 0, 0, 255, 0, _T("ID_SPINCTRL10"));
    Sustain->SetValue(_T("0"));
    Release = new wxSpinCtrl(Instrument, ID_SPINCTRL7, _T("0"), wxPoint(232,288), wxSize(64,21), 0, 0, 255, 0, _T("ID_SPINCTRL7"));
    Release->SetValue(_T("0"));
    StaticText9 = new wxStaticText(Instrument, ID_STATICTEXT9, _("Decay"), wxPoint(144,240), wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    StaticText10 = new wxStaticText(Instrument, ID_STATICTEXT10, _("Sustain"), wxPoint(144,264), wxDefaultSize, 0, _T("ID_STATICTEXT10"));
    StaticText8 = new wxStaticText(Instrument, ID_STATICTEXT8, _("Release"), wxPoint(144,288), wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    ArpMode = new wxChoice(Instrument, ID_CHOICE1, wxPoint(232,145), wxSize(64,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    ArpMode->SetSelection( ArpMode->Append(_("OFF")) );
    ArpMode->Append(_("M slow"));
    ArpMode->Append(_("M med"));
    ArpMode->Append(_("M fast"));
    ArpMode->Append(_("m slow"));
    ArpMode->Append(_("m med"));
    ArpMode->Append(_("m fast"));
    Overdrive = new wxCheckBox(Instrument, ID_CHECKBOX8, _("Overdrive X2"), wxPoint(16,264), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX8"));
    Overdrive->SetValue(false);
    Kick = new wxCheckBox(Instrument, ID_CHECKBOX7, _("Drum kick"), wxPoint(16,288), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
    Kick->SetValue(false);
    SavePatchBtn = new wxButton(Instrument, ID_BUTTON7, _("SAVE AS..."), wxPoint(8,328), wxSize(63,23), 0, wxDefaultValidator, _T("ID_BUTTON7"));
    LoadPatchBtn = new wxButton(Instrument, ID_BUTTON8, _("LOAD"), wxPoint(80,328), wxSize(63,23), 0, wxDefaultValidator, _T("ID_BUTTON8"));
    Button7 = new wxButton(Instrument, ID_BUTTON9, _("EXPORT .C"), wxPoint(152,328), wxSize(63,23), 0, wxDefaultValidator, _T("ID_BUTTON9"));
    Tracks = new wxPanel(this, ID_PANEL2, wxPoint(328,8), wxSize(480,608), wxSIMPLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    Grid = new wxGrid(Tracks, ID_GRID1, wxPoint(0,0), wxSize(472,595), 0, _T("ID_GRID1"));
    Grid->CreateGrid(64,3);
    wxFont GridFont(10,wxTELETYPE,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    Grid->SetFont(GridFont);
    Grid->EnableEditing(true);
    Grid->EnableGridLines(true);
    Grid->SetColLabelSize(17);
    Grid->SetRowLabelSize(30);
    Grid->SetDefaultRowSize(17, true);
    Grid->SetDefaultColSize(140, true);
    wxFont GridLabelFont_1(10,wxTELETYPE,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    Grid->SetLabelFont(GridLabelFont_1);
    Grid->SetColLabelValue(0, _("Track 1"));
    Grid->SetColLabelValue(1, _("Track 2"));
    Grid->SetColLabelValue(2, _("Track 3"));
    Grid->SetCellValue(0, 0, _("--- 00"));
    Grid->SetDefaultCellFont( Grid->GetFont() );
    Grid->SetDefaultCellTextColour( Grid->GetForegroundColour() );
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
    SaveSongDialog = new wxFileDialog(this, _("Save song as..."), wxEmptyString, wxEmptyString, _("Rbtracker song | *.rbs;"), wxFD_SAVE|wxFD_OVERWRITE_PROMPT, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    LoadSongDialog = new wxFileDialog(this, _("Load song"), wxEmptyString, wxEmptyString, _("Rbtracker song | *.rbs;"), wxFD_DEFAULT_STYLE|wxFD_OPEN, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    SavePatchDialog = new wxFileDialog(this, _("Save patch"), wxEmptyString, wxEmptyString, _("Rbtracker patch | *.rbp;"), wxFD_SAVE|wxFD_OVERWRITE_PROMPT, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    LoadPatchDialog = new wxFileDialog(this, _("Load patch"), wxEmptyString, wxEmptyString, _("Rbtracker patch | *.rbp;"), wxFD_DEFAULT_STYLE|wxFD_OPEN, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    Center();

    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&rbtrackerFrame::OnPlaySongClick);
    Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&rbtrackerFrame::OnCh1Click);
    Connect(ID_CHECKBOX6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&rbtrackerFrame::OnCh3Click);
    Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&rbtrackerFrame::OnCh2Click);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&rbtrackerFrame::OnSaveSongBtnClick);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&rbtrackerFrame::OnLoadSongBtnClick);
    Connect(ID_RADIOBOX1,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&rbtrackerFrame::OnWaveSelect);
    Connect(ID_SPINCTRL2,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&rbtrackerFrame::OnInstTuneChange);
    Connect(ID_SPINCTRL3,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&rbtrackerFrame::OnInstVolChange);
    Connect(ID_SPINCTRL1,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&rbtrackerFrame::OnPatchChange);
    Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&rbtrackerFrame::OnInstNameTextEnter);
    Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&rbtrackerFrame::OnInstNameTextEnter);
    Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&rbtrackerFrame::OnLoopClick);
    Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&rbtrackerFrame::OnEchoClick);
    Connect(ID_SPINCTRL5,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&rbtrackerFrame::OnPitchBendChange);
    Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&rbtrackerFrame::OnADSRClick);
    Connect(ID_SPINCTRL8,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&rbtrackerFrame::OnAttackChange);
    Connect(ID_SPINCTRL9,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&rbtrackerFrame::OnAttackChange);
    Connect(ID_SPINCTRL10,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&rbtrackerFrame::OnAttackChange);
    Connect(ID_SPINCTRL7,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&rbtrackerFrame::OnAttackChange);
    Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&rbtrackerFrame::OnArpModeSelect);
    Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&rbtrackerFrame::OnSavePatchBtnClick);
    Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&rbtrackerFrame::OnLoadPatchBtnClick);
    Connect(ID_GRID1,wxEVT_GRID_CELL_LEFT_CLICK,(wxObjectEventFunction)&rbtrackerFrame::OnGrid1CellLeftClick);
    Tracks->Connect(wxEVT_KEY_DOWN,(wxObjectEventFunction)&rbtrackerFrame::OnTracksKeyDown,0,this);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&rbtrackerFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&rbtrackerFrame::OnAbout);
    //*)

    Grid->SetDefaultCellAlignment (wxALIGN_CENTER,wxALIGN_CENTER);
    for (int row = 0; row <= 63 ; row ++)
    {
        Grid->SetCellValue(row,0,wxString("--- 00 --"));
        Grid->SetCellValue(row,1,wxString("--- 00 --"));
        Grid->SetCellValue(row,2,wxString("--- 00 --"));
        if (!(row%4) && row < 63) {
            Grid->SetCellBackgroundColour(row,0,wxColor(150,150,255));
            Grid->SetCellBackgroundColour(row,1,wxColor(150,150,255));
            Grid->SetCellBackgroundColour(row,2,wxColor(150,150,255));
        }
        if (!(row%4) && row < 63-16) {
            Grid->SetCellBackgroundColour(row,0,wxColor(150,255,150));
            Grid->SetCellBackgroundColour(row,1,wxColor(150,255,150));
            Grid->SetCellBackgroundColour(row,2,wxColor(150,255,150));
        }
        if (!(row%4) && row < 63-16-16) {
            Grid->SetCellBackgroundColour(row,0,wxColor(255,150,150));
            Grid->SetCellBackgroundColour(row,1,wxColor(255,150,150));
            Grid->SetCellBackgroundColour(row,2,wxColor(255,150,150));
        }
        if (!(row%4) && row < 63-16-16-16) {
            Grid->SetCellBackgroundColour(row,0,wxColor(150,255,255));
            Grid->SetCellBackgroundColour(row,1,wxColor(150,255,255));
            Grid->SetCellBackgroundColour(row,2,wxColor(150,255,255));
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
    track[0].on = Ch1->IsChecked();
}

void rbtrackerFrame::OnCh2Click(wxCommandEvent& event)
{
    if (Ch2->IsChecked()) for (int row = 0; row <64 ; row++) Grid->SetCellTextColour(row,1,wxColor(0,0,0));
    else for (int row = 0; row <64 ; row++) Grid->SetCellTextColour(row,1,wxColor(170,170,170));
    Grid->Refresh();
    track[1].on = Ch2->IsChecked();
}

void rbtrackerFrame::OnCh3Click(wxCommandEvent& event)
{
    if (Ch3->IsChecked()) for (int row = 0; row <64 ; row++) Grid->SetCellTextColour(row,2,wxColor(0,0,0));
    else for (int row = 0; row <64 ; row++) Grid->SetCellTextColour(row,2,wxColor(170,170,170));
    Grid->Refresh();
    track[2].on = Ch3->IsChecked();
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

    if (event.ControlDown()) {
        char iKey;
        iText = event.GetUnicodeKey();
        iKey = iText[0].GetValue();
        switch (iKey) {
            case 'C':
                wxMessageBox( "Copied to clipboard", "Control-C", wxOK | wxICON_INFORMATION );
                break;
            case 'P':
                wxMessageBox( "Paste from clipboard", "Control-P", wxOK | wxICON_INFORMATION );
                break;
            default:
                return;
        }
        return;
    }


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
    playNote(num);
    if (instrument < 10) iText << " 0" << instrument;
    else iText << " " << instrument;
    if (num < 10) iText << " 0" << num;
    else iText << " " << num;
    Grid->SetCellValue(trackpos,tracknum,iText);
}

void rbtrackerFrame::playNote(uint8_t notenum)
{
    setOSC(&osc1,1,Wave->GetSelection(),Loop->IsChecked(), Echo->IsChecked(), ADSR->IsChecked(),
           notenum,InstVol->GetValue(), Attack->GetValue(), Decay->GetValue(), Sustain->GetValue()<<8,
           Release->GetValue(), MaxBend->GetValue(), BendRate->GetValue(), ArpMode->GetSelection());
}




void rbtrackerFrame::playPtn() {
    uint16_t h = samplespertick; // Initiate samples per tick counter, force first SetOsc
    uint8_t patternpos=0;
    uint8_t i=0;
    tick=3;

    // Zero all oscillators
    setOSC(&osc1,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
    setOSC(&osc2,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
    setOSC(&osc3,0,0,0,0,0,0,0,0,0,0,0,0,0,0);

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
                patch[i].maxbend, patch[i].bendrate, patch[i].arpmode );
                }
            // TRACK 2
            if (track[1].on) i = track[1].instrument[patternpos];
            else i = 0;
            if (i) {
                setOSC(&osc2,1,patch[i].wave,patch[i].loop, patch[i].echo, patch[i].adsr,
                track[1].notenumber[patternpos],patch[i].vol,
                patch[i].attack, patch[i].decay, patch[i].sustain,patch[i].release,
                patch[i].maxbend, patch[i].bendrate, patch[i].arpmode );
                }
            // TRACK 3
            if (track[2].on) i = track[2].instrument[patternpos];
            else i = 0;
            if (i) {
                setOSC(&osc3,1,patch[i].wave,patch[i].loop, patch[i].echo, patch[i].adsr,
                track[2].notenumber[patternpos],patch[i].vol,
                patch[i].attack, patch[i].decay, patch[i].sustain,patch[i].release,
                patch[i].maxbend, patch[i].bendrate, patch[i].arpmode );
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

