#include <cstdlib>
#include "windows.h"
#include "Composition.h"
#include "GeneticAlgorithm.h"

void execute(const Composition::Music& music)
{
    typedef Composition::Music::const_iterator MusicIt;
    typedef Composition::Bar::const_iterator BarIt;
    typedef Composition::Beat::const_iterator BeatIt;
    for (MusicIt itMusic = music.begin(); itMusic != music.end(); ++itMusic) {
        for (BarIt itBar = itMusic->begin(); itBar != itMusic->end(); ++itBar) {
            for (BeatIt itBeat = itBar->begin(); itBeat != itBar->end(); ++itBeat) {
                Beep(itBeat->freq, itBeat->dur);
            }
        }
    }

}

int main()
{
    Composition c(4, 4, 2, 120);

    GeneticAlgorithm algo(c, 1, 1);

    algo.run();

    execute(algo.result(0));

    return EXIT_SUCCESS;
}
