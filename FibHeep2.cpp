#include <iostream>
#include "CircularDynamicArray.cpp"

template <class keytype>

class FibNode{
    keytype key;
    FibNode<keytype> *parent;
    FibNode<keytype> *left;
    FibNode<keytype> *right;
    FibNode<keytype> *child;

    FibNode(keytype k){
        left = right = this;
    }

};

template <class keytype>
class FibHeep2 {
    public:
    FibNode<keytype> *nil;
    FibNode<keytype> *head;
    FibNode<keytype> *min;

    FibHeep2(){

    }

    FibHeep2(keytype k[],int s, CircularDynamicArray<FibHeapNode<keytype> *> &handle){
        
        for(int i = 0; i < s; i++){
            FibHeapNode<keytype> x = FibHeapNode<keytype>(k[i]);
        }
    }

    
};