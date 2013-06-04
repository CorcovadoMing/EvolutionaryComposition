#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include "Composition.h"
#include "Sound.h"
#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm()
    : problem_(),
      max_generation_(1000),
      population_size_(10),
      population_()
{
}

GeneticAlgorithm::GeneticAlgorithm(const Composition& problem,
                                   int max_generation,
                                   int population_size)
    : problem_(problem),
      max_generation_(max_generation),
      population_size_(population_size),
      population_()
{
    std::srand((unsigned int)std::time(NULL));
}

GeneticAlgorithm::GeneticAlgorithm(const Composition& problem,
                                   int max_generation,
                                   const std::vector<Music>& population)
    : problem_(problem),
      max_generation_(max_generation),
      population_size_(population.size()),
      population_(population)
{
    std::srand((unsigned int)std::time(NULL));
}

void
GeneticAlgorithm::run()
{
    // Create initial population
    if (population_.size() == 0) {
        population_ = createInitialPopulation(population_size_);
    }

    // The current generation
    int generation = 0;
    // Do the max of generation times
    while (generation < max_generation_) {

        crossover();
        mutation();

		sort();
        ++generation;
    }
}

/*void
GeneticAlgorithm::readFromFile(const std::string& file_name)
{
    std::ifstream ifs(file_name.c_str());
    if (ifs.is_open()) {
        // read the information of problem
        int beats_per_bar = 0, note_value = 0,
            total_num_bar = 0, tempo = 0;
        ifs >> beats_per_bar >> note_value >> total_num_bar >> tempo;
        problem_(Composition(beats_per_bar, note_value,
                               total_num_bar, tempo));

        // read each Music
        int population_size = 0;
        while (ifs.good()) {
            readMusic(ifs);
            ++population_size;
        }
        population_size_ = population_size;
    }
    else {
        std::cout << "The input file is not be read." << std::endl;
    }
}

void
GeneticAlgorithm::outputToFile(const std::string& file_name) const
{
    std::ofstream ofs(file_name.c_str());
    if (ofs.is_open()) {
        // output the information of problem
        ofs << problem_.BEATS_PER_BAR << " " << problem_.NOTE_VALUE << " " <<
        problem_.TOTAL_NUMBER_BAR << " " << problem_.TEMPO << std::endl;

        // output each Music
        for (auto it = population_.begin(); it != population_.end(); ++it) {
            outputMusic(ofs, *it);
        }
    }
    else {
        std::cout << "The onput file is not be written." << std::endl;
    }
}

void
GeneticAlgorithm::readMusic(std::istream& is)
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
}

void
GeneticAlgorithm::outputMusic(std::ostream& os, const Music& music) const
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
}*/

std::vector<Music>
GeneticAlgorithm::createInitialPopulation(int population_size)
{
    std::vector<Music> population;
    population.reserve(population_size);

    for (int i = 0; i < population_size; ++i) {
        Music new_solution = problem_.createInitialSolution();
        population.push_back(new_solution);
    }

    return population;
}

void
GeneticAlgorithm::crossover()
{
    // randomly select two parents
    Music parent[] =
        {population_[std::rand() % population_.size()],
         population_[std::rand() % population_.size()]};

    // exchange first note of 3rd beat in every bar
    for (std::size_t barIdx = 0;
         barIdx < parent[0].num_bar() && barIdx < parent[1].num_bar();
         ++barIdx) {

        std::swap(parent[0][barIdx][2][0], parent[1][barIdx][2][0]);
    }
}

void
GeneticAlgorithm::mutation()
{
    // mutate a random note in a random bar
    for (std::size_t idx = 0; idx < population_.size(); ++idx) {
        if((double)rand() / (RAND_MAX + 1) < 0.01){// mutation rate = 0.01

            int x = rand() % population_[idx].num_bar(),
                y = rand() % population_[idx][x].num_beat(),
                z = rand() % population_[idx][x][y].num_sound();

			Sound sound = population_[idx][x][y][z];

			sound = problem_.changeFreqOfPitch(sound);

			population_[idx][x][y][z] = sound;
		}
    }
}

void
GeneticAlgorithm::sort(){
	unsigned int i = 0 ,j = 0;
	Music m;
	for (i = 1;i < population_.size();i++){
		m = population_[i];
		j = i - 1;
		while (j && population_[j].degree_of_sounds_good() < m.degree_of_sounds_good()){
			population_[j + 1] = population_[j];
			j--;
		}
		population_[j + 1] = m;
	}
}
