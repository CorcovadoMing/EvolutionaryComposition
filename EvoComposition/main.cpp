#include <cstdlib>
#include <cstddef>
#include <fstream>
#include <iostream>
#include "Composition.h"
#include "GeneticAlgorithm.h"
#include "SoundIO.h"
#include "CompositionIO.h"

void readFromFile(GeneticAlgorithm* algo, int max_generation,
                  const std::string& file_name);
void outputToFile(const std::string& file_name, const GeneticAlgorithm& algo);

void writeToPy(const GeneticAlgorithm& algo);
/*DO NOT CHANGE THIS THREE FUNC*/
void gPyHeader(FILE *, const int&);
void gPyBody(FILE *, const int&, const double&);
void gPyFooter(FILE *);
/*DO NOT CHANGE THIS THREE FUNC*/

int main()
{
    const std::string music_file_name = "Music.txt";


    GeneticAlgorithm algo;
    const int max_generation = 1000;


    // if there have music file, read data from the file
    std::ifstream ifs(music_file_name.c_str());
    if (ifs.is_open()) {
        ifs.close();
        readFromFile(&algo, max_generation, music_file_name);
    }
    // if there have not music file, create one.
    else {
        const int beats_per_bar = 4,
                  note_value = 4,
                  total_num_bar = 12,
                  tempo = 60;

        Composition problem(beats_per_bar, note_value,
                      total_num_bar, tempo);

        const int population_size = 5;


        algo = GeneticAlgorithm(problem, max_generation, population_size);
    }

    // if you want to listen the music,
    // you can use the next code by specific index
    //algo.individual(0).listen();

    // run the algorithm
    algo.run();

    outputToFile(music_file_name, algo);
    writeToPy(algo);

    return EXIT_SUCCESS;
}

void readFromFile(GeneticAlgorithm* algo, int max_generation,
                  const std::string& file_name)
{
    std::ifstream ifs(file_name.c_str());
    if (ifs.is_open()) {
        // read the information of problem
        Composition problem = CompositionIO::input_from(ifs);

        // read each Music
        std::vector<Music> population;
        while (ifs.good()) {
            Music music;
            if (MusicIO::input_from(&music, ifs)) {
                population.push_back(music);
            }
        }
        // set algorithm
        *algo = GeneticAlgorithm(problem, max_generation, population);
    }
    else {
        std::cout << "The input file can not be read." << std::endl;
    }
}

void outputToFile(const std::string& file_name, const GeneticAlgorithm& algo)
{
    std::ofstream ofs(file_name.c_str());
    if (ofs.is_open()) {
        Composition problem = algo.problem();

        // output the information of problem
        CompositionIO::output_to(ofs, problem);

        // output each Music
        const int population_size = algo.population_size();
        for (int idx = 0; idx < population_size; ++idx) {
            MusicIO::output_to(ofs, algo.individual(idx));
        }
    }
    else {
        std::cout << "The onput file can not be written." << std::endl;
    }
}

void writeToPy(const GeneticAlgorithm& algo)
{
	const char *filehead = "generatewave";
	const char *filetype = ".py";
	char *filename;
	int nfile;
	FILE *fp;
	const int population_size = algo.population_size();
	
	for (int idx = 0; idx < population_size; ++idx) 
	{
		nfile = idx + 1;
		sprintf(filename, "%s%d%s", filehead, nfile, filetype);
		fp = fopen(filename, "w+");
		Music music = algo.individual(idx);
		
    	//python script header generate
    	gPyHeader(fp, algo.problem().TEMPO);
    	std::size_t num_bar = music.num_bar();
    	for (std::size_t idxMusic = 0; idxMusic < num_bar; ++idxMusic) {

        	std::size_t num_beat = music[idxMusic].num_beat();
        	for (std::size_t idxBar = 0; idxBar < num_beat; ++idxBar) {

            	std::size_t num_sound = music[idxMusic][idxBar].num_sound();
            	for (std::size_t idxBeat = 0; idxBeat < num_sound; ++idxBeat) {
                	gPyBody(fp,
                        music[idxMusic][idxBar][idxBeat].frequency(),
                        music[idxMusic][idxBar][idxBeat].duration());
                }
            }
        }
        //python script footer generate
    	gPyFooter(fp);
    	fclose(fp);
    }
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

void gPyBody(FILE *fp, const int& freq, const double& dur)
{
	fprintf(fp, "islice(damped_wave(frequency=%d), l*%f),", freq, dur/1000);
}

void gPyFooter(FILE *fp)
{
	fseek(fp, -1, SEEK_CUR);
	fprintf(fp, ")\n\nchannels = ((waves(),), (waves(), white_noise(amplitude=0.001),))\n");
	fprintf(fp, "samples = compute_samples(channels, None)\n");
	fprintf(fp, "write_wavefile(sys.stdout, samples, None)\n");
}
