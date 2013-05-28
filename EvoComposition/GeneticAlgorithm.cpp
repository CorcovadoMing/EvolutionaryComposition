#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include "Composition.h"
#include "Sound.h"
#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(const Composition& problem,
                                   int population_size, int max_generation)
    : problem_(problem),
      population_size_(population_size), max_generation_(max_generation)
{
    std::srand((unsigned int)std::time(NULL));
}

void
GeneticAlgorithm::run()
{
    // Create initial population
    population_ = createInitialPopulation(population_size_);
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
         barIdx < parent[0].sizeOfBar() && barIdx < parent[1].sizeOfBar();
         ++barIdx) {

        std::swap(parent[0][barIdx][2][0], parent[1][barIdx][2][0]);
    }
}

void
GeneticAlgorithm::mutation()
{
    // mutate a random note in a random bar
    for (std::size_t idx = 0; idx < population_.size(); ++idx) {
		if((double)(rand() % 10000) / 10000 < 0.01){// mutation rate = 0.01
			int x = rand() % population_[idx].sizeOfBar() ,y = rand() % population_[idx][x].sizeOfBeat() 
				,z = rand() % population_[idx][x][y].sizeOfSound();
		
			Sound sound = population_[idx][x][y][z];
		
			sound = problem_.changeFreqOfPitch(sound); 
        
        // if sound is must to be repair
        // ......
			population_[idx][x][y][z] = sound;
		}
    }
}







void GeneticAlgorithm::sort(){
	unsigned int i = 0 ,j = 0;
	Music m;
	for (i = 1;i < population_.size() - 1;i++){
		m = population_[i];
		j = i - 1;
		while (j >= 0 && population_[j].degree_of_sounds_good() > m.degree_of_sounds_good()){
			population_[j + 1] = population_[j];
			j--;
		}
		population_[j + 1] = m;
	}
}
