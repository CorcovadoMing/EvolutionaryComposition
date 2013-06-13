#include <cstdlib>
#include <cstddef>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Composition.h"
#include "GeneticAlgorithm.h"
#include "SoundIO.h"
#include "CompositionIO.h"

void readFromFile(GeneticAlgorithm* algo, const std::string& file_name);
void outputToFile(const std::string& file_name, const GeneticAlgorithm& algo);

std::string int2str(const int&);
/*DO NOT CHANGE THIS THREE FUNC*/
void writeToPy(const GeneticAlgorithm& algo);
void gPyHeader(FILE *, const int&);
void gPyBody(FILE *, const double&, const double&);
void gPyFooter(FILE *);
/*DO NOT CHANGE THIS THREE FUNC*/

int main(int argc, char *argv[])
{
    const std::string music_file_name = "Music.txt";


    GeneticAlgorithm algo;
    unsigned int max_generation = 1000;
    double mutation_rate = 0.8;
    int elitism_individual = -1;

    if (argc > 4) {
        std::cout << "insufficient input parameters." << std::endl;
        std::cout << "Program [elitism_individual] [max_generation] [mutation_rate]" << std::endl;
        exit(1);
    }
    else if (argc >= 2 && argc <= 4) {
        for (int i = 2; i <= argc; ++i) {
            std::istringstream iss(std::string(argv[i-1]));
            switch (i) {
            case 2:
                iss >> elitism_individual;
                break;
            case 3:
                iss >> max_generation;
                break;
            case 4:
                iss >> mutation_rate;
                break;
            }
        }
    }
    else {
        // argc == 1, default parameters
    }

    // if there have music file, read data from the file
    std::ifstream ifs(music_file_name.c_str());
    if (ifs.is_open()) {
        ifs.close();
        readFromFile(&algo, music_file_name);
        algo.set_max_generation(max_generation);
        algo.set_mutation_rate(mutation_rate);
        algo.set_elitism_individual(elitism_individual);
    }
    // if there have not music file, create one.
    else {
        const int beats_per_bar = 4,
                  note_value = 4,
                  total_num_bar = 12,
                  tempo = 60;

        Composition problem(beats_per_bar, note_value,
                      total_num_bar, tempo);

        const int population_size = 4;


        algo = GeneticAlgorithm(problem, population_size,
                                max_generation, mutation_rate,
                                elitism_individual);
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

void readFromFile(GeneticAlgorithm* algo, const std::string& file_name)
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
        *algo = GeneticAlgorithm(problem, population);
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
        unsigned int population_size = algo.population_size();
        for (unsigned int idx = 0; idx < population_size; ++idx) {
            MusicIO::output_to(ofs, algo.individual(idx));
        }
    }
    else {
        std::cout << "The onput file can not be written." << std::endl;
    }
}

void writeToPy(const GeneticAlgorithm& algo)
{
	const std::string filehead = "generatewave";
	const std::string filetype = ".py";
	int nfile;
	FILE *fp;
	const int population_size = algo.population_size();

	for (int idx = 0; idx < population_size; ++idx)
	{
		nfile = idx + 1;
		std::string filename = filehead + int2str(nfile) + filetype;
		fp = fopen(filename.c_str(), "w+");
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

void gPyBody(FILE *fp, const double& freq, const double& dur)
{
	fprintf(fp, "islice(damped_wave(frequency=%f), l*%f),", freq/2.0, dur/1000);
}

void gPyFooter(FILE *fp)
{
	fseek(fp, -1, SEEK_CUR);
	fprintf(fp, ")\n\nchannels = ((waves(),), (waves(), white_noise(amplitude=0.001),))\n");
	fprintf(fp, "samples = compute_samples(channels, None)\n");
	fprintf(fp, "write_wavefile(sys.stdout, samples, None)\n");
}

std::string int2str(const int &i)
{
    std::stringstream stream;
    stream << i;
    return stream.str();
}
