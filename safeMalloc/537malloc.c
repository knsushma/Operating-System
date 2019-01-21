/*
* Srujana : srujana@wisc.edu
* Sushma : kudlurnirvan@wisc.edu
*
* File that has Safe Malloc operations : malloc537, free537, memcheck537, realloc537 and other utility functions
*
*/
#ifndef SAFE_MALLOC_C
#define SAFE_MALLOC_C

#include "537malloc.h"

static Node* root = NULL;

void* malloc537(size_t size)
{
    if (size == 0) {
        fprintf(stderr, "\n**WARNING from MALLOC**\n Bad request. Memory size 0 provided for Malloc\n");
    }
    void* mallocAddrs = malloc(size);
    if (mallocAddrs == NULL) {
        fprintf(stderr,"Malloc Failed. Out of space!!!");
        exit(-1);
    }
    Node *rangeNode = getInRangeTargetNode(root,mallocAddrs,NULL);
    if(!rangeNode)
    {
        //not in range, allocate newnode. get_node() method checks if malloc is successful. Otherwise prints "Out of space"
        Node *newNode = get_node(mallocAddrs,size);
        root = insert(root, newNode);
        return newNode->data;
    }
    else
    {   //in range
        if(!rangeNode->alloc) // check if it's already allocated
        {
            if(rangeNode->data == mallocAddrs)
            {
                if(rangeNode->length>size) //if already allocated node size is greater than new one
                { //shrink the old one and insert a new node with alloc flag set to false;
                    size_t diff = rangeNode->length-size;
                    rangeNode->alloc = true;
                    rangeNode->length = size;
                    Node *splitNode = get_node(mallocAddrs+size, diff);
                    splitNode->alloc = false;
                    root = insert(root,splitNode);
                }
                else if(rangeNode->length == size) // newly allocated node is of same size
                {
                    rangeNode->alloc = true;
                }
                else
                { // else assign new size by expanding the node.
                    Node* maxNode = FindMax(root);
                    size_t maxMemoryInTree = (uintptr_t)maxNode->data+maxNode->length-1;
                    root = deleteAllOverLappingNodes(root, size, rangeNode, maxMemoryInTree, 0);
                    rangeNode->alloc = true;
                    rangeNode->length = size;
                }
                return rangeNode->data;
            }
            else
            { //new address is malloced whose starting address is in the middle of the freed node
                Node* maxNode = FindMax(root);
                size_t maxMemoryInTree = (uintptr_t)maxNode->data+maxNode->length-1;
                root = deleteAllOverLappingNodes(root, size, rangeNode, maxMemoryInTree, rangeNode->data-mallocAddrs);
                root = deleteNode(root,rangeNode);
                Node *newRange= get_node(mallocAddrs,size);
                root = insert(root,newRange);
                return newRange->data;
            }
        }
        else
        {//in range but already allocated
            fprintf(stderr,"trying to allocate already allocated memory location");
            exit(-1);
        }
    }
}


void free537(void* ptr) {
    if (ptr != NULL)
    {
        Node* targetNode = getInRangeTargetNode(root, ptr, NULL);
        if (!targetNode) {
            fprintf(stderr, "\n**ERROR IN FREE, TERMINATING PROGRAM**\nAddress %p is not allocated by malloc537\n", ptr);
            exit(-1);
        } else {
            uintptr_t toBefreed = (uintptr_t) ptr;
            uintptr_t targetStartingAddr = (uintptr_t) targetNode->data;
            if (targetStartingAddr != toBefreed) {
                fprintf(stderr, "\n**ERROR IN FREE, TERMINATING PROGRAM**\nFreeing memory %p that is not the first byte of the range of memory that was allocated.\n", targetNode->data);
                exit(-1);
            } else if (!targetNode->alloc) {
                fprintf(stderr, "\n**ERROR IN FREE, TERMINATING PROGRAM**\nFreeing memory %p that was previously freed (double free).\n", targetNode->data);
                exit(-1);
            } else {
                printf("\nFreeing memory address %p.\n", targetNode->data);
                targetNode->alloc = false;
            }
        }
    }
}


void memcheck537(void* ptr, size_t size) {
    if (root == NULL) {
        fprintf(stderr, "\n**MEMCHECK ALERT, TERMINATING PROGRAM**\nAddress %p is not allocated by malloc537\n", ptr);
        exit(-1);
    } else {
        Node * node = getInRangeTargetNode(root, ptr, NULL);
        if (!node) {
            fprintf(stderr, "\n**MEMCHECK ALERT, TERMINATING PROGRAM**\nAddress %p is not allocated by malloc537\n", ptr);
            exit(-1);
        } else {
            uintptr_t nodeAddr = (uintptr_t) node->data;
            uintptr_t targetNodeAddr = (uintptr_t) ptr;
            if ((nodeAddr+node->length) < (targetNodeAddr+size)){
                fprintf(stderr, "\n**MEMCHECK ALERT, TERMINATING PROGRAM**\nTrying to access memory location which is beyond the allocation range of %p\n", node->data);
                exit(-1);
            }
            if (!node->alloc) {
                fprintf(stderr, "\n**MEMCHECK ALERT, TERMINATING PROGRAM**\nTrying to use memory location %p which is already freed\n", node->data);
                exit(-1);
            }
        }
    }
}


void* realloc537(void* ptr, size_t size) {
    if (ptr == NULL) {
        return malloc537(size);
    } else if (size == 0) {
        free537(ptr);
        return NULL;
    } else {//Check if trying to free a non-malloc537 allocated memory and if not the starting byte
        Node *rangeNode = getInRangeTargetNode(root,ptr, NULL);
        if (!rangeNode) {//Check if ptr is allocated by malloc537
            fprintf(stderr, "\n**ERROR IN REALLOC, TERMINATING PROGRAM**\nAddress %p is not allocated by malloc537. Cannot do Realloc.\n", ptr);
            exit(-1);
        } else if (!rangeNode->alloc) {
            fprintf(stderr, "\n**ERROR IN REALLOC, TERMINATING PROGRAM**\nTrying to realloc memory location %p which is already freed\n", ptr);
            exit(-1);
        } else { // Check if ptr is first byte of allocated memory
            uintptr_t oldToBeReallocated = (uintptr_t) ptr;
            uintptr_t oldTargetStartingAddr = (uintptr_t) rangeNode->data;
            if (oldTargetStartingAddr != oldToBeReallocated) {
                fprintf(stderr,"\n** 1 ERROR IN REALLOC, TERMINATING PROGRAM**\nTrying to Reallocate memory %p that is not the first byte of the range of memory that was allocated.\n", ptr);
                exit(-1);
            } // All good, realloc memory now. get_node() method checks if malloc is successful. Otherwise prints "Out of space"
            void* reallocPtr = realloc(ptr, size);
            if (reallocPtr == NULL) {
                fprintf(stderr,"Realloc Failed. Out of space!!!");
                exit(-1);
            }
            Node* reallocedNode = get_node(reallocPtr, size);
            size_t reallocStartingAddr = (uintptr_t)reallocedNode->data;
            if (reallocStartingAddr == oldTargetStartingAddr)
            { // Shrinking the same memory location
                int memLenDiff = (int)rangeNode->length - (int)size;
                if (memLenDiff < 0){
                    Node* maxNode = FindMax(root);
                    size_t maxMemoryInTree = (uintptr_t)maxNode->data+maxNode->length-1;
                    root = deleteAllOverLappingNodes(root, size, rangeNode, maxMemoryInTree, 0);
                }
                rangeNode->alloc = true;
                rangeNode->length = size;
            } else { // Realloc allocated a new memory location, 1. Another free Node in Tree 2. Completely new location
                root = deleteNode(root, rangeNode);
                Node *newRangeNode = getInRangeTargetNode(root,reallocedNode->data, NULL);
                if (newRangeNode != NULL) {
                    if (newRangeNode->alloc) {
                        fprintf(stderr,"\n** 2 ERROR IN REALLOC, TERMINATING PROGRAM**\nTrying to reallocate memory location which is already allocated.\n");
                        exit(-1);
                    }
                    uintptr_t toBeReallocated = (uintptr_t) reallocedNode->data;
                    uintptr_t targetStartingAddr = (uintptr_t) newRangeNode->data;
                    if (targetStartingAddr == toBeReallocated) {
                        int memLenDiff = (int)newRangeNode->length - (int)size;
                        if (memLenDiff < 0) {
                            Node* maxNode = FindMax(root);
                            size_t maxMemoryInTree = (uintptr_t) maxNode->data + maxNode->length-1;
                            root = deleteAllOverLappingNodes(root, size, newRangeNode, maxMemoryInTree, 0);
                        }
                        newRangeNode->alloc = true;
                        newRangeNode->length = size;
                    } else {
                        root = insert(root, reallocedNode);
                    }
                } else {
                    root = insert(root, reallocedNode);
                }
            }
            return reallocedNode->data;
        }
    }
}



Node* deleteAllOverLappingNodes(Node* root, size_t size, Node* rangeNode, size_t maxMemoryInTree, size_t adjustLength) {
    int remaningsize = (int)((uintptr_t)rangeNode->data + size ) - (int)((uintptr_t)rangeNode->data+rangeNode->length ) + (int)adjustLength;
    size_t newaddress = (uintptr_t) rangeNode->data + rangeNode->length ;
    Node * targetNode=NULL;
    targetNode = getInRangeTargetNode(root, (void*)newaddress, targetNode);
    while(remaningsize > 0 && newaddress<=maxMemoryInTree) {
        if (targetNode == NULL) {
            newaddress += 1;
            remaningsize -= 1;
        } else {
            if(targetNode->alloc == true) {
                fprintf(stderr,"**MALLOC FAILED, TERMINATING PROGRAM!!!**\n Trying to allocate memory which is already allocated\n");
                exit(-1);
            }
            if((int)targetNode->length <= remaningsize) {
                remaningsize -= (int)targetNode->length;
                newaddress = (uintptr_t)targetNode->data + targetNode->length;
                root = deleteNode(root, targetNode);
            } else if ((int)targetNode->length > remaningsize) {
                remaningsize = 0;
                root = deleteNode(root, targetNode);
            }
        }
        targetNode = getInRangeTargetNode(root, (void*)newaddress, NULL);
    }
    return root;
}


Node* getInRangeTargetNode(Node* root, void* ptr, Node* targetNode) {
    if (targetNode != NULL)
        return targetNode;
    else if (root != NULL) {
        uintptr_t findAddr = (uintptr_t) ptr;
        uintptr_t rootStartingAddr = (uintptr_t) root->data;
        if (rootStartingAddr > findAddr) {
            targetNode = getInRangeTargetNode(root->left, ptr, targetNode);
        } else if (rootStartingAddr < findAddr) {
            if (findAddr >= rootStartingAddr && (findAddr < (rootStartingAddr+root->length)) ) {
                targetNode = root;
            }
            targetNode = getInRangeTargetNode(root->right, ptr, targetNode);
        } else if (findAddr >= rootStartingAddr && (findAddr < (rootStartingAddr+root->length)) ) {
            targetNode = root;
        }
        return targetNode;
    } else {
        return targetNode;
    }
}


Node* addressInRangeLogNTargetNode(Node* root, void* ptr, size_t size, Node* targetNode) {
    if (targetNode != NULL)
        return targetNode;
    else if (root != NULL) {
        uintptr_t findAddr = (uintptr_t) ptr;
        uintptr_t rootStartingAddr = (uintptr_t) root->data;
        if (rootStartingAddr > findAddr) {
            targetNode = addressInRangeLogNTargetNode(root->left, ptr, size, targetNode);
        } else if (rootStartingAddr < findAddr) {
            if (findAddr >= rootStartingAddr && (findAddr+size) <= (rootStartingAddr+root->length) ) {
                targetNode = root;
            }
            targetNode = addressInRangeLogNTargetNode(root->right, ptr, size, targetNode);
        } else if (findAddr >= rootStartingAddr && (findAddr+size) <= (rootStartingAddr+root->length) ) {
            targetNode = root;
        }
        return targetNode;
    } else {
        return targetNode;
    }
}

#endif
