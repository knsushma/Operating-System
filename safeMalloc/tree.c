/*
* Srujana : srujana@wisc.edu
* Sushma : kudlurnirvan@wisc.edu
*
* File that has tree operations : Create, Insert, Delete and other utility functions
*
*/
#ifndef TREE_C
#define TREE_C

#include "tree.h"

struct node *get_node(void* val, size_t length) {
    struct node *new_node = (struct node *) malloc(sizeof(struct node));
    if (new_node == NULL) {
        fprintf(stderr,"Memory Allocation failed. Out of space!!!");
        exit(-1);
    }
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->data = val;
    new_node->height = HEIGHT;
    new_node->length = length;
    new_node->alloc = true;
    return new_node;
}

struct node *Initialize(void* value, size_t length) {
    struct node *T = NULL;
    T = (struct node *) malloc(sizeof(struct node));;
    if (T == NULL) {
        printf("Out of space!!!");
        exit(-1);
    } else {
        T->left = T->right = NULL;
        T->data = value;
        T->length = length;
        T->alloc = true;
    }
    return T;
}

int get_height(struct node *root) {
    if (!root)
        return 0;
    else
        return root->height;
}

int get_balance(struct node *root) {
    if (!root)
        return 0;
    return (get_height(root->left) - get_height(root->right));
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

struct node *left_rotate(struct node *root) {
    struct node *right = root->right;
    struct node *left = right->left;
    //perform rotation
    right->left = root;
    root->right = left;
    //update heights of the rotated nodes
    root->height = max(get_height(root->left), get_height(root->right)) + 1;
    right->height = max(get_height(right->left), get_height(right->right)) + 1;
    //return new root
    return right;
}

struct node *right_rotate(struct node *root) {
    struct node *left = root->left;
    struct node *right = left->right;
    //perform rotation
    left->right = root;
    root->left = right;
    //update heights of the rotated nodes
    root->height = max(get_height(root->left), get_height(root->right)) + 1;
    left->height = max(get_height(left->left), get_height(left->right)) + 1;
    //return new root
    return left;
}

struct node *insert(struct node *root, struct node *newNode) {
    //normal insertion
    if (!root) {
        //struct node *new_node = get_node(val, length);
        return newNode;
    }
    if (root->data > newNode->data)
        root->left = insert(root->left, newNode);
    else
        root->right = insert(root->right, newNode);
    //update height of root
    root->height = max(get_height(root->left), get_height(root->right)) + 1;
    //check for balancing
    int balance = get_balance(root);
    //left-left case
    if (balance > 1 && root->left->data > newNode->data) {
        root = right_rotate(root);
    }
        //right-right case
    else if (balance < -1 && root->right->data < newNode->data) {
        root = left_rotate(root);
    }
        //left-right case
    else if (balance > 1 && root->left->data < newNode->data) {
        root->left = left_rotate(root->left);
        root = right_rotate(root);
    }
        //right-left case
    else if (balance < -1 && root->right->data > newNode->data) {
        root->right = right_rotate(root->right);
        root = left_rotate(root);
    }
    return root;
}

//utility function used in balancing of node
//in deletion operation
struct node *balance_tree(struct node *root) {
    struct node *x, *y = NULL;
    int lheight, rheight;
    lheight = get_height(root->left);
    rheight = get_height(root->right);
    if (lheight >= rheight)
        x = root->left;
    else
        x = root->right;
    lheight = get_height(x->left);
    rheight = get_height(x->right);
    if (x == root->left) {
        if (lheight >= rheight) {
            y = x->left;
        } else
            y = x->right;
    }
    if (x == root->right) {
        if (lheight > rheight) {
            y = x->left;
        } else
            y = x->right;
    }
    //left-left case
    if (root->left == x && x->left == y) {
        root = right_rotate(root);
    }
        //right-right case
    else if (x == root->right && x->right == y) {
        root = left_rotate(root);
    }
        //left-right case
    else if (x == root->left && y == x->right) {
        root->left = left_rotate(root->left);
        root = right_rotate(root);
    }
        //right-left case
    else if (x == root->right && y == x->left) {
        root->right = right_rotate(root->right);
        root = left_rotate(root);
    }
    return root;
}

//utility function to find inorder successor
//of a given node when it has a right child
struct node *inorder_succ_right_tree(struct node *root) {
    struct node *temp = root->right;
    while (temp->left) {
        temp = temp->left;
    }
    return temp;
}

struct node *deleteNode(struct node *root, Node* delNode) {
    //normal deletion
    if (root == NULL)
        return NULL;
    if (root->data > delNode->data) {
        root->left = deleteNode(root->left, delNode);
    } else if (root->data < delNode->data) {
        root->right = deleteNode(root->right, delNode);
    } else {
        struct node *temp;
        if (root->left == NULL || root->right == NULL) {
            if (root->left)
                temp = root->left;
            else if (root->right)
                temp = root->right;
            else
                temp = NULL;
            root = NULL;
            free(root);
            return temp;
        } else {
            temp = inorder_succ_right_tree(root);
            root->data=temp->data;
            root->alloc=temp->alloc;
            root->length=temp->length;
            root->right = deleteNode(root->right, temp);
        }
    }
    //update height
    root->height = max(get_height(root->left), get_height(root->right)) + 1;
    int balance = get_balance(root);
    if (balance > 1 || balance < -1)
        root = balance_tree(root);
    return root;
}

Node* FindMax(Node* T) {
    while (T->right != NULL)
        T = T->right;

    return T;
}

//function for printing the pre-order of tree
void preorder(struct node *root) {
    if (!root)
        return;
    printf("%p\t", root->data);
    preorder(root->left);
    preorder(root->right);
}

//function for printing the in-order of tree
void inorder(struct node *root) {
    if (!root)
        return;
    inorder(root->left);
    printf("%p\t", root->data);
    inorder(root->right);
}


#endif
