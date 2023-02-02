#include "scheduler.hpp"

int main(int argc, char *argv[]) {
    int algorithm_choice;
    string filename;
    int chronon = 0;
    bool end_of_file = false;
    bool terminate = false;
    array<ProcessData, 3> cpu_cores = {ProcessData(-1, -1, -1), ProcessData(-1, -1, -1), ProcessData(-1, -1, -1)};

    queue<ProcessData> fcfs;
    priority_queue<ProcessData, vector<ProcessData>, Compare> sjf;

    // cout << "Choose used algorithm:" << endl;
    // cout << "1 - FCFS, non-preemptive" << endl;
    // cin >> algorithm_choice;

    while (1) {
        cout << "Enter filename:" << '\n';
        cin >> filename;
        if (exists_test(filename)) {
            break;
        }
        cout << "File does not exist." << '\n';
    }

    ifstream infile(filename);
    string input_line;

    cout << "Chronon" << '\t' << "CPU0" << '\t' << "CPU1" << '\t' << "CPU2" << '\n';
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
                // fcfs.push(process_params);
                sjf.push(process_params);
            }
        } else
            end_of_file = true;
        shortest_jobtime_first(sjf, cpu_cores, chronon, terminate, end_of_file);
        // first_come_first_served(fcfs, cpu_cores, chronon, terminate, end_of_file);

        if (terminate) break;
    }
}