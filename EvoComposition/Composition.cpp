#include <vector>
#include <cstdlib>
#include <cstddef>
#include "Sound.h"
#include "Composition.h"


#if defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L
const std::vector<float> Composition::freq_of_pitch =
    {261.63, 293.66, 329.63, 349.23, 392.0, 440.0, 493.88};

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
const float freq[] = {261.63, 293.66, 329.63, 349.23, 392.0, 440.0, 493.88};

const std::vector<float>
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
Composition::create_initial_solution() const
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

double Composition::evaluate_fitness_value(Music* music) const
{
    double value = 0;
	int avg_frequency[48] = {0} ,kind_of_duration[48] = {0};
    // calculate the fitness value of this Music
	for(int i = 0;i < music[0].num_bar();++i){
		for(int j = 0;j < music[0][i].num_beat();++j){
			int total_duration = 0;
			for(int k = 0;k < music[0][i][j].num_sound();++k){
				if(music[0][i][j][k].frequency() != 0){
				avg_frequency[i * 4 + j] += music[0][i][j][k].frequency() * music[0][i][j][k].duration();
				total_duration += music[0][i][j][k].duration();
				}
			}
			if(total_duration != 0){avg_frequency[i * 4 + j] /= total_duration;}
			if(music[0][i][j][0].duration() == 333){kind_of_duration[i * 4 + j] = 1;}
			else if(music[0][i][j][0].duration() == 750){kind_of_duration[i * 4 + j] = 2;}
			else if(music[0][i][j][0].duration() == 250){kind_of_duration[i * 4 + j] = 4;}
			else{
				if(music[0][i][j][1].duration() == 166){kind_of_duration[i * 4 + j] = 3;}
				else{kind_of_duration[i * 4 + j] = 5;}
			}
		}
	}
	for(int i = 0;i < 12 * 4 - 2;++i){
		if(avg_frequency[i] != avg_frequency[i + 1]){value++;}
		if(avg_frequency[i] != avg_frequency[i + 2]){value++;}
		if(kind_of_duration[i] != kind_of_duration[i + 1]){value++;}
		if(kind_of_duration[i] != kind_of_duration[i + 2]){value++;}
	}

	for(int i = 0;i < 12 * 4 - 1;++i){
		float x = music[0][i / 4][i % 4][0].frequency() ,y = music[0][i / 4][i % 4][0].frequency();
		for(int j = 0;j < music[0][i / 4][i % 4].num_sound();++j){
			if(y != music[0][i / 4][i % 4][j].frequency() && music[0][i / 4][i % 4][j].frequency() != 0){
				y = music[0][i / 4][i % 4][j].frequency();
				break;
			}
		}
		if(x == y){
			for(int j = 0;j < music[0][(i + 1) / 4][(i + 1) % 4].num_sound();++j){
				if(y != music[0][(i + 1) / 4][(i + 1) % 4][j].frequency() 
					&& music[0][(i + 1) / 4][(i + 1) % 4][j].frequency() != 0){
					y = music[0][(i + 1) / 4][(i + 1) % 4][j].frequency();
					break;
				}
			}
			if(x == y){value -= -10000;}
		}
	}


    music->set_fitness_value(value);
    return value;
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
