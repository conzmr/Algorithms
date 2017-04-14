#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include "disjoint_set.h"

using namespace std;

typedef pair<int, int> int_pair;

struct graph {
  int V, E;
    vector< pair<int, int_pair> > edges;   //Set of Edges: int is weight and iPair are Vertices

    graph(int V, int E) {
        this->V = V;
        this->E = E;
    }

    void add_edge(int u, int v, int w) {
        edges.push_back(pair<int, int_pair>(w,int_pair(u,v)));
    }

    int kruskal(){
      int total_weight = 0;
      DisjointSet *ds = new DisjointSet(V);
      ds->make_n_sets();
      sort(edges.begin(), edges.end());
      vector< pair<int,int_pair> >::iterator it;
      for(it = edges.begin(); it != edges.end(); it++){
        int u = it->second.first;
        int v = it->second.second;
        int u_set = ds->find_set(u);
        int v_set = ds->find_set(v);
        if(u_set != v_set) {
          cout << u << " - " << v << endl;
          total_weight += it->first;
          ds->union_(u_set, v_set);
        }
      }
      return total_weight;
    }
};

int main() {
  int V = 9, E = 14;
  graph g(V, E);
  g.add_edge(0, 1, 4);
  g.add_edge(0, 7, 8);
  g.add_edge(1, 2, 8);
  g.add_edge(1, 7, 11);
  g.add_edge(2, 3, 7);
  g.add_edge(2, 8, 2);
  g.add_edge(2, 5, 4);
  g.add_edge(3, 4, 9);
  g.add_edge(3, 5, 14);
  g.add_edge(4, 5, 10);
  g.add_edge(5, 6, 2);
  g.add_edge(6, 7, 1);
  g.add_edge(6, 8, 6);
  g.add_edge(7, 8, 7);

  cout << "Edges of Minimum Spanning Tree:" << endl;
  int MSTWeight = g.kruskal();

  cout << "\nWeight of MST: " << MSTWeight << endl;

  return 0;
}
