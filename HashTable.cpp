//
// Created by cse310 on 4/18/22.
//
#include "HashTable.h"
#include "Utilities.h"
void insertHash(hashTableEntry** hashTable, int m, int index, int id) {
    int key = id % m;
    if (!hashTable[key]) {
        hashTableEntry* new_node = (struct hashTableEntry*) malloc(sizeof(struct hashTableEntry));
        new_node->next = nullptr;
        new_node->vertexLabel = id;
        new_node->mapping = index;
        hashTable[key] = new_node;
    } else {
        // insert at head
        hashTableEntry* new_node = (struct hashTableEntry*) malloc(sizeof(struct hashTableEntry));
        new_node->next = hashTable[key];
        new_node->vertexLabel = id;
        new_node->mapping = index;
        hashTable[key] = new_node;
    }
}

hashTableEntry* findEntry(hashTableEntry** hashTable, int id, int m) {
    int key = id % m;
    if (hashTable[key]) {
        if (hashTable[key]->next) {
            // linked list has more than one node, loop to find id
            hashTableEntry* last = hashTable[key];
            while (last->next) {
                if (last->vertexLabel == id) {
                    return last;
                }
                last = last->next;
            }
        } else if (hashTable[key]->vertexLabel == id) {
            // linked list has only one node (head), check if id match
            return hashTable[key];
        }
    }
    // no linked list at key exists
    return nullptr;
}

int getHashMapArrLength(int n) {
    n = n * 3;

    bool isNotPrime = true;
    while(isNotPrime) {
        if (testForPrime(n)) {
            isNotPrime = false;
        } else {
            n++;
        }
    }

    return n;
}

void buildHashTable(hashTableEntry** hashTable, int* vertexArr, int sizeOfHashTable, int sizeOfVertexArr) {
    for(int i = 0; i < sizeOfVertexArr; i++) {
        insertHash(hashTable, sizeOfHashTable, i, vertexArr[i]);
    }
}