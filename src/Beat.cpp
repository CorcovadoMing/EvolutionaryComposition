#include <vector>
#include <istream>
#include <ostream>
#include <sstream>
#include "Beat.h"
#include "Sound.h"

Beat::Beat()
: sounds_(){}

Beat::Beat(std::size_t num_sounds)
{
    sounds_.reserve(num_sounds);
}

Beat::Beat(const std::vector<Sound>& soundlist)
: sounds_(soundlist){}

void Beat::add_sound(const Sound& sound)
{
    sounds_.push_back(sound);
}

Sound& Beat::operator[] (std::size_t idx)
{
    return const_cast<Sound &>(static_cast<const Beat &>(*this)[idx]);
}

const Sound& Beat::operator[] (std::size_t idx) const
{
    return sounds_[idx];
}

bool Beat::input_from(Beat *beat, std::istream& is)
{
    std::string str;
    if (std::getline(is, str, separator_)) {
        std::istringstream iss(str);
        while (iss.good()) {
            Sound sound;
            if (Sound::input_from(&sound, iss)) {
                beat->add_sound(sound);
            }
        }
        return true;
    }
    else {
        return false;
    }
}

void Beat::output_to(std::ostream& os, const Beat& beat)
{
    std::size_t num_sound = beat.num_sound();
    for (std::size_t idxSound = 0; idxSound < num_sound; ++idxSound) {
        Sound::output_to(os, beat[idxSound]);
    }
    os << separator_;
}
