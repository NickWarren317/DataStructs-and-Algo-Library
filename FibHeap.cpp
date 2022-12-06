/*
    Nicholas Warren
    12164563
    CS 201 - Data Structures and Algorithms
    Phase 3
*/
#include <cmath>
#include "CircularDynamicArray.cpp"

template <class keytype>

class FibHeapNode{
    public:
    keytype key; //value of Node.
    int degree; //number of children below the current node
    int numChildren = 0; //number of children in child list
    bool mark;

    FibHeapNode<keytype> *parent; //points to the parent of the node
    FibHeapNode<keytype> *left; //points to the left brother of the node
    FibHeapNode<keytype> *right; //points to the right brother of the node
    FibHeapNode<keytype> *child;
    FibHeapNode<keytype> *childTail;
    //constructor
    FibHeapNode(keytype k){
        key = k;
        degree = 0;
        mark = false;
        child = nullptr;
        parent = nullptr;
        left = right = this; // sets left and right to point to itself by default
    }
    ~FibHeapNode(){
        delete this;
    }
};
template <class keytype>
class FibHeap{
    public:
         FibHeapNode<keytype> *min; //points to smallest element
         FibHeapNode<keytype> *nil; //holder node
         FibHeapNode<keytype> *rootListHead; //points to start of the root list
         FibHeapNode<keytype> *rootListTail; //points to the end of the root list
         int rootListSize; //number of elements in the root list
         int size; //number of elements in the FibHeap
         int maxDegree; //largest degree in the tree

        FibHeap(){
            size = 0; //number of nodes in the fibHeap
            maxDegree = 0; //might be useful later
            rootListSize = 0; //number of nodes in the root list.
        }
        FibHeap(keytype k[],int s, CircularDynamicArray<FibHeapNode<keytype> *> &handle){
            size = 0;
            maxDegree = 0;
            rootListSize = 0;
            for(int i = 0; i < s; i++){
                handle.addEnd(insert(k[i]));
            }
            consolidate();
        }
        ~FibHeap(){
            deleteHelper();
        }
        void deleteHelper(){
            FibHeapNode<keytype> *current = rootListHead;
            int num = rootListSize;
            for(int i = 0; i < num; i++){ //delete each tree in rootlist
                deleteTree(current);
                current = current->right;
            }
        }
        void deleteTree(FibHeapNode<keytype> *t){
            if(t == nullptr){
                return;
            }
            FibHeapNode<keytype> *current = t->child;
            for(int i = 0; i < t->degree; i++){ //recurse on other siblings
                deleteTree(current);
                current = current->right;
            }
            delete current;
        }
        //insert key into rootlist
        FibHeapNode<keytype>* insert(keytype k){
            //create new node with nulls for pointers
            size++;
            rootListSize++;
            FibHeapNode<keytype> *z = new FibHeapNode<keytype>(k);
            if(size > 1){
                //check to see if node is less than current minimum
                if(z->key < min->key){
                    min = z;
                }
                //link z to the end of the list
                rootListTail->right = z;
                z->left = rootListTail;
                rootListTail = z;
                //link front and back
                rootListTail->right = rootListHead;
                rootListHead->left = rootListTail;                
            } else {//the heap is empty case
                //make the rootlist point to z if it its the only node
                rootListHead = rootListTail = z;
                min = z;
            }
            return z;
        }
        //insert node into rootlist
        void insertNode(FibHeapNode<keytype> *z){ //used for decrease key
            //update parent/mark
            z->parent = nullptr;
            z->mark = false;
            //add to root list
            rootListSize++;
            if(rootListSize > 1){    
                //link z to the end of the list
                rootListTail->right = z;
                z->left = rootListTail;
                rootListTail = z;
                //link front and back
                rootListTail->right = rootListHead;
                rootListHead->left = rootListTail;
                if(min->key > z->key){
                    min = z;
                }
            } else {
                rootListHead = rootListTail = z;
                min = z;
            }                   
        }
        void merge(FibHeap<keytype> &H2){
            //link right of current tail to head of new heap
            this->rootListTail->right = H2.rootListHead;
            H2.rootListHead->left = this->rootListTail;
            this->rootListTail = H2.rootListTail;
            //link front and back
            this->rootListHead->left = this->rootListTail;
            this->rootListTail->right = this->rootListHead;
            //update helper variables
            this->size = this->size + H2.size;
            this->rootListSize = this->rootListSize + H2.rootListSize;
            if(this->min > H2.min) this->min = H2.min;
            if(this->maxDegree < H2.maxDegree) this->maxDegree = H2.maxDegree;
        }
        //adds x to childlist of y
        void merge(FibHeapNode<keytype> *x, FibHeapNode<keytype> *y){
          //maintains proper root
            rootListSize--;
                //increment degree
                y->degree++;
                //max degree might be useful later
                if(y->degree > maxDegree) maxDegree = y->degree;
                //maintain root head/tail
                if(rootListHead == x) rootListHead = x->right;
                if(rootListTail == x) rootListTail = x->left;
                //unlink from root list
                x->left->right = x->right;
                x->right->left = x->left;
                //no child case
                if(y->child == nullptr){
                    //add child to y
                    y->child = y->childTail = x;
                    x->parent = y;

                } else { //has children
                    //add x left of head
                    y->child->left = x;
                    //update head/tail pointers
                    x->right = y->child;
                    y->child = x;
                    //link head/tail
                    y->child->left = y->childTail;
                    y->childTail->right = y->child;
                    //update parent
                    x->parent = y;
                }
            //fixes head/tail point's connection to each other.
            rootListHead->left = rootListTail;
            rootListTail->right = rootListHead;
        }
        //extracts min element from heap
        keytype extractMin(){
            //reduce sizes
            rootListSize--;
            size--;
            //store min value
            keytype val = min->key;
            if(size == 0){ //edge case
                val = rootListHead->key;
                min = nullptr;
                rootListHead = nullptr;
                rootListTail = nullptr;
                return val;
            } 
            //update head/tail
            if(min == rootListHead) rootListHead = rootListHead->right;
            if(min == rootListTail) rootListTail = rootListTail->left;
            //unlink min
            min->left->right = min->right;
            min->right->left = min->left;
            //link head/tail
            rootListHead->left = rootListTail;
            rootListTail->right = rootListHead;
            //add children to root list
            FibHeapNode<keytype> *current;
            if(min->degree > 0){
                //unmark and set parents equal to nullptr
                current = min->child;
                for(int i = 0; i < min->degree; i++){
                    current->parent = nullptr;
                    current->mark = false;
                    current = current->right;
                }
                //link child list to root list
                if(rootListSize > 0){
                    rootListTail->right = min->child;
                    min->child->left = rootListTail;
                    rootListTail = min->childTail;
                //link rootlist head/tail
                    rootListHead->left = rootListTail;
                    rootListTail->right = rootListHead;
                //update rootlist size
                    rootListSize = rootListSize + min->degree;
                } else {
                    rootListHead = min->child;
                    rootListTail = min->childTail;
                    rootListHead->left = rootListTail;
                    rootListTail->right = rootListHead;
                    rootListSize = min->degree;
                }
            }  
            min = min->right;
            consolidate();
            return val;
        }
        //removes a child and splices it to rootlist
        void cut(FibHeapNode<keytype> *x, FibHeapNode<keytype> *y){
            if(y->degree > 1){
                //update childlist head/tail
                if(x == y->child) y->child = y->child->right;
                if(x == y->childTail) y->childTail = y->childTail->left;
                //remove from child list
                x->right->left = x->left;
                x->left->right = x->right;
                //link childlist head/tail
                y->child->left = y->childTail;
                y->childTail->right = y->child;
                //decrement degree of parent
            } else {
                y->child = y->childTail = nullptr;
            }
            //link to rootlist
            rootListTail->right = x;
            x->left = rootListTail;
            rootListTail = x;
            //link rootlist head/tail
            rootListHead->left = rootListTail;
            rootListTail->right = rootListHead;
            //update information
            rootListSize++;
            y->degree--;
            x->parent = nullptr;
            x->mark = false;
        }
        //cuts upward
        void cascadeCut(FibHeapNode<keytype> *x){
            FibHeapNode<keytype> *z = x->parent;
            if(z != nullptr){
                //mark parent
                if(x->mark == false){
                    x->mark = true;
                } else { //if already marked, cut above
                    cut(x,z);
                    cascadeCut(z);
                }
            }
        }
        //decreases key through handle pointer
        bool decreaseKey(FibHeapNode<keytype> *h, keytype k){
            if(k > h->key) return false; //edge case
            //change key
            h->key = k;
            FibHeapNode<keytype> *y = h->parent;
            //check for heap violations
            if(y!= nullptr && y->key > h->key){
                cut(h,y);
                cascadeCut(y);
            }
            //update min
            if(h->key < min->key){
                min = h;
            }
            return true;
        }
        void consolidate(){
            //edge case protection.
            if(rootListSize == 1 || rootListSize == 0) return;
            //maintains current position when traversing the root list
            FibHeapNode<keytype> *current = rootListHead;
            //holds max size, should be log1.6... but meh...thats extra
            int logsize = (int) log2(size) + 1; 
            //make array to hold degrees
            FibHeapNode<keytype> *degreeList[logsize];
            
            //help variables
            int d; //current degree
            FibHeapNode<keytype> *x; //node from array
            FibHeapNode<keytype> *hold = nullptr; //holder
            //set all places to nullptr
            for(int i = 0; i <= logsize; i++){
                degreeList[i] = nullptr;
            }
            //stores rootlist size
            int num = rootListSize; 
            //iterate through root list
            for(int j = 0; j <= num; j++){
                d = current->degree;
                //merge trees of equal degree
                while(degreeList[d] != nullptr){
                    x = degreeList[d];
                    if(x == current) break; //edge case protection
                    if(current->key > x->key){ //exchange
                        hold = current;
                        current = x;
                        x = hold;
                    }
                    merge(x, current);
                    degreeList[d] = nullptr;
                    d++;
                }
                //add to degree list
                degreeList[d] = current;
                current = current->right;
            }
            //clear rootlist
            min = nullptr;
            rootListHead = nullptr;
            rootListTail = nullptr;
            rootListSize = 0;
            //create new rootlist from degreelist
            for(int i = 0; i < logsize; i++){
                if(degreeList[i] != nullptr){
                    insertNode(degreeList[i]);
                }
            }
        }
        //prints trees in preorder transveral
        void printKey(){
            FibHeapNode<keytype> *current = rootListHead;
            for(int i = 0; i < rootListSize; i++){ //print each tree in rootlist
                cout << "Rank " << current->degree << endl;
                printTree(current);
                current = current->right;
                cout << endl << endl;
            }
        }
        //helper to printkey
        void printTree(FibHeapNode<keytype> *t){
            if(t == nullptr){
                return;
            }
            FibHeapNode<keytype> *current = t->child;
            cout << t->key << " ";//print current node key
            for(int i = 0; i < t->degree; i++){ //recurse on other siblings
                printTree(current);
                current = current->right;
            }
        }
        //returns minimum of the heap.
        keytype peekKey(){
            return min->key;
        }    
};
