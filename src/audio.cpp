#include "audio.h"

Audio::Audio(const wxString &title, int width, int height) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(width, height))
{
    Centre();
}