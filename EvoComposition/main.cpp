#include <cstdlib>
#include <cstddef>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "Composition.h"
#include "GeneticAlgorithm.h"
#include "SoundIO.h"
#include "CompositionIO.h"



void readFromFile(GeneticAlgorithm* algo, const std::string& file_name);
void outputToFile(const std::string& file_name, const GeneticAlgorithm& algo);

std::string int2str(const int&);

/*DO NOT CHANGE THIS THREE FUNC*/
int dur2num( const int& );
std::string note2name( const double& );
void writeToPy(const GeneticAlgorithm& algo);
void gPyHeader(FILE *, const int&);
void gPyBody(FILE *, const double&, const double&);
void gPyFooter(FILE *, const int&);
/*DO NOT CHANGE THIS THREE FUNC*/

int main(int argc, char *argv[])
{
    const std::string music_file_name = "Music.txt";


    GeneticAlgorithm algo;
    unsigned int max_generation = 1000;
    double crossover_rate = 0.5;
    double mutation_rate = 0.1;
    int index_elitism_individual = -1;

    if (argc > 5) {
        std::cout << "insufficient input parameters." << std::endl;
        std::cout << "Program [index_elitism_individual] [max_generation] [crossover_rate] [mutation_rate]" << std::endl;
        exit(1);
    }
    else if (argc >= 2 && argc <= 5) {
        for (int i = 2; i <= argc; ++i) {
            std::istringstream iss(argv[i-1]);
            switch (i) {
            case 2:
                iss >> index_elitism_individual;
                break;
            case 3:
                iss >> max_generation;
                break;
            case 4:
                iss >> crossover_rate;
                break;
            case 5:
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
        algo.set_crossover_rate(crossover_rate);
        algo.set_mutation_rate(mutation_rate);
        algo.set_index_elitism_individual(index_elitism_individual);
    }
    // if there have not music file, create one.
    else {
        const int beats_per_bar = 4,
                  note_value = 4,
                  total_num_bar = 12,
                  tempo = 120;

        Composition problem(beats_per_bar, note_value,
                      total_num_bar, tempo);

        const int population_size = 4;


        algo = GeneticAlgorithm(problem, population_size, max_generation,
                                crossover_rate, mutation_rate,
                                index_elitism_individual);
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
    	gPyFooter(fp, nfile);
    	fclose(fp);
    }
}

void gPyHeader(FILE *fp, const int& tempo)
{
	fprintf(fp, "import pysynth\n\n");
	fprintf(fp, "song = (");
}

void gPyBody(FILE *fp, const double& freq, const double& dur)
{
	fprintf(fp, " ('%s', %d ),", note2name(freq).c_str(), dur2num(dur));
}

void gPyFooter(FILE *fp, const int& fn)
{
	fseek(fp, -1, SEEK_CUR);
	fprintf(fp, ")\n\n");
	fprintf(fp, "pysynth.make_wav(song, pause = 0,fn = '%d.wav')\n", fn);
}

std::string int2str(const int &i)
{
    std::stringstream stream;
    stream << i;
    return stream.str();
}

int dur2num( const int& dur )
{
	const int tdur = 4;

	int dur_[] = {333, 334, 666, 1000};
	int num_[] = {12, 12, 6, 4};

	for( int i=0; i<tdur; i++ )
	{
	    if( dur == dur_[i] )
	    	return num_[i];
	}

	return 0;
}


std::string note2name( const double& note )
{
	const int tfreq = 44;

	double freq_[] = {261.6, 277.2, 293.7, 311.1, 329.6, 349.2, 370.0, 392.0, 415.3, 440.0,
    466.2, 493.9, 523.3, 554.4, 587.3, 622.3, 659.3, 698.5, 740.0, 784.0,
    830.6, 880.0, 932.3, 987.8, 1046.5, 1108.7, 1174.7, 1244.5, 1318.5,
    1396.9, 1480.0, 1568.0, 1661.2, 1760.0, 1864.7, 1975.5, 2093.0, 2217.5,
    2349.3, 2489.0, 2637.0, 2793.8, 2960.0, 3136.0};

	std::string name_[] = {"c3", "c#3", "d3", "d#3", "e3", "f3", "gb3", "g3", "ab3", "a4", "bb4", "b4", "c4", "c#4", "d4", "d#4", "e4", "f4", "gb4", "g4", "ab4", "a5", "bb5", "b5", "c5", "c#5", "d5", "d#5", "e5", "f5", "gb5", "g5", "ab5", "a6", "bb6", "b6", "c6", "c#6", "d6", "d#6", "e6", "f6", "gb6", "g6" };

	for( int i=0; i<tfreq; i++ )
	{
		if( note == freq_[i] )
			return name_[i];
	}

	return "r";
}


