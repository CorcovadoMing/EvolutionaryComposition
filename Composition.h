#ifndef COMPOSITION_H
#define COMPOSITION_H

#include <vector>

struct Sound
{
    Sound();
    Sound(int freq, int duration);

    int freq; // hertz
    int dur; // millisecond
};

class Composition
{
public:
    Composition(int beat, int notevalue, int bar, int tempo);

    typedef std::vector<Sound> Beat;
    typedef std::vector<Beat> Bar;
    typedef std::vector<Bar> Music;


    Beat changePatternOfBeat(const Sound& sound) const;
    Beat changePatternOfBeat(const Beat& beat) const;

    Sound changeFreqOfPitch(const Sound& sound) const;
    Beat changeFreqOfPitch(const Beat& beat) const;
    Bar changeFreqOfPitch(const Bar& bar) const;
    Music changeFreqOfPitch(const Music& music) const;


    int objectiveValue(const Music& music) const { return 0; }


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
    const int NOTE_VALUE_ONE_BEAT; // 4

    // https://en.wikipedia.org/wiki/Bar_(music)
    const int TOTAL_BAR; // 12
    // https://en.wikipedia.org/wiki/Tempo
    const int TEMPO;


    static const int FREQ_STD_PITCH; // A: 440 Hz
    // the table of Frequency of Pitch in hertz.
    static const std::vector<int> freqOfPitch;

    // the table of patterns of beat,
    // every patterns are summed up in 1000 millisecond.
    static const std::vector< std::vector<Sound> > patternOfBeat;
};

inline
Sound::Sound() : freq(Composition::FREQ_STD_PITCH), dur(1000)
{
}

inline
Sound::Sound(int freq, int duration) : freq(freq), dur(duration)
{
}

#endif // COMPOSITION_H
