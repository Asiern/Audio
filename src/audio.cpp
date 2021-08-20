#include "audio.h"
#include "menu.h"
#include "updater.h"
wxBEGIN_EVENT_TABLE(Audio, wxFrame) wxEND_EVENT_TABLE()

    Audio::Audio()
    : wxFrame(NULL, wxID_ANY, "Audio", wxDefaultPosition, wxSize(800, 500))
{
    // Menu Bar
    menuBar = new Menu;
    SetMenuBar(menuBar);
    fileslbl =
        new wxStaticText(this, wxID_ANY, "Files", wxPoint(20, 25), wxSize(80, 30), wxALIGN_LEFT, wxStaticTextNameStr);
    files = new wxArrayString();
    files->Add("FILE1");
    files->Add("FILE2");
    filesListBox = new wxListBox(this, wxID_ANY, wxPoint(20, 50), wxSize(380, 200), *files,
                                 wxLB_HSCROLL | wxLB_NEEDED_SB, wxDefaultValidator, wxListBoxNameStr);

    // this->loadBtn = new wxButton(this, wxID_ANY, "Open File(s)", wxPoint(150, 20), wxSize(120, 35), 0,
    // wxDefaultValidator, wxButtonNameStr); this->loadBtn->Bind(wxEVT_BUTTON, &Audio::onloadBtnPress, this);
    // Connect(wxID_OPEN, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Audio::onloadBtnPress));
    cover = new wxImage();
    this->playBtn = new wxButton(this, wxID_ANY, "Play", wxPoint(200, 360), wxSize(120, 30), 0, wxDefaultValidator,
                                 wxButtonNameStr);
    playBtn->Bind(wxEVT_BUTTON, &Audio::onplayBtnPress, this);
    this->pauseBtn = new wxButton(this, wxID_ANY, "Pause", wxPoint(350, 360), wxSize(120, 30), 0, wxDefaultValidator,
                                  wxButtonNameStr);
    pauseBtn->Bind(wxEVT_BUTTON, &Audio::onpauseBtnPress, this);
    this->stopBtn = new wxButton(this, wxID_ANY, "Stop", wxPoint(500, 360), wxSize(120, 30), 0, wxDefaultValidator,
                                 wxButtonNameStr);
    stopBtn->Bind(wxEVT_BUTTON, &Audio::onstopBtnPress, this);
    progresslbl =
        new wxStaticText(this, wxID_ANY, "0:00", wxPoint(150, 390), wxSize(80, 30), wxALIGN_LEFT, wxStaticTextNameStr);
    progressEndlbl =
        new wxStaticText(this, wxID_ANY, "4:07", wxPoint(650, 390), wxSize(80, 30), wxALIGN_LEFT, wxStaticTextNameStr);
    progress = new wxGauge(this, wxID_ANY, 100, wxPoint(200, 385), wxSize(430, 20), wxGA_HORIZONTAL, wxDefaultValidator,
                           wxGaugeNameStr);
    progress->SetValue(50);
    Centre();

    controller = new AudioController(-1, 44100);
}
Audio::~Audio()
{
}
void Audio::onloadBtnPress(wxCommandEvent& evt)
{
    controller->PauseStream();
    wxFileDialog openFileDialog(this, _("Open file"), "", "", "audio files (*.mp3)| *.mp3",
                                wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_MULTIPLE);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return; // the user changed idea...
}
void Audio::onpauseBtnPress(wxCommandEvent& evt)
{
    controller->PauseStream();
}
void Audio::onplayBtnPress(wxCommandEvent& evt)
{
    if (controller->getStreamStatus())
        controller->ResumeStream();
    else
        controller->PlayStream("");
}
void Audio::onstopBtnPress(wxCommandEvent& evt)
{
    controller->StopStream();
}
