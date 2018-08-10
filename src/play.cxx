#include "play.h"

HCHANNEL mp3Stream;

void AudioPlayer::start_playback_file(const char* f)
{
    BASS_ChannelStop(mp3Stream);
    
    BASS_Init(-1, 44100, 0, NULL, NULL);
    mp3Stream = BASS_StreamCreateFile(false, f, 0, 0, BASS_SAMPLE_LOOP);
    BASS_ChannelPlay(mp3Stream, false);
}

void AudioPlayer::start_playback_url(const char* f)
{
    BASS_ChannelStop(mp3Stream);
    
    BASS_Init(-1, 44100, 0, NULL, NULL);
    
    mp3Stream = BASS_StreamCreateURL(f, 0, BASS_STREAM_BLOCK|BASS_STREAM_STATUS|BASS_STREAM_AUTOFREE, NULL, 0);
    BASS_ChannelPlay(mp3Stream, false);
}

void AudioPlayer::pause_playback()
{
    BASS_Pause();
}

void AudioPlayer::unpause_playback()
{
    BASS_Start();
}

void AudioPlayer::set_volume(int v)
{
    BASS_SetConfig(BASS_CONFIG_GVOL_STREAM, v*100);
}

void AudioPlayer::set_position(int p)
{
    BASS_ChannelSetPosition(mp3Stream, BASS_ChannelSeconds2Bytes(mp3Stream, p), BASS_POS_BYTE);
}

double AudioPlayer::get_position()
{
    if (mp3Stream == 0)
        return 0;
    double pos = BASS_ChannelBytes2Seconds(mp3Stream, BASS_ChannelGetPosition(mp3Stream, BASS_POS_BYTE));
    return pos;
}

double AudioPlayer::get_length()
{
    if (mp3Stream == 0)
        return 0;
    double len = BASS_ChannelBytes2Seconds(mp3Stream, BASS_ChannelGetLength(mp3Stream, BASS_POS_BYTE));
    return len;
}
