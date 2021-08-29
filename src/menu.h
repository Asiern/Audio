/**
 * @file menu.h
 * @author Asiern (https://github.com/Asiern)
 * @brief
 * @date 2021-08-27
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef MENU_H
#define MENU_H

#include <wx/wx.h>

/**
 * @brief Menu bar
 * @author Asiern
 * @since Fri Aug 27 2021
 */
class Menu : public wxMenuBar
{
  private:
    wxMenu* file = nullptr;
    wxMenu* help = nullptr;

  protected:
    void onQuit(wxCommandEvent& evt);
    void onAbout(wxCommandEvent& evt);
    void onCheckForUpdates(wxCommandEvent& evt);
    wxDECLARE_EVENT_TABLE();

  public:
    Menu();
};

#endif