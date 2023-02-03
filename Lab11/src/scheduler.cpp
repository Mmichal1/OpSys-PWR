#include "../include/scheduler.hpp"

void first_come_first_served(queue<ProcessData> &fcfs, array<ProcessData, 3> &cpu_cores, bool &terminate, bool end_of_file) {
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

    terminate = check_conditions_for_termination(fcfs.empty(), end_of_file, cpu_cores);
}

void shortest_jobtime_first(priority_queue<ProcessData, vector<ProcessData>, CompareBurstTimeOrPID> &sjf, array<ProcessData, 3> &cpu_cores, bool &terminate, bool end_of_file) {
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

    terminate = check_conditions_for_termination(sjf.empty(), end_of_file, cpu_cores);
}

void shortest_remaining_time(priority_queue<ProcessData, vector<ProcessData>, CompareBurstTimeOrPID> &srtf, array<ProcessData, 3> &cpu_cores, bool &terminate, bool end_of_file) {
    ProcessData buffer = ProcessData(-1, -1, -1);
    for (int i = 0; i < cpu_cores.size(); i++) {
        buffer = srtf.top();

        if (cpu_cores[i].get_pid() == -1 && !srtf.empty()) {
            cpu_cores[i] = srtf.top();
            srtf.pop();
            buffer = srtf.top();
        }

        if (cpu_cores[i].get_burst_time() > buffer.get_burst_time()) {
            srtf.push(cpu_cores[i]);
            cpu_cores[i] = buffer;
            srtf.pop();
        }

        cout << '\t' << cpu_cores[i].get_pid();
        if (i == cpu_cores.size() - 1) cout << '\n';

        cpu_cores[i].run_process();

        if (cpu_cores[i].get_burst_time() <= 0) {
            cpu_cores[i].clear_process_info();
        }
    }

    terminate = check_conditions_for_termination(srtf.empty(), end_of_file, cpu_cores);
}

void round_robin(queue<ProcessData> &rr, array<ProcessData, 3> &cpu_cores, array<int, 3> &time_on_processor, bool &terminate, bool end_of_file) {
    for (int i = 0; i < cpu_cores.size(); i++) {
        if (cpu_cores[i].get_pid() == -1 && !rr.empty()) {
            cpu_cores[i] = rr.front();
            rr.pop();
            time_on_processor[i] = 0;
        }

        if (time_on_processor[i] == 2) {
            rr.push(cpu_cores[i]);
            cpu_cores[i] = rr.front();
            rr.pop();
            time_on_processor[i] = 0;
        }

        cout << '\t' << cpu_cores[i].get_pid();
        if (i == cpu_cores.size() - 1) cout << '\n';

        cpu_cores[i].run_process();
        time_on_processor[i] = time_on_processor[i] + 1;

        if (cpu_cores[i].get_burst_time() <= 0) {
            cpu_cores[i].clear_process_info();
        }
    }

    terminate = check_conditions_for_termination(rr.empty(), end_of_file, cpu_cores);
}

void preemptive_priority_queue_with_fcfs(priority_queue<ProcessData, vector<ProcessData>, ComparePriorityOrPID> &pq_fcfs, array<ProcessData, 3> &cpu_cores, bool &terminate, bool end_of_file) {
    ProcessData buffer = ProcessData(-1, -1, -1);
    for (int i = 0; i < cpu_cores.size(); i++) {
        buffer = pq_fcfs.top();

        if (cpu_cores[i].get_pid() == -1 && !pq_fcfs.empty()) {
            cpu_cores[i] = pq_fcfs.top();
            pq_fcfs.pop();
            buffer = pq_fcfs.top();
        }

        if (cpu_cores[i].get_priority() > buffer.get_priority()) {
            pq_fcfs.push(cpu_cores[i]);
            cpu_cores[i] = buffer;
            pq_fcfs.pop();
        }

        cout << '\t' << cpu_cores[i].get_pid();
        if (i == cpu_cores.size() - 1) cout << '\n';

        cpu_cores[i].run_process();

        if (cpu_cores[i].get_burst_time() <= 0) {
            cpu_cores[i].clear_process_info();
        }
    }

    terminate = check_conditions_for_termination(pq_fcfs.empty(), end_of_file, cpu_cores);
}

void preemptive_priority_queue_with_srtf(priority_queue<ProcessData, vector<ProcessData>, ComparePriorityOrBurstTime> &pq_srtf, array<ProcessData, 3> &cpu_cores, bool &terminate, bool end_of_file) {
    ProcessData buffer = ProcessData(-1, -1, -1);
    for (int i = 0; i < cpu_cores.size(); i++) {
        buffer = pq_srtf.top();

        if (cpu_cores[i].get_pid() == -1 && !pq_srtf.empty()) {
            cpu_cores[i] = pq_srtf.top();
            pq_srtf.pop();
            buffer = pq_srtf.top();
        }

        if (cpu_cores[i].get_priority() > buffer.get_priority()) {
            pq_srtf.push(cpu_cores[i]);
            cpu_cores[i] = buffer;
            pq_srtf.pop();
        }

        cout << '\t' << cpu_cores[i].get_pid();
        if (i == cpu_cores.size() - 1) cout << '\n';

        cpu_cores[i].run_process();

        if (cpu_cores[i].get_burst_time() <= 0) {
            cpu_cores[i].clear_process_info();
        }
    }

    terminate = check_conditions_for_termination(pq_srtf.empty(), end_of_file, cpu_cores);
}

void nonpreemptive_priority_queue_with_fcfs(priority_queue<ProcessData, vector<ProcessData>, ComparePriorityOrPID> &npq_fcfs, array<ProcessData, 3> &cpu_cores, bool &terminate, bool end_of_file) {
    for (int i = 0; i < cpu_cores.size(); i++) {
        if (cpu_cores[i].get_pid() == -1 && !npq_fcfs.empty()) {
            cpu_cores[i] = npq_fcfs.top();
            npq_fcfs.pop();
        }

        cout << '\t' << cpu_cores[i].get_pid();
        if (i == cpu_cores.size() - 1) cout << '\n';

        cpu_cores[i].run_process();

        if (cpu_cores[i].get_burst_time() <= 0) {
            cpu_cores[i].clear_process_info();
        }
    }

    terminate = check_conditions_for_termination(npq_fcfs.empty(), end_of_file, cpu_cores);
}

bool check_conditions_for_termination(bool is_queue_empty, bool end_of_file, array<ProcessData, 3> &cpu_cores) {
    if (is_queue_empty && end_of_file) {
        for (auto process : cpu_cores) {
            if (process.get_pid() != cpu_cores.begin()->get_pid()) {
                return false;
            }
        }
        return true;
    } else
        return false;
}

bool exists_test(const string &name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}