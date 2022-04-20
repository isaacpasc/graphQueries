//
// Created by cse310 on 4/20/22.
//
#include "FloydWarshall.h"

void buildAdjacencyMatrix(int** adjacencyMatrix, int length, graphNode** adjacencyList) {
    for (int i = 0; i < length; i++) {
        if (adjacencyList[i]) {
            graphNode* tmp = adjacencyList[i];
            while(tmp) {
                adjacencyMatrix[i][tmp->index] = 1;
                tmp = tmp->next;
            }
        }
    }
}
int** createMatrix(int size) {
    // initialize matrix
    int** array2D;
    array2D = new int*[size];

    for (int h = 0; h < size; h++)
    {
        array2D[h] = new int[size];

        for (int w = 0; w < size; w++)
        {
            // set all values to INF
            if (w == h) {
                array2D[h][w] = 0;
            } else {
                array2D[h][w] = INF;
            }
        }
    }

    return array2D;
}

int computeDiameter(int** adjacencyMatrix, int size) {
    int diameter = 0;
    for (int k = 0; k < size; k++) {
        // Pick all vertices as source one by one
        for (int i = 0; i < size; i++) {
            // Pick all vertices as destination for the
            // above picked source
            for (int j = 0; j < size; j++) {
                // If vertex k is on the shortest path from
                // i to j, then update the value of dist[i][j]
                if (adjacencyMatrix[i][k] + adjacencyMatrix[k][j] < adjacencyMatrix[i][j]) {
                    adjacencyMatrix[i][j] = adjacencyMatrix[i][k] + adjacencyMatrix[k][j];
                    if (adjacencyMatrix[i][j] > diameter) {
                        diameter = adjacencyMatrix[i][j];
                    }
                }
            }
        }
    }
    return diameter;
}