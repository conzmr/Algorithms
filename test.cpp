#include <iostream>

using namespace std;

void arraycopy(int *A, int *B, int size){
  for(int i = 0; i < size; i++){
    B[i] = A[i];
  }
}

int main(){

  int A[] = {10,20,30};
  int B[3];
  arraycopy(A,B,3);
  cout << B[1] << endl;

  cout << B[]

  return 0;
}
