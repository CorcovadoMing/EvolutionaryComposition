#ifndef SOUNDIO_H
#define SOUNDIO_H

#include <istream>
#include <ostream>

class Sound;
class Beat;
class Bar;
class Music;

/**
 *  SoundIO
 */

class SoundIO
{
public:

    static bool input_from(Sound *sound, std::istream& is);
    static void output_to(std::ostream& os, const Sound& sound);

    static const char freq_dur_separator,
                      separator;
};

/**
 *  BeatIO
 */

class BeatIO
{
public:

    static bool input_from(Beat *beat, std::istream& is);
    static void output_to(std::ostream& os, const Beat& beat);

    static const char separator;
};

/**
 *  BarIO
 */

class BarIO
{
public:

    static bool input_from(Bar *bar, std::istream& is);
    static void output_to(std::ostream& os, const Bar& bar);

    static const char separator;
};

/**
 *  MusicIO
 */

class MusicIO
{
public:

    static bool input_from(Music *music, std::istream& is);
    static void output_to(std::ostream& os, const Music& music);

    static const char separator;
};

#endif // SOUNDIO_H
