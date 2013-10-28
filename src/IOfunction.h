#ifndef IOFUNCTION_H
#define IOFUNCTION_H

void readFromFile(GeneticAlgorithm& algo, const std::string& file_name);
void outputToFile(const std::string& file_name, const GeneticAlgorithm& algo);

std::string int2str(const int&);
int dur2num( const int& );
std::string note2name( const double& );
void writeToPy(const GeneticAlgorithm& algo);
void gPyHeader(FILE *, const int&);
void gPyBody(FILE *, const double&, const double&);
void gPyFooter(FILE *, const int&);

#endif