#include <cstdlib>
#include <cstddef>
#include <fstream>
#include <iostream>
#include "Composition.h"
#include "GeneticAlgorithm.h"

#if defined(_WIN32) || defined(_WIN64)
#include "windows.h"
#endif

void readFromFile(Composition *composition, int *population_size,
                  std::vector<Music> *population,
                  const std::string& file_name);
Music readMusic(std::istream& is);
void outputToFile(const std::string& file_name, const GeneticAlgorithm& ga);
void outputMusic(std::ostream& os, const Music& music);


void execute(const Music& music)
{
    std::size_t sizeOfBar = music.sizeOfBar();
    for (std::size_t idxMusic = 0; idxMusic < sizeOfBar; ++idxMusic) {

        std::size_t sizeOfBeat = music[idxMusic].sizeOfBeat();
        for (std::size_t idxBar = 0; idxBar < sizeOfBeat; ++idxBar) {

            std::size_t sizeOfSound = music[idxMusic][idxBar].sizeOfSound();
            for (std::size_t idxBeat = 0; idxBeat < sizeOfSound; ++idxBeat) {

                Beep(music[idxMusic][idxBar][idxBeat].frequency,
                     music[idxMusic][idxBar][idxBeat].duration);
            }
        }
    }

}

int main()
{
    /*std::ifstream ifs("input.txt");
    if (ifs.is_open()) {

        const int max_generation = 1000;

        Composition c;
        int population_size = 0;
        std::vector<Music> population;

        readFromFile(&c, &population_size, &population, "input.txt");

        GeneticAlgorithm algo(c, population_size, max_generation, population);

        algo.run();

        outputToFile("output.txt", algo);
    }
    else {*/
        const int beats_per_bar = 4,
                  note_value = 4,
                  total_num_bar = 2,
                  tempo = 120;

        Composition c(beats_per_bar, note_value,
                      total_num_bar, tempo);


        const int population_size = 10,
                  max_generation = 1000;

        GeneticAlgorithm algo(c, population_size, max_generation);

        algo.run();

        //execute(algo.individual(0));
        outputToFile("output.txt", algo);
    //}

    return EXIT_SUCCESS;
}

/*void readFromFile(Composition *composition, int *population_size,
                  std::vector<Music> *population,
                  const std::string& file_name)
{
    std::ifstream ifs(file_name.c_str());
    if (ifs.is_open()) {
        // read the information of problem
        int beats_per_bar = 0, note_value = 0,
            total_num_bar = 0, tempo = 0;
        ifs >> beats_per_bar >> note_value >> total_num_bar >> tempo;
        *composition = Composition(beats_per_bar, note_value,
                                   total_num_bar, tempo);

        // read each Music
        int *population_size = 0;
        while (ifs.good()) {
            (*population).push_back(readMusic(ifs));
            ++(*population_size);
        }
    }
    else {
        std::cout << "The input file is not be read." << std::endl;
    }
}

Music readMusic(std::istream& is)
{
    Music music;

    // parse Music
    std::string one_music;
    std::getline(is, one_music);
    std::istringstream iss_one_music(one_music);
    while (iss_one_music.good()) {
        Bar bar;

        // parse Bar
        std::string one_bar;
        std::getline(iss_one_music, one_bar, '|');
        std::istringstream iss_one_bar(one_bar);
        while (iss_one_bar.good()) {
            Beat beat;

            // parse Beat
            std::string one_beat;
            std::getline(iss_one_bar, one_beat, '\t');
            std::istringstream iss_one_beat(one_beat);
            while (iss_one_beat.good()) {
                // parse Sound
                int frequency = 0, duration = 0;
                iss_one_beat >> frequency >> duration;

                beat.addSound(Sound(frequency, duration));
            }
            bar.addBeat(beat);
        }
        music.addBar(bar);
    }
}*/

void outputToFile(const std::string& file_name, const GeneticAlgorithm& ga)
{
    std::ofstream ofs(file_name.c_str());
    if (ofs.is_open()) {
        Composition problem = ga.problem();
        // output the information of problem
        ofs << problem.BEATS_PER_BAR << " " << problem.NOTE_VALUE << " " <<
        problem.TOTAL_NUMBER_BAR << " " << problem.TEMPO << std::endl;

        // output each Music
        const int population_size = ga.populationSize();
        for (int idx = 0; idx < population_size; ++idx) {
            outputMusic(ofs, ga.individual(idx));
        }
    }
    else {
        std::cout << "The onput file is not be written." << std::endl;
    }
}

void outputMusic(std::ostream& os, const Music& music)
{
    std::size_t size_Bar = music.sizeOfBar();
    for (std::size_t idxMusic = 0; idxMusic < size_Bar; ++idxMusic) {

        os << "|";

        std::size_t size_Beat = music[idxMusic].sizeOfBeat();
        for (std::size_t idxBar = 0; idxBar < size_Beat; ++idxBar) {

            os << '\t';

            std::size_t size_Sound = music[idxMusic][idxBar].sizeOfSound();
            for (std::size_t idxBeat = 0; idxBeat < size_Sound; ++idxBeat) {

                os << " " << music[idxMusic][idxBar][idxBeat].frequency <<
                " " << music[idxMusic][idxBar][idxBeat].duration;
            }
        }
    }
    os << "|" << std::endl;
}
