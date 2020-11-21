#include "processor.h"
#include <string>
#include <vector>
#include "linux_parser.h"

using std::string;
using std::vector;

Processor::Processor() : PreTotalCpuTime(0.0), PreIdleCpuTime(0.0){ }; // initialize an empty process

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
  //read current CPU values from file system
  vector<long> CPUValues = ConvertToLong(LinuxParser::CpuUtilization());
  
  //total cpu time since boot = user + nice + system + idle + iowait + irq + softirq + steal
  float TotalCPUTime = CPUValues[LinuxParser::kUser_] + CPUValues[LinuxParser::kNice_] + 
    				CPUValuee[LinuxParser::kSystem_] + CPUValues[LinuxParser::kIdel_] +
    				CPUValues[LinuxParser::kIOwait_] + CPUValues[LinuxParser::kIRQ_] +
    				CPUValues[kSoftIRQ_] + CPUValues[LinuxParser::kSteal_];
  
  //calculate the CPU usage since last update
  float IdelCPUTime = CPUValues[LinuxParser::kIdel_] + CPUValues[LinuxParser::kIOwait_];	//idle time since boot = idle + iowait
  float DiffIdle = IdleCPUTime - PreIdleCpuTime;
  float DiffTotal = TotalCPUTime - preTotalCpuTime;
  float DiffUsage = (DiffTotal - DiffIdle) / DiffTotal;
  
  //update the total and idle time for future use
  PreIdelCpuTime = IdleCPUTime;
  PreTotalCputTime = TotalCPUTime;
  return DiffUsage;  
}

//convert string vector into a long vector
vector<long> Processor::ConvertToLong()vector<string> values){
  vector<long> ConvertedValues{ };
  for (int c = 0; c < (int)values.size(); c++){
    ConvertedValues.push_back(std::stol(values[c]));
  }
  return ConvertedValues;
}