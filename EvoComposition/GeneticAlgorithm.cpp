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
      population_size_(0),
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
    // Create initial population if there is no any population
    if (population_.size() == 0) {
        population_ = create_initial_population(population_size_);
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

std::vector<Music>
GeneticAlgorithm::create_initial_population(int population_size)
{
    std::vector<Music> population;
    population.reserve(population_size);

    for (int i = 0; i < population_size; ++i) {
        Music new_solution = problem_.create_initial_solution();
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
    //std::cout << population_.size() << std::endl;
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
