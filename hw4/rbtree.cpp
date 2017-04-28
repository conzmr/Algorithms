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

  rbnode *get(int key){
    rbnode *temp = this->root;
    while(temp->key != key && temp != this->nil){
      if(temp->key > key){
        temp = temp->left;
      }
      else{
        temp = temp->right;
      }
    }
    return temp;
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

  void rb_transplant(rbnode *u, rbnode *v){
    if(u->p == this->nil){
      this->root = v;
    }
    else if(u == u->p->left){
      u->p->left = v;
    }
    else{
      u->p->right = v;
    }
    v->p = u->p;
  }

  rbnode * tree_minimum(rbnode *node){
    rbnode *min = node;
    while(min->left != this->nil){
      min = min->left;
    }
    return min;
  }




  void rb_delete_fixup(rbnode *x){
    rbnode *w;
    while(x != this->root && x->color == BLACK){
      if(x == x->p->left){
        w = x->p->right;
        if(w->color == RED){
          w->color = BLACK;
          x->p->color = RED;
          left_rotate(x->p);
          w = x->p->right;
        }
        if(w->left->color == BLACK && w->right->color == BLACK){
          w->color = RED;
          x = x->p;
        }
        else{
          if(w->right->color == BLACK){
            w->left->color = BLACK;
            w->color = RED;
            right_rotate(w);
            w = x->p->right;
          }
          w->color = x->p->color;
          x->p->color = BLACK;
          w->right->color = BLACK;
          left_rotate(x->p);
          x = this->root;
        }
      }
      else{
        if(x == x->p->right){
          w = x->p->left;
          if(w->color == RED){
            w->color = BLACK;
            x->p->color = RED;
            right_rotate(x->p);
            w = x->p->left;
          }
          if(w->right->color == BLACK && w->left->color == BLACK){
            w->color = RED;
            x = x->p;
          }
          else{
            if(w->left->color == BLACK){
              w->right->color = BLACK;
              w->color = RED;
              left_rotate(w);
              w = x->p->left;
            }
            w->color = x->p->color;
            x->p->color = BLACK;
            w->left->color = BLACK;
            right_rotate(x->p);
            x = this->root;
          }
        }
      }
    }
    x->color = BLACK;
  }

  void rb_delete(rbnode *z){
    rbnode *x;
    rbnode *y = z;
    bool y_original_color = y->color;
    if(z->left == this->nil){
      x = z->right;
      rb_transplant(z, z->right);
    }
    else if(z->right == this->nil){
      x = z->left;
      rb_transplant(z, z->left);
    }
    else{
      y = tree_minimum(z->right);
      y_original_color = y->color;
      x = y->right;
      if(y->p == z){
        x->p = y;
      }
      else{
        rb_transplant(y, y->right);
        y->right = z->right;
        y->right->p = y;
      }
      rb_transplant(z, y);
      y->left = z->left;
      y->left->p = y;
      y->color = z->color;
    }
    if(y_original_color == BLACK){
      rb_delete_fixup(x);
    }
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

void random_tree_perform() {
  clock_t begin, end;
  for(int n = 10; n < 1000; n++){
    int values[n];
    generate_random_array(values, n, true);
    RedBlackTree *tree = new RedBlackTree();

    begin = clock();
    for(int i = 0; i < n; i++){
      tree->insert(values[i]);
    }
    end = clock();
    double ex_time = (end - begin);
    cout << n << "," << ex_time << endl;
    // cout << tree->get_size() << endl;
    // tree->print_inorder_inverse();
    delete(tree);
  }
}

int main(){
  RedBlackTree *tree = new RedBlackTree();
  tree->insert(30);
  tree->insert(20);
  tree->insert(40);
  tree->insert(35);
  tree->print_inorder_inverse();
  cout << "Delete 20" << endl;
  tree->rb_delete(tree->get(20));
  tree->print_inorder_inverse();
  cout << "Delete 30" << endl;
  tree->rb_delete(tree->get(30));
  tree->print_inorder_inverse();
  cout << "Delete 40" << endl;
  tree->rb_delete(tree->get(40));
  tree->print_inorder_inverse();
  cout << "Delete 35" << endl;
  tree->rb_delete(tree->get(35));
  tree->print_inorder_inverse();
  return 0;
}
