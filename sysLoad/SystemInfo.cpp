/*
 * @Author: Mehedi H. 
 * @Date: 2020-07-14 12:43:26 
 * @Last Modified by: Mehedi H.
 * @Last Modified time: 2020-07-14 12:46:22
 */


#include "SystemInfo.h"

//system headers
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <thread>
#include <chrono>
#include <vector>

using namespace std;

SystemInfo::SystemInfo()
{
  cpuLoad = 0;
}

string SystemInfo::get_cpuLoad()
{
  fetch_cpuLoad_from_system();
  return to_string(cpuLoad) + "%";
}

void SystemInfo::fetch_cpuLoad_from_system()
{
  //read from kernel pseudofile file
  std::ifstream fileStat("/proc/loadavg");

  //reading from file
  std::string line;
	std::getline(fileStat, line);
	
  //init string stream from lines
  std::istringstream ss(line);

  //get total raw_cpu_usage
  float raw_cpu_usage = 0;
  ss >> raw_cpu_usage;

  cout << "Raw cpu usage is: " << raw_cpu_usage << endl;

  cpuLoad = calculate_cpu_usage_percentage(raw_cpu_usage);
  
}
	
size_t SystemInfo::get_logical_cores(){
  
  size_t cores = 1; // valid system has at least one core

  const std::string str_siblings("siblings"); // siblings are total cores including logical processing units.
  const std::size_t len_str_siblings = str_siblings.size();
  
  //read from kernel pseudofile file
  std::ifstream fileStat("/proc/cpuinfo");
  std::string line;

  while(std::getline(fileStat, line)){
    
    // cpu siblings line found
    if(!line.compare(0, len_str_siblings, str_siblings)){
  
      // read total logical cores
      vector<string> v{explode(line, ':')};
      std::istringstream ss(v[1]);
      ss >> cores;
    }
  }

  cout << "Number of logical cores found: " << cores << endl;

  return cores;
}

float SystemInfo::calculate_cpu_usage_percentage(float raw_cpu_usage){

  float calculated_cpu_usage =  100 * (raw_cpu_usage / static_cast<float>(get_logical_cores()));
  cout << "CPU usage calculation has been completet, System CPU Load is: " << calculated_cpu_usage << endl;
  //return (calculated_cpu_usage > 100) ? 100.0: calculated_cpu_usage;
  return calculated_cpu_usage;
}

// this helper function will be moved.
const vector<string> SystemInfo::explode(const string& s, const char& c)
{
	string buff{""};
	vector<string> v;
	
	for(auto n:s)
	{
		if(n != c) buff+=n; else
		if(n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if(buff != "") v.push_back(buff);
	
	return v;
}

