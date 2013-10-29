#include <vector>
#include <cstddef>
#include <cmath>
#include <limits>
#include "Music.h"
#include "Bar.h"

Music::Music()
: bars_(), fitness_value_(0){}

Music::Music(std::size_t num_bars)
{
    bars_.reserve(num_bars);
}

Music::Music(const std::vector<Bar>& barlist)
: bars_(barlist){}

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
