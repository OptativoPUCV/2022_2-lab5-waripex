#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {

  TreeMap *new = (TreeMap *)malloc(sizeof(TreeMap));
  new->root=NULL;
  new->current=NULL;
  new->lower_than = lower_than;
  return new;
  
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  TreeNode * raiz= tree->root;
  TreeNode * aux = NULL;
  
  if(searchTreeMap(tree,key)!=NULL) return; 
  
  while(raiz!=NULL){
    aux=raiz;
    int resultados = tree->lower_than(key,raiz->pair->key);
    if(resultados==1){
      raiz=raiz->left;
    }else{
        if(resultados==0){
        raiz=raiz->right;
      }else return;
    }
  }
  
  TreeNode * newNode= createTreeNode(key,value);
  newNode->parent=aux;
  int resultado = tree->lower_than(key,aux->pair->key);
  if(aux!=NULL){
    if(resultado==1){
      aux->left=newNode;
    }
    if(resultado==0){
      aux->right=newNode;
    } 
    
  }
  if(aux==NULL)tree->root=newNode;
  tree->current=newNode;
  return;
}

TreeNode * minimum(TreeNode * x){
  while(x->left!=NULL){
  x=x->left;
  }
  return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
  tree->current=tree->root;
  while(tree->current !=NULL){
    int valor = is_equal(tree,key,tree->current->pair->key);
    if(valor==1){
      return tree->current->pair;
    }
    int branch = tree->lower_than(key,tree->current->pair->key);
    if(branch==1){
      tree->current=tree->current->left; 
    }
    else{
      tree->current=tree->current->right;
    }
  }
  return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
  TreeNode * X = tree->root;
  tree->current=minimum(X);
  if(tree->current==NULL)return NULL;
  return tree->current->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
