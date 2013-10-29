#ifndef COMPOSITION_H
#define COMPOSITION_H

#include "Music.h"

class Composition
{
public:
    Composition(int beats_per_bar = 4, int note_value = 4,
                int total_num_bar = 12, int tempo = 120);
                
    Music create_initial_solution() const;
    double pitchFitness(const Music& music ) const;
    double beatFitness(const Music& music ) const;
    Beat changePatternOfBeat(const Sound& sound) const;
    Beat changePatternOfBeat(const Beat& beat) const;
    Sound changeFreqOfPitch(const Sound& sound) const;
    
    template<class compositionType>
    compositionType changeFreqOfPitch(const compositionType& type) const;
    
    int BEATS_PER_BAR,
        NOTE_VALUE,
        TOTAL_NUMBER_BAR,
        TEMPO;
    
    static const std::vector<double> freq_of_pitch, C_LICK, F_LICK, G_LICK;
    static const std::vector< std::vector<Sound> > pattern_of_beat;
    
    static Composition input_from(std::istream& is);
    static void output_to(std::ostream& os, const Composition& composition);

    static const char separator, terminal_separator;
};

#endif // COMPOSITION_H
