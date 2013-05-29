#include <cstdlib>
#include <cstddef>
#include "Composition.h"
#include "GeneticAlgorithm.h"

void execute(const Music&, const int&);
/*DO NOT CHANGE THIS THREE FUNC*/
void gPyHeader(FILE *, const int&);
void gPyBody(FILE *, const double&, const double&);
void gPyFooter(FILE *);
/*DO NOT CHANGE THIS THREE FUNC*/

int main()
{
    const int beats_per_bar = 4,
              note_value = 4,
              total_num_bar = 1,
              tempo = 60;

    Composition c(beats_per_bar, note_value,
                  total_num_bar, tempo);

    //const int population_size = 1,
              //max_generation = 1;

	const int population_size = 10,
              max_generation = 1000;
	
    GeneticAlgorithm algo(c, population_size, max_generation);
	
    algo.run();
	
    execute(algo.individual(0) ,tempo);
    return EXIT_SUCCESS;
}

void execute(const Music& music ,const int& tempo)
{
	FILE *fp;
	fp = fopen("generatewave.py" ,"w+");// output file

	/*python script header generate*/
	gPyHeader(fp, tempo);
	
    std::size_t sizeOfBar = music.sizeOfBar();
    for (std::size_t idxMusic = 0; idxMusic < sizeOfBar; ++idxMusic) {

        std::size_t sizeOfBeat = music[idxMusic].sizeOfBeat();
        for (std::size_t idxBar = 0; idxBar < sizeOfBeat; ++idxBar) {

            std::size_t sizeOfSound = music[idxMusic][idxBar].sizeOfSound();
            for (std::size_t idxBeat = 0; idxBeat < sizeOfSound; ++idxBeat) {
			;
                /*Beep(music[idxMusic][idxBar][idxBeat].frequency,
                     music[idxMusic][idxBar][idxBeat].duration * 60 / tempo);

				fprintf(fp ,"%d %d " ,music[idxMusic][idxBar][idxBeat].frequency 
					,music[idxMusic][idxBar][idxBeat].duration * 60 / tempo);*/
				gPyBody(fp, music[idxMusic][idxBar][idxBeat].frequency, music[idxMusic][idxBar][idxBeat].duration);
            }
        }
    }
    
    /*python script footer generate*/
	gPyFooter(fp);
	
	fclose(fp);
}

void gPyHeader(FILE *fp, const int& tempo)
{
	fprintf(fp, "from m_wave import *\n");
	fprintf(fp, "from itertools import *\n");
	fprintf(fp, "import sys\n\n");
	//func def
	fprintf(fp, "def ncycles(iterable, n):\n\treturn chain.from_iterable(repeat(tuple(iterable), n))\n\n");
	
	//func def wave
	fprintf(fp, "def waves():\n\tl = int(44100*%f)\n\n\treturn chain(", (double)1/(tempo/60));
}

void gPyBody(FILE *fp, const double& freq, const double& dur)
{
	fprintf(fp, "islice(damped_wave(frequency=%f), l*%f),", freq, dur/1000);
}


void gPyFooter(FILE *fp)
{
	fseek(fp, -1, SEEK_CUR);
	fprintf(fp, ")\n\nchannels = ((waves(),), (waves(), white_noise(amplitude=0.001),))\n");
	fprintf(fp, "samples = compute_samples(channels, None)\n");
	fprintf(fp, "write_wavefile(sys.stdout, samples, None)\n");
}

