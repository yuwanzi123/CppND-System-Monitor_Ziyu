#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);	//find the file
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_'); 	//changes some space to _, this will make the parser process easier
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  //because const std::string kProcDirectory{"/proc/"};
  //const std::string kVersionFilename{"/version"};
  //so in summary it is /proc/version
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
// The path for MemTotal and MemFree is: /proc/meminfo
float LinuxParser::MemoryUtilization() { 
  float memt = 0.0;
  float memf = 0.0;
  float memu = 0.0;
  string line;
  string key;
  string value;
  
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_oepn()){
  	while (std::getline(filestream, line)){
  	//eliminate space, ":"
      std::remove(line.begin(), line.end(), ' ');
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while(linestream >> key >> value) {
      	if (key == "MemTotal") {
      	memt = std::stof(value);
        }
        else if(key == "MemFree") {
        	memf = std::stof(value);
          break
        }
      }
  	}
  }
  memu = (memt - memf) / memt
  return memu; 
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string line;
  string UpTime;
  long SystemUpTime = 0;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open()){
    while(std::getline(filestream, line)) {
      std::istringstream linstream(line);
      while (linestream >> UpTime){
        SystemUpTime = std::stol(Uptime);
        return SystemUpTime;
        }
      }
    }
  }
  return SystemUpTime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() {
  long jiffies = 0;
  string key;
  string line;
  string value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()){
    while (std::getline(filestream, line)){
      std::istringstream linestream(line);
      while (linestream >> key){
        if (key == "cpu") {
          while (linestream >> value){
            jiffies += std::stol(value);
            return jiffies;
          }
        }
      }
    }
    
  }
  return jiffies; 
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  string line;
  string key;
  string value;
  long ajiffies = 0;
  std::ifstream stream (kProcDirectory + kStatFilename);
  if (filestream.is_open()){
    std::istringstream linestream(line);
    while(linestream >> key){
      if (key == "cpu"){
        for (int i = 0; i < 3; i++){
          while(linestream >> value){
            ajiffies += std::stol(value);
            return ajiffies;
          }
        }
      }
    }
  }
  return ajiffies; 
}



// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  string line;
  string key;
  string value;
  long ijiffies = 0;
  std::ifstream stream (kProcDirectory + kStatFilename);
    if (filestream.is_open()){
      std::istringstream linstream(line);
      while(linstream >> key){
        if(key == "cpu"){
          for (int i = 0; i < 5; i++){
            while(linestream >> value){
              ijiffies += std::stol(value);
              return ijiffies;
            }
          }
        }
      }
    }
  return ijiffies; 
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  vector<string> cpuuti;
  return cpuuti; 
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string line;
  string key;
  string value;
  int TotalProcesses;
  std::isftream filestream (kProcDirectory + kStatFilename);
  if (filestream.is_open()){
    while(std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          TotalProcesses = std::stoi(totalprocesses);
          return TotalProcesses;
        }
      }
    }
  }
  return TotalProcesses; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string line;
  string key;
  string value;
  int RunningProcesses;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()){
    while (std::getline(filestream, line)){
      std::istringstream linestream(line);
      while(linestream >> key >> value){
        if (key == "procs_running") {
          RunningProcesses = std::stoi(value);
          return RunningProcesses;
        }
      }
    }
  }
  return RunningProcesses; 
}


// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid]) { 
  string key;
  string line;
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) + kCmdlineFilename);
  if (filestream.is_open()){
    while(std::getline(filestream, line)){
      std::istringstream linestream(line);
      linestream >> key;
      return key;
    }
  } 
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string key;
  string line;
  string value;
  std::ifstream filestream(kProcDirctory + "/" + std::to_string(pid) + kStatusFilename);
  if (filestream.is_open()){
    while(std::getline(filestream, line)){
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while(linstream >> key >> value){
        if (key == "VmSize"){
        return value;
        }
      }              
    }
  }
  return value;
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) + kStatusFilename);
  if (filestream.is_open()){
    while (std::getline(filestream, line)){
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while(linestream >> key >> value){
        if (key == "Uid"){
          return value; 
        }
      }
    }
  }
  return value;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  string uid = Uid(pid);
  string line;
  string key;
  string value = "";
  string other;
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()){
    while(std::getline(filestream, line)){
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstrem linestream(line);
      while (linestream >> value >> other >> key){
        if(key == uid){
          return value;
        }
      }
    }
  }
  return value;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  string line;
  string value;
  long UpTime = 0;  
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) + kStatFilename);
  if (filestream.is_open()){
    while(std::getline(filestream, line){
      std::istringstream linestream(line);
      for (int i = 1; i <= kStarttime_; i++){
        linestream >> value;
        if (i == kStartime_) {
          UpTime = std::stol(value) / sysconf(_SC_CLK_TCK);
          return UpTime;
        }
      } 
    }
  }
   return UpTime;
}