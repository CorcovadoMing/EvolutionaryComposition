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
      population_size_(0),
      population_(),
      max_generation_(0),
      mutation_rate_(0.0),
      elitism_individual_(-1)
{
}

GeneticAlgorithm::GeneticAlgorithm(const Composition& problem,
                                   unsigned int population_size,
                                   unsigned int max_generation,
                                   double mutation_rate,
                                   int elitism_individual)
    : problem_(problem),
      population_size_(population_size),
      population_(),
      max_generation_(max_generation),
      mutation_rate_(mutation_rate),
      elitism_individual_(elitism_individual)
{
    std::srand((unsigned int)std::time(NULL));
}

GeneticAlgorithm::GeneticAlgorithm(const Composition& problem,
                                   const std::vector<Music>& population)
    : problem_(problem),
      population_size_(population.size()),
      population_(population),
      max_generation_(0),
      mutation_rate_(0.0),
      elitism_individual_(-1)
{
    std::srand((unsigned int)std::time(NULL));
}

void
GeneticAlgorithm::set_max_generation(unsigned int max_generation)
{
    max_generation_ = max_generation;
}

void
GeneticAlgorithm::set_mutation_rate(double mutation_rate)
{
    mutation_rate_ = mutation_rate;
}

void
GeneticAlgorithm::set_elitism_individual(int elitism_individual)
{
    elitism_individual_ = elitism_individual;
}

void
GeneticAlgorithm::run()
{
    // Create initial population if there is no any population
    if (population_.size() == 0) {
        population_ = create_initial_population(population_size_);
    }

    // The current generation
    unsigned int generation = 0;
    // Do the max of generation times
    while (generation < max_generation_) {
    	
    	std::cout << problem_.pitchFitness(population_[0]) << std::endl;
    	std::cout << problem_.pitchFitness(population_[1]) << std::endl;
    	std::cout << problem_.beatFitness(population_[2]) << std::endl;
    	std::cout << problem_.beatFitness(population_[3]) << std::endl;
    	
        if (elitism_individual_ != -1) {
            crossover(elitism_individual_);
        }

        std::vector<Music> children = mutation(population_);
        //sort();
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
GeneticAlgorithm::crossover(int elitism_individual)
{
    // two parent reproduce two children

    // select random two parents
	int a = 0 ,b = 0;
    const int num_parent = 2;
    std::vector<Music> parent(2);
    //for (int i = 0; i < num_parent; ++i) {
		a = std::rand() % population_.size();
		b = std::rand() % population_.size();
        Music m1 = population_[a],
              m2 = population_[b];

        //if (m1.fitness_value() > m2.fitness_value())
            parent[0] = m1;
        //else
            parent[1] = m2;
    //}

	// exchange first x - 1 bar and first y beat in NO.x bar
	unsigned int x = rand() % parent[0].num_bar() ,y = rand() % parent[0][x].num_beat();
	for (unsigned int i = 0; i < parent[0].num_bar(); ++i) {
		if(i < x){
			std::swap(parent[0][i], parent[1][i]);
			continue;
		}
		for (unsigned int j = 0; j < parent[0][x].num_beat(); ++j) {
			if(i == x && j <= y){std::swap(parent[0][i][j], parent[1][i][j]);}
		}
	}

	//may replace
	for (int i = 0; i < num_parent; ++i) {/*problem_.evaluate_fitness_value(&parent[i])*/;}
	if(x < parent[0].num_bar() / 2){
		if(parent[0].fitness_value() > population_[a].fitness_value()){population_[a] = parent[0];}
		if(parent[1].fitness_value() > population_[b].fitness_value()){population_[b] = parent[1];}
	}
	else{
		if(parent[1].fitness_value() > population_[a].fitness_value()){population_[a] = parent[1];}
		if(parent[0].fitness_value() > population_[b].fitness_value()){population_[b] = parent[0];}
	}

    //for (int i = 0; i < num_parent; ++i) {
        //population_.push_back(parent[i]);
    //}
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

void
GeneticAlgorithm::sort(){
	int i = 0 ,j = 0;
	Music m;
	for (i = 1;i < population_.size();i++){
		m = population_[i];
		j = i - 1;
		while (j >= 0 && population_[j].fitness_value() < m.fitness_value()){
			population_[j + 1] = population_[j];
			j--;
		}
		population_[j + 1] = m;
	}
}
