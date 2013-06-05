#include <vector>
#include <cstddef>
#include "Sound.h"

#if defined(_WIN32) || defined(_WIN64)
#include "windows.h"
#endif

/**
 *  Sound
 */

const int Sound::STD_FREQ_PITCH = 440; // A: 440 Hz
const int Sound::STD_DUR_BEAT = 1000; // 1000 millisecond

Sound::Sound()
    : frequency_(STD_FREQ_PITCH), duration_(STD_DUR_BEAT)
{
}

Sound::Sound(int frequency, int duration)
    : frequency_(frequency), duration_(duration)
{
}

/**
 *  Beat
 */

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

/**
 *  Bar
 */

Bar::Bar()
    : beats_()
{
}

Bar::Bar(std::size_t num_beats)
{
    beats_.reserve(num_beats);
}

Bar::Bar(const std::vector<Beat>& beatlist)
    : beats_(beatlist)
{
}

void Bar::add_beat(const Beat& beat)
{
    beats_.push_back(beat);
}

Beat& Bar::operator[] (std::size_t idx)
{
    return const_cast<Beat &>(static_cast<const Bar &>(*this)[idx]);
}

const Beat& Bar::operator[] (std::size_t idx) const
{
    return beats_[idx];
}

/**
 *  Music
 */

Music::Music()
    : bars_(), degree_of_sounds_good_(0)
{
}

Music::Music(std::size_t num_bars)
{
    bars_.reserve(num_bars);
}

Music::Music(const std::vector<Bar>& barlist)
    : bars_(barlist)
{
}

void Music::add_bar(const Bar& bar)
{
    bars_.push_back(bar);
}

Bar& Music::operator[] (std::size_t idx)
{
    return const_cast<Bar &>(static_cast<const Music &>(*this)[idx]);
}

const Bar& Music::operator[] (std::size_t idx) const
{
    return bars_[idx];
}

void Music::set_degree_of_sounds_good(int degree)
{
    degree_of_sounds_good_ = degree;
}

void Music::listen() const
{
    std::size_t num_bar = bars_.size();
    for (std::size_t idxMusic = 0; idxMusic < num_bar; ++idxMusic) {

        std::size_t num_beat = bars_[idxMusic].num_beat();
        for (std::size_t idxBar = 0; idxBar < num_beat; ++idxBar) {

            std::size_t num_sound = bars_[idxMusic][idxBar].num_sound();
            for (std::size_t idxBeat = 0; idxBeat < num_sound; ++idxBeat) {

                #if defined(_WIN32) || defined(_WIN64)
                Beep(bars_[idxMusic][idxBar][idxBeat].frequency(),
                     bars_[idxMusic][idxBar][idxBeat].duration()
                     );
                #endif
            }
        }
    }
}
