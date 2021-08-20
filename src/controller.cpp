#include "controller.h"

AudioController::AudioController(int device, int freq)
{
    this->device = device;
    this->freq = freq;
    this->ShowError = ShowError;

    if (!BASS_Init(device, freq, 0, 0, NULL))
        std::cout << "Error BASS_Init " << BASS_ErrorGetCode() << std::endl;
}

int AudioController::PlayStream(std::string file)
{
    // Init BASS if needed
    if (!BASS_IsStarted())
        BASS_Init(device, freq, 0, 0, NULL);

    // Create File stream
    streamHandle = BASS_StreamCreateFile(FALSE, "/home/aud/Audio/build/test.mp3", 0, 0, 0);
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

int AudioController::PauseStream()
{
    BASS_ChannelPause(this->streamHandle);
    return 0;
}

int AudioController::ResumeStream()
{
    if (BASS_ChannelIsActive(streamHandle))
    {
        BASS_Start();
    }
    return 0;
}

int AudioController::StopStream()
{
    BASS_Stop();
    BASS_ChannelFree(streamHandle);
    BASS_Free();
    return 0;
}

int AudioController::getStreamStatus()
{
    return BASS_ChannelIsActive(streamHandle);
}