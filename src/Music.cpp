#include <vector>
#include <istream>
#include <ostream>
#include <sstream>
#include "Music.h"
#include "Bar.h"

const char Music::separator = '\n';

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


bool Music::input_from(Music *music, std::istream& is)
{
    std::string str;
    if (std::getline(is, str, separator)) {
        std::istringstream iss(str);
        while (iss.good()) {
            Bar bar;
            if (Bar::input_from(&bar, iss)) {
                music->add_bar(bar);
            }
        }

        return true;
    }
    else {
        return false;
    }
}

void Music::output_to(std::ostream& os, const Music& music)
{
    std::size_t num_bar = music.num_bar();
    for (std::size_t idxBar = 0; idxBar < num_bar; ++idxBar) {

        Bar::output_to(os, music[idxBar]);
    }
    os << separator;
}
