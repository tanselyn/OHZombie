/*
 * Example of ownership issues when handling objects directly allocated on the
 * heap. For this test to work, you'll need to have implemented the Poor Man's
 * Priority Queue.
 *
 * This program pushes some numbers into a priority queue, then pops them off
 * in sorted order, and then also prints out the odd numbers that were found in
 * this way.
 */
#include "eecs281_priority_queue.h"
#include "poorman_priority_queue.h"

#include <iostream>
#include <vector>

// Comparison functor for integer pointers.
struct IntPtrComparator {
    // Mark as `const` and take `const` parameters so that we can use this
    // comparator inside `const` member functions and so on.
    //
    // This function returns `true` if `a` has a lower `priority` than `b`.
    // Since we implement max-priority-queues, we want to specify our
    // comparator such that it returns `true` if we want to get `a` after `b`.
    bool operator()(const int* a, const int* b) const {
        return *a < *b;
    }
};

int main() {
    // Create a new priority queue. `eecs281_priority_queue` is an abstract
    // class. In order to be able to use it, we have to declare it as a pointer
    // or reference. Since we access it through a pointer/reference, this also
    // means that we can use polymorphism and resolve virtual functions at
    // runtime.
    eecs281_priority_queue<int*, IntPtrComparator>* pq;
    pq = new poorman_priority_queue<int*, IntPtrComparator>{};

    // These pointers point to elements referenced by the priority queue, but
    // it /does not own/ them. This means that it is not responsible for
    // managing that memory.
    std::vector<int*> odds;

    for (int i : {10, 5, 20, 7}) {
        // Here, we say that `pq` has "ownership" of the `int` objects created
        // here. In order to maintain our sanity, it should also be responsible
        // for cleaning it up.
        pq->push(new int{i});
    }

    while (!pq->empty()) {
        // Pop the top int pointer. The `int` itself is still alive in dynamic
        // memory.
        int* topInt = pq->top();
        pq->pop();

        std::cout << "Got value: " << *topInt << std::endl;

        if ((*topInt % 2) == 0) {
            // Discard even numbers. Since the priority queue owns it, and
            // nobody else needs it, we should now delete it on behalf of the
            // priority queue.
            delete topInt;
        } else {
            // The priority queue no longer cares about the integer. But we
            // want to save it for later in the vector. That means that we
            // should /transfer ownership/ to the vector. From this point on,
            // the priority queue is no longer responsible for handling that
            // memory, but the vector is.
            odds.push_back(topInt);
        }

        // Since the pointer has been popped off, the priority queue no longer
        // has any memory of it. It was either cleaned up or its ownership was
        // transferred elsewhere.
    }

    // Notice that this should be `2` for a correct implementation.
    std::cout << "Found " << odds.size() << " odd numbers." << std::endl;

    // We are now exiting the program. The vector still owns some number of
    // pointers and they need to be cleaned up.
    for (int* intPointer : odds) {
        delete intPointer;
    }

    // Delete the priority queue itself.
    delete pq;

    return 0;
}
