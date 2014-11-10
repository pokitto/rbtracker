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

//(*InternalHeaders(rbtrackerFrame)
#include <wx/settings.h>
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

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
const long rbtrackerFrame::ID_SPINCTRL2 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL3 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL1 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT2 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT3 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT1 = wxNewId();
const long rbtrackerFrame::ID_TEXTCTRL1 = wxNewId();
const long rbtrackerFrame::ID_RADIOBOX1 = wxNewId();
const long rbtrackerFrame::ID_CHECKBOX1 = wxNewId();
const long rbtrackerFrame::ID_CHECKBOX2 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL11 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL12 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL4 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT11 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT12 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT4 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT5 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL5 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT6 = wxNewId();
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
const long rbtrackerFrame::ID_PANEL1 = wxNewId();
const long rbtrackerFrame::ID_GRID1 = wxNewId();
const long rbtrackerFrame::ID_PANEL2 = wxNewId();
const long rbtrackerFrame::ID_TEXTCTRL2 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT14 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT17 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT15 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL15 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL16 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL14 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT16 = wxNewId();
const long rbtrackerFrame::ID_BUTTON6 = wxNewId();
const long rbtrackerFrame::ID_BUTTON8 = wxNewId();
const long rbtrackerFrame::ID_BUTTON7 = wxNewId();
const long rbtrackerFrame::ID_BUTTON4 = wxNewId();
const long rbtrackerFrame::ID_PANEL3 = wxNewId();
const long rbtrackerFrame::ID_BUTTON5 = wxNewId();
const long rbtrackerFrame::ID_BUTTON2 = wxNewId();
const long rbtrackerFrame::ID_BUTTON3 = wxNewId();
const long rbtrackerFrame::ID_BUTTON1 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT18 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT13 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL17 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL13 = wxNewId();
const long rbtrackerFrame::ID_CHECKBOX5 = wxNewId();
const long rbtrackerFrame::ID_CHECKBOX6 = wxNewId();
const long rbtrackerFrame::ID_CHECKBOX4 = wxNewId();
const long rbtrackerFrame::ID_PANEL4 = wxNewId();
const long rbtrackerFrame::idMenuQuit = wxNewId();
const long rbtrackerFrame::idMenuAbout = wxNewId();
const long rbtrackerFrame::ID_STATUSBAR1 = wxNewId();
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
    Instrument = new wxPanel(this, ID_PANEL1, wxPoint(8,288), wxSize(304,296), wxSIMPLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    Instrument->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));
    InstTune = new wxSpinCtrl(Instrument, ID_SPINCTRL2, _T("0"), wxPoint(232,72), wxSize(64,21), 0, -10, 10, 0, _T("ID_SPINCTRL2"));
    InstTune->SetValue(_T("0"));
    InstVol = new wxSpinCtrl(Instrument, ID_SPINCTRL3, _T("127"), wxPoint(232,40), wxSize(64,21), 0, 0, 255, 127, _T("ID_SPINCTRL3"));
    InstVol->SetValue(_T("127"));
    InstNum = new wxSpinCtrl(Instrument, ID_SPINCTRL1, _T("1"), wxPoint(80,8), wxSize(56,21), 0, 1, 15, 1, _T("ID_SPINCTRL1"));
    InstNum->SetValue(_T("1"));
    StaticText2 = new wxStaticText(Instrument, ID_STATICTEXT2, _("Instrument"), wxPoint(8,8), wxSize(64,24), 0, _T("ID_STATICTEXT2"));
    StaticText3 = new wxStaticText(Instrument, ID_STATICTEXT3, _("Volume"), wxPoint(144,40), wxSize(64,16), 0, _T("ID_STATICTEXT3"));
    StaticText1 = new wxStaticText(Instrument, ID_STATICTEXT1, _("Tuning"), wxPoint(144,72), wxSize(64,16), 0, _T("ID_STATICTEXT1"));
    InstName = new wxTextCtrl(Instrument, ID_TEXTCTRL1, _("Description"), wxPoint(144,8), wxSize(152,24), wxTE_NO_VSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    InstName->SetMaxLength(20);
    wxString __wxRadioBoxChoices_1[4] =
    {
    	_("SQUARE"),
    	_("SAW"),
    	_("TRIANGLE"),
    	_("NOISE")
    };
    Wave = new wxRadioBox(Instrument, ID_RADIOBOX1, _("Wave type"), wxPoint(8,40), wxSize(128,101), 4, __wxRadioBoxChoices_1, 1, 0, wxDefaultValidator, _T("ID_RADIOBOX1"));
    Loop = new wxCheckBox(Instrument, ID_CHECKBOX1, _("Loop"), wxPoint(16,152), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    Loop->SetValue(false);
    Echo = new wxCheckBox(Instrument, ID_CHECKBOX2, _("Echo"), wxPoint(104,152), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    Echo->SetValue(false);
    VibAmount = new wxSpinCtrl(Instrument, ID_SPINCTRL11, _T("0"), wxPoint(96,208), wxSize(64,21), 0, 0, 255, 0, _T("ID_SPINCTRL11"));
    VibAmount->SetValue(_T("0"));
    Arp1 = new wxSpinCtrl(Instrument, ID_SPINCTRL12, _T("0"), wxPoint(96,232), wxSize(64,21), 0, -10, 10, 0, _T("ID_SPINCTRL12"));
    Arp1->SetValue(_T("0"));
    Arp2 = new wxSpinCtrl(Instrument, ID_SPINCTRL4, _T("0"), wxPoint(96,256), wxSize(64,21), 0, -10, 10, 0, _T("ID_SPINCTRL4"));
    Arp2->SetValue(_T("0"));
    StaticText11 = new wxStaticText(Instrument, ID_STATICTEXT11, _("Vibrato amount"), wxPoint(16,208), wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    StaticText12 = new wxStaticText(Instrument, ID_STATICTEXT12, _("Arpeggio 1"), wxPoint(16,232), wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    StaticText4 = new wxStaticText(Instrument, ID_STATICTEXT4, _("Arpeggio 2"), wxPoint(16,256), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    StaticText5 = new wxStaticText(Instrument, ID_STATICTEXT5, _("Vibrato speed"), wxPoint(16,184), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    InstBend = new wxSpinCtrl(Instrument, ID_SPINCTRL5, _T("0"), wxPoint(232,104), wxSize(64,21), 0, -127, 127, 0, _T("ID_SPINCTRL5"));
    InstBend->SetValue(_T("0"));
    StaticText6 = new wxStaticText(Instrument, ID_STATICTEXT6, _("Pitch bend"), wxPoint(144,104), wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    VibSpeed = new wxSpinCtrl(Instrument, ID_SPINCTRL6, _T("0"), wxPoint(96,184), wxSize(64,21), 0, 0, 255, 0, _T("ID_SPINCTRL6"));
    VibSpeed->SetValue(_T("0"));
    StaticText7 = new wxStaticText(Instrument, ID_STATICTEXT7, _("Attack"), wxPoint(184,184), wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    ADSR = new wxCheckBox(Instrument, ID_CHECKBOX3, _("ADSR"), wxPoint(184,152), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
    ADSR->SetValue(false);
    Attack = new wxSpinCtrl(Instrument, ID_SPINCTRL8, _T("0"), wxPoint(232,184), wxSize(64,21), 0, 0, 255, 0, _T("ID_SPINCTRL8"));
    Attack->SetValue(_T("0"));
    Decay = new wxSpinCtrl(Instrument, ID_SPINCTRL9, _T("0"), wxPoint(232,208), wxSize(64,21), 0, 0, 255, 0, _T("ID_SPINCTRL9"));
    Decay->SetValue(_T("0"));
    Sustain = new wxSpinCtrl(Instrument, ID_SPINCTRL10, _T("0"), wxPoint(232,232), wxSize(64,21), 0, 0, 255, 0, _T("ID_SPINCTRL10"));
    Sustain->SetValue(_T("0"));
    Release = new wxSpinCtrl(Instrument, ID_SPINCTRL7, _T("0"), wxPoint(232,256), wxSize(64,21), 0, 0, 255, 0, _T("ID_SPINCTRL7"));
    Release->SetValue(_T("0"));
    StaticText9 = new wxStaticText(Instrument, ID_STATICTEXT9, _("Decay"), wxPoint(184,208), wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    StaticText10 = new wxStaticText(Instrument, ID_STATICTEXT10, _("Sustain"), wxPoint(184,232), wxDefaultSize, 0, _T("ID_STATICTEXT10"));
    StaticText8 = new wxStaticText(Instrument, ID_STATICTEXT8, _("Release"), wxPoint(184,256), wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    Test = new wxButton(Instrument, ID_BUTTON9, _("TEST"), wxPoint(244,148), wxSize(47,23), 0, wxDefaultValidator, _T("ID_BUTTON9"));
    Tracks = new wxPanel(this, ID_PANEL2, wxPoint(328,8), wxSize(480,576), wxSIMPLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    Grid = new wxGrid(Tracks, ID_GRID1, wxPoint(0,0), wxSize(472,575), 0, _T("ID_GRID1"));
    Grid->CreateGrid(64,3);
    wxFont GridFont(10,wxTELETYPE,wxFONTSTYLE_NORMAL,wxNORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    Grid->SetFont(GridFont);
    Grid->EnableEditing(false);
    Grid->EnableGridLines(true);
    Grid->SetColLabelSize(17);
    Grid->SetRowLabelSize(30);
    Grid->SetDefaultRowSize(17, true);
    Grid->SetDefaultColSize(140, true);
    wxFont GridLabelFont_1(10,wxTELETYPE,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    Grid->SetLabelFont(GridLabelFont_1);
    Grid->SetColLabelValue(0, _("Channel 1"));
    Grid->SetColLabelValue(1, _("Channel 2"));
    Grid->SetColLabelValue(2, _("Channel 3"));
    Grid->SetCellValue(0, 0, _("--- 00"));
    Grid->SetDefaultCellFont( Grid->GetFont() );
    Grid->SetDefaultCellTextColour( Grid->GetForegroundColour() );
    Control = new wxPanel(this, ID_PANEL3, wxPoint(8,136), wxSize(304,144), wxSIMPLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    Control->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));
    SongName = new wxTextCtrl(Control, ID_TEXTCTRL2, _("Song name"), wxPoint(64,8), wxSize(232,24), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    SongName->SetMaxLength(20);
    StaticText14 = new wxStaticText(Control, ID_STATICTEXT14, _("SONG"), wxPoint(8,8), wxDefaultSize, 0, _T("ID_STATICTEXT14"));
    StaticText17 = new wxStaticText(Control, ID_STATICTEXT17, _("Instruments"), wxPoint(8,40), wxDefaultSize, 0, _T("ID_STATICTEXT17"));
    StaticText15 = new wxStaticText(Control, ID_STATICTEXT15, _("Tempo"), wxPoint(176,64), wxDefaultSize, 0, _T("ID_STATICTEXT15"));
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
    Panel1 = new wxPanel(this, ID_PANEL4, wxPoint(8,8), wxSize(304,120), wxSIMPLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL4"));
    Panel1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));
    PlaySong = new wxButton(Panel1, ID_BUTTON5, _("Play SONG"), wxPoint(8,8), wxSize(71,23), 0, wxDefaultValidator, _T("ID_BUTTON5"));
    PlayPattern = new wxButton(Panel1, ID_BUTTON2, _("Play PTN"), wxPoint(88,8), wxSize(71,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    Rewind = new wxButton(Panel1, ID_BUTTON3, _("REWIND"), wxPoint(88,40), wxSize(71,23), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    Pause = new wxButton(Panel1, ID_BUTTON1, _("PAUSE"), wxPoint(8,40), wxSize(71,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    StaticText18 = new wxStaticText(Panel1, ID_STATICTEXT18, _("PATTERN"), wxPoint(176,8), wxDefaultSize, 0, _T("ID_STATICTEXT18"));
    StaticText13 = new wxStaticText(Panel1, ID_STATICTEXT13, _("POSITION"), wxPoint(176,40), wxDefaultSize, 0, _T("ID_STATICTEXT13"));
    Position = new wxSpinCtrl(Panel1, ID_SPINCTRL17, _T("1"), wxPoint(240,40), wxSize(49,21), 0, 1, 64, 1, _T("ID_SPINCTRL17"));
    Position->SetValue(_T("1"));
    Pattern = new wxSpinCtrl(Panel1, ID_SPINCTRL13, _T("1"), wxPoint(240,8), wxSize(49,21), 0, 1, 10, 1, _T("ID_SPINCTRL13"));
    Pattern->SetValue(_T("1"));
    Ch1 = new wxCheckBox(Panel1, ID_CHECKBOX5, _("CHANNEL 1"), wxPoint(16,88), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
    Ch1->SetValue(true);
    Ch3 = new wxCheckBox(Panel1, ID_CHECKBOX6, _("CHANNEL 3"), wxPoint(208,88), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
    Ch3->SetValue(true);
    Ch2 = new wxCheckBox(Panel1, ID_CHECKBOX4, _("CHANNEL 2"), wxPoint(112,88), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
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
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    Center();

    Connect(ID_GRID1,wxEVT_GRID_CELL_LEFT_CLICK,(wxObjectEventFunction)&rbtrackerFrame::OnGrid1CellLeftClick);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&rbtrackerFrame::OnPlaySongClick);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&rbtrackerFrame::OnPauseClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&rbtrackerFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&rbtrackerFrame::OnAbout);
    //*)

    Grid->SetDefaultCellAlignment (wxALIGN_CENTER,wxALIGN_CENTER);
    for (int row = 0; row <= 63 ; row ++)
    {
        Grid->SetCellValue(row,0,wxString("--- 00"));
        Grid->SetCellValue(row,1,wxString("--- 00"));
        Grid->SetCellValue(row,2,wxString("--- 00"));
    }

    timer = new wxTimer(this, 1);
    Connect(wxEVT_TIMER, wxTimerEventHandler(rbtrackerFrame::OnTimer));
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

void rbtrackerFrame::OnGrid1CellLeftClick(wxGridEvent& event)
{
}

void rbtrackerFrame::OnTimer(wxTimerEvent& event)
{
    int p = Position->GetValue();
    p++;
    if (p>64) p=1;
    Position->SetValue(p);
    Grid->MakeCellVisible(p-1,0);
    Grid->SelectRow(p-1);
}

void rbtrackerFrame::OnPlaySongClick(wxCommandEvent& event)
{
    long period = 1000*60; // ms per minute
    period /= Tempo->GetValue(); // beats per minute
    period /= 4; // 4 ticks per beat
    timer->Start(period); // 1000 ms * 60 (for minute) / tempo in BPM / 4 (4 ticks per bar)
}

void rbtrackerFrame::OnPauseClick(wxCommandEvent& event)
{
    timer->Stop();
}
