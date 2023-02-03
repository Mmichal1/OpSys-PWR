#include "process_data.hpp"

class CompareBurstTimeOrPID {
   public:
    bool operator()(ProcessData a, ProcessData b) {
        if (a.get_burst_time() == b.get_burst_time()) {
            return a.get_pid() > b.get_pid();
        }
        return a.get_burst_time() > b.get_burst_time();
    }
};

class ComparePriorityOrPID {
   public:
    bool operator()(ProcessData a, ProcessData b) {
        if (a.get_burst_time() == b.get_priority()) {
            return a.get_pid() > b.get_pid();
        }
        return a.get_priority() > b.get_priority();
    }
};

class ComparePriorityOrBurstTime {
   public:
    bool operator()(ProcessData a, ProcessData b) {
        if (a.get_burst_time() == b.get_priority()) {
            return a.get_burst_time() > b.get_burst_time();
        }
        return a.get_priority() > b.get_priority();
    }
};