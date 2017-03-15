#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node node;
typedef struct node{
  char c;
  int freq;
  node * left;
  node * right;
} node;

typedef struct heap{
  node * nodes[56];
  int size;
} heap;

void min_heapify(heap * heap, int index){
  int size = heap->size+1;
  if(size < 1){
    printf("Empty array\n");
    return;
  }
  int min = index;
  do{
    index = min;
    int left = index*2;
    int right = left+1;
    if(left < size && heap->nodes[left]->freq < heap->nodes[min]->freq){
      min = left;
    }
    if(right < size && heap->nodes[right]->freq < heap->nodes[min]->freq){
      min = right;
    }
    if(min != index){
      node *temp = heap->nodes[index];
      heap->nodes[index] = heap->nodes[min];
      heap->nodes[min] = temp;
    }
  }while(min != index);
}

void min_heap_insert(heap * heap, node *value){
  if(heap->size > 0){
    int child = heap->size+1;
    heap->nodes[child] = value;
    while(child > 1){
      int parent = child/2;
      if(heap->nodes[child]->freq < heap->nodes[parent]->freq){
        node *temp = heap->nodes[child];
        heap->nodes[child] = heap->nodes[parent];
        heap->nodes[parent] = temp;
        child = parent;
      }
      else{
        break;
      }
    }
    int position = heap->size++;
  }
  else{
    heap->nodes[1] = value;
    heap->size++;
  }
}

node * extract_min(heap * heap){
  node * temp = heap->nodes[1];
  heap->nodes[1] = heap->nodes[heap->size];
  heap->size--;
  min_heapify(heap, 1);
  return temp;
}

void add(node ** nodes, int i, char c, float freq){
  nodes[i] = malloc(sizeof(node));
  nodes[i]->c = c;
  nodes[i]->freq = freq;
}

void print_heap(heap * heap){
  for(int i = 0; i <= heap->size; i++){
    printf("heap[%d] = %c,%d  ", i, heap->nodes[i]->c,heap->nodes[i]->freq);
  }
  printf("\n");
}

void huffman_procedure(node ** nodes, heap * encoding, int n){
  for(int it = 0; it < n; it++){
    encoding->nodes[it] = malloc(sizeof(node));
  }
  encoding->size = 0;
  for(int it = 0; it < n; it++){
    min_heap_insert(encoding, nodes[it]);
  }
  print_heap(encoding);
  while(encoding->size > 1){
    node *i = extract_min(encoding);
    node *j = extract_min(encoding);
    node *new = malloc(sizeof(node));
    new->freq = i->freq + j->freq;
    new->c = '*';
    new->left = i;
    new->right = j;
    printf("*****left = %c  ",new->left->c);
    printf("right = %c\n",new->right->c);
    min_heap_insert(encoding, new);
    print_heap(encoding);
  }
}

void print_encoding_tree(node * node){
  if(node->left != NULL){
    print_encoding_tree(node->left);
  }
  printf("[%c,%d]\n",node->c,node->freq);
  if(node->right != NULL){
    print_encoding_tree(node->right);
  }
}

void print_preorder(node * node){
  printf("[%c,%d]\n",node->c,node->freq);
  if(node->left != NULL){
    print_encoding_tree(node->left);
  }
  if(node->right != NULL){
    print_encoding_tree(node->right);
  }
}

int main(){
  heap encoding[27];
  node * nodes[27];

  char c[] = {' ','e','t','a','o','i','n','s','h','r','d','l','c','u','m','w','f','g','y','p','b','v','k','j','x','q','z'};
  int freq[] = {183,102,77,68,59,58,55,51,49,48,35,34,26,24,21,19,18,17,16,16,13,9,6,2,2,1,1};
  int n = 27;
  for(int i = 0; i < n; i++){
    nodes[i] = malloc(sizeof(node));
    add(nodes, i, c[i], freq[i]);
  }
  for(int i = 0; i < n; i++){
    printf("%c, %d\n",nodes[i]->c, nodes[i]->freq);
  }

  huffman_procedure(nodes, encoding, n);

  print_encoding_tree(encoding->nodes[1]);
  printf("\n");
  print_preorder(encoding->nodes[1]);

  return 0;

}
