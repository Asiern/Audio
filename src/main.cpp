#include "main.h"
#include "audio.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
  Audio *mainWindow = new Audio(wxT("Audio"), 640, 480);
  mainWindow->Show(true);

  return true;
}