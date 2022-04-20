#include "Utilities.h"
#include "HashTable.h"
#include "AdjacencyList.h"
#include "FloydWarshall.h"
#include "DFS.h"
#include <iostream>
#include <fstream>
#include <cmath>

int main(int argc, char** argv) {
    if (argc == 4) {

        // get start and end year
        int startYear = getYear(argv[3], true);
        int endYear = getYear(argv[3], false);

        // initialize vertex array
        int vertexArrSize = getVertexArrayLength(argv[2], startYear, endYear);
        int vertexArr [vertexArrSize];

        // build vertex array
        buildVertexArray(argv[2], vertexArr, startYear, endYear);

        // sort vertex array
        sortVertexArray(vertexArr, 0, vertexArrSize);

        // build hashmap
        int hashTableArrSize = getHashMapArrLength(vertexArrSize);
        hashTableEntry* hashTable[hashTableArrSize];
        buildHashTable(hashTable, vertexArr, hashTableArrSize, vertexArrSize);

        // build adjacency list
        graphNode* adjacencyList[vertexArrSize];
        int edgeCount = buildAdjacencyList(hashTable, hashTableArrSize, adjacencyList, vertexArrSize, argv[1], false);

        // initialize out-degree counter
        int outDegreeArr [vertexArrSize];
        buildOutDegreeArr(outDegreeArr, vertexArrSize, adjacencyList);

        // initialize adjacency matrix
        int** adjacencyMatrix = createMatrix(vertexArrSize);
        buildAdjacencyMatrix(adjacencyMatrix, vertexArrSize, adjacencyList);

        // find diameter with floyd warshall
        int diameter = computeDiameter(adjacencyMatrix, vertexArrSize);

        // run Kosaraju's Algorithm to find scc
        int outputArr[vertexArrSize];
        int scc = computeSCC(adjacencyList, vertexArrSize, hashTable, hashTableArrSize, argv[1], outputArr);

        // begin print to stdout
        std::cout << "Command: start-graph " << startYear << " " << endYear << '\n' << std::endl;
        std::cout << "The graph G for the years " << startYear << '-' << endYear << " has:" << std::endl;
        std::cout << '\t' << "|V| = " << vertexArrSize << " vertices" << std::endl;
        std::cout << '\t' << "|E| = " << edgeCount << " edges\n" << std::endl;

        // read commands
        std::ifstream inFile;
        inFile.open(argv[3]);
        std::string line;
        getline(inFile, line); // skip first line

        while(inFile.good()) {
            getline(inFile, line);

            if (line[0] == 'e') {
                // end graph
                return 0;
            }

            // echo command
            std::cout << "Command: " << trimWhiteSpace(line) << '\n' << std::endl;

            if (line[0] == 'o') {
                // out-degree
                float outDegree = floor(100 * (float(edgeCount)/vertexArrSize)) / 100; // compute out-degree with 2 places after decimal WITHOUT rounding
                std::cout << "The graph G has an average out-degree " << edgeCount << '/' << vertexArrSize << " = " << outDegree << ".\n" << std::endl;
                std::cout << "The out-degree distribution is:" << std::endl;
                std::cout << '\t' << "Out-degree : Number of vertices" << std::endl;
                for (int i = 0; i < vertexArrSize; i++) {
                    if (outDegreeArr[i] != 0) {
                        std::cout << '\t' << i << " : " << outDegreeArr[i] << std::endl;
                    }
                }
                std::cout << '\n';
            } else if (line[0] == 'd') {
                // diameter
                std::cout << "The graph G has diameter " << diameter << ".\n" << std::endl;

            } else if (line[0] == 's') {
                // scc
                std::cout << "The graph G has " << scc << " strongly connected components:" << std::endl;
                std::cout << "\tSize : Number" << std::endl;
                for (int i = 0; i < vertexArrSize; i++) {
                    if (outputArr[i] != 0) {
                        std::cout << '\t' << i << " : " << outputArr[i] << std::endl;
                    }
                }
            }
        }
        inFile.close();
    } else {
        std::cout << "Incorrect Usage" << std::endl;
        return -1;
    }
    return -1;
}
