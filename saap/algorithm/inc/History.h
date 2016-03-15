/**
* @file History.h
* @author Specific Atomics
* @author Dat Tran
* @date 2-24-16
* @brief Represents history of snapshots
*/

#ifndef SAAS_HISTORY_H
#define SAAS_HISTORY_H
#include "Snapshot.h"

class History {
private:
    Snapshot *_last; /** The most recent Snapshot. */
    Snapshot *_second_to_last; /** The second most recent Snapshot. */

public:
    History();
    ~History();
    /**
     * Accessor to the most recent Snapshot.
     *
     * @return The most recent Snapshot.
     */
    Snapshot *GetLast() const;

    /**
     * Accessor to the second to most recent Snapshot.
     *
     * @return The second to most recent Snapshot.
     */
    Snapshot *GetSecondToLast() const;

    /**
     * Adds a Snapshot to the history and shifts subsequent Snapshots
     *
     * @return 0 on success and 1 on failure
     */
    int AddSnapshot(Snapshot *snapshot);
};

#endif //SAAS_HISTORY_H
