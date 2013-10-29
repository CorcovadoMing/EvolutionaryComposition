#ifndef COMPOSITION_H
#define COMPOSITION_H

#include "Music.h"

class Composition
{
public:
    Composition(int beats_per_bar = 4, int note_value = 4,
                int total_num_bar = 12, int tempo = 60);
                
    Music create_initial_solution() const;
    double pitchFitness(const Music& music ) const;
    double beatFitness(const Music& music ) const;
    Beat changePatternOfBeat(const Sound& sound) const;
    Beat changePatternOfBeat(const Beat& beat) const;
    Sound changeFreqOfPitch(const Sound& sound) const;
    Beat changeFreqOfPitch(const Beat& beat) const;
    Bar changeFreqOfPitch(const Bar& bar) const;
    Music changeFreqOfPitch(const Music& music) const;
    
    int BEATS_PER_BAR;
    int NOTE_VALUE;
    
    int TOTAL_NUMBER_BAR; // 12
    int TEMPO;
    
    static const std::vector<float> freq_of_pitch;
    static const std::vector<double> C_LICK;
    static const std::vector<double> F_LICK;
    static const std::vector<double> G_LICK;
    static const std::vector< std::vector<Sound> > pattern_of_beat;
};

#endif // COMPOSITION_H
