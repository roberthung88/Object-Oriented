#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
#include <math.h>       /* ceil */
using namespace std;

template <typename T, typename PComparator = std::less<T>>
class Heap
{
public:
    /// Constructs an m-ary heap for any m >= 2
    Heap(int m, PComparator c = PComparator());

    /// Destructor as needed
    ~Heap();

    /// Adds an item
    void push(const T& item);
    
    //helper function for push
    void trickleUp(int loc);

    /// returns the element at the top of the heap
    ///  max (if max-heap) or min (if min-heap)
    T const & top() const;

    //helper function for pop
    void heapify(int idx);
    /// Removes the top element
    void pop();

    /// returns true if the heap is empty
    bool empty() const;

private:
    /// Add whatever helper functions and data members you need below
    vector<T> items_;
    int m;
    PComparator comparator;

};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c){
    //Converting An Array to a Heap
    T temp;
    items_.push_back(temp);
    comparator = c;
//    for(int i = items_.size() - 1; i >= 1; --i){
//        if(!((i * m) > int(items_.size() - 1))){
//            heapify(i);
//        }
//    }
    this->m = m;
    
}
template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap(){
    
}
// We will start top() for you to handle the case of
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
    // Here we use exceptions to handle the case of trying
    // to access the top element of an empty heap
    if(empty()) {
        throw std::logic_error("can't top an empty heap");
    }else{
        // If we get here we know the heap has at least 1 item
        // Add code to return the top element
        return items_[1];
    }

}


// We will start pop() for you to handle the case of
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
    if(empty()) {
        throw std::logic_error("can't pop an empty heap");
    }

    items_[1] = items_.back();
    items_.pop_back();
    heapify(1);

}

template <typename T, typename PComparator>
void Heap<T,PComparator>::heapify(int idx){
    //leaf node
    if((m*(idx - 1) + 2) > int(items_.size() - 1)) return;
    
    int smallerChild = m*(idx - 1) + 2;
    for(int i = m*(idx - 1) + 3; i <= (m*idx) + 1; ++i){
        if(i > int(items_.size() - 1)){
            break;
        }else{
            if(comparator(items_[i], items_[smallerChild])){
                smallerChild = i;
            }
        }
    }
    if(items_[smallerChild] == items_[m*(idx - 1) + 2]){
        smallerChild = m*(idx - 1) + 2;
    }
   
    if(!comparator(items_[idx], items_[smallerChild])){
        swap(items_[idx], items_[smallerChild]);
        heapify(smallerChild);
    }
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item){
    items_.push_back(item);
    trickleUp(items_.size() - 1);
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleUp(int loc)
{
    
    int parent = ceil((loc - 1)/(m*1.0));
    while(parent >= 1 && comparator(items_[loc], items_[parent]))
    {
        swap(items_[parent], items_[loc]);
        loc = parent;
        parent = ceil((loc - 1)/(m*1.0));
    }
}


template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const{
    return items_.size() == 1;
}


#endif

