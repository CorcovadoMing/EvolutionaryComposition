#include <vector>
#include <cstdlib>
#include <cstddef>
#include "Music.h"
#include "Bar.h"
#include "Beat.h"
#include "Sound.h"
#include "Composition.h"

const std::vector<float> Composition::freq_of_pitch =
    {261.6, 277.2, 293.7, 311.1, 329.6, 349.2, 370.0, 392.0, 415.3, 440.0,
    466.2, 493.9, 523.3, 554.4, 587.3, 622.3, 659.3, 698.5, 740.0, 784.0,
    830.6, 880.0, 932.3, 987.8, 1046.5, 1108.7, 1174.7, 1244.5, 1318.5,
    1396.9, 1480.0, 1568.0, 1661.2, 1760.0, 1864.7, 1975.5, 2093.0, 2217.5,
    2349.3, 2489.0, 2637.0, 2793.8, 2960.0, 3136.0};

const std::vector<double> Composition::C_LICK =
    {261.6, 293.7, 311.1, 329.6, 349.2, 370.0, 392.0, 466.2, 523.3, 587.3,
    622.3, 659.3, 698.5, 740.0, 784.0, 932.3, 1046.5, 1174.7, 1244.5,
    1318.5, 1396.9, 1480.0, 1568.0, 1864.7, 2093.0};
const std::vector<double> Composition::F_LICK =
    {349.2, 392.0, 440.0, 466.2, 523.3, 587.3, 659.3, 698.5, 784.0, 880.0,
    932.3, 1046.5, 1174.7, 1318.5, 1396.9, 1568.0, 1760.0, 1864.7, 2093.0,
    2349.3, 2637.0};
const std::vector<double> Composition::G_LICK =
    {392.0, 440.0, 492.9, 523.3, 587.3, 659.3, 698.5, 784.0, 880.0, 987.8,
    1046.5, 1174.7, 1318.5, 1396.9, 1568.0, 1760.0, 1975.7, 2093.0, 2349.3,
    2637.0, 2793.8, 3136.0};

const std::vector< std::vector<Sound> > Composition::pattern_of_beat =
{
    {Sound(Sound::STD_FREQ_PITCH, 333),Sound(Sound::STD_FREQ_PITCH, 333), Sound(Sound::STD_FREQ_PITCH, 334)},
    {Sound(Sound::STD_FREQ_PITCH, 666), Sound(Sound::STD_FREQ_PITCH, 334)},
    {Sound(Sound::STD_FREQ_PITCH, 1000)}
};


bool isIn( const double& elem, const std::vector<double>& list )
{
    for( std::size_t i=0; i<list.size(); i++ )
        if( elem == list[i] ) return true;
    return false;
}

Composition::Composition(int beats_per_bar, int note_value,
                         int total_num_bar, int tempo)
: BEATS_PER_BAR(beats_per_bar), NOTE_VALUE(note_value),
                TOTAL_NUMBER_BAR(total_num_bar), TEMPO(tempo){}

Music Composition::create_initial_solution() const
{
    Music music(TOTAL_NUMBER_BAR);
    for (int barIdx = 0; barIdx < TOTAL_NUMBER_BAR; ++barIdx) {
        Bar bar(BEATS_PER_BAR);
        for (int beatIdx = 0; beatIdx < BEATS_PER_BAR; ++beatIdx) {
            Beat beat = changePatternOfBeat(Sound());
            beat = changeFreqOfPitch(beat);
            bar.add_beat(beat);
        }
        music.add_bar(bar);
    }
    return music;
}

double
Composition::pitchFitness( const Music& music ) const
{
    double fitness = 0;
    double exp_avg = 523.3;
    const double hope_avg_upper = 784.0;
    const double hope_avg_lower = 392.0;

    std::size_t num_bar = music.num_bar();
    for (std::size_t idxMusic = 0; idxMusic < num_bar; ++idxMusic) {

        //for part3 score use
        double bar_avg = 0;

        std::size_t num_beat = music[idxMusic].num_beat();
        for (std::size_t idxBar = 0; idxBar < num_beat; ++idxBar) {

            //for part3 score use
            double beat_avg = 0;

            std::size_t num_sound = music[idxMusic][idxBar].num_sound();
            for (std::size_t idxBeat = 0; idxBeat < num_sound; ++idxBeat) {

                // part1 score whether pitch is in chord
                switch( idxMusic ){
                case 1:
                case 4:
                case 5:
                case 9:
                    if( isIn( music[idxMusic][idxBar][idxBeat].frequency(), F_LICK ))
                        fitness+=300;
                    break;
                case 8:
                    if( isIn( music[idxMusic][idxBar][idxBeat].frequency(), G_LICK ))
                        fitness+=300;
                    break;
                default:
                    if( isIn( music[idxMusic][idxBar][idxBeat].frequency(), C_LICK ))
                        fitness+=300;
                }
                //end part1 score

                //part2 score jumpping-step
                if( music[idxMusic][idxBar][idxBeat].frequency()/2.0 >= exp_avg || music[idxMusic][idxBar][idxBeat].frequency()*2.0 <= exp_avg )
                    fitness-=100; //-100 is this is truely strong penalty
                exp_avg = music[idxMusic][idxBar][idxBeat].frequency();
                //end part2 score

                //part3 score avarage pitch
                beat_avg += music[idxMusic][idxBar][idxBeat].frequency();
            }

            beat_avg /= num_sound;
            bar_avg += beat_avg;
        }

        bar_avg /= num_bar;
        if(bar_avg >= hope_avg_upper || bar_avg <= hope_avg_lower )
            fitness-=500;
    }
    return fitness;
}

double
Composition::beatFitness( const Music& music ) const
{
    double fitness = 0;
    int note_avg = 0;
    const int exp_avg = 12;

    std::size_t num_bar = music.num_bar();
    for (std::size_t idxMusic = 0; idxMusic < num_bar; ++idxMusic) {

        std::size_t num_beat = music[idxMusic].num_beat();
        for (std::size_t idxBar = 0; idxBar < num_beat; ++idxBar) {

            note_avg += music[idxMusic][idxBar].num_sound(); //for part1 score use

            std::size_t num_sound = music[idxMusic][idxBar].num_sound();
            for (std::size_t idxBeat = 0; idxBeat < num_sound; ++idxBeat) {



            }
        }

        //part1 score for avg number of note each TWO BAR
        if( idxMusic % 2 == 1 )
        {
            note_avg /= 2;
            if( note_avg >= exp_avg+4 || note_avg <= exp_avg-4 )
                fitness -= 70;
            else
                fitness += 100;
            note_avg = 0;
        }
        //end part1 score
    }
    return fitness;
}

Beat
Composition::changePatternOfBeat(const Sound& sound) const
{
    int rand = std::rand() % pattern_of_beat.size();
    std::vector<Sound> pattern = pattern_of_beat[rand];
    Beat beat(pattern);

    if (sound.isRestNote()) {
        // do nothing
    }
    else {
        // change each frequency of beat to input sound
        for (std::size_t i = 0; i < beat.num_sound(); ++i) {

            if (beat[i].isRestNote()) {
                // do nothing
            }
            else {
                beat[i].set_frequency(sound.frequency());
            }
        }
    }
    return beat;
}

Beat
Composition::changePatternOfBeat(const Beat& beat) const
{
    int rand = std::rand() % pattern_of_beat.size();
    std::vector<Sound> pattern = pattern_of_beat[rand];
    Beat new_beat(pattern);

    // change each frequency of new beat to input beat
    std::size_t idx_new_sound = 0, idx_sound = 0;
    std::size_t num_new_sound = new_beat.num_sound(), num_sound = beat.num_sound();
    while ((idx_new_sound < num_new_sound) && (idx_sound < num_sound)) {

        if (new_beat[idx_new_sound].isRestNote()) {
            // do not change
            ++idx_new_sound;
        }
        else if (beat[idx_sound].isRestNote()) {
            // do not change
            ++idx_sound;
        }
        else {
            new_beat[idx_new_sound].set_frequency(beat[idx_sound].frequency());
            ++idx_new_sound;
            ++idx_sound;
        }
    }
    // if there are some note of new neat does not be changed
    while (idx_new_sound < num_new_sound) {

        if (new_beat[idx_new_sound].isRestNote()) {
            // do not change
        }
        else {
            // randomly select frequency
            int rand = std::rand() % freq_of_pitch.size();
            new_beat[idx_new_sound].set_frequency(freq_of_pitch[rand]);
        }
        ++idx_new_sound;
    }
    return new_beat;
}

Sound
Composition::changeFreqOfPitch(const Sound& sound) const
{
    // if it is a rest note
    if (sound.isRestNote()) {
        return sound;
    }
    else {
        int rand = std::rand() % freq_of_pitch.size();
        return Sound(freq_of_pitch[rand], sound.duration());
    }
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
