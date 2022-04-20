//
// Created by cse310 on 4/20/22.
//

#ifndef P3_DFS_H
#define P3_DFS_H
#include "defns.h"
#include <string>
int computeSCC(graphNode**, int, hashTableEntry**, int, std::string, int*);
void visit(graphNode**, int, char*, int*, int*, int*);
#endif //P3_DFS_H
