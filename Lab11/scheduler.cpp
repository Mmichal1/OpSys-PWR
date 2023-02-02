#include "scheduler.hpp"

void first_come_first_served(queue<ProcessData> &fcfs, array<ProcessData, 3> &cpu_cores, int &chronon, bool &terminate, bool end_of_file) {
    cout << chronon;

    for (int i = 0; i < cpu_cores.size(); i++) {
        if (cpu_cores[i].get_pid() == -1 && !fcfs.empty()) {
            cpu_cores[i] = fcfs.front();
            fcfs.pop();
        }

        cout << '\t' << cpu_cores[i].get_pid();        
        if (i == cpu_cores.size() - 1) cout << '\n';

        cpu_cores[i].run_process();

        if (cpu_cores[i].get_burst_time() <= 0) {
            cpu_cores[i].clear_process_info();
        }
    }

    if ((fcfs.empty() && end_of_file)) {
        terminate = true;
    }

    chronon += 1;
}

void shortest_jobtime_first(priority_queue <ProcessData, vector<ProcessData>, Compare> &sjf, array<ProcessData, 3> &cpu_cores, int &chronon, bool &terminate, bool end_of_file) {
    cout << chronon;

    for (int i = 0; i < cpu_cores.size(); i++) {
        if (cpu_cores[i].get_pid() == -1 && !sjf.empty()) {
            cpu_cores[i] = sjf.top();
            sjf.pop();
        }

        cout << '\t' << cpu_cores[i].get_pid();        
        if (i == cpu_cores.size() - 1) cout << '\n';

        cpu_cores[i].run_process();

        if (cpu_cores[i].get_burst_time() <= 0) {
            cpu_cores[i].clear_process_info();
        }
    }

    if ((sjf.empty() && end_of_file)) {
        terminate = true;
    }

    // if (chronon == 20) {
    //     terminate = true;
    // }

    chronon += 1;
}

bool exists_test(const string &name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}