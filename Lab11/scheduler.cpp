#include "scheduler.hpp"

void first_come_first_served(queue<ProcessData> &fcfs, array<ProcessData, 1> &cpu_cores, int &chronon, bool &terminate, bool end_of_file) {
    if (cpu_cores[0].get_pid() == -1) {
        cpu_cores[0] = fcfs.front();
        fcfs.pop();
    }

    cout << chronon << " " << cpu_cores[0].get_pid() << endl;

    cpu_cores[0].run_process();

    if (cpu_cores[0].get_burst_time() <= 0) {
        cpu_cores[0].clear_process_info();
    }

    if ((fcfs.empty() && end_of_file)) {
        terminate = true;
    }

    chronon += 1;
}