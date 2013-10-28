#ifndef COMPOSITIONIO_H
#define COMPOSITIONIO_H

#include <istream>
#include <ostream>
#include <sstream>
#include "Composition.h"

class CompositionIO
{
public:

    static Composition input_from(std::istream& is);
    static void output_to(std::ostream& os, const Composition& composition);

    static const char separator, terminal_separator;
};

const char CompositionIO::separator = ' ',
           CompositionIO::terminal_separator = '\n';

Composition
CompositionIO::input_from(std::istream& is)
{
    int beats_per_bar = 0, note_value = 0,
        total_num_bar = 0, tempo = 0;

    if (is.good()) {
        // parse line
        std::string line;
        std::getline(is, line, terminal_separator);
        std::istringstream iss_line(line);
        if (iss_line.good()) {

            // parse each information
            std::string str_beats_per_bar, str_note_value,
                        str_total_num_bar, str_tempo;
            std::getline(iss_line, str_beats_per_bar, separator);
            std::getline(iss_line, str_note_value, separator);
            std::getline(iss_line, str_total_num_bar, separator);
            std::getline(iss_line, str_tempo, separator);
            std::istringstream iss_beats_per_bar(str_beats_per_bar),
                               iss_note_value(str_note_value),
                               iss_total_num_bar(str_total_num_bar),
                               iss_tempo(str_tempo);

            iss_beats_per_bar >> beats_per_bar;
            iss_note_value >> note_value;
            iss_total_num_bar >> total_num_bar;
            iss_tempo >> tempo;
        }
    }

    return Composition(beats_per_bar, note_value,
                       total_num_bar, tempo);
}

void
CompositionIO::output_to(std::ostream& os,
                           const Composition& composition)
{
    os << composition.BEATS_PER_BAR << separator <<
          composition.NOTE_VALUE << separator <<
          composition.TOTAL_NUMBER_BAR << separator <<
          composition.TEMPO << terminal_separator;
}

#endif // COMPOSITIONIO_H
