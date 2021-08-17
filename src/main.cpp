#include "main.h"

#include "audio.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    Audio* mainWindow = new Audio();
    mainWindow->Show(true);

    return true;
}