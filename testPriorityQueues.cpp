/*
 * This is an example test for one of the priority queues. We /strongly/
 * recommend that you utilize unit tests like this file to ensure that your
 * priority queues are correct. This test suite is not enough to verify that
 * your priority queues are working.
 *
 * This test will be failing until you implement all of the priority queues.
 */
#include "binary_priority_queue.h"
#include "eecs281_priority_queue.h"
#include "pairing_priority_queue.h"
#include "poorman_priority_queue.h"
#include "sorted_priority_queue.h"

#include <cassert>
#include <iostream>
#include <string>
#include <utility>

void testNext(eecs281_priority_queue<int>& pq, int nextValue) {
    std::cout << "Expected " << nextValue << ", got " << pq.top() << std::endl;
    assert(pq.top() == nextValue);
    pq.pop();
}

int main() {
    std::vector<std::pair<std::string, eecs281_priority_queue<int>*>> pqs = {
        // Ordered from easiest to hardest to implement.
        {"Poorman", new poorman_priority_queue<int>{}},
        {"Sorted", new sorted_priority_queue<int>{}},
        {"Binary", new binary_priority_queue<int>{}},
        {"Pairing", new pairing_priority_queue<int>{}},
    };

    for (auto& pqInfo : pqs) {
        std::cout << "Priority queue " << pqInfo.first << std::endl;

        eecs281_priority_queue<int>& pq = *pqInfo.second;
        pq.push(1);
        pq.push(10);
        pq.push(5);

        testNext(pq, 10);
        testNext(pq, 5);
        testNext(pq, 1);

        std::cout << "All tests passed for queue " << pqInfo.first << std::endl;
    }

    // Clean up memory.
    for (auto& pqInfo : pqs) {
        delete pqInfo.second;
    }
}
