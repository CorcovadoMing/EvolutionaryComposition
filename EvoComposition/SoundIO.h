#ifndef SOUNDIO_H
#define SOUNDIO_H

#include <istream>
#include <ostream>
#include <sstream>
#include "Sound.h"

class SoundIO
{
public:

    static Music input_from(std::istream& is);
    static void output_to(std::ostream& os, const Music& music);

    static const char sound_separator,
                      beat_separator,
                      bar_separator,
                      music_separator;
};


const char SoundIO::sound_separator = ' ',
           SoundIO::beat_separator = '\t',
           SoundIO::bar_separator = '|',
           SoundIO::music_separator = '\n';


Music
SoundIO::input_from(std::istream& is)
{
    Music music;

    while (is.good()) {
        // parse Music
        std::string str_music;
        std::getline(is, str_music, music_separator);
        std::istringstream iss_music(str_music);
        while (iss_music.good()) {
            Bar bar;

            // parse Bar
            std::string str_bar;
            std::getline(iss_music, str_bar, bar_separator);
            std::istringstream iss_bar(str_bar);
            while (iss_bar.good()) {
                Beat beat;

                // parse Beat
                std::string str_beat;
                std::getline(iss_bar, str_beat, beat_separator);
                std::istringstream iss_beat(str_beat);
                while (iss_beat.good()) {
                    Sound sound;

                    // parse Sound
                    std::string str_frequency, str_duration;
                    std::getline(iss_beat, str_frequency, sound_separator);
                    std::getline(iss_beat, str_duration, sound_separator);
                    std::istringstream iss_frequency(str_frequency),
                                       iss_duration(str_duration);
                    int frequency = 0, duration = 0;
                    iss_frequency >> frequency;
                    iss_duration >> duration;

                    beat.add_sound(Sound(frequency, duration));
                }
                bar.add_beat(beat);
            }
            music.add_bar(bar);
        }
    }
    return music;
}

void
SoundIO::output_to(std::ostream& os, const Music& music)
{
    std::size_t num_bar = music.num_bar();
    for (std::size_t idxMusic = 0; idxMusic < num_bar; ++idxMusic) {

        os << bar_separator;

        std::size_t num_beat = music[idxMusic].num_beat();
        for (std::size_t idxBar = 0; idxBar < num_beat; ++idxBar) {

            os << beat_separator;

            std::size_t num_sound = music[idxMusic][idxBar].num_sound();
            for (std::size_t idxBeat = 0; idxBeat < num_sound; ++idxBeat) {

                os << sound_separator <<
                      music[idxMusic][idxBar][idxBeat].frequency() <<
                      sound_separator <<
                      music[idxMusic][idxBar][idxBeat].duration();
            }
        }
    }
    os << bar_separator << music_separator;
}

#endif // SOUNDIO_H
