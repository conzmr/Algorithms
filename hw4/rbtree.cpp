#include <iostream>
#include <random>
#include <limits.h>

using namespace std;

bool RED = 0;
bool BLACK = 1;
//char RED = 'r';
//char BLACK = 'b';

struct rbnode{
  int key;
  rbnode *p;
  rbnode *left;
  rbnode *right;
  bool color; //1 is black, 0 is red
  //char color; //b is black, r is red
  rbnode(int k) {
    key = k;
    left = right = p = NULL;
    color = RED;
  }
  rbnode() {
    left = right = p = NULL;
    color = BLACK;
  }
};

class RedBlackTree{
private:
  int size;
  rbnode *root;
  rbnode *nil;
public:
  RedBlackTree(){
    this->size = 0;
    this->nil = new rbnode();
    this->nil->color = BLACK;
    this->root = this->nil;
    this->nil->p = this->nil;
  }
  int get_size(){
    return this->size;
  }
  void print_inorder_inverse(){
    print_inorder_inverse(this->root, 1);
  }
  void print_inorder_inverse(rbnode *node, int mult){
    if(node->right != NULL){
      print_inorder_inverse(node->right, mult+1);
    }
    for(int i = 1; i < mult; i++){
      cout << "\t";
    }
    cout << "[" << node->key << ", ";
    if(node->color){
      cout << "B";
    }
    else cout << "R";
    cout << "]" << endl;
    if(node->left != NULL){
      print_inorder_inverse(node->left, mult+1);
    }
  }

  void insert(int key){
    rbnode *z = new rbnode(key);
    rbnode *y = this->nil;
    rbnode *x = this->root;

    while(x != this->nil){
      y = x;
      if(z->key < x->key)
        x = x->left;
      else
        x = x->right;
    }
    z->p = y;
    if(y == this->nil){
      this->root = z;
    }
    else if(z->key < y->key)
      y->left = z;
    else
      y->right = z;
    z->left = this->nil;
    z->right = this->nil;
    z->color = RED;

    this->size++;

    rb_insert_fixup(z);
  }

  void left_rotate(rbnode *x){
    rbnode *y = x->right;
    x->right = y->left;
    if(y->left != this->nil){
      y->left->p = x;
    }
    y->p = x->p;
    if(x->p == this->nil){
      this->root = y;
    }
    else if(x == x->p->left){
      x->p->left = y;
    }
    else{
      x->p->right = y;
    }
    y->left = x;
    x->p = y;
  }

  void right_rotate(rbnode *x){
    rbnode *y = x->left;
    x->left = y->right;
    if(y->right != this->nil){
      y->right->p = x;
    }
    y->p = x->p;
    if(x->p == this->nil){
      this->root = y;
    }
    else if(x == x->p->right){
      x->p->right = y;
    }
    else{
      x->p->left = y;
    }
    y->right = x;
    x->p = y;
  }

  void rb_insert_fixup(rbnode *z){
    rbnode *y;
    while(z->p->color == RED){
      if(z->p == z->p->p->left) {
        y = z->p->p->right;
        if(y->color == RED) {
          z->p->color = BLACK;
          y->color = BLACK;
          z->p->p->color = RED;
          z = z->p->p;
        }
        else {
          if(z == z->p->right) {
            z = z->p;
            left_rotate(z);
          }
          z->p->color = BLACK;
          z->p->p->color = RED;
          right_rotate(z->p->p);
        }
      }
      else {
        y = z->p->p->left;
        if(y->color == RED) {
          z->p->color = BLACK;
          y->color = BLACK;
          z->p->p->color = RED;
          z = z->p->p;
        }
        else {
          if(z == z->p->left) {
            z = z->p;
            right_rotate(z);
          }
          z->p->color = BLACK;
          z->p->p->color = RED;
          left_rotate(z->p->p);
        }
      }
    }
    this->root->color = BLACK;
  }
};

void generate_random_array(int *a, int n, bool silence){
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(1,100);
  for(int i = 0; i < n; i++){
    a[i] = dis(gen);
    if(!silence)
      cout << a[i] << "  ";
  }
  if(!silence)
    cout << endl;
}

int main(){
  int n = 10;
  int values[n];
  generate_random_array(values, n, false);
  RedBlackTree *tree = new RedBlackTree();

  for(int i = 0; i < n; i++){
    tree->insert(values[i]);
  }

  cout << tree->get_size() << endl;
  tree->print_inorder_inverse();
  delete(tree);

  return 0;
}
