#ifndef DD_IMPROVED_H
#define DD_IMPROVED_H

namespace __dd {

    void PerformCreateMutex(unsigned long mutex_addr);

    void PerformCreateThread(int tid);

    void PerformBeforeLock(int tid, unsigned long mutex_addr);

    void PerformAfterLock(int tid, unsigned long mutex_addr);

    void PerformUnlock(int tid, unsigned long mutex_addr);

    void PerformDestroyMutex(unsigned long mutex_addr);

    void PerformDestroyThread(int tid);
}  // namespace __dd

#endif  // DD_IMPROVED_H