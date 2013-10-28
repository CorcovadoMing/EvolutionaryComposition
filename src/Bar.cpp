#include <vector>
#include <cstddef>
#include <cmath>
#include <limits>
#include "Bar.h"
#include "Beat.h"

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