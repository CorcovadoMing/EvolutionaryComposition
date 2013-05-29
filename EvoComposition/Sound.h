#ifndef SOUND_H
#define SOUND_H

#include <vector>
#include <cstddef>

struct Sound
{
    Sound() : frequency(STD_FREQ_PITCH), duration(STD_DUR_BEAT) {}
    Sound(int frequency, int duration)
        : frequency(frequency), duration(duration) {}


    // the standard frequency and duration of a note
    static const int STD_FREQ_PITCH = 440; // A: 440 Hz
    static const int STD_DUR_BEAT = 1000; // 1000 millisecond


    int frequency; // in hertz
    int duration; // in millisecond
};

class Beat
{
public:
    Beat() : sounds_() {}
    Beat(std::size_t num_sounds) { sounds_.reserve(num_sounds); }
    Beat(const std::vector<Sound>& soundlist) : sounds_(soundlist) {}


    // Add a Beat into Bar
    void addSound(const Sound& sound) { sounds_.push_back(sound); }


    // how many Sounds in this Beat
    std::size_t sizeOfSound() const { return sounds_.size(); }


    // operator []
    Sound& operator[] (std::size_t idx)
    {
        return const_cast<Sound &>(static_cast<const Beat &>(*this)[idx]);
    }
    const Sound& operator[] (std::size_t idx) const
    {
        return sounds_[idx];
    }
private:
    std::vector<Sound> sounds_;
};

class Bar
{
public:
    Bar() : beats_() {}
    Bar(std::size_t num_beats) { beats_.reserve(num_beats); }
    Bar(const std::vector<Beat>& beatlist) : beats_(beatlist) {}


    // Add a Beat into Bar
    void addBeat(const Beat& beat) { beats_.push_back(beat); }


    // how many Beats in this Bar
    std::size_t sizeOfBeat() const { return beats_.size(); }


    // operator []
    Beat& operator[] (std::size_t idx)
    {
        return const_cast<Beat &>(static_cast<const Bar &>(*this)[idx]);
    }
    const Beat& operator[] (std::size_t idx) const
    {
        return beats_[idx];
    }
private:
    std::vector<Beat> beats_;
};

class Music
{
public:
    Music() : bars_(), degree_of_sounds_good_(0) {}
    Music(std::size_t num_bars) { bars_.reserve(num_bars); }
    Music(const std::vector<Bar>& barlist) : bars_(barlist) {}


    // Add a Bar into Music
    void addBar(const Bar& bar) { bars_.push_back(bar); }
    // Set the degree of sounds good
    void setDegreeOfSoundsGood(int degree)
    {
        degree_of_sounds_good_ = degree;
    }


    // How many Bars in this Music
    std::size_t sizeOfBar() const { return bars_.size(); }
    // Get the degree of sounds good
    int degree_of_sounds_good() const { return degree_of_sounds_good_; }


    // operator []
    Bar& operator[] (std::size_t idx)
    {
        return const_cast<Bar &>(static_cast<const Music &>(*this)[idx]);
    }
    const Bar& operator[] (std::size_t idx) const
    {
        return bars_[idx];
    }
private:
    std::vector<Bar> bars_;

    int degree_of_sounds_good_;
};

#endif // SOUND_H
