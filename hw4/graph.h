#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include <limits.h>

using namespace std;

bool WHITE = false;
bool BLACK = true;

struct edge;

struct vertex {
  string name;
  vector<edge> adj_list;
  string prev;
  vertex *pi;
  double d;
  bool color;
};

struct edge {
  vertex *dest;
  double distance;
};

class MinHeap {
  vertex *pq;
  int n;
public:
  MinHeap(int initCapacity) {
    n = 0;
    pq = new vertex[initCapacity+1];
  }
  void min_heapify(int i) {
    int l = 2*i;
    int r = l+1;
    int minimum = 0;
    if(l <= n && pq[l].d < pq[i].d)
      minimum = l;
    else
      minimum = i;
    if(r <= n && pq[r].d < pq[minimum].d)
      minimum = r;
    if(minimum != i) {
      vertex temp = pq[i];
      pq[i] = pq[minimum];
      pq[minimum] = temp;
      min_heapify(minimum);
    }
  }
  vertex extract_min() {
    if(n < 1) cout << "\nHeapUnderFlow" << endl;;
    vertex min = pq[1];
    pq[1] = pq[n];
    n--;
    min_heapify(1);
    return min;
  }
  void decrease_key(int i, vertex *item) {
    if(item->d > pq[i].d) {
      cout << "\nKey larger than currentKey" << endl;
      return;
    }
    pq[i] = *item;
    while(i > 1 && pq[i/2].d > pq[i].d) {
      vertex temp = pq[i];
      pq[i] = pq[i/2];
      pq[i/2] = temp;
      i = i/2;
    }
  }
  void insert(vertex *item) {
    n++;
    vertex* temp = new vertex;
    temp->d = INT_MAX;
    pq[n] = *temp;
    decrease_key(n, item);
  }
  bool is_empty() {
    return n == 0;
  }
};

class Graph {
public:
  map<string, vertex> G;
  Graph() {};
  vertex *get_vertex(string name) {
    if(G.find(name) == G.end()) {
      vertex* node = new vertex;
      node->name = name;
      node->d = 0;
      node->color = WHITE;
      G[name] = *node;
      return node;
    }
    else {
      return &G[name];
    }
  }
  void add_edge(string src, string end, double dist) {
    vertex* v = get_vertex(src);
    vertex* w = get_vertex(end);
    edge* e = new edge;
    e->dest = w;
    e->distance = dist;
    v->adj_list.push_back( *e );
    G[src] = *v;
    G[end] = *w;
  }
  void relax(string u, string v, double w) {
    if(G[v].d > G[u].d + w) {
      vertex *temp = new vertex();
      temp = this->get_vertex(u);
      G[v].d = G[u].d + w;
      G[v].prev = u;
      G[v].pi = temp;
    }
  }

  void print_edges() {
    for ( std::map<string, vertex>::iterator it = G.begin(); it != G.end(); ++it ) {
      cout << "Vertex: " <<  it->second.name << " -- Adjacency List:" << endl;
      for ( int i = 0; i < it->second.adj_list.size(); i++ ) {
        //cout << "hola" << endl;
        cout << it->second.adj_list[i].dest->name << "\tWeight: " << it->second.adj_list[i].distance << endl;
      }
    }
  }
};

#endif
