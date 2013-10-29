#include <vector>
#include <istream>
#include <ostream>
#include <sstream>
#include "Bar.h"
#include "Beat.h"

const char Bar::separator = '|';

Bar::Bar()
: beats_(){}

Bar::Bar(std::size_t num_beats)
{
    beats_.reserve(num_beats);
}

Bar::Bar(const std::vector<Beat>& beatlist)
: beats_(beatlist){}

void Bar::add_beat(const Beat& beat)
{
    beats_.push_back(beat);
}

Beat& Bar::operator[] (std::size_t idx)
{
    return const_cast<Beat &>(static_cast<const Bar&>(*this)[idx]);
}

const Beat& Bar::operator[] (std::size_t idx) const
{
    return beats_[idx];
}

bool Bar::input_from(Bar *bar, std::istream& is)
{
    std::string str;
    if (std::getline(is, str, separator)) {
        std::istringstream iss(str);
        while (iss.good()) {
            Beat beat;
            if (Beat::input_from(&beat, iss)) {
                bar->add_beat(beat);
            }
        }

        return true;
    }
    else {
        return false;
    }
}

void Bar::output_to(std::ostream& os, const Bar& bar)
{
    std::size_t num_beat = bar.num_beat();
    for (std::size_t idxBeat = 0; idxBeat < num_beat; ++idxBeat) {
        Beat::output_to(os, bar[idxBeat]);
    }
    os << separator;
}