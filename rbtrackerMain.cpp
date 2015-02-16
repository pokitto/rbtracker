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
#include <wx/icon.h>
#include "led.h"
#include "Synth.h"
#include "oscillator.h"
#include "utilities.h"

//(*InternalHeaders(rbtrackerFrame)
#include <wx/bitmap.h>
#include <wx/icon.h>
#include <wx/settings.h>
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

uint8_t ticks=0;
uint16_t period=100, instedited=1;
BLOCK clipboard[3];
int clipwidth, clipheight, cliprow = -1, clipcol = -1;

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
const long rbtrackerFrame::ID_STATICBITMAP1 = wxNewId();
const long rbtrackerFrame::ID_BUTTON5 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT13 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL18 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT19 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL15 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT6 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT15 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL13 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL14 = wxNewId();
const long rbtrackerFrame::ID_BUTTON3 = wxNewId();
const long rbtrackerFrame::ID_BUTTON4 = wxNewId();
const long rbtrackerFrame::ID_BUTTON13 = wxNewId();
const long rbtrackerFrame::ID_BUTTON6 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT18 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL4 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT11 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL17 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT22 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL16 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT16 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL20 = wxNewId();
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
const long rbtrackerFrame::ID_SPINCTRL12 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL11 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT20 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT17 = wxNewId();
const long rbtrackerFrame::ID_STATICTEXT14 = wxNewId();
const long rbtrackerFrame::ID_CHECKBOX5 = wxNewId();
const long rbtrackerFrame::ID_CHECKBOX4 = wxNewId();
const long rbtrackerFrame::ID_SPINCTRL19 = wxNewId();
const long rbtrackerFrame::ID_CHECKBOX6 = wxNewId();
const long rbtrackerFrame::ID_PANEL2 = wxNewId();
const long rbtrackerFrame::idMenuQuit = wxNewId();
const long rbtrackerFrame::idMenuAbout = wxNewId();
const long rbtrackerFrame::ID_STATUSBAR1 = wxNewId();
const long rbtrackerFrame::ID_MESSAGEDIALOG1 = wxNewId();
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
    SetClientSize(wxSize(840,680));
    SetMinSize(wxSize(-1,-1));
    SetMaxSize(wxSize(-1,-1));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DDKSHADOW));
    {
    	wxIcon FrameIcon;
    	FrameIcon.CopyFromBitmap(wxBitmap(wxImage(_T("aaa_rbticon.ico"))));
    	SetIcon(FrameIcon);
    }
    Panel1 = new wxPanel(this, ID_PANEL4, wxPoint(16,8), wxSize(306,278), wxSIMPLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL4"));
    Panel1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));
    StaticBitmap1 = new wxStaticBitmap(Panel1, ID_STATICBITMAP1, wxBitmap(wxImage(_T("rbtrackerlgreen2.png"))), wxPoint(1,0), wxDefaultSize, 0, _T("ID_STATICBITMAP1"));
    PlaySong = new wxButton(Panel1, ID_BUTTON5, _("Play SONG"), wxPoint(8,72), wxSize(100,32), 0, wxDefaultValidator, _T("ID_BUTTON5"));
    StaticText13 = new wxStaticText(Panel1, ID_STATICTEXT13, _("OCTAVE"), wxPoint(144,200), wxDefaultSize, 0, _T("ID_STATICTEXT13"));
    Octave = new wxSpinCtrl(Panel1, ID_SPINCTRL18, _T("3"), wxPoint(248,200), wxSize(49,21), 0, 0, 7, 3, _T("ID_SPINCTRL18"));
    Octave->SetValue(_T("3"));
    StaticText19 = new wxStaticText(Panel1, ID_STATICTEXT19, _("PATCHES USED"), wxPoint(144,168), wxDefaultSize, 0, _T("ID_STATICTEXT19"));
    NumInstruments = new wxSpinCtrl(Panel1, ID_SPINCTRL15, _T("5"), wxPoint(248,168), wxSize(50,21), 0, 1, 15, 5, _T("ID_SPINCTRL15"));
    NumInstruments->SetValue(_T("5"));
    StaticText4 = new wxStaticText(Panel1, ID_STATICTEXT6, _("BPM"), wxPoint(144,224), wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    StaticText15 = new wxStaticText(Panel1, ID_STATICTEXT15, _("ROW JUMPING"), wxPoint(144,248), wxDefaultSize, 0, _T("ID_STATICTEXT15"));
    RowJump = new wxSpinCtrl(Panel1, ID_SPINCTRL13, _T("0"), wxPoint(248,248), wxSize(49,21), 0, 0, 16, 0, _T("ID_SPINCTRL13"));
    RowJump->SetValue(_T("0"));
    Tempo = new wxSpinCtrl(Panel1, ID_SPINCTRL14, _T("230"), wxPoint(248,224), wxSize(49,21), 0, 1, 300, 230, _T("ID_SPINCTRL14"));
    Tempo->SetValue(_T("230"));
    SaveSongBtn = new wxButton(Panel1, ID_BUTTON3, _("SAVE AS..."), wxPoint(10,128), wxSize(100,23), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    LoadSongBtn = new wxButton(Panel1, ID_BUTTON4, _("LOAD"), wxPoint(10,160), wxSize(100,23), 0, wxDefaultValidator, _T("ID_BUTTON4"));
    NewSong = new wxButton(Panel1, ID_BUTTON13, _("NEW SONG"), wxPoint(10,208), wxSize(100,23), 0, wxDefaultValidator, _T("ID_BUTTON13"));
    ExportCSong = new wxButton(Panel1, ID_BUTTON6, _("EXPORT .C"), wxPoint(10,240), wxSize(100,23), 0, wxDefaultValidator, _T("ID_BUTTON6"));
    StaticText18 = new wxStaticText(Panel1, ID_STATICTEXT18, _("BLOCKS USED"), wxPoint(144,144), wxDefaultSize, wxALIGN_LEFT, _T("ID_STATICTEXT18"));
    NumBlocks = new wxSpinCtrl(Panel1, ID_SPINCTRL4, _T("3"), wxPoint(248,144), wxSize(49,21), 0, 1, 10, 3, _T("ID_SPINCTRL4"));
    NumBlocks->SetValue(_T("3"));
    StaticText5 = new wxStaticText(Panel1, ID_STATICTEXT11, _("SONG POSITION"), wxPoint(144,64), wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    Position = new wxSpinCtrl(Panel1, ID_SPINCTRL17, _T("0"), wxPoint(248,64), wxSize(49,21), 0, 0, 9, 0, _T("ID_SPINCTRL17"));
    Position->SetValue(_T("0"));
    StaticText17 = new wxStaticText(Panel1, ID_STATICTEXT22, _("LAST PATTERN"), wxPoint(144,88), wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT22"));
    SongLength = new wxSpinCtrl(Panel1, ID_SPINCTRL16, _T("0"), wxPoint(248,88), wxSize(49,21), 0, 0, 9, 0, _T("ID_SPINCTRL16"));
    SongLength->SetValue(_T("0"));
    StaticText16 = new wxStaticText(Panel1, ID_STATICTEXT16, _("LOOP TO"), wxPoint(144,112), wxDefaultSize, 0, _T("ID_STATICTEXT16"));
    LoopTo = new wxSpinCtrl(Panel1, ID_SPINCTRL20, _T("0"), wxPoint(248,112), wxSize(49,21), 0, -1, 9, 0, _T("ID_SPINCTRL20"));
    LoopTo->SetValue(_T("0"));
    Instrument = new wxPanel(this, ID_PANEL1, wxPoint(16,296), wxSize(306,322), wxSIMPLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL1"));
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
    StaticText2 = new wxStaticText(Instrument, ID_STATICTEXT2, _("Patch #"), wxPoint(8,8), wxSize(64,24), 0, _T("ID_STATICTEXT2"));
    StaticText3 = new wxStaticText(Instrument, ID_STATICTEXT3, _("Volume"), wxPoint(144,40), wxSize(64,16), 0, _T("ID_STATICTEXT3"));
    Pitchbendrate = new wxStaticText(Instrument, ID_STATICTEXT1, _("Pitch bend rate"), wxPoint(144,72), wxSize(87,16), 0, _T("ID_STATICTEXT1"));
    InstName = new wxTextCtrl(Instrument, ID_TEXTCTRL1, _("Patchname"), wxPoint(144,8), wxSize(152,24), wxTE_NO_VSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    InstName->SetMaxLength(20);
    Loop = new wxCheckBox(Instrument, ID_CHECKBOX1, _("Loop"), wxPoint(16,184), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    Loop->SetValue(false);
    Echo = new wxCheckBox(Instrument, ID_CHECKBOX2, _("Echo"), wxPoint(16,208), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    Echo->SetValue(false);
    StaticText12 = new wxStaticText(Instrument, ID_STATICTEXT12, _("Arp modes"), wxPoint(144,144), wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    asdff = new wxStaticText(Instrument, ID_STATICTEXT5, _("Transpose"), wxPoint(144,120), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    asdff->Disable();
    MaxBend = new wxSpinCtrl(Instrument, ID_SPINCTRL5, _T("0"), wxPoint(232,96), wxSize(64,21), 0, -6000, 6000, 0, _T("ID_SPINCTRL5"));
    MaxBend->SetValue(_T("0"));
    StaticText21 = new wxStaticText(Instrument, ID_STATICTEXT21, _("Pitch bend max"), wxPoint(144,96), wxDefaultSize, 0, _T("ID_STATICTEXT21"));
    VibRate = new wxSpinCtrl(Instrument, ID_SPINCTRL6, _T("0"), wxPoint(232,120), wxSize(64,21), 0, 0, 12, 0, _T("ID_SPINCTRL6"));
    VibRate->SetValue(_T("0"));
    VibRate->Disable();
    StaticText1 = new wxStaticText(Instrument, ID_STATICTEXT4, _("Attack"), wxPoint(144,184), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    ADSR = new wxCheckBox(Instrument, ID_CHECKBOX3, _("ADSR"), wxPoint(88,184), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
    ADSR->SetValue(false);
    Attack = new wxSpinCtrl(Instrument, ID_SPINCTRL8, _T("0"), wxPoint(232,184), wxSize(64,21), 0, 0, 255, 0, _T("ID_SPINCTRL8"));
    Attack->SetValue(_T("0"));
    Decay = new wxSpinCtrl(Instrument, ID_SPINCTRL9, _T("0"), wxPoint(232,208), wxSize(64,21), 0, 0, 255, 0, _T("ID_SPINCTRL9"));
    Decay->SetValue(_T("0"));
    Sustain = new wxSpinCtrl(Instrument, ID_SPINCTRL10, _T("0"), wxPoint(232,232), wxSize(64,21), 0, 0, 255, 0, _T("ID_SPINCTRL10"));
    Sustain->SetValue(_T("0"));
    Release = new wxSpinCtrl(Instrument, ID_SPINCTRL7, _T("0"), wxPoint(232,256), wxSize(64,21), 0, 0, 255, 0, _T("ID_SPINCTRL7"));
    Release->SetValue(_T("0"));
    StaticText9 = new wxStaticText(Instrument, ID_STATICTEXT9, _("Decay"), wxPoint(144,208), wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    StaticText10 = new wxStaticText(Instrument, ID_STATICTEXT10, _("Sustain"), wxPoint(144,232), wxDefaultSize, 0, _T("ID_STATICTEXT10"));
    StaticText8 = new wxStaticText(Instrument, ID_STATICTEXT8, _("Release"), wxPoint(144,256), wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    ArpMode = new wxChoice(Instrument, ID_CHOICE1, wxPoint(232,145), wxSize(64,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    ArpMode->SetSelection( ArpMode->Append(_("OFF")) );
    ArpMode->Append(_("M slow"));
    ArpMode->Append(_("M med"));
    ArpMode->Append(_("M fast"));
    ArpMode->Append(_("m slow"));
    ArpMode->Append(_("m med"));
    ArpMode->Append(_("m fast"));
    ArpMode->Append(_("Vib 1 slow"));
    ArpMode->Append(_("Vib 1 med"));
    ArpMode->Append(_("Vib 1 fast"));
    ArpMode->Append(_("Oct slow"));
    ArpMode->Append(_("Oct med"));
    ArpMode->Append(_("Oct fast"));
    ArpMode->Append(_("Funk slo"));
    ArpMode->Append(_("Funk med"));
    ArpMode->Append(_("Funk fast"));
    Overdrive = new wxCheckBox(Instrument, ID_CHECKBOX8, _("Distort X2"), wxPoint(16,232), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX8"));
    Overdrive->SetValue(false);
    Kick = new wxCheckBox(Instrument, ID_CHECKBOX7, _("Normalize to 50%"), wxPoint(16,256), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
    Kick->SetValue(false);
    SavePatchBtn = new wxButton(Instrument, ID_BUTTON7, _("SAVE AS..."), wxPoint(8,288), wxSize(63,23), 0, wxDefaultValidator, _T("ID_BUTTON7"));
    LoadPatchBtn = new wxButton(Instrument, ID_BUTTON8, _("LOAD"), wxPoint(80,288), wxSize(63,23), 0, wxDefaultValidator, _T("ID_BUTTON8"));
    ExportCPatch = new wxButton(Instrument, ID_BUTTON9, _("EXPORT .C"), wxPoint(152,288), wxSize(63,23), 0, wxDefaultValidator, _T("ID_BUTTON9"));
    Tracks = new wxPanel(this, ID_PANEL2, wxPoint(336,8), wxSize(480,610), wxSIMPLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    Tracks->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));
    Grid = new wxGrid(Tracks, ID_GRID1, wxPoint(4,32), wxSize(472,563), 0, _T("ID_GRID1"));
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
    Block1 = new wxSpinCtrl(Tracks, ID_SPINCTRL12, _T("0"), wxPoint(112,8), wxSize(49,21), 0, 0, 29, 0, _T("ID_SPINCTRL12"));
    Block1->SetValue(_T("0"));
    Block2 = new wxSpinCtrl(Tracks, ID_SPINCTRL11, _T("1"), wxPoint(264,8), wxSize(49,21), 0, 0, 29, 1, _T("ID_SPINCTRL11"));
    Block2->SetValue(_T("1"));
    StaticText14 = new wxStaticText(Tracks, ID_STATICTEXT20, _("Block"), wxPoint(80,8), wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT20"));
    StaticText11 = new wxStaticText(Tracks, ID_STATICTEXT17, _("Block"), wxPoint(232,8), wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT17"));
    StaticText6 = new wxStaticText(Tracks, ID_STATICTEXT14, _("Block"), wxPoint(376,8), wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT14"));
    Ch1 = new wxCheckBox(Tracks, ID_CHECKBOX5, _("ON"), wxPoint(32,16), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
    Ch1->SetValue(true);
    Ch2 = new wxCheckBox(Tracks, ID_CHECKBOX4, _("ON"), wxPoint(176,16), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
    Ch2->SetValue(true);
    Block3 = new wxSpinCtrl(Tracks, ID_SPINCTRL19, _T("2"), wxPoint(408,8), wxSize(49,21), 0, 0, 29, 2, _T("ID_SPINCTRL19"));
    Block3->SetValue(_T("2"));
    Ch3 = new wxCheckBox(Tracks, ID_CHECKBOX6, _("ON"), wxPoint(328,16), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
    Ch3->SetValue(true);
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
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -10 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    NewSongDialog = new wxMessageDialog(this, _("Wipe current song and start a new one \?"), _("New song"), wxOK|wxCANCEL, wxDefaultPosition);
    ExportPatchDialog = new wxFileDialog(this, _("Export patch as .c file"), wxEmptyString, wxEmptyString, _(".C file | *.c;"), wxFD_SAVE|wxFD_OVERWRITE_PROMPT, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    ExportSongDialog = new wxFileDialog(this, _("Export song as .C file"), wxEmptyString, wxEmptyString, _(".C file | *.c;"), wxFD_SAVE|wxFD_OVERWRITE_PROMPT, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    Center();

    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&rbtrackerFrame::OnPlaySongClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&rbtrackerFrame::OnSaveSongBtnClick);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&rbtrackerFrame::OnLoadSongBtnClick);
    Connect(ID_BUTTON13,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&rbtrackerFrame::OnNewSongClick);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&rbtrackerFrame::OnExportCSongClick);
    Connect(ID_SPINCTRL4,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&rbtrackerFrame::OnPatternChange);
    Connect(ID_SPINCTRL17,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&rbtrackerFrame::OnPositionChange);
    Connect(ID_SPINCTRL16,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&rbtrackerFrame::OnSongLengthChange);
    Connect(ID_SPINCTRL20,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&rbtrackerFrame::OnLoopToChange);
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
    Connect(ID_CHECKBOX8,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&rbtrackerFrame::OnOverdriveClick);
    Connect(ID_CHECKBOX7,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&rbtrackerFrame::OnKickClick);
    Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&rbtrackerFrame::OnSavePatchBtnClick);
    Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&rbtrackerFrame::OnLoadPatchBtnClick);
    Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&rbtrackerFrame::OnExportCPatchClick);
    Connect(ID_GRID1,wxEVT_GRID_CELL_LEFT_CLICK,(wxObjectEventFunction)&rbtrackerFrame::OnGrid1CellLeftClick);
    Connect(ID_SPINCTRL12,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&rbtrackerFrame::OnBlock1Change);
    Connect(ID_SPINCTRL11,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&rbtrackerFrame::OnBlock2Change);
    Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&rbtrackerFrame::OnCh1Click);
    Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&rbtrackerFrame::OnCh2Click);
    Connect(ID_SPINCTRL19,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&rbtrackerFrame::OnBlock3Change);
    Connect(ID_CHECKBOX6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&rbtrackerFrame::OnCh3Click);
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
            Grid->SetCellBackgroundColour(row,0,wxColor(140,220,255));
            Grid->SetCellBackgroundColour(row,1,wxColor(140,220,255));
            Grid->SetCellBackgroundColour(row,2,wxColor(140,220,255));
        }
        if (!(row%4) && row < 63-16) {
            Grid->SetCellBackgroundColour(row,0,wxColor(200,255,255));
            Grid->SetCellBackgroundColour(row,1,wxColor(200,255,255));
            Grid->SetCellBackgroundColour(row,2,wxColor(200,255,255));
        }
        if (!(row%4) && row < 63-16-16) {
            Grid->SetCellBackgroundColour(row,0,wxColor(120,255,120));
            Grid->SetCellBackgroundColour(row,1,wxColor(120,255,120));
            Grid->SetCellBackgroundColour(row,2,wxColor(120,255,120));
        }
        if (!(row%4) && row < 63-16-16-16) {
            Grid->SetCellBackgroundColour(row,0,wxColor(200,255,200));
            Grid->SetCellBackgroundColour(row,1,wxColor(200,255,200));
            Grid->SetCellBackgroundColour(row,2,wxColor(200,255,200));
        }
    }

    timer = new wxTimer(this, 1);
    Connect(wxEVT_TIMER, wxTimerEventHandler(rbtrackerFrame::OnTimer));
    initSound();
    startSound(); // sound is running all the time
    timer->Start(50);
}

rbtrackerFrame::~rbtrackerFrame()
{
    delete timer;
    //(*Destroy(rbtrackerFrame)
    //*)

}

void rbtrackerFrame::OnQuit(wxCommandEvent& event)
{
    timer->Stop();
    terminateSound();
    Close();
}

void rbtrackerFrame::OnAbout(wxCommandEvent& event)
{
    //wxString msg = wxbuildinfo(long_f);
    wxString msg="Rboy Tracker Alpha 0.03";
    wxMessageBox(msg, _("Hello World !"));
}

void rbtrackerFrame::OnTimer(wxTimerEvent& event)
{
    if (tableRefresh) {
        readBlocksToAllTracks(sequencepos);
        tableRefresh=false;
        Grid->MakeCellVisible(0,0);
    }
        if (playing) {
            Position->SetValue(sequencepos);
            if (playerpos>62) {
                    // gone over the edge of current pattern
                    Grid->MakeCellVisible(0,0);
            }
            else if (playerpos>31) {
                    Grid->MakeCellVisible(63,0);
                    Grid->MakeCellVisible(32,0);
            }
            Grid->SelectRow(playerpos-1);
            PlaySong->SetBackgroundColour(*wxGREEN);
        } else PlaySong->SetBackgroundColour(wxNullColour);
        wxString s;
            s << "Notetick: " << notetick;
            s << " Samples per tick: " << samplespertick;
            s << " Stream time: " << getStreamTime() << " First sample time: " << getFirstSampleTime();
            SetStatusText(s);

        //timer->Start(-1,wxTIMER_ONE_SHOT);
}

void rbtrackerFrame::OnPlaySongClick(wxCommandEvent& event)
{
    if (!playing) {
        long per = 1000*60; // ms per minute was 1000*60
        per /= Tempo->GetValue(); // beats per minute
        per /= 4; // 4 ticks per beat
        period = (uint16_t) per;
        samplespertick = period*57;
        samplesperpattern = samplespertick * 64;
        playerpos=0;
        sequencepos = Position->GetValue();
        playPtn();

    } else {
        // Zero all oscillators
        setOSC(&osc1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
        setOSC(&osc2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
        setOSC(&osc3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
        playing = false;
    }

}

void rbtrackerFrame::OnPauseClick(wxCommandEvent& event)
{
    playing=false;
    timer->Stop();
}

void rbtrackerFrame::OnCh1Click(wxCommandEvent& event)
{
    if (Ch1->IsChecked()) for (int row = 0; row <64 ; row++) Grid->SetCellTextColour(row,0,wxColor(0,0,0));
    else {
            for (int row = 0; row <64 ; row++) Grid->SetCellTextColour(row,0,wxColor(170,170,170));
            setOSC(&osc1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
    }
    Grid->Refresh();
    track1on = Ch1->IsChecked();
}

void rbtrackerFrame::OnCh2Click(wxCommandEvent& event)
{
    if (Ch2->IsChecked()) for (int row = 0; row <64 ; row++) Grid->SetCellTextColour(row,1,wxColor(0,0,0));
    else {
            for (int row = 0; row <64 ; row++) Grid->SetCellTextColour(row,1,wxColor(170,170,170));
            setOSC(&osc2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
    }
    Grid->Refresh();
    track2on = Ch2->IsChecked();
}

void rbtrackerFrame::OnCh3Click(wxCommandEvent& event)
{
    if (Ch3->IsChecked()) for (int row = 0; row <64 ; row++) Grid->SetCellTextColour(row,2,wxColor(0,0,0));
    else {
            for (int row = 0; row <64 ; row++) Grid->SetCellTextColour(row,2,wxColor(170,170,170));
            setOSC(&osc3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
    }
    Grid->Refresh();
    track3on = Ch3->IsChecked();
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
    if (event.GetKeyCode()==WXK_UP) {
            if (event.ControlDown()) {
                /** TRANSPOSE UP **/
                wxGridCellCoordsArray top,bottom;
                int tc,tr,bc,br;
                // Get selection coords
                top = Grid->GetSelectionBlockTopLeft();
                tc = top.Item(0).GetCol();
                tr = top.Item(0).GetRow();
                clipcol = tc;
                cliprow = tr;
                bottom = Grid->GetSelectionBlockBottomRight();
                bc = bottom.Item(0).GetCol();
                br = bottom.Item(0).GetRow();
                clipheight = br-tr;
                clipwidth = bc-tc;

                copyToClipboard(tc,tr,bc,br);
                transposeSelection(1);
                pasteFromClipboard(tracknum,trackpos);
                return;
            } else {
                Grid->MoveCursorUp(false);
                return;
            }
    }
    if (event.GetKeyCode()==WXK_DOWN) {
            if (event.ControlDown()) {
                /** TRANSPOSE DOWN **/
                wxGridCellCoordsArray top,bottom;
                int tc,tr,bc,br;
                // Get selection coords
                top = Grid->GetSelectionBlockTopLeft();
                tc = top.Item(0).GetCol();
                tr = top.Item(0).GetRow();
                clipcol = tc;
                cliprow = tr;
                bottom = Grid->GetSelectionBlockBottomRight();
                bc = bottom.Item(0).GetCol();
                br = bottom.Item(0).GetRow();
                clipheight = br-tr;
                clipwidth = bc-tc;

                copyToClipboard(tc,tr,bc,br);
                transposeSelection(-1);
                pasteFromClipboard(tracknum,trackpos);
                return;
            } else {
            Grid->MoveCursorDown(false);
            return;
            }
    }
    if (event.GetKeyCode()==WXK_PAGEUP) {
            if (event.ControlDown()) {
                /** TRANSPOSE UP OCTAVE **/
                wxGridCellCoordsArray top,bottom;
                int tc,tr,bc,br;
                // Get selection coords
                top = Grid->GetSelectionBlockTopLeft();
                tc = top.Item(0).GetCol();
                tr = top.Item(0).GetRow();
                clipcol = tc;
                cliprow = tr;
                bottom = Grid->GetSelectionBlockBottomRight();
                bc = bottom.Item(0).GetCol();
                br = bottom.Item(0).GetRow();
                clipheight = br-tr;
                clipwidth = bc-tc;

                copyToClipboard(tc,tr,bc,br);
                transposeSelection(12);
                pasteFromClipboard(tracknum,trackpos);
                return;
            } else {
                for (int t = 0; t < 16; t++) Grid->MoveCursorUp(false);
                return;
            }
    }
    if (event.GetKeyCode()==WXK_PAGEDOWN) {
            if (event.ControlDown()) {
                /** TRANSPOSE DOWN OCTAVE **/
                wxGridCellCoordsArray top,bottom;
                int tc,tr,bc,br;
                // Get selection coords
                top = Grid->GetSelectionBlockTopLeft();
                tc = top.Item(0).GetCol();
                tr = top.Item(0).GetRow();
                clipcol = tc;
                cliprow = tr;
                bottom = Grid->GetSelectionBlockBottomRight();
                bc = bottom.Item(0).GetCol();
                br = bottom.Item(0).GetRow();
                clipheight = br-tr;
                clipwidth = bc-tc;

                copyToClipboard(tc,tr,bc,br);
                transposeSelection(-12);
                pasteFromClipboard(tracknum,trackpos);
                return;
            } else {
                for (int t = 0; t < 16; t++) Grid->MoveCursorDown(false);
                return;
            }
            }
    if (event.GetKeyCode()==WXK_HOME) {
            for (int t = 0; t < 63; t++) Grid->MoveCursorUp(false);
            return; }
    if (event.GetKeyCode()==WXK_END) {
            for (int t = 0; t < 63; t++) Grid->MoveCursorDown(false);
            return; }
    if (event.ShiftDown()) {
            char iKey;
            iText = event.GetUnicodeKey();
            iKey = iText[0].GetValue();
            if (!iKey) return; // don't do anything if only shift is pressed
            }
    if (event.GetKeyCode()==WXK_BACK) {
            int tc,tr,bc,br;
            // Generate selection coords
            tc = tracknum;
            tr = trackpos;
            bc = tc;
            br = PATTERNLENGTH - 1;
            clipheight = br-tr;
            clipwidth = 0;
            copyToClipboard(tc,tr,bc,br);
            pasteFromClipboard(tc,tr-1);
            Grid->MoveCursorUp(false);
            return; }

    if (event.GetKeyCode()==WXK_INSERT) {
            int tc,tr,bc,br;
            // Generate selection coords
            tc = tracknum;
            tr = trackpos;
            bc = tc;
            br = PATTERNLENGTH - 1;
            clipheight = br-tr;
            clipwidth = 0;
            copyToClipboard(tc,tr,bc,br);
            pasteFromClipboard(tc,tr+1);
            Grid->MoveCursorDown(false);
            return; }

    if (event.ControlDown()) {
        char iKey;
        iText = event.GetUnicodeKey();
        iKey = iText[0].GetValue();
        wxGridCellCoordsArray top,bottom;
        int tc,tr,bc,br;

        switch (iKey) {
            case 'C':

                // Get selection coords
                top = Grid->GetSelectionBlockTopLeft();
                tc = top.Item(0).GetCol();
                tr = top.Item(0).GetRow();
                clipcol = tc;
                cliprow = tr;
                bottom = Grid->GetSelectionBlockBottomRight();
                bc = bottom.Item(0).GetCol();
                br = bottom.Item(0).GetRow();
                clipheight = br-tr;
                clipwidth = bc-tc;

                copyToClipboard(tc,tr,bc,br);
                wxMessageBox( "Copied to clipboard", "Control-C", wxOK | wxICON_INFORMATION );
                break;
            case 'V':
                if (cliprow == -1 || clipcol == -1) {
                    wxMessageBox( "Clipboard is empty", "Control-V", wxOK | wxICON_INFORMATION );
                    return;
                }
                pasteFromClipboard(tracknum,trackpos);
                wxMessageBox( "Paste from clipboard", "Control-V", wxOK | wxICON_INFORMATION );
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
        if (playing) return;
        iText = "--- 00 --";
        Grid->SetCellValue(trackpos,tracknum,iText);
        uint8_t blocknum;
        blocknum = song.block_sequence[tracknum][sequencepos];
        block[blocknum].notenumber[trackpos] = 255;
        block[blocknum].instrument[trackpos] = 0;
        for (uint8_t z = 0; z<RowJump->GetValue(); z++) Grid->MoveCursorDown(false);
        return;
    }
    if (!playing ) {
        // play and record note
        uint8_t blocknum;
        blocknum = song.block_sequence[tracknum][sequencepos];
        block[blocknum].notenumber[trackpos] = num;
        block[blocknum].instrument[trackpos] = instrument;
        playNote(num);
        if (instrument < 10) iText << " 0" << instrument;
        else iText << " " << instrument;
        if (num < 10) iText << " 0" << num;
        else iText << " " << num;
        Grid->SetCellValue(trackpos,tracknum,iText);
        for (uint8_t z = 0; z<RowJump->GetValue(); z++) Grid->MoveCursorDown(false);
    } else {
        // play and record note
        playNote(num);
    }
}

void rbtrackerFrame::playNote(uint8_t notenum)
{
    uint8_t tracknum = Grid->GetCursorColumn();
    if (tracknum == 0){
        setOSC(&osc1,1,Wave->GetSelection(),Loop->IsChecked(), Echo->IsChecked(), ADSR->IsChecked(),
           notenum,InstVol->GetValue(), Attack->GetValue(), Decay->GetValue(), Sustain->GetValue()<<8,
           Release->GetValue(), MaxBend->GetValue(), BendRate->GetValue(), ArpMode->GetSelection(), Overdrive->GetValue(), Kick->GetValue());
    } else if (tracknum == 1){
        setOSC(&osc2,1,Wave->GetSelection(),Loop->IsChecked(), Echo->IsChecked(), ADSR->IsChecked(),
           notenum,InstVol->GetValue(), Attack->GetValue(), Decay->GetValue(), Sustain->GetValue()<<8,
           Release->GetValue(), MaxBend->GetValue(), BendRate->GetValue(), ArpMode->GetSelection(), Overdrive->GetValue(), Kick->GetValue());
    } else {
        setOSC(&osc3,1,Wave->GetSelection(),Loop->IsChecked(), Echo->IsChecked(), ADSR->IsChecked(),
           notenum,InstVol->GetValue(), Attack->GetValue(), Decay->GetValue(), Sustain->GetValue()<<8,
           Release->GetValue(), MaxBend->GetValue(), BendRate->GetValue(), ArpMode->GetSelection(), Overdrive->GetValue(), Kick->GetValue());
    }
}

void rbtrackerFrame::playPtn() {
    notetick = samplespertick; // Initiate samples per tick counter, force first SetOsc
    tick=3;

    // Zero all oscillators
    setOSC(&osc1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
    setOSC(&osc2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
    setOSC(&osc3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
    // Put stream memory pointers in place
    initStreams(sequencepos);
    playing=true;
    Grid->MakeCellVisible(0,0);
}






void rbtrackerFrame::OnNewSongClick(wxCommandEvent& event)
{
    setOSC(&osc1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
    setOSC(&osc2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
    setOSC(&osc3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
    playing=false;
    int dlg=NewSongDialog->ShowModal();
    if (dlg == wxID_OK)
    {
        emptySong();
        emptyOscillators();
        emptyBlocks();
        emptyPatches();
    }
    playerpos=0; sequencepos =0;
    for (int row =0; row<PATTERNLENGTH; row++) {
        Grid->SetCellValue(row,0,wxString("--- 00 --"));
        Grid->SetCellValue(row,1,wxString("--- 00 --"));
        Grid->SetCellValue(row,2,wxString("--- 00 --"));
    }
    Grid->SelectRow(0,false);

}
