#ifndef BEAT_H
#define BEAT_H

#include <vector>
#include <cstddef>
#include "Sound.h"

class Beat
{
public:
    Beat();
    Beat(std::size_t num_sounds);
    Beat(const std::vector<Sound>& soundlist);

    void add_sound(const Sound& sound);
    Sound& operator[] (std::size_t idx);
    const Sound& operator[] (std::size_t idx) const;
    std::size_t num_sound() const { return sounds_.size(); }

private:
    std::vector<Sound> sounds_;
};

#endif