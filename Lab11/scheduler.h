#include <string.h>

#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>

using namespace std;

class ProcessData {
   public:
    int priority;
    int time_to_execute;
    int cpu_priority;
};