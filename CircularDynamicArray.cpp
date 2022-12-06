//Nicholas Warren
//Data Structures and Algorithms
//Project Phase 1
//12164563

#include<iostream>
#include <cstdlib>
using namespace std;

template <class elmtype>
class CircularDynamicArray{ //Classinator
   public:
        elmtype* arr;
        elmtype error;
        elmtype* hold;
        int frontidx,size,cap;
CircularDynamicArray(){  // Contructinator
   cap= 2;
   size = 0;
   frontidx = 0;
   arr= new elmtype[cap];
}

CircularDynamicArray(int s){ //Contructer with input size-inator
  cap= s;
  size = s;
  frontidx = 0;
  arr = new elmtype[cap];
}
~CircularDynamicArray(){//destroyinator
    delete[] arr;
}
CircularDynamicArray(CircularDynamicArray &arr2){ //copy constructorinator
	cap = arr2.cap;
	size = arr2.size;
	frontidx = arr2.frontidx;
	arr = new elmtype[cap];
	for(int i = 0; i < size; i++){
		 arr[(frontidx+i)%cap] = arr2.arr[(frontidx+i)%cap];
	}
}

CircularDynamicArray& operator=(CircularDynamicArray arr2){ //copy assignment operatorinator
	delete[] arr;
	frontidx = arr2.frontidx;
    cap = arr2.cap;
	size = arr2.size;
	arr = new elmtype[cap];
	for(int i = 0; i < size; i++){
	 	arr[(frontidx+i)%cap] = arr2.arr[(frontidx+i)%cap];
	}
	return *this;
}
int length(){ //get lengthinator
    return size;
}
int capacity(){//get capacityinator
    return cap;
}
void clear(){//clearinator
    delete[] arr;
    cap= 2;
    size = 0;
    frontidx = 0;
    arr = new elmtype[cap];
}
elmtype& operator[](int i){ //gives return when arr[i] is used
if(i > size-1 || i < 0){
    return error;
} else { 
    return arr[(frontidx+i)%cap]; //special math to adjust for circularity
}
}
void addEnd(elmtype v){ // Add to the back
size++;
if(size > cap){
	cap = cap*2; //doubles the capacity
	hold = new elmtype[cap]; //creates auxillary array
	for(int i = 0; i < size-1; i++){
		 hold[i] = arr[(frontidx+i)%(cap/2)]; //copies the original array to the aux array and puts it in order.
	}
	hold[size-1] = v; //inserts new element at end
	delete[] arr;
	arr = new elmtype[cap];
	for(int i = 0; i < size; i++) {
		arr[i] = hold[i]; //copies hold array back over
	}
	delete[] hold;
    frontidx = 0;
} else {
    arr[(frontidx+size-1)%cap] = v;
}
}
void addFront(elmtype v){ //Add to the front
    size++;
    if(size > cap){
        cap = cap*2;
	    hold = new elmtype[cap];
        hold[0] = v;
        for(int i = 0; i < size-1; i++){
            hold[i+1] = arr[(frontidx+i)%(cap/2)];
        }
        delete[] arr;
        arr = new elmtype[cap];
        for(int i = 0; i < size; i++) {
            arr[i] = hold[i];
        }
        frontidx = 0;
        delete[] hold;
    } else {
      frontidx = frontidx - 1;
      if(frontidx < 0){
         frontidx = cap-1;
      }
      arr[frontidx] = v;
    }
}
void delEnd(){ //Deletes the end of the array
    size--;
    if(size <= cap/4){
        cap = cap/2;
        hold = new elmtype[cap];
        for(int i = 0; i < size; i++){
            hold[i] = arr[(frontidx+i)%(cap*2)];
        }
        delete[] arr;
        arr = new elmtype[cap];
        for(int i = 0; i < size; i++){
            arr[i] = hold[i];
        }
        delete[] hold;
        frontidx = 0;
    }
}
void delFront(){ //deletes front of the array
    size--;
    frontidx = (frontidx+1)%cap;
    if(size <= cap/4){
        cap=cap/2;
        hold = new elmtype[cap];
        for(int i = frontidx+1; i < size; i++){
            hold[i] = arr[(frontidx+i)%(cap*2)];
        }
        delete[] arr;
        arr = new elmtype[cap];
        for(int i = frontidx+1; i < size; i++){
            arr[i] = hold[i];
        }
        frontidx = 0;
        delete[] hold;
   } 
}
void uncircle(){ //Unrolls the Array to help with sorting
    hold = new elmtype[cap];
    for(int i = 0; i < size; i++){
        hold[i] = arr[(frontidx+i)%cap];
    }
    for(int i = 0; i < size; i++){
        arr[i] = hold[i];
    }
    frontidx = 0;
    delete[] hold;
}
elmtype QuickSelect(int k){ //this is only here to pass QuickSelect with one parameter
    if(size > 1 && k > 0 && k <= size){ //error catcher
        hold = new elmtype[cap]; //temp array so main array doesnt change.
        for(int i = 0; i < size; i++){
            hold[i] = arr[(frontidx+i)%cap];
        }
        return QSRecursive(hold,0, size-1, k);
        delete[] hold;
    } else if (size == 0 || k == 0 || k > size){ //error catcher
        return -1;
    } else { //if array is of size 1
    return arr[0];
    }
}
elmtype QSRecursive(elmtype array[], int left, int right, int k){ //recursion  
    if(right == left){
         return array[left];
    }
    int idx = Partition(array,left, right);
    if(idx-left == k-1){
        return array[idx];
    } else if(idx - left > k - 1){
        return QSRecursive(array,left, idx - 1, k);
     } else {
          return QSRecursive(array,idx+1,right,k-idx+left-1);
     }
}

int Partition(elmtype array[],int left, int right){ //divides the array in the best way
    int randidx = left + rand()%(right - left);
    swap(array[randidx], array[right]);
    
    elmtype pivot = array[right];

    int i = left;
    for(int j = left; j < right;j++){
        if(array[j] < pivot){
            swap(array[i], array[j]);
            i++;
        }
    }
    swap(array[i], array[right]);
    return i;
}
/*int WCPartition(elmtype array[],int left, int right, elmtype pivot){ //attempted fix didnt work
    int i = left;
    for(int j = left; j < right;j++){
        if(array[j] < pivot){
            swap(array[i], array[j]);
            i++;
        }
    }
    swap(array[i], array[right]);
    return i;
}*/
elmtype WCSelect(int k){ 
    if(size > 1 && k > 0 && k <= size){ //error catcher
        hold = new elmtype[cap]; //temp array so main array doesnt change.
        for(int i = 0; i < size; i++){
            hold[i] = arr[(frontidx+i)%cap];
         }
        return QSRecursive(hold,0, size-1, k); //I gave it my best but WC was too powerful ;-;
    } else if (size == 0 || k == 0 || k > size){
        return -1;
    } else {
        return arr[0];
    }
}
/*elmtype WCRecurive(elmtype array[],int left, int right, int k){ 
        int n = right - left + 1;
        int i,medOfMeds;
        elmtype med[(size+4)/5]; //Stores medians
        //Divides Array into 5 groups and finds the median
        for(i = 0; i <n/5; i++){
            med[i] = findMed(array + left + i*5, 5);
        }
        //Does the same as above but for the rest of the array
        if(i*5 < n){
            med[i] = findMed(array + left + i*5, n%5);
        }
        
        if(i != 1){
            WCRecurive(med,0,i-1,i/2);
        } else {
            medOfMeds = med[i-1];
        }
        int idx = WCPartition(array,left,right,medOfMeds);
        if(idx - left == k - 1){
            return array[idx];
        } else if(idx-left > k-1){
            return WCRecurive(array, left, idx-1, k);
        } else {
            return WCRecurive(array, idx +1, right, k-idx+left-1);
        }
}
elmtype findMed(elmtype array[], int s){ //I know this part worked
    //insertion sort
    int i, j;
    elmtype k;
    for(i = 1; i < s; i++){
        k = array[i];
        j = i - 1;

        while(j >= 0 && arr[j] > k){
            array[j+1] = array[j];
            j--;
        }
        array[j + 1] = k;
    }
    return array[s / 2]; //returns the center element(median) of sorted array
}*/

void stableSort(){ //sort call
    if(size > 1){
    uncircle();
    mergeSort(0,(size-1)/2);
    mergeSort((size-1)/2+1,size-1);
    merge(0,size-1);
    } else {
        return;
    }
}
void mergeSort(int l, int r){ //sort recursion
    if(l < r){
        int mid = l + (r - l) / 2;
        mergeSort(l,mid);
        mergeSort(mid+1, r);
        merge(l,r);
    } else {
        return;
    }
}
void merge(int l, int r){ //merges the arrays into a sorted array
        int mid = (l + r)/2;
        int n1 = mid - l + 1;
        int n2 = r - mid;

        elmtype L[n1], R[n2]; //Creation of sub arrays

        for(int i = 0; i < n1; i++){
            L[i] = arr[l + i];
        }
        for(int j = 0; j < n2; j++){
            R[j] = arr[mid + 1 + j];
        }
        int i,j,k; //current index of sub-arrays and main array
        i = 0;
        j = 0;
        k = l;
        while(i < n1 && j < n2){ //sorts through the sub arrays and places the correct item in the main array
            if(L[i] <= R[j]){
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }
        //Sorts through remaining elements
        while (i < n1){
            arr[k] = L[i];
            i++;
            k++;
        }
        while (j < n2){
            arr[k] = R[j];
            j++;
            k++;
        }
    }
int linearSearch(elmtype e){ //Searches one by one.
    for(int i = 0; i < size; i++){
        if(arr[i] == e){
            return i;
        }
    }
    return -1;
}
int binSearch(elmtype e){ //created to pass binsearch with one parameter
   return BinRecurse(e, 0, size-1);
}
int BinRecurse(elmtype e, int l, int r){ //Searches one by one-half
    if(l > r){
        return -1;
    } else {
        int mid = (l + r)/2;
        if(arr[mid] == e){
            return mid;
        } else if (arr[mid] > e){
            return BinRecurse(e,l, mid - 1);
        } else {
            return BinRecurse(e, mid + 1, r);
        }
    }
}
};


