#include "menu.h"
#include "updater.h"
#include <curl/curl.h>
wxBEGIN_EVENT_TABLE(Menu, wxMenuBar)
wxEND_EVENT_TABLE()

Menu::Menu() : wxMenuBar()
{
    file = new wxMenu;
    help = new wxMenu;
    file->Append(wxID_OPEN, wxT("&Open File(s)"));
    file->Append(wxID_EXIT, wxT("&Quit"));
    int ID_Check_for_Updates = wxNewId();
    help->Append(ID_Check_for_Updates, wxT("&Check for Updates..."));
    help->Append(wxID_ABOUT, wxT("&About"));
    Append(file, wxT("&File"));
    Append(help, wxT("&Help"));
    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Menu::onQuit));
    Connect(wxID_ABOUT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Menu::onAbout));
    Connect(ID_Check_for_Updates, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Menu::onCheckForUpdates));
}

void Menu::onQuit(wxCommandEvent &evt)
{
    Close(true);
}

void Menu::onAbout(wxCommandEvent &evt)
{
    system("xdg-open https://github.com/Asiern/Audio");
}

void Menu::onCheckForUpdates(wxCommandEvent &evt)
{
    // Request Headers
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "User-Agent: product/1");
    headers = curl_slist_append(headers, "Accept: application/vnd.github.v3+json");
    
    // Updater
    Updater *updater = new Updater("https://api.github.com/repos/asiern/Audio/releases/latest", headers);
    if (updater->compareVersions(updater->getLatestVersion(), "1.0.0") > 0)
    {
        if (wxMessageBox("Newer version avaliable. Click on YES to download the new version.", "Updater", wxICON_INFORMATION | wxYES_NO, this, 0, 0) == wxYES)
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