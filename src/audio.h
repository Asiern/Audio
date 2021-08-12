#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <wx/wx.h>

class Audio : public wxFrame
{

protected:
    wxMenuBar *menuBar = nullptr;

    wxButton *loadBtn = nullptr;

    //Events
    void onloadBtnPress(wxCommandEvent &evt);
    wxDECLARE_EVENT_TABLE();

public:
    Audio();
    ~Audio();
};

#endif