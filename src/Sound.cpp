#include <vector>
#include <cmath>
#include <limits>
#include <istream>
#include <ostream>
#include <sstream>
#include "Sound.h"

const char Sound::freq_dur_separator = ',',
           Sound::separator = ' ';
           
const double Sound::STD_FREQ_PITCH = 440.0; // A: 440 Hz
const int Sound::STD_DUR_BEAT = 1000; // 1000 millisecond

Sound::Sound()
: frequency_(STD_FREQ_PITCH), duration_(STD_DUR_BEAT){}

Sound::Sound(double frequency, int duration)
: frequency_(frequency), duration_(duration){}

bool Sound::isRestNote() const
{
    return std::fabs(frequency_) < std::numeric_limits<double>::epsilon();
}

bool Sound::input_from(Sound *sound, std::istream& is)
{
    std::string str;
    if (std::getline(is, str, separator)) {
        std::string::size_type n = str.find(freq_dur_separator);
        std::istringstream iss_freq(str.substr(0, n)),
                           iss_dur(str.substr(n+1));

        double freq = 0;
        int dur = 0;
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

void Sound::output_to(std::ostream& os, const Sound& sound)
{
   os << sound.frequency() << freq_dur_separator <<
         sound.duration() << separator;
}

