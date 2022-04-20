//
// Created by cse310 on 4/20/22.
//
#include "DFS.h"
#include "Utilities.h"
#include "AdjacencyList.h"

int computeSCC(graphNode** adjacencyList, int length, hashTableEntry** hashTable, int hashTableSize, std::string edges, int* outputArr) {

    // set startTime to 0
    int time = 0;
    int* timePtr = &time;

    // create visited array
    char visited[length];

    // create sorted list of finish times
    int index[length];

    // mark all nodes white for not visited and index array with indexes
    for (int i = 0; i < length; i++) {
        visited[i] = 'w';
        index[i] = i;
    }

    // create finishTime array
    int finishedTime[length];

    // visit each node in adjacency list in order
    for (int i = 0; i < length; i++) {
        if (visited[i] == 'w') {
            int sizeOfComponent = 0;
            visit(adjacencyList, i, visited, timePtr, finishedTime, &sizeOfComponent);
        }
    }

    // create G transpose
    graphNode* transposeAdjacencyList[length];
    buildAdjacencyList(hashTable, hashTableSize, transposeAdjacencyList, length, edges, true);

    // sort index array
    sortFinishedTimeArr(finishedTime, index, 0, length);

    // reset visited array and initialize outputArr to 0
    for (int i = 0; i < length; i++) {
        visited[i] = 'w';
        outputArr[i] = 0;
    }

    // visit each node in transpose adjacency list in decreasing order of finished time
    time = 30;
    int sccCounter = 0;
    for (int i = 0; i < length; i++) {
        if (visited[index[i]] == 'w') {
            sccCounter++;
            int sizeOfComponent = 0;
            visit(transposeAdjacencyList, index[i], visited, timePtr, finishedTime, &sizeOfComponent);
            outputArr[sizeOfComponent]++;
        }
    }
    return sccCounter;
}

void visit(graphNode** adjacencyList, int index, char* visited, int* timePtr, int* finishedTime, int* sizeOfComponent) {

    // increase component size
    *sizeOfComponent = *sizeOfComponent + 1;

    // start time
    *timePtr = *timePtr + 1;

    // node is marked red for visited
    visited[index] = 'r';

    // traverse linked list in adjacency list
    graphNode* tmp = adjacencyList[index];

    while (tmp) {
        if (visited[tmp->index] == 'w') {
            visit(adjacencyList, tmp->index, visited, timePtr, finishedTime, sizeOfComponent);
        }
        tmp = tmp->next;
    }

    // set node color to blue as it is visited along with all its connected nodes
    visited[index] = 'b';

    // finish time
    *timePtr = *timePtr + 1;
    finishedTime[index] = *timePtr;
}