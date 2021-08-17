#include "audio.h"
#include "menu.h"
#include "updater.h"
wxBEGIN_EVENT_TABLE(Audio, wxFrame) wxEND_EVENT_TABLE()

    Audio::Audio()
    : wxFrame(NULL, wxID_ANY, "Audio", wxDefaultPosition, wxSize(500, 500))
{
    // Menu Bar
    menuBar = new Menu;
    SetMenuBar(menuBar);

    this->loadBtn = new wxButton(this, wxID_ANY, "Open File(s)", wxPoint(20, 20), wxSize(20, 20), 0, wxDefaultValidator,
                                 wxButtonNameStr);
    this->loadBtn->Bind(wxEVT_BUTTON, &Audio::onloadBtnPress, this);
    Connect(wxID_OPEN, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Audio::onloadBtnPress));
    Centre();
}

Audio::~Audio()
{
}

void Audio::onloadBtnPress(wxCommandEvent& evt)
{
    wxFileDialog openFileDialog(this, _("Open file"), "", "", "audio files (*.mp3)| *.mp3",
                                wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_MULTIPLE);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return; // the user changed idea...
}
