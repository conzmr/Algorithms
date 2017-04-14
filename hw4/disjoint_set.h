#ifndef DISJOINT_SET_H_
#define DISJOINT_SET_H_

using namespace std;

class DisjointSet {
private:
  int *p;
  int *rank;
  int *size;
  int set_num;
  int n;
public:
  DisjointSet(int n) { //Create n sets: 0..n-1
    this->set_num = this->n = n;
    this->p = new int[n];
    this->rank = new int[n];
    this->size = new int[n];
    for(int i = 0; i < n; i++) {
      this->rank[i] = 0;
      this->size[i] = 0;
    }
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
    if(this->p[x] != x)
      this->p[x] = find_set(this->p[x]);
    return this->p[x];
  }

  void union_(int u, int v) {
    u = find_set(u);
    v = find_set(v);
    if(u == v) return;

    if(this->rank[u] > this->rank[v]) {
      this->p[v] = u;
      this->size[u] += this->size[v];
    }
    else {
      this->p[u] = this->p[v];
      this->size[this->p[v]] += this->size[u];
    }
    if (this->rank[u] == this->rank[v])
      this->rank[v]++;
    this->set_num--;
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

#endif
