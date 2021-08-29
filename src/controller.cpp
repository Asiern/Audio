/**
 * @file controller.cpp
 * @author Asiern (https://github.com/Asiern)
 * @brief Audio Controller class
 * @date 2021-08-27
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "controller.h"
#include "bass_fx.h"

/**
 * @brief Controller constructor
 * @param device Audio device
 * @param freq Audio frequency
 */
AudioController::AudioController(int device, int freq)
{
    this->device = device;
    this->freq = freq;
    this->ShowError = ShowError;

    if (!BASS_Init(device, freq, 0, 0, NULL))
        std::cout << "Error BASS_Init " << BASS_ErrorGetCode() << std::endl;
}

/**
 * @brief Destructor
 */
AudioController::~AudioController()
{
    free(ShowError);
}

/**
 * @brief Play audio file
 * @param path file path
 * @return
 */
int AudioController::PlayStream(const std::string& path)
{
    // Init BASS if needed
    if (!BASS_IsStarted())
        BASS_Init(device, freq, 0, 0, NULL);

    // Create File stream
    streamHandle = BASS_StreamCreateFile(FALSE, &path, 0, 0, 0);
    // Play stream on channel
    int channelPlay = BASS_ChannelPlay(streamHandle, FALSE);

    // Error filter
    switch (channelPlay)
    {
    case BASS_ERROR_HANDLE:
        std::cout << "Error BASS_Init " << BASS_ErrorGetCode() << std::endl;
        return streamHandle;
        break;
    case BASS_ERROR_START:
        BASS_Start();
        break;
    case BASS_ERROR_DECODE:
        std::cout << "Error BASS_Init " << BASS_ErrorGetCode() << std::endl;
        break;
    }

    return 0;
}

/**
 * @brief Pause audio stream
 * @return
 */
int AudioController::PauseStream()
{
    BASS_ChannelPause(this->streamHandle);
    return 0;
}

/**
 * @brief Resume audio stream
 * @return
 */
int AudioController::ResumeStream()
{
    if (BASS_ChannelIsActive(streamHandle))
    {
        BASS_Start();
    }
    return 0;
}

/**
 * @brief Stop audio stream
 * @return
 */
int AudioController::StopStream()
{
    BASS_Stop();
    BASS_ChannelFree(streamHandle);
    BASS_Free();
    return 0;
}

/**
 * @brief
 * @return
 */
int AudioController::getStreamStatus()
{
    return BASS_ChannelIsActive(streamHandle);
}

/**
 * @brief Increase channel pitch
 * @return
 */
int AudioController::IncreasePitch()
{
    HFX handle = BASS_ChannelSetFX(this->streamHandle, BASS_FX_BFX_PITCHSHIFT, 0);
    BASS_BFX_PITCHSHIFT params = {0.5, 0, 2048, 8, this->streamHandle};
    // BOOL value = BASS_FXSetParameters(handle, params);
    return 0;
}

/**
 * @brief Decrease channel pitch
 * @return
 */
int AudioController::DecreasePitch()
{
}