#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "Composition.h"
#include "GeneticAlgorithm.h"
#include "Helperfunction.h"
using namespace std;
extern GeneticAlgorithm Main_Genetic_Algorithm;

void gPyHeader(FILE *, const int&);
void gPyBody(FILE *, const double&, const double&);
void gPyFooter(FILE *, const int&);

void readFromFile(const string& file_name)
{
    ifstream ifs(file_name.c_str());
    if (ifs.is_open()) 
    {
        Composition problem = Composition::input_from(ifs);
        vector<Music> population;
        while (ifs.good()) 
        {
            Music music;
            if (Music::input_from(&music, ifs)) 
            {
                population.push_back(music);
            }
        }
        Main_Genetic_Algorithm = GeneticAlgorithm(problem, population);
    }
    else
    { 
        cout << "The input file can not be read." << endl;
    }
}

void outputToFile(const string& file_name)
{
    ofstream ofs(file_name.c_str());
    if (ofs.is_open()) {
        Composition problem = Main_Genetic_Algorithm.problem();

        // output the information of problem
        Composition::output_to(ofs, problem);

        // output each Music
        unsigned int population_size = Main_Genetic_Algorithm.population_size();
        for (unsigned int idx = 0; idx < population_size; ++idx) {
            Music::output_to(ofs, Main_Genetic_Algorithm.individual(idx));
        }
    }
    else {
        cout << "The onput file can not be written." << endl;
    }
}

void writeToPy()
{
    const string filehead = "./handler/generatewave"; 
    const string filetype = ".py";
    const int population_size = Main_Genetic_Algorithm.population_size();
    FILE *fp;
    
    for (int idx = 0; idx < population_size; ++idx)
    {
        string filename = filehead + int2str(idx+1) + filetype;
        fp = fopen(filename.c_str(), "w+");
        Music music = Main_Genetic_Algorithm.individual(idx);
        gPyHeader(fp, Main_Genetic_Algorithm.problem().TEMPO);
        for (auto idxMusic = 0; idxMusic < music.num_bar(); ++idxMusic) {
            for (auto idxBar = 0; idxBar < music[idxMusic].num_beat(); ++idxBar) {
                for (auto idxBeat = 0; idxBeat < music[idxMusic][idxBar].num_sound(); ++idxBeat) {
                    gPyBody(fp, music[idxMusic][idxBar][idxBeat].frequency(),
                                music[idxMusic][idxBar][idxBeat].duration());
                }
            }
        }
        gPyFooter(fp, idx+1);
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

const string int2str(const int &inputInt)
{
    stringstream sstream;
    sstream << inputInt;
    return sstream.str();
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


const string note2name( const double& frequency )
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