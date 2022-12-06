#include <iostream>
using namespace std;
#include "CircularDynamicArray.cpp"
#include "Heap.cpp"

int main(){
    Heap<int> H;
    for(int i = 0; i < 10; i++){
        H.insert(i);
    }
    for(int i = 0; i < 10; i++){
        cout << H.extractMin() << " ";
    }
    return 0;
}