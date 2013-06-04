#ifndef COMPOSITIONIO_H
#define COMPOSITIONIO_H

#include <istream>
#include <ostream>
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
        // no use the separator
        is >> beats_per_bar >> note_value >> total_num_bar >> tempo;
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
