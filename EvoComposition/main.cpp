#include <cstdlib>
#include <cstddef>
#include "Composition.h"
#include "GeneticAlgorithm.h"
#include "windows.h"

void execute(const Music& music ,int tempo)
{
	FILE *fp;
	fp = fopen("Music.txt" ,"w+");// output file
	fprintf(fp ,"%d\n" ,tempo);

    std::size_t sizeOfBar = music.sizeOfBar();
    for (std::size_t idxMusic = 0; idxMusic < sizeOfBar; ++idxMusic) {

        std::size_t sizeOfBeat = music[idxMusic].sizeOfBeat();
        for (std::size_t idxBar = 0; idxBar < sizeOfBeat; ++idxBar) {

            std::size_t sizeOfSound = music[idxMusic][idxBar].sizeOfSound();
            for (std::size_t idxBeat = 0; idxBeat < sizeOfSound; ++idxBeat) {

                Beep(music[idxMusic][idxBar][idxBeat].frequency,
                     music[idxMusic][idxBar][idxBeat].duration * 60 / tempo);

				fprintf(fp ,"%d %d " ,music[idxMusic][idxBar][idxBeat].frequency 
					,music[idxMusic][idxBar][idxBeat].duration * 60 / tempo);
            }
        }
    }

	fclose(fp);
}

int main()
{
    const int beats_per_bar = 4,
              note_value = 4,
              total_num_bar = 2,
              tempo = 120;

    Composition c(beats_per_bar, note_value,
                  total_num_bar, tempo);


    //const int population_size = 1,
              //max_generation = 1;

	const int population_size = 10,
              max_generation = 1000;
	
    GeneticAlgorithm algo(c, population_size, max_generation);
	
    algo.run();
	
    execute(algo.individual(0) ,tempo);

	system("pause");
	
    return EXIT_SUCCESS;
}
