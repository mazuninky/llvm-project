#include "sanitizer_common/sanitizer_common.h"
#include "tsan_rtl_dd_impoved.h"
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

namespace __dd {
    map<int, vector<unsigned long>> locked;
    map<int, unsigned long> request;
    map<unsigned long, bool> is_captured;

    void PerformDeadlock() {
        __sanitizer::Printf("Deadlock auhtung!");
    }

    void PerformCreateMutex(unsigned long mutex_addr) {
        __sanitizer::Printf("[Create thread]Mutex 0x%zx\n", mutex_addr);
        is_captured.insert(pair<unsigned long, bool>(mutex_addr, false));
    }

    void PerformCreateThread(int tid) {
        __sanitizer::Printf("[Create thread]Thread%d\n", tid);
        locked.insert(pair<int, vector<unsigned long>>(tid, vector<unsigned long>()));
    }

    void PerformBeforeLock(int tid, unsigned long mutex_addr) {
        __sanitizer::Printf("[Before lock]Thread%d with mutex 0x%zx\n", tid, mutex_addr);
        request[tid] = mutex_addr;

        if (!is_captured[mutex_addr])
            return;

        auto it = find_if(locked.begin(), locked.end(),
                          [mutex_addr](const std::pair<int, vector<unsigned long>> &item) -> bool {
                              auto list = item.second;
                              return find_if(list.begin(), list.end(),
                                             [mutex_addr](unsigned long mutex) -> bool {
                                                 return mutex == mutex_addr;
                                             }) != list.end();
                          });

        if (it == locked.end()) {
            __sanitizer::Printf("Illegal state\n");
            return;
        }

        auto find_thread = (*it).first;

        if (request.count(find_thread) == 0)
            return;

        auto locked_thread = locked[tid];
        auto possible_deadlock = find(locked_thread.begin(), locked_thread.end(), request[find_thread]);
        if (possible_deadlock != locked_thread.end()) {
            PerformDeadlock();
            return;
        }
    }

    void PerformAfterLock(int tid, unsigned long mutex_addr) {
        __sanitizer::Printf("[After lock]Thread%d with mutex 0x%zx\n", tid, mutex_addr);

        request.erase(tid);
        locked[tid].push_back(mutex_addr);
        is_captured[mutex_addr] = true;
    }

    void PerformUnlock(int tid, unsigned long mutex_addr) {
        __sanitizer::Printf("[Unlock]Thread%d with mutex 0x%zx\n", tid, mutex_addr);
        locked[tid].pop_back();
        is_captured[mutex_addr] = false;
    }

    void PerformDestroyMutex(unsigned long mutex_addr) {
        __sanitizer::Printf("[Destroy mutex]Mutex 0x%zx\n", mutex_addr);

        is_captured.erase(mutex_addr);
    }

    void PerformDestroyThread(int tid) {
        __sanitizer::Printf("[Destroy thread]Thread %d\n", tid);

        locked.erase(tid);
        request.erase(tid);
    }
} // namespace __dd