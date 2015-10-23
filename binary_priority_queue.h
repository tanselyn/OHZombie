#ifndef BINARY_PRIORITY_QUEUE_H
#define BINARY_PRIORITY_QUEUE_H

#include <vector>
#include <algorithm>

#include "eecs281_priority_queue.h"

//A specialized version of the 'priority_queue' ADT implemented as a binary priority_queue.
template<typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class binary_priority_queue : public eecs281_priority_queue<TYPE, COMP_FUNCTOR> {
public:
    typedef unsigned size_type;
    
    //Description: Construct a priority_queue out of an iterator range with an optional
    //             comparison functor.
    //Runtime: O(n) where n is number of elements in range.
    template<typename InputIterator>
    binary_priority_queue(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR());
    
    //Description: Construct an empty priority_queue with an optional comparison functor.
    //Runtime: O(1)
    binary_priority_queue(COMP_FUNCTOR comp = COMP_FUNCTOR());
    
    //Description: Assumes that all elements inside the priority_queue are out of order and
    //             'rebuilds' the priority_queue by fixing the priority_queue invariant.
    //Runtime: O(n)
    virtual void update_priorities();
    
    //Description: Add a new element to the priority_queue.
    //Runtime: O(log(n))
    virtual void push(const TYPE& val);
    
    //Description: Remove the most extreme (defined by 'compare') element from
    //             the priority_queue.
    //Note: We will not run tests on your code that would require it to pop an
    //element when the priority_queue is empty. Though you are welcome to if you are
    //familiar with them, you do not need to use exceptions in this project.
    //Runtime: O(log(n))
    virtual void pop();
    
    //Description: Return the most extreme (defined by 'compare') element of
    //             the priority_queue.
    //Runtime: O(1)
    virtual const TYPE& top() const;
    
    //Description: Get the number of elements in the priority_queue.
    //Runtime: O(1)
    virtual size_type size() const {
        return data.size();
    }
    
    //Description: Return true if the priority_queue is empty.
    //Runtime: O(1)
    virtual bool empty() const {
        return data.empty();
    }
private:
    //Note: This vector *must* be used your priority_queue implementation.
    std::vector<TYPE> data;
private:
    // TODO: Add any additional member functions or data you require here.
};

template<typename TYPE, typename COMP_FUNCTOR>
template<typename InputIterator>
binary_priority_queue<TYPE, COMP_FUNCTOR>::binary_priority_queue(
                                                                 InputIterator start, InputIterator end, COMP_FUNCTOR comp) {
    
    this->compare = comp;
    for (InputIterator i = start; i < end; ++i) {
        data.push_back(*i);
    }
    update_priorities();
}

template<typename TYPE, typename COMP_FUNCTOR>
binary_priority_queue<TYPE, COMP_FUNCTOR>::binary_priority_queue(COMP_FUNCTOR comp) {
    this->compare = comp;
}

template<typename TYPE, typename COMP_FUNCTOR>
void binary_priority_queue<TYPE, COMP_FUNCTOR>::update_priorities() {
    for (int i = data.size()/2; i > 0; --i) {
        int k = i;
        while (2*k <= data.size()) {
            int j = 2*k;
            if (j < data.size() && this->compare(data[j - 1],data[j])) j++;
            if (this->compare(data[j - 1],data[k - 1])) break;
            std::swap(data[k - 1],data[j - 1]);
            k = j;
        }
    }
}

template<typename TYPE, typename COMP_FUNCTOR>
void binary_priority_queue<TYPE, COMP_FUNCTOR>::push(const TYPE& val) {
    if (data.empty()) {
        data.push_back(val);
        return;
    }
    if (this->compare(data[0],val)) {
        data.insert(data.begin(),val);
        return;
    }
    else if (this->compare(val,data.back())) {
        data.push_back(val);
        return;
    }
    else {
        data.push_back(val);
        int i = data.size();
        while (i > 1 && this->compare(data[(i/2) - 1],data[i-1])) {
            std::swap(data[i - 1],data[(i/2) - 1]);
            i = i/2;
        }
    }
}

template<typename TYPE, typename COMP_FUNCTOR>
void binary_priority_queue<TYPE, COMP_FUNCTOR>::pop() {
    if (!data.empty()) {
        if (data.size() == 1) {
            data.pop_back();
            return;
        }
        else {
            std::swap(data[0],data[data.size() - 1]);
            data.pop_back();
            int k = 1;
            while (2*k <= data.size()) {
    	        int j = 2*k;
                if (j < data.size() && this->compare(data[j - 1],data[j])) j++;
                if (this->compare(data[j - 1],data[k - 1])) break;
                std::swap(data[k - 1],data[j - 1]);
                k = j;
            }
        }
    }
}

template<typename TYPE, typename COMP_FUNCTOR>
const TYPE& binary_priority_queue<TYPE, COMP_FUNCTOR>::top() const {
    if (data.empty()) return NULL;
    return data.front();
}

#endif //BINARY_PRIORITY_QUEUE_H