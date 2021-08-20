#ifndef AUDIOCONTROLLER_H
#define AUDIOCONTROLLER_H
#include "bass.h"
#include <iostream>
#include <string>

class AudioController
{
  public:
    AudioController(int device, int freq);
    int PlayStream(std::string file);
    int PauseStream(void);
    int ResumeStream(void);
    int StopStream(void);
    int getStreamStatus(void);

  private:
    int device;
    int freq;
    HSTREAM streamHandle;
    void* ShowError;
};
#endif