#include <sys/stat.h>

#include <array>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

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

class Compare {
   public:
    bool operator()(ProcessData a, ProcessData b) {
        if (a.get_burst_time() == b.get_burst_time()) {
            return a.get_pid() > b.get_pid();
        }
        return a.get_burst_time() > b.get_burst_time();
    }
};

void first_come_first_served(queue<ProcessData> &fcfs, array<ProcessData, 3> &cpu_cores, int &chronon, bool &terminate, bool end_of_file);

void shortest_jobtime_first(priority_queue<ProcessData, vector<ProcessData>, Compare> &sjf, array<ProcessData, 3> &cpu_cores, int &chronon, bool &terminate, bool end_of_file);

bool exists_test(const string &name);