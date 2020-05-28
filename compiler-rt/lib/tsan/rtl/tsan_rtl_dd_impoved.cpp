#include "sanitizer_common/sanitizer_common.h"
#include "tsan_rtl_dd_impoved.h"

namespace __dd {

    void PerformBeforeLock(int tid, unsigned long mutex_addr) {
        __sanitizer::Printf("[Before lock]Thread%d with mutex %zx\n", tid, mutex_addr);
    }

    void PerformAfterLock(int tid, unsigned long mutex_addr) {
        __sanitizer::Printf("[After lock]Thread%d with mutex %zx\n", tid, mutex_addr);
    }

    void PerformUnlock(int tid, unsigned long mutex_addr) {
        __sanitizer::Printf("[Unlock]Thread%d with mutex %zx\n", tid, mutex_addr);
    }

    void PerformDestroy(unsigned long mutex_addr) {
        __sanitizer::Printf("[Destroy]Mutex %zx\n", mutex_addr);
    }
}