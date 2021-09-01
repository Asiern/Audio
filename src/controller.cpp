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

    // BASS initialization
    if (!BASS_Init(device, freq, 0, 0, NULL))
        std::cout << "Error BASS_Init " << BASS_ErrorGetCode() << std::endl;

    // BASS FX initialization
    if (HIWORD(BASS_FX_GetVersion()) != BASSVERSION)
        std::cout << "Incorrect BASS FX version loaded" << std::endl;
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
 * @return If no error occurred 0 is returned, else -1 is returned
 */
int AudioController::PlayStream(const std::string& path)
{
    // Init BASS if needed
    if (!BASS_IsStarted())
        BASS_Init(device, freq, 0, 0, NULL);

    // Create File stream
    BASS_ChannelFree(streamHandle);
    streamHandle = BASS_StreamCreateFile(FALSE, path.c_str(), 0, 0, 0);
    // Play stream on channel
    if (BASS_ChannelPlay(streamHandle, FALSE))
        return 0;
    return -1;
}

/**
 * @brief Pause audio stream
 * @return If no error occurred 0 is returned, else -1 is returned
 */
int AudioController::PauseStream()
{
    if (BASS_Pause())
        return 0;
    return -1;
}

/**
 * @brief Resume audio stream
 * @return If no error occurred 0 is returned, else -1 is returned
 */
int AudioController::ResumeStream()
{
    if (BASS_ChannelIsActive(streamHandle))
    {
        if (BASS_Start())
            return 0;
    }
    return -1;
}

/**
 * @brief Stop audio stream
 * @return If no error occurred 0 is returned, else -1 is returned
 */
int AudioController::StopStream()
{
    BASS_Stop();
    BASS_ChannelFree(streamHandle);
    BASS_Free();
    return 0;
}

/**
 * @brief Checks if a sample, stream, or MOD music is active (playing) or stalled. Can also check if a recording is in
 * progress.
 * @return
 *
 * The return value is one of the following.
 *
 * BASS_ACTIVE_STOPPED	The channel is not active, or handle is not a valid channel.
 *
 * BASS_ACTIVE_PLAYING	The channel is playing (or recording).
 *
 * BASS_ACTIVE_PAUSED	The channel is paused.
 *
 * BASS_ACTIVE_PAUSED_DEVICE	The channel's device is paused.
 *
 * BASS_ACTIVE_STALLED	Playback of the stream has been stalled due to a lack of sample data.
 *
 * Playback will automatically resume once there is sufficient data to do so.
 */
int AudioController::getStreamStatus()
{
    return BASS_ChannelIsActive(streamHandle);
}

/**
 * @brief Private member to shift pitch
 * @param value Semitones (0 won't change the pitch)
 * @return If successful, TRUE is returned, else FALSE is returned
 */
bool AudioController::_PitchShift(float value)
{
    HFX handle = BASS_ChannelSetFX(this->streamHandle, BASS_FX_BFX_PITCHSHIFT, 0);
    BASS_BFX_PITCHSHIFT params = {0, value, 2048, 8, this->streamHandle};
    return BASS_FXSetParameters(handle, &params);
}

/**
 * @brief Increase stream channel pitch
 * @param semitones number of semitones to increase (must be between [0..8])
 * @return If no error occurred 0 is returned, else -1 is returned
 */
int AudioController::IncreasePitch(int semitones)
{
    if (_PitchShift(semitones))
        return 0;
    else
        return -1;
}

/**
 * @brief Decrease  stream channel pitch
 * @param semitones number of semitones to decrease (must be between [0..8])
 * @return If no error occurred 0 is returned, else -1 is returned
 */
int AudioController::DecreasePitch(int semitones)
{
    if (_PitchShift(-semitones))
        return 0;
    else
        return -1;
}

/**
 * @brief
 * @param speed
 * @return
 */
int AudioController::SetStreamSpeed(float speed)
{
    return 0;
}

// void CALLBACK GetBpmCallback(DWORD channel, float percent, void* user)
// {
//     std::cout << percent << std::endl;
// }

/**
 * @brief Get bpm from file
 * @param path File path
 * @param start Start detecting position in seconds
 * @param end End detecting position in seconds
 * @return Beats per minute
 */
float AudioController::GetBpm(const std::string& path, double start, double end)
{
    // Create decoding stream
    HSTREAM DecodingStream = BASS_StreamCreateFile(FALSE, path.c_str(), 0L, 0L, BASS_STREAM_DECODE);
    // Get bpm from decoding stream
    float val = BASS_FX_BPM_DecodeGet(DecodingStream, start, end, MAKELONG(29, 200), BASS_FX_FREESOURCE, NULL, NULL);
    BASS_FX_BPM_Free(DecodingStream); // Free mem
    return val;
}