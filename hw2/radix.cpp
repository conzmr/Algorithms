#include <iostream>
#include <ctime>
#include <random>
#include <limits.h>
#include <list>

using namespace std;

void arraycopy(int *A, int *B, int size){
  for(int i = 0; i < size; i++){
    B[i] = A[i];
  }
}

void countingsort(int *A, int *B, int k, int size){
  int C[k+1];
  //Initialize the helping array C.
  for(int i = 0; i <= k; i++){
    C[i] = 0;
  }
  //C[A[i]]: How many elements of A[i] are in A.
  for(int i = 0; i < size; i++){
    C[A[i]]++;
  }
  //C[i] contains the number of elements less than or equal to i in A.
  for(int i = 1; i <= k; i++){
    C[i] = C[i]+C[i-1];
  }
  for(int i = size-1; i >= 0; i--){
    B[C[A[i]]-1] = A[i];
    C[A[i]] = C[A[i]] - 1;
  }
}

void countingsortRadix(int *A, int *B, int k, int size, int power){
  int C[k+1];
  //Initialize the helping array C.
  for(int i = 0; i <= k; i++){
    C[i] = 0;
  }
  //C[A[i]]: How many elements of A[i] are in A.
  for(int i = 0; i < size; i++){
    C[(A[i]/power)%10]++;
  }
  //C[i] contains the number of elements less than or equal to i in A.
  for(int i = 1; i <= k; i++){
    C[i] = C[i]+C[i-1];
  }
  for(int i = size-1; i >= 0; i--){
    B[C[((A[i]/power)%10)]-1] = A[i];
    C[(A[i]/power)%10] = C[(A[i]/power)%10] - 1;
  }
}

void radixsort(int *A, int k, int size){
  //Sort k-digit based numbers.
  int B[size];
  int power = 1;
  for(int i = 0; i < k; i++){
    //Use a stable sort to sort array A on digit i.
    for(int i = 0; i < size; i++){
      B[i] = '\0';
    }
    countingsortRadix(A, B, 10, size, power);
    arraycopy(B, A, size);
    power*=10;
  }
}

void radixQueue(int *A, int k, int size){
  int B[size];
  int power = 1;
  int index;
  list<int> queues[10];
  for(int i = 0; i < 10; i++){
    queues[i] = list<int>();
  }
  for(int i = 0; i < k; i++){
    for(int j = 0; j < size; j++){
      queues[(A[j]/power)%10].push_back(A[j]);
    }
    index = 0;
    for(int j = 0; j < 10; j++){
      while(!queues[j].empty()){
        A[index++] = queues[j].front();
        queues[j].pop_front();
      }
    }
    power*=10;
  }
}

void worst_case(int size){
  clock_t start,end;

  int array[size];

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(1,1000);
  for(int i = 0; i < size; i++){
    array[i] = dis(gen);
  }
  start = clock();
  radixQueue(array, 4, size);
  end = clock();
  cout << "Worst case - time = " << end-start << endl;
  for(int i = 0; i < size; i++){
    array[i] = dis(gen);
  }
}

void best_case(int size){
  clock_t start,end;

  int array[size];

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(10,99);
  for(int i = 0; i < size; i++){
    array[i] = dis(gen);
  }
  start = clock();
  radixQueue(array, 2, size);
  end = clock();
  cout << "Best case - time = " << end-start << endl;
  for(int i = 0; i < size; i++){
    array[i] = dis(gen);
  }
}

void average_case(int size){
  clock_t start,end;

  int array[size];

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(1,100);
  for(int i = 0; i < size; i++){
    array[i] = dis(gen);
  }
  start = clock();
  radixQueue(array, 3, size);
  end = clock();
  cout << "Average case - time = " << end-start << endl;
  for(int i = 0; i < size; i++){
    array[i] = dis(gen);
  }
}

int main(){
  int size;
  cout << "Enter size of test: ";
  cin >> size;
  best_case(size);
  average_case(size);
  worst_case(size);

  return 0;
}
