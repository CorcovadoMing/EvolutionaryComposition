#include <vector>
#include <cstdlib>
#include <cstddef>
#include "Sound.h"
#include "Composition.h"

#if defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L
const std::vector<float> Composition::freq_of_pitch =
    {261.6, 277.2, 293.7, 311.1, 329.6, 349.2, 370.0, 392.0, 415.3, 440.0, 466.2, 493.9, 523.3, 554.4, 587.3, 622.3, 659.3, 698.5, 740.0, 784.0, 830.6, 880.0, 932.3, 987.8, 1046.5, 1108.7, 1174.7, 1244.5, 1318.5, 1396.9, 1480.0, 1568.0, 1661.2, 1760.0, 1864.7, 1975.5, 2093.0, 2217.5, 2349.3, 2489.0, 2637.0, 2793.8, 2960.0, 3136.0};
//
const std::vector<double> Composition::C_LICK = {261.6, 293.7, 311.1, 329.6, 349.2, 370.0, 392.0, 466.2, 523.3, 587.3, 622.3, 659.3, 698.5, 740.0, 784.0, 932.3, 1046.5, 1174.7, 1244.5, 1318.5, 1396.9, 1480.0, 1568.0, 1864.7, 2093.0};
const std::vector<double> Composition::F_LICK = {349.2, 392.0, 440.0, 466.2, 523.3, 587.3, 659.3, 698.5, 784.0, 880.0, 932.3, 1046.5, 1174.7, 1318.5, 1396.9, 1568.0, 1760.0, 1864.7, 2093.0, 2349.3, 2637.0};
const std::vector<double> Composition::G_LICK = {392.0, 440.0, 492.9, 523.3, 587.3, 659.3, 698.5, 784.0, 880.0, 987.8, 1046.5, 1174.7, 1318.5, 1396.9, 1568.0, 1760.0, 1975.7, 2093.0, 2349.3, 2637.0, 2793.8, 3136.0};
//

const std::vector< std::vector<Sound> > Composition::pattern_of_beat =
    {
        {Sound(Sound::STD_FREQ_PITCH, 333),
         Sound(0, 333), Sound(Sound::STD_FREQ_PITCH, 334)},
        {Sound(Sound::STD_FREQ_PITCH, 750), Sound(Sound::STD_FREQ_PITCH, 250)},
        {Sound(Sound::STD_FREQ_PITCH, 500), Sound(Sound::STD_FREQ_PITCH, 166),
         Sound(Sound::STD_FREQ_PITCH, 166), Sound(Sound::STD_FREQ_PITCH, 168)},
        {Sound(Sound::STD_FREQ_PITCH, 250), Sound(Sound::STD_FREQ_PITCH, 250),
         Sound(Sound::STD_FREQ_PITCH, 250), Sound(Sound::STD_FREQ_PITCH, 250)},
        {Sound(Sound::STD_FREQ_PITCH, 750),
         Sound(Sound::STD_FREQ_PITCH, 125), Sound(Sound::STD_FREQ_PITCH, 125)},
        {Sound(Sound::STD_FREQ_PITCH, 1000)},
        {Sound(Sound::STD_FREQ_PITCH, 2000)},
        {Sound(Sound::STD_FREQ_PITCH, 3000)},
        {Sound(Sound::STD_FREQ_PITCH, 4000)}
    };
#else
const float freq[] = {261.6, 277.2, 293.7, 311.1, 329.6, 349.2, 370.0, 392.0, 415.3, 440.0, 466.2, 493.9, 523.3, 554.4, 587.3, 622.3, 659.3, 698.5, 740.0, 784.0, 830.6, 880.0, 932.3, 987.8, 1046.5, 1108.7, 1174.7, 1244.5, 1318.5, 1396.9, 1480.0, 1568.0, 1661.2, 1760.0, 1864.7, 1975.5, 2093.0, 2217.5, 2349.3, 2489.0, 2637.0, 2793.8, 2960.0, 3136.0};

//
const double C_LICK_[] = {261.6, 293.7, 311.1, 329.6, 349.2, 370.0, 392.0, 466.2, 523.3, 587.3, 622.3, 659.3, 698.5, 740.0, 784.0, 932.3, 1046.5, 1174.7, 1244.5, 1318.5, 1396.9, 1480.0, 1568.0, 1864.7, 2093.0};
const double F_LICK_[] = {349.2, 392.0, 440.0, 466.2, 523.3, 587.3, 659.3, 698.5, 784.0, 880.0, 932.3, 1046.5, 1174.7, 1318.5, 1396.9, 1568.0, 1760.0, 1864.7, 2093.0, 2349.3, 2637.0};
const double G_LICK_[] = {392.0, 440.0, 492.9, 523.3, 587.3, 659.3, 698.5, 784.0, 880.0, 987.8, 1046.5, 1174.7, 1318.5, 1396.9, 1568.0, 1760.0, 1975.7, 2093.0, 2349.3, 2637.0, 2793.8, 3136.0};

const std::vector<double>
Composition::C_LICK(C_LICK_, C_LICK_+sizeof(C_LICK_)/sizeof(C_LICK_[0]));
const std::vector<double>
Composition::F_LICK(F_LICK_, F_LICK_+sizeof(F_LICK_)/sizeof(F_LICK_[0]));
const std::vector<double>
Composition::G_LICK(G_LICK_, G_LICK_+sizeof(G_LICK_)/sizeof(G_LICK_[0]));
//

const std::vector<float>
Composition::freq_of_pitch(freq, freq+sizeof(freq)/sizeof(freq[0]));

Sound a1[] = {Sound(Sound::STD_FREQ_PITCH, 333),
              Sound(0, 333), Sound(Sound::STD_FREQ_PITCH, 334)};
Sound a2[] = {Sound(Sound::STD_FREQ_PITCH, 750), Sound(Sound::STD_FREQ_PITCH, 250)};
Sound a3[] = {Sound(Sound::STD_FREQ_PITCH, 500), Sound(Sound::STD_FREQ_PITCH, 166),
              Sound(Sound::STD_FREQ_PITCH, 166), Sound(Sound::STD_FREQ_PITCH, 168)};
Sound a4[] = {Sound(Sound::STD_FREQ_PITCH, 250), Sound(Sound::STD_FREQ_PITCH, 250),
              Sound(Sound::STD_FREQ_PITCH, 250), Sound(Sound::STD_FREQ_PITCH, 250)};
Sound a5[] = {Sound(Sound::STD_FREQ_PITCH, 750), Sound(Sound::STD_FREQ_PITCH, 125),
              Sound(Sound::STD_FREQ_PITCH, 125)};
Sound a6[] = {Sound(Sound::STD_FREQ_PITCH, 1000)};
Sound a7[] = {Sound(Sound::STD_FREQ_PITCH, 2000)};
Sound a8[] = {Sound(Sound::STD_FREQ_PITCH, 3000)};
Sound a9[] = {Sound(Sound::STD_FREQ_PITCH, 4000)};
std::vector<Sound> s1(&a1[0], &a1[0]+3);
std::vector<Sound> s2(&a2[0], &a2[0]+2);
std::vector<Sound> s3(&a3[0], &a3[0]+4);
std::vector<Sound> s4(&a4[0], &a4[0]+4);
std::vector<Sound> s5(&a5[0], &a5[0]+3);
std::vector<Sound> s6(&a6[0], &a6[0]+1);
std::vector<Sound> s7(&a7[0], &a7[0]+1);
std::vector<Sound> s8(&a8[0], &a8[0]+1);
std::vector<Sound> s9(&a9[0], &a9[0]+1);
std::vector<Sound> s[] = {s1, s2, s3, s4, s5, s6, s7, s8, s9};

const std::vector< std::vector<Sound> >
Composition::pattern_of_beat(s, s+sizeof(s)/sizeof(s[0]));
#endif


//functions for fitness calc

bool
isIn( const double& elem, const std::vector<double>& list )
{
	for( int i=0; i<list.size(); i++ )
		if( elem == list[i] ) return true;
	return false;
}

//


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
/*
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
*/

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
