#include "audio.h"
#include <curl/curl.h>

wxBEGIN_EVENT_TABLE(Audio, wxFrame)
    wxEND_EVENT_TABLE()

        Audio::Audio() : wxFrame(NULL, wxID_ANY, "Audio", wxDefaultPosition, wxSize(500, 500))
{
    // Menu Bar
    menuBar = new wxMenuBar;
    file = new wxMenu;
    help = new wxMenu;
    file->Append(wxID_OPEN, wxT("&Open File(s)"));
    file->Append(wxID_EXIT, wxT("&Quit"));
    int ID_Check_for_Updates = wxNewId();
    help->Append(ID_Check_for_Updates, wxT("&Check for Updates..."));
    help->Append(wxID_ABOUT, wxT("&About"));
    menuBar->Append(file, wxT("&File"));
    menuBar->Append(help, wxT("&Help"));
    Connect(wxID_OPEN, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Audio::onloadBtnPress));
    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Audio::onQuit));
    Connect(wxID_ABOUT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Audio::onAbout));
    Connect(ID_Check_for_Updates, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Audio::onCheckForUpdates));
    SetMenuBar(menuBar);

    this->loadBtn = new wxButton(this, wxID_ANY, "Open File(s)", wxPoint(20, 20), wxSize(20, 20), 0, wxDefaultValidator, wxButtonNameStr);
    this->loadBtn->Bind(wxEVT_BUTTON, &Audio::onloadBtnPress, this);
    Centre();
}

Audio::~Audio()
{
}

void Audio::onloadBtnPress(wxCommandEvent &evt)
{
    wxFileDialog openFileDialog(this, _("Open file"), "", "", "audio files (*.mp3)| *.mp3", wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_MULTIPLE);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return; // the user changed idea...
}

void Audio::onQuit(wxCommandEvent &evt)
{
    Close(true);
}

void Audio::onAbout(wxCommandEvent &evt)
{
    system("xdg-open https://github.com/Asiern/Audio");
}

void Audio::onCheckForUpdates(wxCommandEvent &evt)
{
    CURL *curl = curl_easy_init();
    CURLcode res;

    if (curl)
    {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "User-Agent: product/1");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.github.com/repos/asiern/nierhook/releases/latest");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            curl_easy_cleanup(curl);
            return;
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}
