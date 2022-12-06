#include <iostream>
using namespace std;
#include "CircularDynamicArray.cpp"
#include "Heap.cpp"
#include "FibHeap.cpp"

//inside FibHeap.cpp the definitition of FibHeapNode is expected, for example:
//template <typename keytype>
//struct FibHeapNode {
//    keytype x;
//    FibHeapNode<keytype> *ptr;
//    etc.  You may define any elements needed inside FibHeapNode
//};


int main(){
	FibHeap<int> F5;
    for (int i = 0; i < 200000; i++)
        F5.insert(i);
    // Extract first couple mins to prove working
    cout << endl;
	return 0;
}