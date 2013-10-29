#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <vector>
#include <cstddef>
#include "Music.h"
#include "Composition.h"

class GeneticAlgorithm
{
public:
    GeneticAlgorithm();
    GeneticAlgorithm(const Composition& problem,
                     unsigned int population_size,
                     unsigned int max_generation,
                     double crossover_rate,
                     double mutation_rate,
                     int index_elitism_individual);

    GeneticAlgorithm(const Composition& problem,
                     const std::vector<Music>& population);

    void run();
    
    void setMaxGeneration(unsigned int max_generation)
        {max_generation_ = max_generation;}
    void setCrossoverRate(double crossover_rate)
        {crossover_rate_ = crossover_rate;}
    void setMutationRate(double mutation_rate)
        {mutation_rate_ = mutation_rate;}
    void setIndexElitismIndividual(int index_elitism_individual)
        {index_elitism_individual_ = index_elitism_individual;}

    const Composition& problem() const { return problem_; }
    unsigned int population_size() const { return population_size_; }
    Music individual(std::size_t idx) const { return population_.at(idx); }
    unsigned int max_generation() const { return max_generation_; }
    double crossover_rate() const { return crossover_rate_; }
    double mutation_rate() const { return mutation_rate_; }
    int index_elitism_individual() const { return index_elitism_individual_; }

private:
    Composition problem_;

    unsigned int population_size_;
    std::vector<Music> population_;

    unsigned int max_generation_;
    double crossover_rate_;
    double mutation_rate_;
    int index_elitism_individual_;

    std::vector<Music> create_initial_population(unsigned int population_size);

    void crossover(unsigned int idx_elitism);

    std::vector<Music> mutation(const std::vector<Music>& parents) const;
    Music pitch_mutation(const Music& parent) const;
    Music beat_pattern_mutation(const Music& parent) const;

    std::vector<Music> selection(const std::vector<Music>& parents,
                                 const std::vector<Music>& children) const;

    void repair();
};

#endif // GENETICALGORITHM_H