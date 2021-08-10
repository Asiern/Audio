#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <wx/wx.h>

class Audio : public wxFrame
{
protected:
    wxMenuBar *menuBar = nullptr;
    wxMenu *file = nullptr;
    wxMenu *help = nullptr;
    wxButton *loadBtn = nullptr;

    //Events
    void onloadBtnPress(wxCommandEvent &evt);
    void onQuit(wxCommandEvent &evt);
    void onAbout(wxCommandEvent &evt);
    void onCheckForUpdates(wxCommandEvent &evt);
    wxDECLARE_EVENT_TABLE();

public:
    Audio();
    ~Audio();
};

#endif