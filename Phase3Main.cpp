/* ------------------------------------------------ */
/* FILE: Phase3Main_Kai.cpp                         */
/* DESCRIPTION: Test suite for Phase 3.             */
/* ------------------------------------------------ */
/* AUTHOR: Kaitlyn NeSmith                          */
/* EMAIL: klnesmith@crimson.ua.edu                  */
/* COURSE: CS 201-002 (Dixon)                       */
/* PROJECT: Project 3                               */
/* DATE: 2022-11-21                                 */
/* ------------------------------------------------ */

#include <ostream>
using namespace std;
#include "CircularDynamicArray.cpp"
#include "Heap.cpp"
#include "FibHeap.cpp"

/* Ignition!! */
int main()
{
    cout << "==================HEAP==================" << endl;

    // Test normal constructor
    Heap<int> H1;

    // Test empty print case
    H1.printKey();
    /* Should print nothing */

    // Insert a bunch of keys
    for (int i = 23; i >= 0; i--)
        H1.insert(i);

    // Print
    H1.printKey();
    /* Should print:                                                 *|
    |* 0 2 1 7 3 10 11 14 8 6 4 13 18 19 12 23 17 20 9 21 15 16 5 22 */

    // Add one, then print
    H1.insert(-1);
    H1.printKey();
    /* Should print:                                                    *|
    |* -1 2 0 7 3 1 11 14 8 6 4 10 18 19 12 23 17 20 9 21 15 16 5 22 13 */

    // Test copy assignment & constructor, print to show proper copy
    Heap<int> H2 = H1;
    Heap<int> H3(H1);
    H2.printKey();
    H3.printKey();
    /* Should print:                                                    *|
    |* -1 2 0 7 3 1 11 14 8 6 4 10 18 19 12 23 17 20 9 21 15 16 5 22 13 *|
    |* -1 2 0 7 3 1 11 14 8 6 4 10 18 19 12 23 17 20 9 21 15 16 5 22 13 */


    // Test peek
    cout << H1.peekKey() << endl;
    /* Should print: *|
    |* -1            */

    // Heapsort
    for (int i = 0; i < 25; i++)
        cout << H1.extractMin() << " ";
    cout << endl;
    /* Should print:                                                    *|
    |* -1 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 */

    // Ensure we've removed everything from the heap
    H1.printKey();
    /* Should print nothing */

    // Ensure that our other heaps are still intact
    H2.printKey();
    H3.printKey();
    /* Should print:                                                    *|
    |* -1 2 0 7 3 1 11 14 8 6 4 10 18 19 12 23 17 20 9 21 15 16 5 22 13 *|
    |* -1 2 0 7 3 1 11 14 8 6 4 10 18 19 12 23 17 20 9 21 15 16 5 22 13 */

    // Test array constructor
    char arr1[26];
    // Backwards alphabet
    for (int i = 25; i >= 0; i--)
        arr1[i] = 90 - i;
    
    // Construct & print
    Heap<char> H4(arr1, 26);
    H4.printKey();
    /* Should print:                                       *|
    |* A D B H E C L J I F P O N M T K S W R G Q V Y X Z U */

    // Heapsort
    for (int i = 0; i < 26; i++)
        cout << H4.extractMin() << " ";
    cout << endl;
    /* Should print:                                       *|
    |* A B C D E F G H I J K L M N O P Q R S T U V W X Y Z */

    // Size test
    Heap<int> H5;
    for (int i = 1000000; i >= 0; i--)
        H5.insert(i);
    // No print on this one, just makes sure that your memory management is solid
    // This should run in no more than 2 seconds

    // Peek first, extract a few
    cout << H5.peekKey() << endl;
    for (int i = 0; i < 10; i++)
        cout << H5.extractMin() << " ";
    cout << endl;
    /* Should print:                                       *|
    |* A B C D E F G H I J K L M N O P Q R S T U V W X Y Z */

    cout << "================FIBHEAP=================" << endl;

    // Regular constructor
    FibHeap<int> F1;

    // Test empty print
    F1.printKey();
    /* Should print nothing */

    // Insert some keys then print
    for (int i = 0; i < 4; i++)
        F1.insert(i);
    F1.printKey();
    /* Should print: *|
    |* Rank 0        *|
    |* 0             *|
    |*               *|
    |* Rank 0        *|
    |* 1             *|
    |*               *|
    |* Rank 0        *|
    |* 2             *|
    |*               *|
    |* Rank 0        *|
    |* 3             */

    // Ensure peek works
    cout << F1.peekKey() << endl;
    /* Should print: *|
    |* 0             */

    // Add some more, extract min, print
    for (int i = 4; i < 17; i++)
        F1.insert(i);
    cout << F1.extractMin() << endl;
    F1.printKey();
    /* Should print:                          *|
    |* 0                                      *|
    |* Rank 4                                 *|
    |* 1 9 13 15 16 14 11 12 10 5 7 8 6 3 4 2 */

    // Test array constructor
    int arr2[31];
    for (int i = 0; i < 31; i++)
        arr2[i] = i + 17;
    CircularDynamicArray<FibHeapNode<int> *> nodes;
    FibHeap<int> F2(arr2, 31, nodes);

    // Print out keys
    F2.printKey();
    /* Should print:                                   *|
    |* Rank 0                                          *|
    |* 47                                              *|
    |*                                                 *|
    |* Rank 1                                          *|
    |* 45 46                                           *|
    |*                                                 *|
    |* Rank 2                                          *|
    |* 41 43 44 42                                     *|
    |*                                                 *|
    |* Rank 3                                          *|
    |* 33 37 39 40 38 35 36 34                         *|
    |*                                                 *|
    |* Rank 4                                          *|
    |* 17 25 29 31 32 30 27 28 26 21 23 24 22 19 20 18 */

    // Test merge
    F1.merge(F2);
    F2.printKey();
    /* Should print nothing */
    F1.printKey();
    /* Should print:                                   *|
    |* Rank 4                                          *|
    |* 1 9 13 15 16 14 11 12 10 5 7 8 6 3 4 2          *|
    |*                                                 *|
    |* Rank 0                                          *|
    |* 47                                              *|
    |*                                                 *|
    |* Rank 1                                          *|
    |* 45 46                                           *|
    |*                                                 *|
    |* Rank 2                                          *|
    |* 41 43 44 42                                     *|
    |*                                                 *|
    |* Rank 3                                          *|
    |* 33 37 39 40 38 35 36 34                         *|
    |*                                                 *|
    |* Rank 4                                          *|
    |* 17 25 29 31 32 30 27 28 26 21 23 24 22 19 20 18 */

    // Extract min, then print heap
    cout << F1.extractMin() << endl;
    F1.printKey();
    /* Should print:                                                                                  *|
    |* 1                                                                                              *|
    |* Rank 1                                                                                         *|
    |* 2 47                                                                                           *|
    |*                                                                                                *|
    |* Rank 2                                                                                         *|
    |* 3 45 46 4                                                                                      *|
    |*                                                                                                *|
    |* Rank 3                                                                                         *|
    |* 5 41 43 44 42 7 8 6                                                                            *|
    |*                                                                                                *|
    |* Rank 5                                                                                         *|
    |* 9 17 25 29 31 32 30 27 28 26 21 23 24 22 19 20 18 33 37 39 40 38 35 36 34 13 15 16 14 11 12 10 */

    // Couple more extract mins for good measure
    for (int i = 0; i < 15; i++)
        cout << F1.extractMin() << " ";
    cout << endl;
    /* Should print:                        *|
    |* 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 */

    // One final print
    F1.printKey();
    /* Should print:                                   *|
    |* Rank 0                                          *|
    |* 47                                              *|
    |*                                                 *|
    |* Rank 1                                          *|
    |* 45 46                                           *|
    |*                                                 *|
    |* Rank 2                                          *|
    |* 41 43 44 42                                     *|
    |*                                                 *|
    |* Rank 3                                          *|
    |* 33 37 39 40 38 35 36 34                         *|
    |*                                                 *|
    |* Rank 4                                          *|
    |* 17 25 29 31 32 30 27 28 26 21 23 24 22 19 20 18 */

    // Test decrease key
    // This should not affect heap order
    F1.decreaseKey(nodes[0], 0);
    // This should affect heap order
    F1.decreaseKey(nodes[10], 1);
    F1.decreaseKey(nodes[14], 2);

    // Print
    F1.printKey();
    /* Should print:                      *|
    |* Rank 0                             *|
    |* 47                                 *|
    |*                                    *|
    |* Rank 1                             *|
    |* 45 46                              *|
    |*                                    *|
    |* Rank 2                             *|
    |* 41 43 44 42                        *|
    |*                                    *|
    |* Rank 3                             *|
    |* 33 37 39 40 38 35 36 34            *|
    |*                                    *|
    |* Rank 4                             *|
    |* 0 25 29 30 26 21 23 24 22 19 20 18 *|
    |*                                    *|
    |* Rank 1                             *|
    |* 1 28                               *|
    |*                                    *|
    |* Rank 1                             *|
    |* 2 32                               */

    // Test copy assign and construct
    //FibHeap<int> F3 = F1;
    //F3.printKey();
    /* Should print same as above */
    //FibHeap<int> F4(F3);
    //F4.printKey();
    /* Should print same as above */

    // Size test
    FibHeap<int> F5;
    for (int i = 0; i < 2000000; i++)
        F5.insert(i);
    // Extract first ALL the mins to prove working
    int val;
    int fails;
    for (int i = 0; i < 2000000; i++){
        val = F5.extractMin();
        if(val != i){
            cout << "FAIL! correct is "<< i <<" you got "<< val << endl;
            fails++;
        }
    }
    cout << "TESTS PASSED with "<<fails<<"!" << endl;
    cout << "-------------------------------------------" << endl;
    /* Should print: *|
    |* 0 1 2 3 4 5 6 7 8 9 */
    
    return 0;
}