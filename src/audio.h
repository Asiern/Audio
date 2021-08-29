/**
 * @file audio.h
 * @author Asiern (https://github.com/Asiern)
 * @brief Audio Main Frame
 * @date 2021-08-27
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "controller.h"
#include "updater.h"
#include <map>
#include <wx/gauge.h>
#include <wx/listctrl.h>
#include <wx/wx.h>

/**
 * @brief Main frame class
 * @author Asiern
 * @since Fri Aug 27 2021
 */
class Audio : public wxFrame
{

  private:
    AudioController* controller = nullptr;
    std::string getPath(const std::string& filename);

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
    wxListCtrl* filesListBox = nullptr;
    std::map<std::string, std::string>* files = nullptr;

    // Audio Controls
    wxStaticText* pitchlbl = nullptr;
    wxButton* incpitchbtn = nullptr;
    wxButton* decpitchbtn = nullptr;
    wxComboBox* pitchcb = nullptr;
    wxArrayString* pitchChoices;

  protected:
    // Events
    void onloadBtnPress(wxCommandEvent& evt);
    void onplayBtnPress(wxCommandEvent& evt);
    void onpauseBtnPress(wxCommandEvent& evt);
    void onstopBtnPress(wxCommandEvent& evt);
    void onPitchIncrease(wxCommandEvent& evt);
    void onPitchDecrease(wxCommandEvent& evt);
    wxDECLARE_EVENT_TABLE();

  public:
    Audio();
    ~Audio();
};

#endif