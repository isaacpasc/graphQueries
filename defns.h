//
// Created by cse310 on 4/17/22.
//

#ifndef P3_DEFNS_H
#define P3_DEFNS_H
#define INF 999999999

struct hashTableEntry {
    int vertexLabel;
    int mapping;
    struct hashTableEntry* next;
};

struct graphNode {
    int index;
    struct graphNode* next;
};

#endif //P3_DEFNS_H
