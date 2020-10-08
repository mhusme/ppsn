/*
 * @Author: Mehedi H. 
 * @Date: 2020-07-14 12:46:16 
 * @Last Modified by: Mehedi H.
 * @Last Modified time: 2020-07-14 12:47:25
 */


#ifndef _SYSTEMINFO_H
#define _SYSTEMINFO_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <thread>
#include <chrono>
#include <vector>

using namespace std;

class SystemInfo
{
public:
  SystemInfo();
  string get_cpuLoad();

private:
  float cpuLoad;
  void fetch_cpuLoad_from_system();
  size_t get_logical_cores();
  float calculate_cpu_usage_percentage(float raw_cpu_usage);
  const vector<string> explode(const string& s, const char& c);
};

#endif
