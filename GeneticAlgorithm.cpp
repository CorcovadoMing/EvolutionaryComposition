#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include "Composition.h"
#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(const Composition& problem, int size, int generation)
    : problem(problem), populationSize(size), generation(generation)
{
    std::srand(std::time(0));
}

void GeneticAlgorithm::run()
{
    // initialize population
    population = initialPopulation();

    for (; generation > 0; --generation) {

        crossover();
        mutation();
    }
}

std::vector<Composition::Music>
GeneticAlgorithm::initialPopulation()
{
    std::vector<Composition::Music> population;
    population.reserve(populationSize);
    for (int i = 0; i < populationSize; ++i) {
        population.push_back(initialSolution());
    }
    return population;
}

Composition::Music
GeneticAlgorithm::initialSolution() const
{
    Composition::Music music;
    music.reserve(problem.TOTAL_BAR);

    for (int barIdx = 0; barIdx < problem.TOTAL_BAR; ++barIdx) {
        Composition::Bar bar;
        bar.reserve(problem.BEATS_PER_BAR);
        for (int beatIdx = 0; beatIdx < problem.BEATS_PER_BAR; ++beatIdx) {
            Composition::Beat beat = problem.changePatternOfBeat(Sound());
            beat = problem.changeFreqOfPitch(beat);
            bar.push_back(beat);
        }
        music.push_back(bar);
    }

    return music;
}

void
GeneticAlgorithm::crossover()
{
    // select parents by 2-tournament
    Composition::Music parent[] =
        {population[std::rand() % population.size()],
         population[std::rand() % population.size()]};

    // exchange first note of 3rd beat in every bar
    for (std::size_t barIdx = 0;
         barIdx < parent[0].size() && barIdx < parent[1].size(); ++barIdx) {

        std::swap(parent[0][barIdx][2][0], parent[1][barIdx][2][0]);
    }
}

void
GeneticAlgorithm::mutation()
{
    // mutate first note in first bar
    for (std::size_t idx = 0; idx < population.size(); ++idx) {
        Sound sound = population[idx][0][0][0];
        sound = problem.changeFreqOfPitch(sound); // mutation rate = 1.0
        // if sound is must to be repair
        // ......
        population[idx][0][0][0] = sound;
    }
}
