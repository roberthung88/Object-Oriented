#include <vector>
#include <functional>
#include <iostream>
#include <cstdlib>
#include "heap.h"
using namespace std;

int main()
{
//    greater<int> c;
//    Heap<int, greater<int> > h(2, c);
//    for(int i=0; i < 20; i++) {
//        h.push(rand() % 100);
//    }
//    while(!h.empty()) {
//        cout << h.top() << " ";
//        h.pop();
//    }
//    cout << endl;
//
//    Heap<int> h2(3);
//    for(int i=0; i < 20; i++) {
//        h2.push(rand() % 100);
//    }
//    while(!h2.empty()) {
//        cout << h2.top() << " ";
//        h2.pop();
//    }
//    cout << endl;
//    return 0;
    Heap<int> heap(2);
    heap.push(50);
    heap.push(49);
    cout << heap.top() << endl;
    //EXPECT_EQ(49, heap.top());

    heap.pop();
    cout << heap.top() << endl;
    //EXPECT_EQ(50, heap.top());
}
