/**
 * @file audio.cpp
 * @author Asiern (https://github.com/Asiern)
 * @brief Audio Main Frame
 * @date 2021-08-27
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "audio.h"
#include "menu.h"
#include "updater.h"
#include "utils.h"
#include <wx/filedlg.h>
#include <wx/wfstream.h>

wxBEGIN_EVENT_TABLE(Audio, wxFrame) wxEND_EVENT_TABLE()

    /**
     * @brief Constructor
     */
    Audio::Audio()
    : wxFrame(NULL, wxID_ANY, "Audio", wxDefaultPosition, wxSize(800, 500))
{
    // Menu Bar
    menuBar = new Menu;
    SetMenuBar(menuBar);
    fileslbl =
        new wxStaticText(this, wxID_ANY, "Files", wxPoint(20, 25), wxSize(80, 30), wxALIGN_LEFT, wxStaticTextNameStr);
    filesListBox = new wxListCtrl(this, wxID_ANY, wxPoint(20, 50), wxSize(380, 200), wxLC_SINGLE_SEL | wxLC_LIST,
                                  wxDefaultValidator, wxListCtrlNameStr);

    Connect(wxID_OPEN, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Audio::onloadBtnPress));
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

    // Pitch controls
    pitchChoices = new wxArrayString();
    pitchChoices->Add("+8 Semitones");
    pitchChoices->Add("+7 Semitones");
    pitchChoices->Add("+6 Semitones");
    pitchChoices->Add("+5 Semitones");
    pitchChoices->Add("+4 Semitones");
    pitchChoices->Add("+3 Semitones");
    pitchChoices->Add("+2 Semitones");
    pitchChoices->Add("+1 Semitones");
    pitchChoices->Add("Original");
    pitchChoices->Add("-1 Semitones");
    pitchChoices->Add("-2 Semitones");
    pitchChoices->Add("-3 Semitones");
    pitchChoices->Add("-4 Semitones");
    pitchChoices->Add("-5 Semitones");
    pitchChoices->Add("-6 Semitones");
    pitchChoices->Add("-7 Semitones");
    pitchChoices->Add("-8 Semitones");
    pitchlbl = new wxStaticText(this, wxID_ANY, "Pitch", wxPoint(600, 25), wxSize(40, 30), 0, wxStaticTextNameStr);
    decpitchbtn =
        new wxButton(this, wxID_ANY, "-", wxPoint(500, 50), wxSize(40, 40), 0, wxDefaultValidator, wxButtonNameStr);
    decpitchbtn->Bind(wxEVT_BUTTON, &Audio::onPitchDecrease, this);
    incpitchbtn =
        new wxButton(this, wxID_ANY, "+", wxPoint(700, 50), wxSize(40, 40), 0, wxDefaultValidator, wxButtonNameStr);
    incpitchbtn->Bind(wxEVT_BUTTON, &Audio::onPitchIncrease, this);

    pitchcb = new wxComboBox(this, wxID_ANY, "", wxPoint(560, 50), wxSize(120, 40), *pitchChoices, wxCB_READONLY,
                             wxDefaultValidator, wxComboBoxNameStr);
    pitchcb->SetSelection(8);
    controller = new AudioController(-1, 44100);
}

/**
 * @brief Destructor
 */
Audio::~Audio()
{
    delete pitchChoices;
}

/**
 * @brief Load file event
 * @param evt
 * @return (void)
 */
void Audio::onloadBtnPress(wxCommandEvent& evt)
{
    wxFileDialog openFileDialog(this, _("Open audio file"), "", "", "mp3 files (*.mp3)|*.mp3",
                                wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return; // the user changed idea...

    std::string path = (std::string)openFileDialog.GetPath();
    std::string filename = getFileName(path);
    filesListBox->InsertItem(0, filename);
    files = new std::map<std::string, std::string>();
    files->insert(std::pair<std::string, std::string>(path, filename));
}

/**
 * @brief Pause event
 * @param evt
 * @return (void)
 */
void Audio::onpauseBtnPress(wxCommandEvent& evt)
{
    controller->PauseStream();
}

/**
 * @brief Play event
 * @param evt
 * @return (void)
 */
void Audio::onplayBtnPress(wxCommandEvent& evt)
{
    if (controller->getStreamStatus())
        controller->ResumeStream();
    else
        controller->PlayStream(getPath("Symphony No.6 (1st movement)"));
}

/**
 * @brief Stop event
 * @param evt
 * @return (void)
 */
void Audio::onstopBtnPress(wxCommandEvent& evt)
{
    controller->StopStream();
}

/**
 * @brief Get path from filename
 * @param filename
 * @return file path
 */
std::string Audio::getPath(const std::string& filename)
{
    std::map<std::string, std::string>::iterator it = files->begin();
    std::map<std::string, std::string>::iterator end = files->end();
    for (; it != end; it++)
    {
        if (it->second == filename)
        {
            return it->first;
        }
    }
    return "";
}

/**
 * @brief Pitch increase event
 * @param evt
 * @return (void)
 */
void Audio::onPitchIncrease(wxCommandEvent& evt)
{
    if (pitchcb->GetSelection() == 0)
        return;

    // Call controller
    int error = controller->IncreasePitch(1);

    if (error != 0)
    {
        wxMessageBox("error");
        return;
    }

    // Update UI
    pitchcb->SetSelection(pitchcb->GetSelection() - 1);
}

/**
 * @brief Pitch decrease event
 * @param evt
 * @return (void)
 */
void Audio::onPitchDecrease(wxCommandEvent& evt)
{
    if (pitchcb->GetSelection() == pitchChoices->size() - 1)
        return;

    // Call controller
    int error = controller->DecreasePitch(1);

    if (error != 0)
    {
        wxMessageBox("" + error, "Error Dialog", wxOK, this, 0, 0);
        return;
    }

    // Update UI
    pitchcb->SetSelection(pitchcb->GetSelection() + 1);
}