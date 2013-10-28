#include <vector>
#include <cstddef>
#include <cmath>
#include <limits>
#include "Sound.h"

const float Sound::STD_FREQ_PITCH = 440.0; // A: 440 Hz
const int Sound::STD_DUR_BEAT = 1000; // 1000 millisecond

Sound::Sound()
: frequency_(STD_FREQ_PITCH), duration_(STD_DUR_BEAT){}

Sound::Sound(float frequency, int duration)
: frequency_(frequency), duration_(duration){}

bool Sound::isRestNote() const
{
    return std::fabs(frequency_) < std::numeric_limits<float>::epsilon();
}
