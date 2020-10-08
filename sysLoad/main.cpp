/*
 * @Author: Mehedi
 * @Date: 2020-07-14 12:30:42 
 * @Last Modified by: Mehedi H.
 * @Last Modified time: 2020-07-14 13:51:24
 */


//system headers
#include <iostream>
#include <time.h>
 

//ThirdParty libs
#include "lib/json.hpp"

//custom headers
#include "SystemInfo.h"

//JSON converters
string getCpuUsageDataInJSON();



using namespace std;
using json = nlohmann::json;

int main(int argc, char* argv[])
{ 
  //Receive subscription message

  cout << argv[0] << " started to measure system load..." << endl;

  int request_num {0};
  for (;;) 
  {
      std::this_thread::sleep_for(1s);
      ++request_num;

      cout << endl << "CpuLoad data has been fetched and binded into JSON string: " << endl
         << getCpuUsageDataInJSON() << endl;

      if(request_num == INT16_MAX) request_num = 0;
  }
 
  return 0;
}

string getCpuUsageDataInJSON(){
  
  //current time
  time_t my_time = time(NULL); 

  SystemInfo s1;
  string v_cpuLoadInPrcnt {s1.get_cpuLoad()};

  //building json
  json obj_json;

  obj_json["SystemLoad"] = v_cpuLoadInPrcnt;
  obj_json["time"] = ctime(&my_time);

  return obj_json.dump(4);
}
