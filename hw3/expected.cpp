#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int main(){
  double total_sum, n, p, entropy;
  ifstream inp("prob.txt");
  ifstream inn("n.txt");

  total_sum = 0;
  entropy = 0;

  for(int i = 0; inp && inn && i < 27; i++){
    inn >> n;
    inp >> p;
    p /= 100;
    cout << n << " * " << p << endl;
    total_sum += n*p;
    entropy += p*log2(1/p);
  }

  inp.close();
  inn.close();

  cout << "Expected value is: "  << total_sum << endl;
  cout << "Entropy is: " << entropy << endl;
  return 0;
}
