/**
 * @file main.cpp
 * @author Asiern (https://github.com/Asiern)
 * @brief Main class
 * @date 2021-08-27
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "main.h"

#include "audio.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    Audio* mainWindow = new Audio();
    mainWindow->Show(true);

    return true;
}