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
    int populationSize() const { return population_size_; }
    int maxGeneration() const { return max_generation_; }
    Music individual(std::size_t idx) const { return population_[idx]; }

    //void readFromFile(const std::string& file_name);
    //void outputToFile(const std::string& file_name) const;

private:
    Composition problem_;
    int max_generation_;

    int population_size_;
    std::vector<Music> population_;


    std::vector<Music> createInitialPopulation(int population_size);

    void crossover();
    void mutation();
    void repair();

    void sort();

    //void readMusic(std::istream& is);
    //void outputMusic(std::ostream& os, const Music& music) const;
};

#endif // GENETICALGORITHM_H
