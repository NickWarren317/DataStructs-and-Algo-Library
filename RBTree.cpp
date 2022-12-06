/*
    Nicholas Warren
    12164563
    CS201
    Phase2 Resubmit
*/
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;
template <typename keytype, typename valuetype>
    class RBNode{
        public:
            RBNode<keytype, valuetype> *left,*right,*parent; //adjacent pointers
            keytype key; //key of the node
            valuetype val; //value of the node
            bool red; //is the node red
            int siz; //number of nodes below

        RBNode(keytype k, valuetype v){
            this->right = this->left = this->parent = nullptr;
            this->key = k;
            this->val =v;
            this->siz = 0;
            this->red = true;
        }
        RBNode(){
            this->right = this->left = this->parent = nullptr;
            this->red = true;
            this->siz = 0;
        }
};
template <typename keytype, typename valuetype>
class RBTree{
    public:
        RBNode<keytype, valuetype>* root; //pointer to the root of the list
        RBNode<keytype, valuetype>* nil; //filler node for null
        int s;//size of the tree
    RBTree(){
        s = 0;
        nil = new RBNode<keytype,valuetype>;
        root = new RBNode<keytype,valuetype>;
        nil->red = false;
        root->red = false;
        root->parent = nil;
        root = nil;
    }
    RBTree(vector<keytype> k, vector<valuetype> v, int s){
        nil = new RBNode<keytype,valuetype>;
        root = new RBNode<keytype,valuetype>;
        nil->red = false;
        root->red = false;
        root = nil;
        for(int i = 0; i < s; i++){
            insert(k.pop_back(i), v.pop_back(i));
        }
    }
    RBTree(keytype k[], valuetype v[], int s){
        nil = new RBNode<keytype,valuetype>;
        root = new RBNode<keytype,valuetype>;
        nil->red = false;
        root->red = false;
        root = nil;
        for(int i = 0; i < s; i++){
            insert(k[i], v[i]);
        }
    }
    //copy constructor
    RBTree(const RBTree &old){
        this->nil = new RBNode<keytype, valuetype>();
        this->nil->siz = 0;
        this->root = this->nil;
        this->root = Ncopy(old.root,this->nil,this->nil);
        this->s = old.s;
    }
    //copy helper function
    RBNode<keytype, valuetype> *Ncopy(RBNode<keytype, valuetype> *x, RBNode<keytype, valuetype> *newNil, RBNode<keytype, valuetype> *newparent){
        if(x->siz == 0){
            return newNil;
        } 
        //copies node
        RBNode<keytype, valuetype> *copy = new RBNode<keytype,valuetype>;
        copy->red = x->red;
        copy->siz = x->siz;
        copy->key = x->key;
        copy->val = x->val;
        copy->parent = newparent;
        //recurse on other nodes
        copy->left = Ncopy(x->left, newNil, copy);
        copy->right = Ncopy(x->right, newNil, copy);
        return copy;
    }
    //destructor
    ~RBTree(){
        postOrderDelete(root);
    }
    void postOrderDelete(RBNode<keytype, valuetype> *x){ //deletes in postorder transversal
        if(x == nil){
            return;
        }
        postOrderDelete(x->left);
        postOrderDelete(x->right);
        delete x;
    }
    //inserts an element into the tree
    void insert(keytype k, valuetype v){
        this->s++; //increase size
        RBNode<keytype, valuetype> *y = this->nil; //holder variable
        RBNode<keytype, valuetype> *x = this->root; //holder variable
        RBNode<keytype, valuetype> *z = new RBNode<keytype,valuetype>(k,v); //Node to be inserted
        nil->red = false;
        z->left = this->nil;
        z->right = this->nil;
        z->red = true;
        while(x != nil){ //finds where it should go
            y = x;
            x->siz++;
            if(z->key < x->key){
                x = x->left;
            } else {
                x = x->right;
            }
        }
        z->parent = y;
        if(y == nil){ //tree is empty
            z->siz++;
            root = z;
        } else if(z->key < y->key){ // if smaller than y, put it in the left
            z->siz++;
            y->left = z;

        } else { //if greater, put it right
            z->siz++;
            y->right = z;

        }
        fixup(z);
    }
    void fixup(RBNode<keytype,valuetype> *z){
       RBNode<keytype,valuetype> *y = new RBNode<keytype, valuetype>;
       while(z->parent->red == true){ //while the parent is red
            if(z->parent == z->parent->parent->left){ //is current node a left child?
              y = z->parent->parent->right;  
                if((y->red == true) && (y != nil)){ //if uncle is red, can only happen if it doesnt equal nil
                    //case 1 recolor
                    z->parent->red = false;
                    y->red = false;
                    z->parent->parent->red = true;
                    z = z->parent->parent;
                } else { 
                    if(z == z->parent->right){ //if z is a right child
                        //case 2
                        z = z->parent;
                        leftRotate(z);
                    }
                        //case 3
                        z->parent->red = false;
                        z->parent->parent->red = true;
                        rightRotate(z->parent->parent);
                }
            } else { //is current node a right child?
                y = z->parent->parent->left; 
                if((y->red == true) && (y != nil)){ //if uncle is red, can only happen if it doesnt equal nil
                    //case 1 recolor
                    z->parent->red = false;
                    y->red = false;
                    z->parent->parent->red = true;
                    z = z->parent->parent;
                } else { 
                    if(z == z->parent->left){
                       //case 2 right rotate if left grand child
                        z = z->parent;
                        rightRotate(z);
                    }
                    //case 3 left rotate if right grandchild
                    z->parent->red = false;
                    z->parent->parent->red = true;
                    leftRotate(z->parent->parent);
                }
            }
            if(z == root){
                break;
            }
        }
        root->red = false;
    }
    void RBTransplant(RBNode<keytype, valuetype> *u,RBNode<keytype, valuetype> *v){ //replaces u with v
        if(u->parent == nil){ // does u have a parent?
            root = v; //if not then v becomes the root
        } else if(u == u->parent->left){ // is u a left child?
            u->parent->left = v; //replace left with v
        } else { // is u a right child?
            u->parent->right = v; //replace right with v
        }
        v->parent = u->parent; 
    }
    RBNode<keytype,valuetype> *searchNodeDel(keytype k){ //finds the node based on key
        RBNode<keytype,valuetype> *y = new RBNode<keytype, valuetype>;
        if(root->key == k){
            root->siz--;
            return root;
        }
        y = root;
        while(y->key != k){ 
            y->siz--;
            if(y->key > k){
                y = y->left;
            } else if(y->key < k){
                y = y->right;
            }
            if(y == nil){
                y->siz--;
                break;
            }
        }
        if(y == nil){
            return NULL;
        } else {
            return y;
        }
    }
    int remove(keytype k){
        this->s--;       
        RBNode<keytype,valuetype> *x = new RBNode<keytype, valuetype>; //holder variables
        RBNode<keytype,valuetype> *y = new RBNode<keytype, valuetype>;
        RBNode<keytype,valuetype> *z = new RBNode<keytype, valuetype>; //variable to be deleted
        RBNode<keytype,valuetype> *temp = new RBNode<keytype, valuetype>;
        z = searchNode(k); //find the node to delete
        if(z == NULL){ //didnt find the node
            return 0;
        }
        this->root->siz--;
        y = z;
        bool OGYcolor = y->red;
        if(z->left == nil){ //if z only has right child
            x = z->right;
            decrement(z);
            RBTransplant(z,z->right);
        } else if(z->right == nil){ //if z only has left child
            x = z->left;
            decrement(z);
            RBTransplant(z,z->left);
        } else { //if z has both left and right children
            y = getMax(z->left); // y is predecessor
            decrement(y);
            OGYcolor = y->red; //original y color is saved
            x = y->right;
            if(y->parent == z){
                x->parent = y;
            } else {
                RBTransplant(y,y->left);
                y->left = z->left;
                y->left->parent = y;
            }
            y->siz = z->siz;
            RBTransplant(z,y);
            y->right = z->right;
            y->right->parent = y;
            y->red = z->red;
        }
        if(OGYcolor == false){
            deleteFixUp(x);
        }
        return 1;
    }
    void decrement(RBNode<keytype, valuetype> *start){
        RBNode<keytype, valuetype> *x = start;
        while(x->parent != this->nil || x != this->root){
            x->siz--;
            x = x->parent;
        }
    }
    void deleteFixUp(RBNode<keytype, valuetype>* x){
        RBNode<keytype,valuetype> *w = new RBNode<keytype, valuetype>;
        while((x != root) && (x->red == false)){
            if(x == x->parent->left){
                w = x->parent->right;
                if(w->red == true){
                    //case1
                    w->red = false;
                    x->parent->red = true;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if((w->left->red == false) && (w->right->red == false)) {
                    //case 2
                    w->red = true;
                    x = x->parent;
                } else{
                    if (w->right->red == false) {
                    //case 3
                    w->left->red = false;
                    w->red = true;
                    rightRotate(w);
                    w = x->parent->right;
                    }
                    //case 4
                    w->red = x->parent->red;
                    x->parent->red = false;
                    w->right->red = false;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                w = x->parent->left;
                if(w->red == true){
                    //case 1
                    w->red = false;
                    x->parent->red = true;
                    rightRotate(x->parent);
                    w = x->parent->left;
                } else if((w->right->red == false) && (w->left->red == false)) {
                    //case 2
                    w->red = true;
                    x = x->parent;
                } else {
                    if(w->left->red == false){
                    //case 3
                    w->right->red = false;
                    w->red = true;
                    leftRotate(w);
                    w = x->parent->left;
                    }
                    //case 4
                    w->red = x->parent->red;
                    x->parent->red = false;
                    w->left->red = false;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->red = false;
    }
    void printk(int k){
        int count = 0;
        inOrderK(root,k, count);
        cout << endl;
    }
    void inOrderK(RBNode<keytype, valuetype> *x,int k, int &count){ //print inorder transveral
        if(count > k){
            return;
        }
        if(x == nil){
            return;
        }
        inOrderK(x->left,k, count);
        count++;
        if(count > k){
            return;
        }
        cout << x->key << " ";
        inOrderK(x->right,k, count);
    }
    RBNode<keytype, valuetype>* getMax(RBNode<keytype, valuetype> *x){ //gets max value in subtree
        while(x->right != nil){
            x = x->right;
        }
        return x;
    }
    RBNode<keytype, valuetype>* getMin(RBNode<keytype, valuetype> *x){ //gets min value in subtree
        while(x->left != nil){
            x = x->left;
        }
        return x;
    }
    RBNode<keytype, valuetype>* getPredecessor(RBNode<keytype, valuetype> *x){
        if(x->left != nil){
            return getMax(x->left);
        }
        RBNode<keytype,valuetype> *y = new RBNode<keytype, valuetype>;
        y = x->parent;
        while((y != nil) && (x == y->left)){
            x = y;
            y = y->parent;
        }
        return y;
    }
    RBNode<keytype, valuetype>* getSuccessor(RBNode<keytype, valuetype> *x){
        if(x->right != nil){
            return getMin(x->right);
        }
        RBNode<keytype,valuetype> *y = new RBNode<keytype, valuetype>;
        y = x->parent;
        while((y != nil) && (x == y->right)){
            x = y;
            y = y->parent;
        }
        return y;
    }
    void printHelper(RBNode<keytype,valuetype> *root, string indent, bool last) { //helper function to print the tree. Source: programiz.com
    if (root != nil) {
      cout << indent;
      if (last) {
        cout << "R----";
        indent += "   ";
      } else {
        cout << "L----";
        indent += "|  ";
      }

      string sColor = root->red ? "RED" : "BLACK";
      cout << root->key << "(" << sColor << ")" << '['<<root->siz << ']'<< endl;
      printHelper(root->left, indent, false);
      printHelper(root->right, indent, true);
        }
    } 
    void leftRotate(RBNode<keytype, valuetype>* x){ //rotates left
        RBNode<keytype, valuetype> *y;
        y = x->right;
        x->right = y->left;
        if(y->left != nil){
            y->left->parent = x;
        }
        y->parent = x->parent;
        if(x->parent == nil){
            this->root = y;
        } else if(x == x->parent->left){
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
        y->siz = x->siz;
        x->siz = x->left->siz + x->right->siz + 1;
    }
    void rightRotate(RBNode<keytype, valuetype>* x){ //rotates right
        RBNode<keytype, valuetype> *y;
        y = x->left;
        x->left = y->right;
        if(y->right != nil){
            y->right->parent = x;
        }
        y->parent = x->parent;
        if(x->parent == nil){
            root = y;
        } else if(x == x->parent->right){
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
        y->siz = x->siz;
        x->siz = x->left->siz + x->right->siz + 1;
        return;
    }
    RBNode<keytype,valuetype> *searchNode(keytype k){ //finds the node based on key
        RBNode<keytype,valuetype> *y = new RBNode<keytype, valuetype>;
        if(root->key == k){
            return root;
        }
        y = root;
        while(y->key != k){ 
            if(y->key > k){
                y = y->left;
            } else if(y->key < k){
                y = y->right;
            }
            if(y == nil){
                break;
            }
        }
        if(y == nil){
            return NULL;
        } else {
            return y;
        }
    }
    keytype *successor(keytype k){
        RBNode<keytype, valuetype> *x = getSuccessor(searchNode(k));
        if(x == nil){
            return NULL;
        }
        return &(x->key);
    }
    keytype *predecessor(keytype k){
        RBNode<keytype, valuetype> *x = getPredecessor(searchNode(k));
        if(x == nil){
            return NULL;
        }
        return &(x->key);
    }
    keytype select(int pos){
      RBNode<keytype,valuetype> *currentNode = this->root;
      while(pos > 0){
        if(currentNode->left->siz + 1 > pos){
                currentNode = currentNode->left;
        } else if(currentNode->left->siz + 1 < pos){
                pos = pos - currentNode->left->siz -1;
                currentNode = currentNode->right;
        } else if(currentNode->left->siz + 1 == pos){
            break;
        }
      }
      return currentNode->key;
    }
    valuetype *search(keytype k){ //finds the value of the node based on key
        RBNode<keytype,valuetype> *y = new RBNode<keytype, valuetype>;
        y = root;
        if(root->key == k){
            return &(root->val);
        }
        while((y->key != k) && (y!=nil)){ 
            if(y->key > k){
                y = y->left;
            } else {
                y = y->right;
            }
        }
        if(y == root){
            return NULL;
        } else {
            return &(y->val);
        }
    }
    void inorder(){ //passes inorder with no parameters
        inOrder(root);
        cout << endl;
    }
    void preorder(){ //passes preorder with no parameters
        preOrder(root);
        cout << endl;
    }
    void postorder(){ //passes post order with no parameters
        postOrder(root);
        cout << endl;
    }
    void inOrder(RBNode<keytype, valuetype> *x){ //print inorder transveral
        if(x == nil){
            return;
        }
        inOrder(x->left);
        cout << x->key << " ";
        inOrder(x->right);
    }
    void preOrder(RBNode<keytype, valuetype> *x){ //print preorder transversal
        if(x == nil){
            return;
        }
        cout << x->key << " ";
        preOrder(x->left);
        preOrder(x->right);
    }
    void postOrder(RBNode<keytype, valuetype> *x){ //print postorder transversal
        if(x == nil){
            return;
        }
        postOrder(x->left);
        postOrder(x->right);
        cout << x->key << " ";
    }
    int size(){
        return s;
    }
    int rank(keytype k){
        RBNode<keytype, valuetype> *z = searchNode(k);
        RBNode<keytype, valuetype> *y;
        if(z == NULL){
            return 0;
        }
        int r = z->left->siz + 1;
        y = z;
        while(y != root){
            if(y == y->parent->right){
                r = r + y->parent->left->siz + 1;
            }
            y = y->parent;
        }
        return r;
    }
};
