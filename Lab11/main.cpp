#include "scheduler.hpp"

int main(int argc, char* argv[]) {
    int algorithm_choice;
    int chronon = 0;
    // cout << "Choose used algorithm:" << endl;
    // cout << "1 - FCFS, non-preemptive" << endl;
    // cin >> algorithm_choice;

    // read file name here

    ifstream infile("sched1.in");
    string input_line;
    bool end_of_file = false;
    bool terminate = false;
    queue<ProcessData> fcfs;
    array<ProcessData, atol(argv[1])> cpu_cores;

    // cout << cpu_0.get_pid() << cpu_0.get_burst_time() << cpu_0.get_priority() << endl;

    while (1) {
        if (getline(infile, input_line)) {
            istringstream iss(input_line);
            string process_info;
            vector<int> buffer;

            while (getline(iss, process_info, ' ')) {
                buffer.push_back(stoi(process_info));
            }

            for (int i = 1; i < buffer.size(); i++) {
                ProcessData process_params = ProcessData(buffer[i], buffer[i++], buffer[i++]);
                fcfs.push(process_params);
                // cout << "index: " << i << '\n';
                // cout << "pid: " << process_params.get_pid() << " burst_time: " << process_params.get_burst_time() << " priority: " << process_params.get_priority() << '\n';
            }
        } else {
            end_of_file = true;
        }

        // cout << chronon << " " << cpu_0.get_pid() << endl;

        first_come_first_served(fcfs, cpu_cores, chronon, terminate, end_of_file);

        if (terminate) {
            break;
        }
    }
}