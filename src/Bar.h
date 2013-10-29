#ifndef BAR_H
#define BAR_H

#include <vector>
#include "Beat.h"

class Bar
{
public:
    Bar();
    Bar(std::size_t num_beats);
    Bar(const std::vector<Beat>& beatlist);

    void add_beat(const Beat& beat);
    Beat& operator[] (std::size_t idx);
    const Beat& operator[] (std::size_t idx) const;
    std::size_t num_beat() const { return beats_.size(); }
    std::size_t num() const { return num_beat(); }
    
    static bool input_from(Bar *bar, std::istream& is);
    static void output_to(std::ostream& os, const Bar& bar);

    static const char separator;

private:
    std::vector<Beat> beats_;
};

#endif