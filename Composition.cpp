#include <vector>
#include <cstdlib>
#include <cstddef>
#include "Composition.h"

const int Composition::FREQ_STD_PITCH = 440; // A: 440 Hz

const std::vector<int> Composition::freqOfPitch =
    {262, 294, 330, 349, 392, 440, 494};

const std::vector< std::vector<Sound> > Composition::patternOfBeat =
    {
        {Sound(FREQ_STD_PITCH, 333), Sound(0, 333), Sound(FREQ_STD_PITCH, 334)},
        {Sound(FREQ_STD_PITCH, 750), Sound(FREQ_STD_PITCH, 250)},
        {Sound(FREQ_STD_PITCH, 500), Sound(FREQ_STD_PITCH, 166),
         Sound(FREQ_STD_PITCH, 166), Sound(FREQ_STD_PITCH, 168)},
        {Sound(FREQ_STD_PITCH, 250), Sound(FREQ_STD_PITCH, 250),
         Sound(FREQ_STD_PITCH, 250), Sound(FREQ_STD_PITCH, 250)},
        {Sound(FREQ_STD_PITCH, 500),
         Sound(FREQ_STD_PITCH, 250), Sound(FREQ_STD_PITCH, 250)}
    };

Composition::Composition(int beat, int notevalue, int bar, int tempo)
    : BEATS_PER_BAR(beat), NOTE_VALUE_ONE_BEAT(notevalue),
      TOTAL_BAR(bar), TEMPO(tempo)
{
}

Composition::Beat
Composition::changePatternOfBeat(const Sound& sound) const
{
    int rand = std::rand() % patternOfBeat.size();
    std::vector<Sound> pattern = patternOfBeat[rand];

    Composition::Beat beat(pattern.size(), Sound(sound.freq, 0));

    for (std::size_t i = 0; i < pattern.size(); ++i) {
        // if it is a rest note
        if (pattern[i].freq == 0) {
            beat[i].freq = pattern[i].freq;
        }

        beat[i].dur = pattern[i].dur;
    }

    return beat;
}

Composition::Beat
Composition::changePatternOfBeat(const Beat& beat) const
{
    return beat;
}

Sound
Composition::changeFreqOfPitch(const Sound& sound) const
{
    int rand = std::rand() % freqOfPitch.size();
    return Sound(freqOfPitch[rand], sound.dur);
}

Composition::Beat
Composition::changeFreqOfPitch(const Beat& beat) const
{
    Beat b(beat);
    for (Composition::Beat::iterator it = b.begin();
            it != b.end(); ++it) {
        *it = changeFreqOfPitch(*it);
    }
    return b;
}

Composition::Bar
Composition::changeFreqOfPitch(const Bar& bar) const
{
    Bar b(bar);
    for (Composition::Bar::iterator it = b.begin();
            it != b.end(); ++it) {
        *it = changeFreqOfPitch(*it);
    }
    return b;
}

Composition::Music
Composition::changeFreqOfPitch(const Music& music) const
{
    Music m(music);
    for (Composition::Music::iterator it = m.begin();
            it != m.end(); ++it) {
        *it = changeFreqOfPitch(*it);
    }
    return m;
}
