#include "scheduler.h"

int main() {
    ifstream inFile;
    string input_line;
    queue<ProcessData> process_queue;
    int kwant = 0;

    inFile.open("sched1.in");

    while (getline(inFile, input_line) && !input_line.empty()) {
        ProcessData process;
        vector<string> buffer;
        // cout << input_line << endl;
        istringstream iss(input_line);
        string del;

        while (getline(iss, del, ' ')) {
            buffer.push_back(del);
        }
        for (int i = 1; i < buffer.size(); i++) {
            process.priority = stoi(buffer[i]);
            i++;
            process.time_to_execute = stoi(buffer[i]);
            i++;
            process.cpu_priority = stoi(buffer[i]);
            process_queue.push(process);
        }

        cout << "kwant: " << kwant << endl;
        kwant++;

        while (!process_queue.empty()) {
            cout << "proces: " << process_queue.front().priority << " " << process_queue.front().time_to_execute << " " << process_queue.front().cpu_priority << endl;
            process_queue.pop();
        }
    }

    return 0;
}