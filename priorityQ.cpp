#include <iostream>
#include <ctime>
#include <random>
#include <limits.h>

using namespace std;

clock_t start,finish;

class Heap{
private:
  int size;
  int limit;
  int *array;
  void max_heapify(int index, int *a){
    if(size < 1){
      cout << "Empty heap" << endl;
      return;
    }
    int max = index;
    do{
      index = max;
      int left = index*2;
      int right = left+1;
      if(left <= size && a[left] > a[max]){
        max = left;
      }
      else if(right <= size && a[right] > a[max]){
        max = right;
      }
      if(max != index){
        int temp = a[index];
        a[index] = a[max];
        a[max] = temp;
      }
    }while(max != index);
  }
public:
  Heap(int initial_size){
    limit = initial_size;
    Heap::array = new int[initial_size];
    Heap::size = 0;
  }
  Heap(int *a, int inSize){
    limit = inSize;
    array = new int[inSize];
    array[0]=0;
    for(int i = 0; i < inSize; i++){
      array[i+1] = a[i+1];
    }
    Heap::size = inSize;
    for(int i = size/2; i > 0; i--){
        max_heapify(i,array);
    }
  }
  void printOut(){
    for(int i = 0; i < size; i++){
      cout << array[i+1] << " ";
    }
    cout << endl;
  }
  void insert(int value){
    if(size > 0 and size < limit-1){
      int child = size+1;
      array[child]=value;
      while(child > 1){
        int parent = child/2;
        if(array[child] > array[parent]){
          int temp = array[child];
          array[child] = array[parent];
          array[parent] = temp;
          child = parent;
        }
        else{
          break;
        }
      }
      size++;
    }
    else{
      array[1] = value;
      size++;
    }
  }

  int extract_max(){
    int temp = array[1];
    array[1] = array[size];
    array[size] = '\0';
    max_heapify(1, array);
    size--;
    return temp;
  }

  int get_max(){
    return array[1];
  }

  int get_size(){
    return size;
  }

  bool increase_key(int index, int key){
    if(key < array[index]){
      cout << "Invalid key, must increase" << endl;
      return false;
    }
    array[index] = key;
    int parent = index/2;
    while(index > 1 && array[parent] < array[index]){
      int temp = array[parent];
      array[parent] = array[index];
      array[index] = temp;
      index = parent;
      parent = index/2;
    }
    return true;
  }
};

void worst_case(int size){
  Heap* priority_qW = new Heap(size);
  start = clock();
  uniform_int_distribution<> dis(0,size);
  for(int i = 0; i < size-1; i++){
    priority_qW->insert(i);
  }
  finish = clock();
  cout << "Worst case (insert) - time = " << finish-start << endl;
  start = clock();
  int max = priority_qW->extract_max();
  finish = clock();
  cout << "Get max: " << max  << "- time = " << finish - start << endl;
  free(priority_qW);
}

void average_case(int size){
  Heap* priority_qA = new Heap(size);
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(0,size);
  start = clock();
  for(int i = 0; i < size-1; i++){
    priority_qA->insert(dis(gen));
  }
  finish = clock();
  cout << "Average case (insert) - time = " << finish-start << endl;
  start = clock();
  int max = priority_qA->extract_max();
  finish = clock();
  cout << "Get max: " << max  << "- time = " << finish - start << endl;
  free(priority_qA);
}

void best_case(int size){
  Heap* priority_qB = new Heap(size);
  start = clock();
  for(int i = size-1; i > 0; i--){
    priority_qB->insert(i);
  }
  finish = clock();
  cout << "Best case (insert) - time = " << finish-start << endl;
  start = clock();
  int max = priority_qB->extract_max();
  finish = clock();
  cout << "Get max: " << max  << "- time = " << finish - start << endl;
  free(priority_qB);
}

int main(){
  int test_size;
  cout << "Enter size: ";
  cin >> test_size;
  average_case(test_size);
  cout << "---------------------------------------------------------------------" << endl;
  worst_case(test_size);
  cout << "---------------------------------------------------------------------" << endl;
  best_case(test_size);
  return 0;
}
