#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <string>
#include <vector>
#include <cstddef>
#include "Sound.h"
#include "Composition.h"

class GeneticAlgorithm
{
public:
    GeneticAlgorithm(const Composition& problem,
                     int population_size, int max_generation);


    void run();


    int populationSize() const { return population_size_; }
    int maxGeneration() const { return max_generation_; }
    Music individual(std::size_t idx) const { return population_[idx]; }

private:
    Composition problem_;
    int population_size_;
    int max_generation_;

    std::vector<Music> population_;


    std::vector<Music> createInitialPopulation(int population_size);

    void crossover();
    void mutation();
    void repair();
};

#endif // GENETICALGORITHM_H
