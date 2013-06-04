#include <vector>
#include <cstdlib>
#include <cstddef>
#include "Sound.h"
#include "Composition.h"


#if defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L
const std::vector<int> Composition::freq_of_pitch =
    {262, 294, 330, 349, 392, 440, 494};

const std::vector< std::vector<Sound> > Composition::pattern_of_beat =
    {
        {Sound(Sound::STD_FREQ_PITCH, 333),
         Sound(0, 333), Sound(Sound::STD_FREQ_PITCH, 334)},
        {Sound(Sound::STD_FREQ_PITCH, 750), Sound(Sound::STD_FREQ_PITCH, 250)},
        {Sound(Sound::STD_FREQ_PITCH, 500), Sound(Sound::STD_FREQ_PITCH, 166),
         Sound(Sound::STD_FREQ_PITCH, 166), Sound(Sound::STD_FREQ_PITCH, 168)},
        {Sound(Sound::STD_FREQ_PITCH, 250), Sound(Sound::STD_FREQ_PITCH, 250),
         Sound(Sound::STD_FREQ_PITCH, 250), Sound(Sound::STD_FREQ_PITCH, 250)},
        {Sound(Sound::STD_FREQ_PITCH, 500),
         Sound(Sound::STD_FREQ_PITCH, 250), Sound(Sound::STD_FREQ_PITCH, 250)}
    };
#else
const int freq[] = {262, 294, 330, 349, 392, 440, 494};

const std::vector<int>
Composition::freq_of_pitch(freq, freq+sizeof(freq)/sizeof(freq[0]));

Sound a1[] = {Sound(Sound::STD_FREQ_PITCH, 333),
              Sound(0, 333), Sound(Sound::STD_FREQ_PITCH, 334)};
Sound a2[] = {Sound(Sound::STD_FREQ_PITCH, 750), Sound(Sound::STD_FREQ_PITCH, 250)};
Sound a3[] = {Sound(Sound::STD_FREQ_PITCH, 500), Sound(Sound::STD_FREQ_PITCH, 166),
              Sound(Sound::STD_FREQ_PITCH, 166), Sound(Sound::STD_FREQ_PITCH, 168)};
Sound a4[] = {Sound(Sound::STD_FREQ_PITCH, 250), Sound(Sound::STD_FREQ_PITCH, 250),
              Sound(Sound::STD_FREQ_PITCH, 250), Sound(Sound::STD_FREQ_PITCH, 250)};
Sound a5[] = {Sound(Sound::STD_FREQ_PITCH, 500), Sound(Sound::STD_FREQ_PITCH, 250),
              Sound(Sound::STD_FREQ_PITCH, 250)};
std::vector<Sound> s1(&a1[0], &a1[0]+3);
std::vector<Sound> s2(&a2[0], &a2[0]+2);
std::vector<Sound> s3(&a3[0], &a3[0]+4);
std::vector<Sound> s4(&a4[0], &a4[0]+4);
std::vector<Sound> s5(&a5[0], &a5[0]+3);
std::vector<Sound> s[] = {s1, s2, s3, s4, s5};

const std::vector< std::vector<Sound> >
Composition::pattern_of_beat(s, s+sizeof(s)/sizeof(s[0]));
#endif


Composition::Composition(int beats_per_bar, int note_value,
                         int total_num_bar, int tempo)
    : BEATS_PER_BAR(beats_per_bar), NOTE_VALUE(note_value),
      TOTAL_NUMBER_BAR(total_num_bar), TEMPO(tempo)
{
}

/**
 *  All operations below are related to Evolutionary Algorithm
 */

Music
Composition::createInitialSolution() const
{
    Music music(TOTAL_NUMBER_BAR);

    // for every Bar in Music
    for (int barIdx = 0; barIdx < TOTAL_NUMBER_BAR; ++barIdx) {
        Bar bar(BEATS_PER_BAR);
        // for every Beat in a Bar
        for (int beatIdx = 0; beatIdx < BEATS_PER_BAR; ++beatIdx) {
            Beat beat = changePatternOfBeat(Sound());
            beat = changeFreqOfPitch(beat);
            bar.add_beat(beat);
        }
        music.add_bar(bar);
    }

    return music;
}

//int
//Composition::evaluateDecisionValue(Music* music) const
//{
//}

int
Composition::evaluateObjectiveValue(Music* music) const
{
    int fitness = 0;
    // calculate the fitness of the Music
    // here just assign 5 to all Music
    fitness = 5;
    music->set_degree_of_sounds_good(fitness);
    return fitness;
}

/**
 *  All operations below are related to Composition
 */

Beat
Composition::changePatternOfBeat(const Sound& sound) const
{
    int rand = std::rand() % pattern_of_beat.size();
    std::vector<Sound> pattern = pattern_of_beat[rand];

    Beat beat(pattern);

    for (std::size_t i = 0; i < beat.num_sound(); ++i) {
        // if it is not a rest note
        if (beat[i].frequency() != 0) {
            beat[i].set_frequency(sound.frequency());
        }
    }

    return beat;
}

Beat
Composition::changePatternOfBeat(const Beat& beat) const
{
    // does NOT implement
    return beat;
}

Sound
Composition::changeFreqOfPitch(const Sound& sound) const
{
    int rand = std::rand() % freq_of_pitch.size();
    return Sound(freq_of_pitch[rand], sound.duration());
}

Beat
Composition::changeFreqOfPitch(const Beat& beat) const
{
    Beat b(beat);
    for (std::size_t idx = 0; idx < b.num_sound(); ++idx) {
        b[idx] = changeFreqOfPitch(b[idx]);
    }
    return b;
}

Bar
Composition::changeFreqOfPitch(const Bar& bar) const
{
    Bar b(bar);
    for (std::size_t idx = 0; idx < b.num_beat(); ++idx) {
        b[idx] = changeFreqOfPitch(b[idx]);
    }
    return b;
}

Music
Composition::changeFreqOfPitch(const Music& music) const
{
    Music m(music);
    for (std::size_t idx = 0; idx < m.num_bar(); ++idx) {
        m[idx] = changeFreqOfPitch(m[idx]);
    }
    return m;
}
