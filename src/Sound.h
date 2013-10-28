#ifndef SOUND_H
#define SOUND_H

#include <vector>
#include <cstddef>

class Sound
{
public:
    Sound();
    Sound(float frequency, int duration);

    static const float STD_FREQ_PITCH;    // A: 440 Hz
    static const int STD_DUR_BEAT;    // 1000 millisecond

    bool isRestNote() const;

    void set_frequency(float frequency) { frequency_ = frequency; }
    void set_duration(int duration) { duration_ = duration; }

    float frequency() const { return frequency_; }
    int duration() const { return duration_; }

private:
    float frequency_;    // in hertz
    int duration_;    // in millisecond
};

#endif // SOUND_H
