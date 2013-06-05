#include <istream>
#include <ostream>
#include <string>
#include <sstream>
#include "Sound.h"
#include "SoundIO.h"

const char SoundIO::freq_dur_separator = ',',
           SoundIO::separator = ' ',
           BeatIO::separator = '\t',
           BarIO::separator = '|',
           MusicIO::separator = '\n';

bool
SoundIO::input_from(Sound *sound, std::istream& is)
{
    std::string str;
    if (std::getline(is, str, separator)) {
        std::string::size_type n = str.find(freq_dur_separator);
        std::istringstream iss_freq(str.substr(0, n)),
                           iss_dur(str.substr(n+1));

        int freq = 0, dur = 0;
        iss_freq >> freq;
        iss_dur >> dur;
        sound->set_frequency(freq);
        sound->set_duration(dur);

        return true;
    }
    else {
        return false;
    }
}

void
SoundIO::output_to(std::ostream& os, const Sound& sound)
{

    os << sound.frequency() << freq_dur_separator <<
          sound.duration() << separator;
}

bool
BeatIO::input_from(Beat *beat, std::istream& is)
{
    std::string str;
    if (std::getline(is, str, separator)) {
        std::istringstream iss(str);
        while (iss.good()) {
            Sound sound;
            if (SoundIO::input_from(&sound, iss)) {
                beat->add_sound(sound);
            }
        }

        return true;
    }
    else {
        return false;
    }
}

void
BeatIO::output_to(std::ostream& os, const Beat& beat)
{
    std::size_t num_sound = beat.num_sound();
    for (std::size_t idxSound = 0; idxSound < num_sound; ++idxSound) {

        SoundIO::output_to(os, beat[idxSound]);
    }
    os << separator;
}

bool
BarIO::input_from(Bar *bar, std::istream& is)
{
    std::string str;
    if (std::getline(is, str, separator)) {
        std::istringstream iss(str);
        while (iss.good()) {
            Beat beat;
            if (BeatIO::input_from(&beat, iss)) {
                bar->add_beat(beat);
            }
        }

        return true;
    }
    else {
        return false;
    }
}

void
BarIO::output_to(std::ostream& os, const Bar& bar)
{
    std::size_t num_beat = bar.num_beat();
    for (std::size_t idxBeat = 0; idxBeat < num_beat; ++idxBeat) {

        BeatIO::output_to(os, bar[idxBeat]);
    }
    os << separator;
}

bool
MusicIO::input_from(Music *music, std::istream& is)
{
    std::string str;
    if (std::getline(is, str, separator)) {
        std::istringstream iss(str);
        while (iss.good()) {
            Bar bar;
            if (BarIO::input_from(&bar, iss)) {
                music->add_bar(bar);
            }
        }

        return true;
    }
    else {
        return false;
    }
}

void
MusicIO::output_to(std::ostream& os, const Music& music)
{
    std::size_t num_bar = music.num_bar();
    for (std::size_t idxBar = 0; idxBar < num_bar; ++idxBar) {

        BarIO::output_to(os, music[idxBar]);
    }
    os << separator;
}
