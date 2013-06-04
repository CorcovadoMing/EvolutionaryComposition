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

void writeToPy(const Music& music, int tempo);
/*DO NOT CHANGE THIS THREE FUNC*/
void gPyHeader(FILE *, int);
void gPyBody(FILE *, double, double);
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
        std::cout << "read first" << std::endl;
        readFromFile(&algo, max_generation, music_file_name);
        std::cout << "read second" << std::endl;
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
    std::cout << "run" << std::endl;
    // run the algorithm
    algo.run();
    std::cout << "output" << std::endl;
    outputToFile(music_file_name, algo);

    return EXIT_SUCCESS;
}

void readFromFile(GeneticAlgorithm* algo, int max_generation,
                  const std::string& file_name)
{
    std::ifstream ifs(file_name.c_str());
    if (ifs.is_open()) {
        // read the information of problem
        Composition problem = CompositionIO::input_from(ifs);
        std::cout << "Music" << std::endl;
        // read each Music
        std::vector<Music> population;
        while (ifs.good()) {
            Music music = SoundIO::input_from(ifs);
            population.push_back(music);
        }
        std::cout << "set algorithm" << std::endl;
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
        const int population_size = algo.populationSize();
        for (int idx = 0; idx < population_size; ++idx) {
            SoundIO::output_to(ofs, algo.individual(idx));
        }
    }
    else {
        std::cout << "The onput file can not be written." << std::endl;
    }
}

void writeToPy(const Music& music, int tempo)
{
    FILE *fp;
    fp = fopen("generatewave.py" ,"w+");  // output file

    /*python script header generate*/
    gPyHeader(fp, tempo);

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

    /*python script footer generate*/
    gPyFooter(fp);

    fclose(fp);
}

void gPyHeader(FILE *fp, int tempo)
{
	fprintf(fp, "from m_wave import *\n");
	fprintf(fp, "from itertools import *\n");
	fprintf(fp, "import sys\n\n");
	//func def
	fprintf(fp, "def ncycles(iterable, n):\n\treturn chain.from_iterable(repeat(tuple(iterable), n))\n\n");

	//func def wave
	fprintf(fp, "def waves():\n\tl = int(44100*%f)\n\n\treturn chain(", (double)1/(tempo/60));
}

void gPyBody(FILE *fp, double freq, double dur)
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
