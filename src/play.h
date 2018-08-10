#include "bass.h"
#include <iostream>
#include <unistd.h>

class AudioPlayer
{
    public:
        void start_playback_file(const char* f);
        void start_playback_url(const char* f);
        void pause_playback();
        void unpause_playback();
        void set_volume(int v);
        void set_position(int p);
        double get_position();
        double get_length();
};
