#include <vector>
#include <cstddef>
#include <cmath>
#include <limits>
#include "Beat.h"
#include "Sound.h"

Beat::Beat()
    : sounds_()
{
}

Beat::Beat(std::size_t num_sounds)
{
    sounds_.reserve(num_sounds);
}

Beat::Beat(const std::vector<Sound>& soundlist)
    : sounds_(soundlist)
{
}

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
