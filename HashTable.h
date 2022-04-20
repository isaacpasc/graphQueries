//
// Created by cse310 on 4/18/22.
//

#ifndef P3_HASHTABLE_H
#define P3_HASHTABLE_H
#include "defns.h"
void insertHash(hashTableEntry**, int, int, int);
hashTableEntry* findEntry(hashTableEntry**, int, int);
int getHashMapArrLength(int);
void buildHashTable(hashTableEntry**, int*, int, int);
#endif //P3_HASHTABLE_H
