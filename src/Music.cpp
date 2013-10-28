#include <vector>
#include <cstddef>
#include <cmath>
#include <limits>
#include "Music.h"
#include "Bar.h"

Music::Music()
    : bars_(), fitness_value_(0)
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

void Music::set_fitness_value(double fitness_value)
{
    fitness_value_ = fitness_value;
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
