#ifndef SOUND_H
#define SOUND_H

#include <vector>
#include <cstddef>

class Sound
{
public:
    static const double STD_FREQ_PITCH;    // A: 440 Hz
    static const int STD_DUR_BEAT;    // 1000 millisecond
    Sound();
    Sound(double frequency, int duration);

    bool isRestNote() const;
    void set_frequency(double frequency) { frequency_ = frequency; }
    void set_duration(int duration) { duration_ = duration; }
    double frequency() const { return frequency_; }
    int duration() const { return duration_; }
    
    static bool input_from(Sound *sound, std::istream& is);
    static void output_to(std::ostream& os, const Sound& sound);

    static const char freq_dur_separator,
                      separator;

private:
    double frequency_;    // in hertz
    int duration_;    // in millisecond
};

#endif // SOUND_H
