#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <string>
#include <vector>
#include <cstddef>
#include "Composition.h"

class GeneticAlgorithm
{
public:
    GeneticAlgorithm(const Composition& problem, int size, int generation);

    void run();

    Composition::Music result(std::size_t idx) const
    {
        return population[idx];
    }

private:
    Composition problem;
    int populationSize;
    int generation;

    std::vector<Composition::Music> population;


    Composition::Music initialSolution() const;
    std::vector<Composition::Music> initialPopulation();

    void crossover();
    void mutation();
};

#endif // GENETICALGORITHM_H
