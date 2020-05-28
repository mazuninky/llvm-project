#ifndef DD_IMPROVED_H
#define DD_IMPROVED_H

//#include <map>

namespace __dd {

    void PerformBeforeLock(int tid, unsigned long mutex_addr);

    void PerformAfterLock(int tid, unsigned long mutex_addr);

    void PerformUnlock(int tid, unsigned long mutex_addr);

    void PerformDestroy(unsigned long mutex_addr);
}  // namespace __dd

#endif  // DD_IMPROVED_H