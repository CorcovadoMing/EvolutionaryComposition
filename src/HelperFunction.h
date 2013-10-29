#ifndef IOFUNCTION_H
#define IOFUNCTION_H

void readFromFile(const std::string& file_name);
void outputToFile(const std::string& file_name);

const std::string int2str(const int&);
const int dur2num(const int&);
const std::string note2name(const double&);
void writeToPy();

#endif