#ifndef COMPOSITION_H
#define COMPOSITION_H

#include "Sound.h"

class Composition
{
public:
    Composition(int beats_per_bar, int note_value,
                int total_num_bar, int tempo);

    /**
     *  All operations below are related to Evolutionary Algorithm.
     */

    // Create an initial solution.
    Music createInitialSolution() const;
    // Evaluate the fitness of an indivisual.
    // note that:
    //     EA may use both decision and objective value.
    //     For example, in Permutation Flow Shop Scheduling Problem,
    //     makespan is refer to objective value, and the resemblance
    //     to two PFSP solution is maybe refer to decision value.
    //     If you use it, remeber to add a new variable to Music.
    //int evaluateDecisionValue(Music* music) const;
    int evaluateObjectiveValue(Music* music) const;

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
    const int BEATS_PER_BAR; // 3
    const int NOTE_VALUE; // 4

    // https://en.wikipedia.org/wiki/Bar_(music)
    const int TOTAL_NUMBER_BAR; // 12
    // https://en.wikipedia.org/wiki/Tempo
    const int TEMPO;


    // the table of Frequency of Pitch in hertz.
    static const std::vector<int> freq_of_pitch;

    // the table of patterns of beat,
    // every patterns are summed up in 1000 millisecond.
    static const std::vector< std::vector<Sound> > pattern_of_beat;
};


#endif // COMPOSITION_H
