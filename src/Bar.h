#ifndef BAR_H
#define BAR_H

#include <vector>
#include <cstddef>
#include "Beat.h"

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

#endif