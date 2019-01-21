/*
* Srujana : srujana@wisc.edu
* Sushma : kudlurnirvan@wisc.edu
*
* File that has tree operations : Create, Insert, Delete and other utility functions
*
*/
#ifndef TREE_H
#define TREE_H

#include<stdlib.h>
#include<stdio.h>
#include <stdbool.h>

#define HEIGHT 1
#define MAX_Q_SIZE 100

typedef struct node {
    struct node *left;
    struct node *right;
    int height;
    void* data;
    size_t length;
    bool alloc;
}Node;

struct node *get_node(void* val, size_t length);
int get_height(struct node *root);
int get_balance(struct node *root);
int max(int a, int b);
struct node *left_rotate(struct node *root);
struct node *right_rotate(struct node *root);
struct node *insert(struct node *root, struct node *newNode);
struct node *balance_tree(struct node *root);
struct node *inorder_succ_right_tree(struct node *root);
struct node *deleteNode(struct node *root, Node* delNode);
Node* FindMax(Node* T);

void preorder(struct node *root);
void inorder(struct node *root);

#endif
