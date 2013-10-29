#ifndef MUSIC_H
#define MUSIC_H

#include <vector>
#include "Bar.h"

class Music
{
public:
    Music();
    Music(std::size_t num_bars);
    Music(const std::vector<Bar>& barlist);
    
    void add_bar(const Bar& bar);
    Bar& operator[] (std::size_t idx);
    const Bar& operator[] (std::size_t idx) const;
    void set_fitness_value(double fitness_value);
    std::size_t num_bar() const { return bars_.size(); }
    std::size_t num() const { return num_bar(); }
    double fitness_value() const { return fitness_value_; }
    
    static bool input_from(Music *music, std::istream& is);
    static void output_to(std::ostream& os, const Music& music);

    static const char separator;

private:
    std::vector<Bar> bars_;
    double fitness_value_; 
};

#endif