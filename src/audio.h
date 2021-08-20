#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "controller.h"
#include "updater.h"
#include <wx/gauge.h>
#include <wx/wx.h>

class Audio : public wxFrame
{

  private:
    AudioController* controller = nullptr;

  protected:
    wxMenuBar* menuBar = nullptr;

    wxImage* cover = nullptr;
    wxButton* loadBtn = nullptr;
    wxButton* playBtn = nullptr;
    wxButton* pauseBtn = nullptr;
    wxButton* stopBtn = nullptr;
    wxStaticText* progresslbl = nullptr;
    wxStaticText* progressEndlbl = nullptr;
    wxGauge* progress = nullptr;

    wxStaticText* fileslbl = nullptr;
    wxArrayString* files = nullptr;
    wxListBox* filesListBox = nullptr;

    // Events
    void onloadBtnPress(wxCommandEvent& evt);
    void onplayBtnPress(wxCommandEvent& evt);
    void onpauseBtnPress(wxCommandEvent& evt);
    void onstopBtnPress(wxCommandEvent& evt);
    wxDECLARE_EVENT_TABLE();

  public:
    Audio();
    ~Audio();
};

#endif