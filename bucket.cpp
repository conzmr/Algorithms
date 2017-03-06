#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <random>
#include <limits.h>

using namespace std;

void bucket_sort(float a[], int size){
  vector< vector<float> > buckets(size);
  for(int i = 0; i < size; i++){
    buckets.push_back(vector<float>());
  }
  for(int i = 0; i < size; i++){
    int bucket = floor(a[i]*size);
    buckets.at(bucket).push_back(a[i]);
  }
  for(int i = 0; i < size; i++){
    //Insertion Sort
    for(int j = 1; j < buckets.at(i).size(); j++){
      float key = buckets.at(i).at(j);
      int h = j-1;
      while(h >= 0 && buckets[i][h] > key){
        buckets.at(i).at(h+1) = buckets.at(i).at(h);
        h--;
      }
      buckets.at(i).at(h+1) = key;
    }
  }
  int index = 0;
  for(int i = 0; i < size; i++){
    for(int j = 0; j < buckets.at(i).size(); j++){
      a[index++] = buckets.at(i).at(j);
    }
  }
}

void worst_case(int size){
  clock_t start,end;

  float array[size];

  random_device rd;
  mt19937 gen(rd());
  uniform_real_distribution<> dis(0,0.001);
  for(int i = 0; i < size; i++){
    array[i] = dis(gen);
  }
  start = clock();
  bucket_sort(array, size);
  end = clock();
  cout << "Worst case - time = " << end-start << endl;
}

void best_case(int size){
  clock_t start,end;

  float array[size];

  random_device rd;
  mt19937 gen(rd());
  uniform_real_distribution<> dis(0,1);
  for(int i = 0; i < size; i++){
    array[i] = dis(gen);
  }
  start = clock();
  bucket_sort(array, size);
  end = clock();
  cout << "Best case - time = " << end-start << endl;
}

void average_case(int size){
  clock_t start,end;
  float array[size];
  random_device rd;
  mt19937 gen(rd());
  uniform_real_distribution<> dis(0,1);
  for(int i = 0; i < size; i++){
    array[i] = dis(gen);
  }
  start = clock();
  bucket_sort(array, size);
  end = clock();
  cout << "Average case - time = " << end-start << endl;
}

int main(){
  int test_size;

  cout << "Enter size of test: " << endl;
  cin >> test_size;

  best_case(test_size);
  average_case(test_size);
  worst_case(test_size);
}
