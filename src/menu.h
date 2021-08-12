#ifndef MENU_H
#define MENU_H
#include <wx/wx.h>
class Menu : public wxMenuBar
{
private:
    wxMenu *file = nullptr;
    wxMenu *help = nullptr;

protected:
    void onQuit(wxCommandEvent &evt);
    void onAbout(wxCommandEvent &evt);
    void onCheckForUpdates(wxCommandEvent &evt);
    wxDECLARE_EVENT_TABLE();

public:
    Menu();
};

#endif