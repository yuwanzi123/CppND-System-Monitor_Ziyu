#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <string>
#include <vector>

using std::string;
using std::vector;

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  //constructor
  Processor();
  
  // TODO: Declare any necessary private members
 private:
  float PreTotalCpuTime;
  float PreIdleCpuTime;
  vector<long> ConvertToLong(vector<string> values);
};

#endif