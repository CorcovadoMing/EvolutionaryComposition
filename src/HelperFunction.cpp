#include <cstdlib>
#include <cstddef>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <cstdarg>
#include <cstdio>
#include "Composition.h"
#include "GeneticAlgorithm.h"
#include "Helperfunction.h"

using namespace std;

void readFromFile(GeneticAlgorithm& algo, const std::string& file_name)
{
    std::ifstream ifs(file_name.c_str());
    if (ifs.is_open()) 
    {
        Composition problem = Composition::input_from(ifs);

        std::vector<Music> population;
        while (ifs.good()) 
        {
            Music music;
            if (Music::input_from(&music, ifs)) 
            {
                population.push_back(music);
            }
        }
        algo = GeneticAlgorithm(problem, population);
    }
    else
    { 
        std::cout << "The input file can not be read." << std::endl;
    }
}

void outputToFile(const std::string& file_name, const GeneticAlgorithm& algo)
{
    std::ofstream ofs(file_name.c_str());
    if (ofs.is_open()) {
        Composition problem = algo.problem();

        // output the information of problem
        Composition::output_to(ofs, problem);

        // output each Music
        unsigned int population_size = algo.population_size();
        for (unsigned int idx = 0; idx < population_size; ++idx) {
            Music::output_to(ofs, algo.individual(idx));
        }
    }
    else {
        std::cout << "The onput file can not be written." << std::endl;
    }
}

void writeToPy(const GeneticAlgorithm& algo)
{
    const std::string filehead = "./handler/generatewave";
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

const int dur2num( const int& duration )
{
    vector<int> durationCollection = {333, 334, 666, 1000};
    vector<int> notetime = {12, 12, 6, 4};

    for( auto i = 0; i < durationCollection.size(); i++ )
    {
        if( duration == durationCollection[i] )
            return notetime[i];
    }
    return 0;
}


const std::string note2name( const double& frequency )
{
    const string restnote = "r";
    vector<double> frequencyCollection = {261.6, 277.2, 293.7, 311.1, 329.6, 349.2, 370.0, 392.0, 415.3, 440.0,
    466.2, 493.9, 523.3, 554.4, 587.3, 622.3, 659.3, 698.5, 740.0, 784.0,
    830.6, 880.0, 932.3, 987.8, 1046.5, 1108.7, 1174.7, 1244.5, 1318.5,
    1396.9, 1480.0, 1568.0, 1661.2, 1760.0, 1864.7, 1975.5, 2093.0, 2217.5,
    2349.3, 2489.0, 2637.0, 2793.8, 2960.0, 3136.0};
    vector<string> notename = {"c3", "c#3", "d3", "d#3", "e3", "f3", "gb3", "g3", 
    "ab3", "a4", "bb4", "b4", "c4", "c#4", "d4", "d#4", "e4", "f4", "gb4", "g4", "ab4", 
    "a5", "bb5", "b5", "c5", "c#5", "d5", "d#5", "e5", "f5", "gb5", "g5", "ab5", "a6", 
    "bb6", "b6", "c6", "c#6", "d6", "d#6", "e6", "f6", "gb6", "g6" };

    for( auto i = 0; i < frequencyCollection.size(); i++ )
    {
        if( frequency == frequencyCollection[i] )
            return notename[i];
    }
    return restnote;
}