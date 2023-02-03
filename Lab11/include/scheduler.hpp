#include <sys/stat.h>

#include <array>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

#include "comparators.hpp"

using namespace std;

void first_come_first_served(queue<ProcessData> &fcfs, array<ProcessData, 3> &cpu_cores, bool &terminate, bool end_of_file);

void shortest_jobtime_first(priority_queue<ProcessData, vector<ProcessData>, CompareBurstTimeOrPID> &sjf, array<ProcessData, 3> &cpu_cores, bool &terminate, bool end_of_file);

void shortest_remaining_time(priority_queue<ProcessData, vector<ProcessData>, CompareBurstTimeOrPID> &srtf, array<ProcessData, 3> &cpu_cores, bool &terminate, bool end_of_file);

void round_robin(queue<ProcessData> &rr, array<ProcessData, 3> &cpu_cores, array<int, 3> &time_on_processor, bool &terminate, bool end_of_file);

void preemptive_priority_queue_with_fcfs(priority_queue<ProcessData, vector<ProcessData>, ComparePriorityOrPID> &pq_fcfs, array<ProcessData, 3> &cpu_cores, bool &terminate, bool end_of_file);

void preemptive_priority_queue_with_srtf(priority_queue<ProcessData, vector<ProcessData>, ComparePriorityOrBurstTime> &pq_srtf, array<ProcessData, 3> &cpu_cores, bool &terminate, bool end_of_file);

void nonpreemptive_priority_queue_with_fcfs(priority_queue<ProcessData, vector<ProcessData>, ComparePriorityOrPID> &npq_fcfs, array<ProcessData, 3> &cpu_cores, bool &terminate, bool end_of_file);

bool check_conditions_for_termination(bool is_queue_empty, bool end_of_file, array<ProcessData, 3> &cpu_cores);

bool exists_test(const string &name);