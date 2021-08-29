/**
 * @file controller.h
 * @author Asiern (https://github.com/Asiern)
 * @brief Audio Controller class
 * @date 2021-08-27
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef AUDIOCONTROLLER_H
#define AUDIOCONTROLLER_H
#include "bass.h"
#include <iostream>
#include <string>

/**
 * @brief BASS controller
 * @author Asiern
 * @since Fri Aug 27 2021
 */
class AudioController
{
  public:
    AudioController(int device, int freq);
    ~AudioController();
    int PlayStream(const std::string& file);
    int PauseStream(void);
    int ResumeStream(void);
    int StopStream(void);
    int getStreamStatus(void);
    int IncreasePitch(void);
    int DecreasePitch(void);

  private:
    int device;
    int freq;
    HSTREAM streamHandle;
    void* ShowError;
};
#endif