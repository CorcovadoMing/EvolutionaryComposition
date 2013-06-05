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
    GeneticAlgorithm();

    GeneticAlgorithm(const Composition& problem,
                     int max_generation,
                     int population_size);

    GeneticAlgorithm(const Composition& problem,
                     int max_generation,
                     const std::vector<Music>& population);

    void run();

    const Composition& problem() const { return problem_; }
    int population_size() const { return population_size_; }
    int max_generation() const { return max_generation_; }
    Music individual(std::size_t idx) const { return population_[idx]; }

private:
    Composition problem_;
    int max_generation_;

    int population_size_;
    std::vector<Music> population_;


    std::vector<Music> create_initial_population(int population_size);

    void crossover();
    void mutation();
    void repair();

    void sort();

};

#endif // GENETICALGORITHM_H
