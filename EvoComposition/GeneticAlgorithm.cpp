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
    std::srand(std::time(NULL));
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
    // mutate first note in first bar
    for (std::size_t idx = 0; idx < population_.size(); ++idx) {
        Sound sound = population_[idx][0][0][0];
        sound = problem_.changeFreqOfPitch(sound); // mutation rate = 1.0
        // if sound is must to be repair
        // ......
        population_[idx][0][0][0] = sound;
    }
}
