#ifndef COMPOSITION_H
#define COMPOSITION_H

#include "Sound.h"

class Composition
{
public:
    Composition(int beats_per_bar = 4, int note_value = 4,
                int total_num_bar = 12, int tempo = 60);

    /**
     *  All operations below are related to Evolutionary Algorithm.
     */

    // Create an initial solution.
    Music create_initial_solution() const;

    // Evaluate the fitness of an indivisual.
    //double evaluate_fitness_value(Music* music) const;
    
    double pitchFitness( const Music& music ) const;
    double beatFitness( const Music& music ) const;

    /**
     *  All operations below are related to Composition.
     */

    Beat changePatternOfBeat(const Sound& sound) const;
    Beat changePatternOfBeat(const Beat& beat) const;

    Sound changeFreqOfPitch(const Sound& sound) const;
    Beat changeFreqOfPitch(const Beat& beat) const;
    Bar changeFreqOfPitch(const Bar& bar) const;
    Music changeFreqOfPitch(const Music& music) const;


    /**
     *  The following variables are member data.
     */

    /* https://en.wikipedia.org/wiki/Time_signature
     *
     * The time signature consist of two numerals:
     *
     * the upper numeral indicates how many such beats there are in a bar,
     * the lower numeral indicates the note value which represents one beat.
     *
     * 3
     * 4 means three quarter-note beats per bar.
     */
    int BEATS_PER_BAR; // 3
    int NOTE_VALUE; // 4

    // https://en.wikipedia.org/wiki/Bar_(music)
    int TOTAL_NUMBER_BAR; // 12
    // https://en.wikipedia.org/wiki/Tempo
    int TEMPO;


    // the table of Frequency of Pitch in hertz.
    static const std::vector<float> freq_of_pitch;
    
    static const std::vector<double> C_LICK;
    static const std::vector<double> F_LICK;
    static const std::vector<double> G_LICK;
    
    // the table of patterns of beat,
    // every patterns are summed up in 1000 millisecond.
    static const std::vector< std::vector<Sound> > pattern_of_beat;
};


#endif // COMPOSITION_H
