//
// Created by cse310 on 4/18/22.
//
#include "HashTable.h"
#include "Utilities.h"
void insertHash(hashTableEntry** hashTable, int m, int index, int id) {
    int key = id % m;
    hashTableEntry* new_node = (struct hashTableEntry*) malloc(sizeof(struct hashTableEntry));
    new_node->next = nullptr;
    new_node->vertexLabel = id;
    new_node->mapping = index;
    if (!hashTable[key]) {
        hashTable[key] = new_node;
    } else {
        // insert at tail
        hashTableEntry *temp = hashTable[key];
        while(temp->next) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

hashTableEntry* findEntry(hashTableEntry** hashTable, int id, int m) {
    int key = id % m;
    hashTableEntry* tmp = hashTable[key];
    while(tmp) {
        if (tmp->vertexLabel == id) {
            return tmp;
        }
        tmp = tmp->next;
    }
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
    for(int i = 0; i < sizeOfHashTable; i++)
        hashTable[i] = nullptr;
    for(int i = 0; i < sizeOfVertexArr; i++) {
        insertHash(hashTable, sizeOfHashTable, i, vertexArr[i]);
    }
}