/*
    Nicholas Warren
    12164563
    CS 201 - Data Structures and Algoriths
    Phase 3
*/
#include <iostream>
//#include "CircularDynamicArray.cpp"


template <class keytype>
class Heap {
    public:
        CircularDynamicArray<keytype> heapArr;
        int size;
    Heap(){
        size = 0;
    }
    ~Heap(){
        
    }
    //Heap constructor from initial array.
    Heap(keytype k[], int s){
        size = s;
        for(int i = 0; i < s; i++){
            heapArr.addEnd(k[i]);
        }
        bottomUpConstruction();
    }
    //builds heap bottom to top
    void bottomUpConstruction(){
        int siz = heapArr.length();
        for(int i = siz/2; i >= 0; i--){
            heapify(i);
        }
    }
    //returns the minimum element without effecting the array
    keytype peekKey(){
        return heapArr[0];
    }

    //removes the minimum element from the heap and returns the key
    keytype extractMin(){
        keytype minValue;
        minValue = heapArr[0]; //stores minimum value
        swap(heapArr[0], heapArr[size-1]); //replaces front with back
        heapArr.delEnd(); //deletes duplicate at the back
        size--;
        heapify(0); //fixes heap
        return minValue; //returns minimum value.
    }
    //helper function to get the index of the given index's parent.
    int getParent(int idx){
        return ((idx-1)/2); //math to find the parent.
    }
    //helper function to get the index of the right child of the given index.
    int getRight(int idx){
        return (2*idx+2); //math to find the position of the right child.
    }
    //helper function to get the index of the given index's left child if there is one
    int getLeft(int idx){
        return (2*idx+1); //math to find the position of the left child.
    }
    //inserts new key into the array
    void insert(keytype k){
        size++;
        heapArr.addEnd(k);

        int i = size-1;
        //maintains heap properties after insert
        while(i != 0 && heapArr[getParent(i)] > heapArr[i]){
            swap(heapArr[i], heapArr[getParent(i)]);
            i = getParent(i);
        }
    }
    //fixes heap after delete
    void heapify(int idx){
        int left, right;
        left = getLeft(idx);
        right = getRight(idx);
        int smallest = idx;

        keytype temp;

        if(left < size && heapArr[left] < heapArr[idx]){
            smallest = left;
        } 
        if(right < size && heapArr[right] < heapArr[smallest]){
            smallest = right;
        }
        if(smallest != idx){
            swap(heapArr[idx],heapArr[smallest]);
            heapify(smallest);
        }
    }
    //prints the keys in the array starting at root
    void printKey(){
        for(int i = 0; i < size; i++){
            cout << heapArr[i] << " ";
        }
        cout << endl;
    }
};

/*
    TODO
        MAKE:
            destructor?
        FIX:
        TEST:
            extractMin
            insert




*/