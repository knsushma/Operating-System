/*
* Srujana : srujana@wisc.edu
* Sushma : kudlurnirvan@wisc.edu
*
* File that has Safe Malloc operations : malloc537, free537, memcheck537, realloc537 and other utility functions
*
*/
#ifndef SAFE_MALLOC_H
#define SAFE_MALLOC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "tree.h"

void* malloc537(size_t size);
void free537(void* ptr);
void memcheck537(void* ptr, size_t size);
void* realloc537(void* ptr, size_t size);
Node* deleteAllOverLappingNodes(Node* root, size_t size, Node* rangeNode, size_t maxMemoryInTree, size_t adjustLength);
Node* addressInRangeLogNTargetNode(Node* root, void* ptr, size_t size, Node* targetNode);
Node* getInRangeTargetNode(Node* root, void* ptr, Node* targetNode);


#endif
