#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
#include <array>

using namespace std;

class ProcessData {
   private:
    int pid;
    int burst_time;
    int priority;

   public:
    ProcessData(int priority, int burst_time, int pid) {
        ProcessData::pid = pid;
        ProcessData::burst_time = burst_time;
        ProcessData::priority = priority;
    }

    void clear_process_info() {
        ProcessData::pid = -1;
        ProcessData::burst_time = -1;
        ProcessData::priority = -1;
    };

    void set_pid(int value) {
        ProcessData::pid = value;
    };

    void set_burst_time(int value) {
        ProcessData::burst_time = value;
    };

    void set_priority(int value) {
        ProcessData::priority = value;
    };
    
    int get_pid() {
        return ProcessData::pid;
    };

    int get_burst_time() {
        return ProcessData::burst_time;
    };

    int get_priority() {
        return ProcessData::priority;
    };

    void run_process() {
        ProcessData::burst_time = ProcessData::burst_time - 1;
    }
};

void first_come_first_served(queue<ProcessData> &fcfs, array<ProcessData, 1> &cpu_cores, int &chronon, bool &terminate, bool end_of_file);