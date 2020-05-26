#pragma once

//#include <map>

namespace __dd {

    void PerformBeforeLock();
    void PerformAfterLock();
    void PerformBeforeUnlock();
    void PerformDestroy();

//    std::map< > _captured_mutex;
}  // namespace __dd
