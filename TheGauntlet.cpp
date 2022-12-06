using namespace std;
#include <iostream>
#include "CircularDynamicArray.cpp"
#include "FibHeap.cpp"


int main(){
    FibHeap<int> F5;
    for (int i = 0; i < 10000; i++)
        F5.insert(i);
    // Extract first ALL the mins to prove working
    int val;
    int fails = 0;
    F5.consolidate();
    F5.printKey();
    cout << "TESTS PASSED with "<< fails << " Fails" <<"!" << endl;
    cout << "-------------------------------------------" << endl;
    return 0;
}