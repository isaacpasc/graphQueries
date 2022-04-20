//
// Created by cse310 on 4/18/22.
//
#include <fstream>
#include "AdjacencyList.h"
#include "Utilities.h"
#include "HashTable.h"

int buildAdjacencyList(hashTableEntry** hashTable, int hashTableSize, graphNode** adjacencyList, int adjacencyListSize, std::string edges, bool isTranspose) {
    for (int i = 0; i < adjacencyListSize; i++) {
        adjacencyList[i] = nullptr;
    }
    int edgeCount = 0;
    std::ifstream inFile;
    inFile.open(edges);
    std::string line;
    std::string startEdge;
    std::string endEdge;
    while(inFile.good()) {
        getline(inFile, line);
        bool isStart = true;
        for(int i = 0; i < line.length(); i++) {
            if (i == line.length() - 1) {
                endEdge += line[i];
                hashTableEntry* startEdgeHash;
                hashTableEntry* endEdgeHash;
                if (isTranspose) {
                    startEdgeHash = findEntry(hashTable, getIntFromString(endEdge), hashTableSize);
                    endEdgeHash = findEntry(hashTable, getIntFromString(startEdge), hashTableSize);
                } else {
                    startEdgeHash = findEntry(hashTable, getIntFromString(startEdge), hashTableSize);
                    endEdgeHash = findEntry(hashTable, getIntFromString(endEdge), hashTableSize);
                }
                if (startEdgeHash && endEdgeHash) {
                    edgeCount++;
                    if (!adjacencyList[startEdgeHash->mapping]) {
                        // insert first node
                        graphNode* new_node = (struct graphNode*) malloc(sizeof(struct graphNode));
                        new_node->next = nullptr;
                        new_node->index = endEdgeHash->mapping;
                        adjacencyList[startEdgeHash->mapping] = new_node;
                    } else if (!adjacencyList[startEdgeHash->mapping]->next) {
                        if (adjacencyList[startEdgeHash->mapping]->index > endEdgeHash->mapping) {
                            // insert at head
                            graphNode* new_node = (struct graphNode*) malloc(sizeof(struct graphNode));
                            new_node->next = adjacencyList[startEdgeHash->mapping];
                            new_node->index = endEdgeHash->mapping;
                            adjacencyList[startEdgeHash->mapping] = new_node;
                        } else {
                            // insert after head
                            graphNode* new_node = (struct graphNode*) malloc(sizeof(struct graphNode));
                            new_node->next = nullptr;
                            new_node->index = endEdgeHash->mapping;
                            adjacencyList[startEdgeHash->mapping]->next = new_node;
                        }
                    } else {
                        // insert in order of index
                        graphNode* last = adjacencyList[startEdgeHash->mapping];
                        bool didInsert = false;
                        while (last->next) {
                            if (endEdgeHash->mapping <= last->next->index) {
                                // next node is greater, insert new node here
                                graphNode* new_node = (struct graphNode*) malloc(sizeof(struct graphNode));
                                new_node->next = last->next;
                                new_node->index = endEdgeHash->mapping;
                                last->next = new_node;
                                didInsert = true;
                                break;
                            }
                            last = last->next;
                        }
                        if (!didInsert) {
                            // append to linked list
                            graphNode* new_node = (struct graphNode*) malloc(sizeof(struct graphNode));
                            new_node->next = nullptr;
                            new_node->index = endEdgeHash->mapping;
                            last->next = new_node;
                        }
                    }
                }
                endEdge = "";
                startEdge = "";
                continue;
            }
            if (line[i] == '\t') {
                isStart = false;
                continue;
            }
            if (isStart) {
                startEdge += line[i];
            } else {
                endEdge += line[i];
            }
        }
    }
    inFile.close();
    return edgeCount;
}


