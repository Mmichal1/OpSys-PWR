#include "scheduler.hpp"

int main(int argc, char *argv[]) {
    int algorithm_choice = -1;
    string filename;
    int chronon = 0; // Quantum of time
    bool end_of_file = false;
    bool terminate = false;
    array<ProcessData, 3> cpu_cores = {ProcessData(-1, -1, -1), ProcessData(-1, -1, -1), ProcessData(-1, -1, -1)};
    array<int, 3> time_on_processor = {0, 0, 0};

    queue<ProcessData> fcfs;
    queue<ProcessData> rr;
    priority_queue<ProcessData, vector<ProcessData>, CompareBurstTimeOrPID> sjf;
    priority_queue<ProcessData, vector<ProcessData>, CompareBurstTimeOrPID> srtf;
    priority_queue<ProcessData, vector<ProcessData>, ComparePriorityOrPID> pq_fcfs;
    priority_queue<ProcessData, vector<ProcessData>, ComparePriorityOrPID> npq_fcfs;
    priority_queue<ProcessData, vector<ProcessData>, ComparePriorityOrBurstTime> pq_srtf;

    // \e[1m and \e[0m is only for command line formatting
    while (1) {
        cout << "\e[1mEnter filename:\e[0m" << '\n';
        cin >> filename;
        if (exists_test(filename)) {
            break;
        }
        cout << "\e[1mFile does not exist.\e[0m" << '\n';
    }

    while (1) {
        cout << "\e[1mChoose used algorithm:\e[0m" << '\n';
        cout << "0 - FCFS, non-preemptive" << '\n';
        cout << "1 - SJF, non-preemptive" << '\n';
        cout << "2 - SRTF, preemptive" << '\n';
        cout << "3 - RR, preemptive" << '\n';
        cout << "4 - Priority Queue, preemptive, processes with the same priority sorted by FCFS" << '\n';
        cout << "5 - Priority Queue, preemptive, processes with the same priority sorted by SRTF" << '\n';
        cout << "6 - Priority Queue, non-preemptive, processes with the same priority sorted by FCFS" << '\n';
        cin >> algorithm_choice;
        if (algorithm_choice >= 0 && algorithm_choice <= 6) {
            break;
        }
        cout << "Wrong argument." << '\n';
    }

    ifstream infile(filename);
    string input_line;

    cout << "\e[1mChronon" << '\t' << "\e[1mCPU0" << '\t' << "\e[1mCPU1" << '\t' << "\e[1mCPU2\e[0m" << '\n';
    while (1) {
        if (getline(infile, input_line)) {
            istringstream iss(input_line);
            string process_info;
            vector<int> buffer;

            // Split string by space and load into buffer  
            while (getline(iss, process_info, ' ')) {
                buffer.push_back(stoi(process_info));
            }

            // First element in buffer vector is always the unit of time, then the process parameters are parsed
            // Process parameters are as follows: pid priority burst_time
            for (int i = 1; i < buffer.size(); i++) {
                ProcessData process_params = ProcessData(buffer[i], buffer[i++], buffer[i++]);
                switch (algorithm_choice) {
                    case 0:
                        fcfs.push(process_params);
                        break;
                    case 1:
                        sjf.push(process_params);
                        break;
                    case 2:
                        srtf.push(process_params);
                        break;
                    case 3:
                        rr.push(process_params);
                        break;
                    case 4:
                        pq_fcfs.push(process_params);
                        break;
                    case 5:
                        pq_srtf.push(process_params);
                        break;
                    case 6:
                        npq_fcfs.push(process_params);
                        break;
                }
            }
            buffer.clear();
        } else
            end_of_file = true;

        cout << chronon;
        
        switch (algorithm_choice) {
            case 0:
                first_come_first_served(fcfs, cpu_cores, terminate, end_of_file);
                break;
            case 1:
                shortest_jobtime_first(sjf, cpu_cores, terminate, end_of_file);
                break;
            case 2:
                shortest_remaining_time(srtf, cpu_cores, terminate, end_of_file);
                break;
            case 3:
                round_robin(rr, cpu_cores, time_on_processor, terminate, end_of_file);
                break;
            case 4:
                preemptive_priority_queue_with_fcfs(pq_fcfs, cpu_cores, terminate, end_of_file);
                break;
            case 5:
                preemptive_priority_queue_with_srtf(pq_srtf, cpu_cores, terminate, end_of_file);
                break;
            case 6:
                nonpreemptive_priority_queue_with_fcfs(npq_fcfs, cpu_cores, terminate, end_of_file);
                break;
        }
        if (terminate) break;

        chronon++;
    }

    cout << "\e[1mALL PROCESSES FINISHED\e[1m" << '\n';
}