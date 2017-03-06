#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <random>
#include <limits.h>
#include <string>
#include <bitset>

using namespace std;

clock_t start, finish;

struct node{
  int key;
  int value;
};

class HashTable{
private:
  vector<struct node> *table;
  double A;
  int n;
  int m;
  int **r_matrix;
  int b;
public:
  HashTable(int buckets){
    table = new vector<struct node>[buckets];
    for(int i = 0; i < buckets; i++){
      table[i] = vector<struct node>();
    }
    HashTable::m = buckets;
    HashTable::n = 0;
    HashTable::A = (sqrt(5)-1.0)/2.0;
    HashTable::b = log(m);


    r_matrix = new int*[b];
    for(int i = 0; i < b; ++i){
      r_matrix[i] = new int[16];
    }
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 1);
    for ( int i = 0; i < b; i++ ) {
      for ( int j = 0; j < 16; j++) {
        r_matrix[i][j] = dis(gen);
      }
    }
  }
  int product ( int row, int v ) {
    int i = row & v;
    i = i - ( ( i >> 1 ) & 0x55555555 );
    i = ( ( i & 0x33333333 ) + ( ( i >> 2 ) & 0x33333333) );
    i = ( ( ( i + ( i >> 4 ) ) & 0x0F0F0F0F ) * 0x01010101 ) >> 24;
    return i & 0x00000001;
}

  int hash_matrix(int key){
    string hash_bits;
    string row;
    int result;
    for ( int i = 0; i < b; i++ ) {
      for ( int j = 0; j < 16; j++) {
        row += to_string( r_matrix[i][j] );
      }
      bitset<16> bits( row );
      int rowInt = bits.to_ulong();
      hash_bits += to_string( product( rowInt, key ) );
      row = "";
    }
    bitset<16> bit_r(hash_bits);
    result = bit_r.to_ulong();
    return result;
  }
  void insert_matrix(int key, int value){
    struct node node;
    node.key = key;
    node.value = value;
    int h = hash_matrix(node.key);
    table[h].push_back(node);
  }
  int search_matrix(int key){
    int value = '\0';
    int h = hash_matrix(key);
    for(int i = 0; i < table[h].size(); i++){
      if(table[h].at(i).key == key){
        value = table[h].at(i).value;
        cout << "Successful search ";
        return value;
      }
    }
    cout << "Unsuccessful search ";
    return value;
  }
  int delete_matrix(int key){
    int value = '\0';
    int h = hash_matrix(key);
    for(int i = 0; i < table[h].size(); i++){
      if(table[h].at(i).key == key){
        value = table[h].at(i).value;
        table[h].erase(table[h].begin()+i);
        return value;
      }
    }
    cout << "No such element" << endl;
    return value;
  }

  int hash_division(int key){
    return key%m;
  }
  void insert_division(int key, int value){
    struct node node;
    node.key = key;
    node.value = value;
    int h = hash_division(node.key);
    table[h].push_back(node);
  }
  int search_division(int key){
    int value = '\0';
    int h = hash_division(key);
    for(int i = 0; i < table[h].size(); i++){
      if(table[h].at(i).key == key){
        value = table[h].at(i).value;
        cout << "Successful search ";
        return value;
      }
    }
    cout << "Unsuccessful search ";
    return value;
  }
  int delete_division(int key){
    int value = '\0';
    int h = hash_division(key);
    for(int i = 0; i < table[h].size(); i++){
      if(table[h].at(i).key == key){
        value = table[h].at(i).value;
        table[h].erase(table[h].begin()+i);
        return value;
      }
    }
    cout << "No such element" << endl;
    return value;
  }
  int hash_multiplication(int key){
    return floor(m*(fmod(key*A,1)));
  }
  void insert_multiplication(int key, int value){
    struct node node;
    node.key = key;
    node.value = value;
    int h = hash_multiplication(node.key);
    table[h].push_back(node);
  }
  int search_multiplication(int key){
    int value = '\0';
    int h = hash_multiplication(key);
    for(int i = 0; i < table[h].size(); i++){
      if(table[h].at(i).key == key){
        value = table[h].at(i).value;
        cout << "Successful search ";
        return value;
      }
    }
    cout << "Unsuccessful search ";
    return value;
  }
  int delete_multiplication(int key){
    int value = '\0';
    int h = hash_multiplication(key);
    for(int i = 0; i < table[h].size(); i++){
      if(table[h].at(i).key == key){
        value = table[h].at(i).value;
        table[h].erase(table[h].begin()+i);
        return value;
      }
    }
    cout << "No such element" << endl;
    return value;
  }
};

void division_test(int m, int n){
  cout << "-------------------------------" << endl;
  cout << "Division Method" << endl;
  HashTable* di = new HashTable(m);

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(1,100);
  int key;
  for(int i = 0; i < n; i++){
    key = dis(gen);
    di->insert_division(key, key);
  }
  for(int i = 0; i < 100; i++){
    int value=dis(gen);
    start = clock();
    cout << di->search_division(value) << " ";
    finish = clock();
    cout << "Time for search = " << finish-start << endl;
  }

  free(di);
}

void multiplication_test(int m, int n){
  cout << "-------------------------------" << endl;
  cout << "Multiplication Method" << endl;
  HashTable* mul = new HashTable(m);

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(1,100);
  int key;
  for(int i = 0; i < n; i++){
    key = dis(gen);
    mul->insert_multiplication(key, key);
  }
  for(int i = 0; i < 100; i++){
    int value=dis(gen);
    start = clock();
    cout << mul->search_multiplication(value) << " ";
    finish = clock();
    cout << "Time for search = " << finish-start << endl;
  }
  free(mul);
}

void matrix_test(int m, int n){
  cout << "-------------------------------" << endl;
  cout << "Matrix Method" << endl;
  HashTable* mat = new HashTable(m);

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(1,100);
  int key;
  for(int i = 0; i < n; i++){
    key = dis(gen);
    mat->insert_matrix(key, key);
  }
  for(int i = 0; i < 100; i++){
    int value=dis(gen);
    start = clock();
    cout << mat->search_matrix(value) << " ";
    finish = clock();
    cout << "Time for search = " << finish-start << endl;
  }
  free(mat);
}

int main(){
  int mu, nu;
  cout << "Enter m: ";
  cin >> mu;
  cout << "Enter n: ";
  cin >> nu;
  division_test(mu,nu);
  multiplication_test(mu,nu);
  matrix_test(mu,nu);



  return 0;
}
