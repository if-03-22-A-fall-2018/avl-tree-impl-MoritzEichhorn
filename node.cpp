#include "node.h"
#include <stdlib.h>

int get_key(Node node) {
  if(node == 0) { return 0; }
  return node->key;
}

Node get_left(Node node) {
  if(node == 0) { return 0; }
  return node->left_node;
}

void set_left(Node node, Node left_node) {
  if(node == 0) { return; }
  node->left_node = left_node;
}

Node get_right(Node node) {
  if(node == 0) { return 0; }
  return node->right_node;
}

void set_right(Node node, Node right_node) {
  if(node == 0) { return; }
  node->right_node = right_node;
}

int get_height(Node node) {
  if(node == 0) { return 0; }
  return node->height;
}

void set_height(Node node, int height) {
  if(node == 0) { return; }
  node->height = height;
}

Node create_node(int key) {
  Node new_node = (Node)malloc(sizeof(struct node));
  new_node->right_node = 0;
  new_node->left_node = 0;
  new_node->key = key;
  new_node->height = 1;
  return new_node;
}
