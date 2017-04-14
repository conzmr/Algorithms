#include <iostream>
#include <random>
#include <limits.h>

using namespace std;

class DisjointSetWeighted {
private:
  int *p;
  int *rank;
  int *next;
  int *size;
  int set_num;
  int n;
public:
  DisjointSetWeighted(int n) { //Create n sets: 0..n-1
    this->set_num = this->n = n;
    this->p = new int[n];
    this->rank = new int[n];
    this->size = new int[n];
    this->next = new int[n];
  }

  void make_set(int x) {
    this->p[x] = x;
    this->size[x] = 1;
  }

  void make_n_sets() {
    for(int i = 0; i < this->set_num; i++)
      make_set(i);
  }

  int find_set(int x) {
    if(p[x] == x) {
      return x;
    }
    return find_set(p[x]);
  }

  void union_(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if(a == b) return;

    if(this->rank[a] < this->rank[b]) {
      this->p[a] = b;
      this->size[this->p[b]] += this->size[a];
    }
    else if(this->rank[a] > this->rank[b]) {
      this->p[b] = a;
      this->size[a] += this->size[b];
    }
    else {
      this->p[b] = a;
      this->size[this->p[b]] += this->size[a];
      this->rank[a]++;
    }
    set_num--;
  }

  void print_out(){
    cout << "Number of sets: " << this->set_num << endl;
    cout << "Parents: ";
		for(int i = 0; i < this->n; i++) {
			cout << "[" << this->p[i] << "]";
		}
		cout << endl;
	  cout << "Size: ";
		for(int i = 0; i < n; i++) {
			cout << "[" << this->size[i] << "]";
		}
		cout << endl;
		cout << "Rank: ";
		for(int i = 0; i < n; i++) {
			cout << "[" << this->rank[i] << "]";
    }
    cout << endl;
  }
};


int main() {
  int n = 5;

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(-1,n-1);

  DisjointSetWeighted *sets = new DisjointSetWeighted(n);

  sets->make_n_sets();

  for(int i = 0; i < n - 1; i++)
    sets->union_(dis(gen),dis(gen));
  sets->print_out();

  delete(sets);

  return 0;
}
