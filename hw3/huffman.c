#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct node node;
typedef struct node{
  char c;
  int freq;
  node * left;
  node * right;
} node;

typedef struct heap{
  node * nodes[60];
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
  //print_heap(encoding);
  while(encoding->size > 1){
    node *i = extract_min(encoding);
    node *j = extract_min(encoding);
    node *new = malloc(sizeof(node));
    new->freq = i->freq + j->freq;
    new->c = '*';
    new->left = i;
    new->right = j;
    min_heap_insert(encoding, new);
    //print_heap(encoding);
  }
}

//Print in-order-walk, swapping left and right.
void print_encoding_tree(node * node, int mult){
  if(node->right != NULL){
    print_encoding_tree(node->right, mult+1);
  }
  for(int i = 1; i < mult; i++){
    printf("\t");
  }
  printf("[%c,%d]\n",node->c,node->freq);
  if(node->left != NULL){
    print_encoding_tree(node->left, mult+1);
  }
}

//Print pre-order-walk.
void print_preorder(node * node, int mult){
  for(int i = 1; i < mult; i++){
    printf("\t");
  }
  printf("[%c,%d]\n",node->c,node->freq);
  if(node->left != NULL){
    print_preorder(node->left,mult+1);
  }
  if(node->right != NULL){
    print_preorder(node->right,mult+1);
  }
}

//The string for the binary representation.
char str[60];

void print_binary(node* node, int i) {
  if(node != NULL) {
    if (node->c != '*'){
      printf("%c : ", node->c);
      printf("%.*s\n", i, str);
    }
    str[i] = '0';
    print_binary(node->left, i+1);
    str[i] = '1';
    print_binary(node->right, i+1);
  }
}

void print_encode_phrase(char phrase[], int n){
  for(int i = 0; i < n; i++){
    //printf("Char at i:%d = %c\n",i, phrase[i]);
    switch (phrase[i]) {
      case 'a': printf("1010 "); break;
      case 'b': printf("100100 "); break;
      case 'c': printf("00101 "); break;
      case 'd': printf("10111 "); break;
      case 'e': printf("010 "); break;
      case 'f': printf("110100 "); break;
      case 'g': printf("100111 "); break;
      case 'h': printf("0001 "); break;
      case 'i': printf("0111 "); break;
      case 'j': printf("1101111110 "); break;
      case 'k': printf("11011110 "); break;
      case 'l': printf("10110 "); break;
      case 'm': printf("110110 "); break;
      case 'n': printf("0110 "); break;
      case 'o': printf("1000 "); break;
      case 'p': printf("100110 "); break;
      case 'q': printf("1101111100 "); break;
      case 'r': printf("0000 "); break;
      case 's': printf("0011 "); break;
      case 't': printf("1100 "); break;
      case 'u': printf("00100 "); break;
      case 'v': printf("1101110 "); break;
      case 'w': printf("110101 "); break;
      case 'x': printf("1101111111 "); break;
      case 'y': printf("100101 "); break;
      case 'z': printf("1101111101 "); break;
      case ' ': printf("111 "); break;
    }
  }
  printf("\n");
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

  printf("**Tilt your head to the left: Quasi-in-order (swapped left and right so that the tree looks nice)\n");
  print_encoding_tree(encoding->nodes[1],1);
  printf("\n");

  printf("**Tilt your head to the left: Pre-order\n");
  print_preorder(encoding->nodes[1],1);
  printf("\n");
  print_binary(encoding->nodes[1],0);

  char phrase[21] = {"hey my name is arturo"};

  print_encode_phrase(phrase, 21);

  return 0;

}
