#include <iostream>
#include <map>
#include <limits.h>
#include <random>
#include "graph.h"

using namespace std;

void initialize_single_source(Graph *g, vertex *s){
  for(map<string, vertex>::iterator it = g->G.begin(); it != g->G.end(); it++){
    if(it->second.name == s->name){
      it->second.prev = "NULL";
      it->second.pi = NULL;
      it->second.d = 0;
      it->second.color = WHITE;
    }
    else{
      it->second.prev = "NULL";
      it->second.pi = NULL;
      it->second.d = 99999;
      it->second.color = WHITE;
    }
  }
}

void dijkstra(Graph *g, string source_name, int size){
  vertex *s = & g->G[source_name];
  initialize_single_source(g, s);
  MinHeap *Q = new MinHeap(size + 1);
  Q->insert(s);

  while(!Q->is_empty()){
    vertex u = Q->extract_min();
    g->G[u.name].color = BLACK;

    for(int i = 0; i < g->G[u.name].adj_list.size(); i++){
      g->relax(u.name, u.adj_list[i].dest->name, u.adj_list[i].distance);
      if(!g->G[u.adj_list[i].dest->name].color){
        Q->insert(&g->G[u.adj_list[i].dest->name]);
        g->G[u.adj_list[i].dest->name].color = BLACK;
      }
    }
  }
}

void print_path(Graph *g, string u){
  vertex *temp = new vertex();
  temp = g->get_vertex(u);
  cout << temp->name << endl;
  while(temp->pi != NULL){
    temp = temp->pi;
    cout << temp->name << endl;
  }
}

int main() {
  for(int h = 10; h < 1000; h += 10) {
    Graph *g = new Graph();
    int graph_size = h;

    double Et = 0.2, a;

    for(int i = 0, j = graph_size - 1; i < graph_size/2  + 1 && j >= graph_size / 2 - 1; i++, j--) {
        //Generate random alpha.
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(0.0, 1);
        a = (float) dis(gen);

        if (a > Et && i != j) {
          //Generate random weight
          random_device rd;
          mt19937 gen(rd());
          uniform_real_distribution<> dis(0.0, 10);
          float w = (float) dis(gen);
          //End generate random weight
          string ri, rj;
          ri = to_string(i);
          rj = to_string(j);

          g->add_edge( ri, rj, w);
        }

    }
    //g->print_edges();

    clock_t begin, end;

    begin = clock();
    dijkstra(g, "0", graph_size);
    end = clock();

    double exTime = ( end - begin );

    cout << graph_size << "," << exTime << endl;

    //print_path(g, "4");

    delete(g);
  }
  return 0;
}
