#include <fstream>
#include "Composition.h"
#include "GeneticAlgorithm.h"
#include "HelperFunction.h"
using namespace std;

//Parameters of Music
const int Beat_Per_Bar = 4,
          Note_Value = 4,
          Total_Num_Bar = 12,
          Tempo = 120;
          
//Parameters of Genetic ALgorithm
const int Population_Size = 4;
const unsigned int Max_Generation = 1000;
const double Crossover_Rate = 0.5;
const double Mutation_Rate = 0.1;
const int Index_Elitism_Individual = -1;

bool isMusicFileExist(const string&);
void readMusicFileOrNewAlgorithm(const string&);
void tryReadFremExistMusicFile(const string&);
void newMainAlgorithm();

GeneticAlgorithm Main_Genetic_Algorithm;

int main(int argc, char *argv[])
{
    const string music_file_name = "Music";
    readMusicFileOrNewAlgorithm(music_file_name);
    Main_Genetic_Algorithm.run();
    outputToFile(music_file_name);
    writeToPy();
    return EXIT_SUCCESS;
}

bool isMusicFileExist(const string& music_file_name)
{
    ifstream ifs(music_file_name.c_str());
    if(ifs.is_open()){ ifs.close(); return true;} 
    else return false;
}

void readMusicFileOrNewAlgorithm(const string& music_file_name)
{
    isMusicFileExist(music_file_name) ?
    tryReadFremExistMusicFile(music_file_name) : newMainAlgorithm();
}

void tryReadFremExistMusicFile(const string& music_file_name)
{
    readFromFile(music_file_name);
    Main_Genetic_Algorithm.setMaxGeneration(Max_Generation);
    Main_Genetic_Algorithm.setCrossoverRate(Crossover_Rate);
    Main_Genetic_Algorithm.setMutationRate(Mutation_Rate);
    Main_Genetic_Algorithm.setIndexElitismIndividual(Index_Elitism_Individual);
}

void newMainAlgorithm() 
{
    Composition problem(Beat_Per_Bar, Note_Value, Total_Num_Bar, Tempo);
    Main_Genetic_Algorithm = GeneticAlgorithm(problem, Population_Size, Max_Generation,
                            Crossover_Rate, Mutation_Rate,
                            Index_Elitism_Individual);
}


