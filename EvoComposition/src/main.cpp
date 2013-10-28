#include <fstream>
#include "Composition.h"
#include "GeneticAlgorithm.h"
#include "IOfunction.h"
using namespace std;

//paras
const int beats_per_bar = 4,
          note_value = 4,
          total_num_bar = 12,
          tempo = 120;

const int population_size = 4;
const unsigned int max_generation = 1000;
const double crossover_rate = 0.5;
const double mutation_rate = 0.1;
const int index_elitism_individual = -1;

void readMusicFileOrNewAlgorithm(const string&);
void tryReadFremExistMusicFile(const string&);
void newMainAlgorithm();

GeneticAlgorithm algo;

int main(int argc, char *argv[])
{
    const string music_file_name = "./handler/Music.txt";
    
    readMusicFileOrNewAlgorithm(music_file_name);
    algo.run();
    outputToFile(music_file_name, algo);
    writeToPy(algo);
    return EXIT_SUCCESS;
}

void readMusicFileOrNewAlgorithm(const string&)
{
    std::ifstream ifs(music_file_name.c_str());
    if (ifs.is_open())
    {
        ifs.close(); 
        tryReadFremExistMusicFile(music_file_name);
    } 
    else 
    {
        newMainAlgorithm();
    }
}

void tryReadFremExistMusicFile(const string& music_file_name)
{
    readFromFile(algo, music_file_name);
    algo.set_max_generation(max_generation);
    algo.set_crossover_rate(crossover_rate);
    algo.set_mutation_rate(mutation_rate);
    algo.set_index_elitism_individual(index_elitism_individual);
}

void newMainAlgorithm() 
{
    Composition problem(beats_per_bar, note_value, total_num_bar, tempo);

    algo = GeneticAlgorithm(problem, population_size, max_generation,
                            crossover_rate, mutation_rate,
                            index_elitism_individual);

}


