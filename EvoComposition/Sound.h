#ifndef SOUND_H
#define SOUND_H

#include <vector>
#include <cstddef>

/**
 *  Sound
 */

class Sound
{
public:
    Sound();
    Sound(int frequency, int duration);

    // the standard frequency and duration of a note
    static const int STD_FREQ_PITCH;    // A: 440 Hz
    static const int STD_DUR_BEAT;    // 1000 millisecond

    void set_frequency(int frequency) { frequency_ = frequency; }
    void set_duration(int duration) { duration_ = duration; }

    // getter
    int frequency() const { return frequency_; }
    int duration() const { return duration_; }

private:
    int frequency_;    // in hertz
    int duration_;    // in millisecond
};

/**
 *  Beat
 */

class Beat
{
public:
    Beat();
    Beat(std::size_t num_sounds);
    Beat(const std::vector<Sound>& soundlist);


    // Add a Sound into Beat
    void add_sound(const Sound& sound);

    // Access specified Sound
    Sound& operator[] (std::size_t idx);
    const Sound& operator[] (std::size_t idx) const;


    // how many Sounds in this Beat
    std::size_t num_sound() const { return sounds_.size(); }

private:
    std::vector<Sound> sounds_;
};

/**
 *  Bar
 */

class Bar
{
public:
    Bar();
    Bar(std::size_t num_beats);
    Bar(const std::vector<Beat>& beatlist);


    // Add a Beat into Bar
    void add_beat(const Beat& beat);

    // Access specified Beat
    Beat& operator[] (std::size_t idx);
    const Beat& operator[] (std::size_t idx) const;

    // how many Beats in this Bar
    std::size_t num_beat() const { return beats_.size(); }

private:
    std::vector<Beat> beats_;
};

/**
 *  Music
 */

class Music
{
public:
    Music();
    Music(std::size_t num_bars);
    Music(const std::vector<Bar>& barlist);


    // Add a Bar into Music
    void add_bar(const Bar& bar);

    // Access specified Bar
    Bar& operator[] (std::size_t idx);
    const Bar& operator[] (std::size_t idx) const;

    // Set the fitness
    void set_fitness_value(int fitness_value);


    // How many Bars in this Music
    std::size_t num_bar() const { return bars_.size(); }

    // Get the fitness
    int fitness_value() const { return fitness_value_; }


    // listen to the Music
    void listen() const;

private:
    std::vector<Bar> bars_;

    int fitness_value_;  // the degree of sounds good
};

#endif // SOUND_H
