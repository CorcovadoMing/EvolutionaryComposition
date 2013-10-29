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
#include "Music.h"
#include "Beat.h"
#include "Bar.h"
#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm()
    : problem_(),
      population_size_(0),
      population_(),
      max_generation_(0),
      crossover_rate_(0.0),
      mutation_rate_(0.0),
      index_elitism_individual_(-1)
{
    std::srand((unsigned int)std::time(NULL));
}

GeneticAlgorithm::GeneticAlgorithm(const Composition& problem,
                                   unsigned int population_size,
                                   unsigned int max_generation,
                                   double crossover_rate,
                                   double mutation_rate,
                                   int index_elitism_individual)
    : problem_(problem),
      population_size_(population_size),
      population_(),
      max_generation_(max_generation),
      crossover_rate_(crossover_rate),
      mutation_rate_(mutation_rate),
      index_elitism_individual_(index_elitism_individual)
{
    std::srand((unsigned int)std::time(NULL));
}

GeneticAlgorithm::GeneticAlgorithm(const Composition& problem,
                                   const std::vector<Music>& population)
    : problem_(problem),
      population_size_(population.size()),
      population_(population),
      max_generation_(0),
      crossover_rate_(0.0),
      mutation_rate_(0.0),
      index_elitism_individual_(-1)
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

    // if it exist elitism individual, pass its information to the others
    if (index_elitism_individual_ != -1) {
        crossover(static_cast<unsigned int>(index_elitism_individual_));
    }

    // The current generation
    unsigned int generation = 0;
    // Do the max of generation times
    while (generation < max_generation_) {

        std::cout << problem_.pitchFitness(population_[0]) << std::endl;
        std::cout << problem_.pitchFitness(population_[1]) << std::endl;
        std::cout << problem_.beatFitness(population_[2]) << std::endl;
        std::cout << problem_.beatFitness(population_[3]) << std::endl;

        std::vector<Music> children = mutation(population_);
        population_ = selection(population_, children);
        ++generation;
    }
}

std::vector<Music>
GeneticAlgorithm::create_initial_population(unsigned int population_size)
{
    std::vector<Music> population;
    population.reserve(population_size);

    for (std::size_t i = 0; i < population_size; ++i) {
        Music new_solution = problem_.create_initial_solution();
        population.push_back(new_solution);
    }

    return population;
}

void
GeneticAlgorithm::crossover(unsigned int idx_elitism)
{
    if (idx_elitism >= population_.size()) {
        return ;
    }

    // pass informations to the other indivisual
    for (std::size_t idxMusic = 0; idxMusic < population_.size(); ++idxMusic) {
        if (idxMusic == idx_elitism) {
            continue;
        }

        Music elitism = population_[idx_elitism];

        std::size_t num_bar = population_[idxMusic].num_bar();
        for (std::size_t idxBar = 0; idxBar < num_bar; ++idxBar) {

            std::size_t num_beat = population_[idxMusic][idxBar].num_beat();
            for (std::size_t idxBeat = 0; idxBeat < num_beat; ++idxBeat) {

                // every beat have a probability to pass it to another
                double rnd = rand() / (double)(((unsigned)RAND_MAX)+1u);
                if(rnd < crossover_rate_) {

                    std::swap(population_[idxMusic][idxBar][idxBeat],
                              elitism[idxBar][idxBeat]);
                }
            }
        }
    }
}

std::vector<Music>
GeneticAlgorithm::mutation(const std::vector<Music>& parents) const
{
    std::vector<Music> children;
    children.reserve(parents.size());

    // The first half do pitch mutation
    std::size_t half_parents_size = parents.size() / 2;
    for (std::size_t idx = 0; idx < half_parents_size; ++idx) {
        children.push_back(pitch_mutation(parents[idx]));
    }
    // The last half do beat pattern mutation
    for (std::size_t idx = half_parents_size; idx < parents.size(); ++idx) {
        children.push_back(beat_pattern_mutation(parents[idx]));
    }

    return children;
}

Music
GeneticAlgorithm::pitch_mutation(const Music& parent) const
{
    Music child = parent;

    std::size_t num_bar = child.num_bar();
    for (std::size_t idxBar = 0; idxBar < num_bar; ++idxBar) {

        std::size_t num_beat = child[idxBar].num_beat();
        for (std::size_t idxBeat = 0; idxBeat < num_beat; ++idxBeat) {

            std::size_t num_sound = child[idxBar][idxBeat].num_sound();
            for (std::size_t idxSound = 0; idxSound < num_sound; ++idxSound) {

                // mutate all note under mutation rate condition
                double rnd = rand() / (double)(((unsigned)RAND_MAX)+1u);
                if(rnd < mutation_rate_) {

                    Sound sound = child[idxBar][idxBeat][idxSound];

                    sound = problem_.changeFreqOfPitch(sound);

                    child[idxBar][idxBeat][idxSound] = sound;
                }
            }
        }
    }
    return child;
}

Music
GeneticAlgorithm::beat_pattern_mutation(const Music& parent) const
{
    Music child = parent;

    std::size_t num_bar = child.num_bar();
    for (std::size_t idxBar = 0; idxBar < num_bar; ++idxBar) {

        std::size_t num_beat = child[idxBar].num_beat();
        for (std::size_t idxBeat = 0; idxBeat < num_beat; ++idxBeat) {

            // mutate all beat under mutation rate condition
            double rnd = rand() / (double)(((unsigned)RAND_MAX)+1u);
            if(rnd < mutation_rate_) {

                Beat beat = child[idxBar][idxBeat];

                beat = problem_.changePatternOfBeat(beat);

                child[idxBar][idxBeat] = beat;
            }

        }
    }

    return child;
}

std::vector<Music>
GeneticAlgorithm::selection(const std::vector<Music>& parents,
                            const std::vector<Music>& children) const
{
    //return children;
    std::vector<Music> result;
    result.reserve(parents.size());

    std::size_t half_parents_size = parents.size() / 2;
    for (std::size_t idx = 0; idx < parents.size() && idx < children.size(); ++idx) {

        Music parent = parents[idx],
              child = children[idx];

        double fitness_parent = 0.0, fitness_child = 0.0;
        if (idx < half_parents_size) {
            fitness_parent = problem_.pitchFitness(parent);
            fitness_child = problem_.pitchFitness(child);
        }
        else {
            fitness_parent = problem_.beatFitness(parent);
            fitness_child = problem_.beatFitness(child);
        }

        // if child is better than parent
        if (fitness_child > fitness_parent) {
            result.push_back(child);
        }
        else {
            result.push_back(parent);
        }
    }

    return result;
}