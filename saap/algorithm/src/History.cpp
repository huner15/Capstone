/**
* @file History.cpp
* @author Specific Atomics
* @author Dat Tran
* @date 2-24-16
* @brief Represents history of snapshots
*/

#include "History.h"
#include "Snapshot.h"

History::History() {

}

History::~History() {

}

Snapshot *History::GetLast() const {
    return _last;
}

Snapshot *History::GetSecondToLast() const {
    return _second_to_last;
}

int History::AddSnapshot(Snapshot *snapshot) {
    int status = 0;

    if (snapshot == NULL) {
        status = 1;
    }
    else {
        // Empty last snapshot
        time_t t = _last->GetTimestamp();
        if (time(&t) == -1) {
            _last = snapshot;
        } else {
            _last = snapshot;
            _second_to_last = _last;
        }
    }
    return status;
}
