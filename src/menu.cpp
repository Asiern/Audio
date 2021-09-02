/**
 * @file menu.cpp
 * @author Asiern (https://github.com/Asiern)
 * @brief
 * @date 2021-08-27
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "menu.h"

#include "updater.h"
#include "utils.h"
#include <curl/curl.h>
#include <wx/aboutdlg.h>
wxBEGIN_EVENT_TABLE(Menu, wxMenuBar) wxEND_EVENT_TABLE()

    Menu::Menu(Audio* parent)
    : wxMenuBar()
{
    this->parent = parent;
    file = new wxMenu;
    help = new wxMenu;
    int ID_Open_Files = wxNewId();
    int ID_Check_for_Updates = wxNewId();
    int ID_Documentation = wxNewId();
    int ID_Release_Notes = wxNewId();
    file->Append(wxID_OPEN, wxT("&Open File"));
    file->Append(ID_Open_Files, wxT("&Open Files"));
    file->Append(wxID_EXIT, wxT("&Quit"));
    help->Append(ID_Documentation, wxT("&Documentation"));
    help->Append(ID_Release_Notes, wxT("&Release Notes"));
    help->Append(ID_Check_for_Updates, wxT("&Check for Updates..."));
    help->Append(wxID_ABOUT, wxT("&About"));
    Append(file, wxT("&File"));
    Append(help, wxT("&Help"));
    Connect(wxID_OPEN, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Menu::onOpenFile));
    Connect(ID_Open_Files, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Menu::onOpenFiles));
    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Menu::onQuit));
    Connect(ID_Release_Notes, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Menu::onReleaseNotes));
    Connect(ID_Documentation, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Menu::onDocumentation));
    Connect(wxID_ABOUT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Menu::onAbout));
    Connect(ID_Check_for_Updates, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Menu::onCheckForUpdates));
}

/**
 * @brief Destructor
 */
Menu::~Menu()
{
}

/**
 * @brief Open audio file event
 * @param evt
 * @return (void)
 */
void Menu::onOpenFile(wxCommandEvent& WXUNUSED(evt))
{
    wxFileDialog openFileDialog(this, _("Open audio file"), "", "", "mp3 wav files (*.mp3;*.wav)|*.mp3;*.wav",
                                wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return; // the user changed idea...

    std::string path = (std::string)openFileDialog.GetPath();
    parent->loadFile(path, true);
}
/**
 * @brief Open audio files event
 * @param evt
 * @return (void)
 */
void Menu::onOpenFiles(wxCommandEvent& WXUNUSED(evt))
{
    wxFileDialog openFileDialog(this, _("Open audio files"), "", "", "mp3 wav files (*.mp3;*.wav)|*.mp3;*.wav",
                                wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_MULTIPLE);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return; // the user changed idea...

    wxArrayString paths;
    openFileDialog.GetPaths(paths);
    for (wxString path : paths)
        parent->loadFile((std::string)path, false);
}

/**
 * @brief On quit event
 * @param evt
 * @return (void)
 */
void Menu::onQuit(wxCommandEvent& WXUNUSED(evt))
{
    this->m_parent->Close(true);
}

/**
 * @brief About event
 * @param evt
 * @return (void)
 */
void Menu::onAbout(wxCommandEvent& WXUNUSED(evt))
{
    wxAboutDialogInfo info;

    // About
    info.SetName(_("Audio"));
    info.SetVersion(_("1.0.0"));
    info.SetWebSite(_("https://asiern.github.io/Audio/"));

    // Credits
    wxArrayString developers = wxArrayString();
    developers.Add("Asiern", 1);
    info.SetDevelopers(developers);

    // License
    info.SetLicence(_("MIT"));

    // Show About
    wxAboutBox(info, this);
}

/**
 * @brief Check for updated event
 * @param evt
 * @return (void)
 */
void Menu::onCheckForUpdates(wxCommandEvent& WXUNUSED(evt))
{
    // Request Headers
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "User-Agent: product/1");
    headers = curl_slist_append(headers, "Accept: application/vnd.github.v3+json");

    // Updater
    Updater* updater = new Updater("https://api.github.com/repos/asiern/Audio/releases/latest", headers);
    if (updater->compareVersions(updater->getLatestVersion(), "1.0.0") > 0)
    {
        if (wxMessageBox("Newer version avaliable. Click on YES to download "
                         "the new version.",
                         "Updater", wxICON_INFORMATION | wxYES_NO, this, 0, 0) == wxYES)
        {
            system("xdg-open https://github.com/Asiern/Audio/releases/latest");
        }
    }
    else
    {
        wxMessageBox("No updates avaliable", "Updater", wxICON_INFORMATION | wxOK, this, 0, 0);
    }
    free(updater);
    free(headers);
}

/**
 * @brief Open documentation event
 * @param evt
 * @return (void)
 */
void Menu::onDocumentation(wxCommandEvent& WXUNUSED(evt))
{
    openWebLink("https://asiern.github.io/Audio/");
}

/**
 * @brief Open Release Notes event
 * @param evt
 * @return (void)
 */
void Menu::onReleaseNotes(wxCommandEvent& WXUNUSED(evt))
{
    openWebLink("https://github.com/Asiern/Audio/blob/master/CHANGELOG.md");
}