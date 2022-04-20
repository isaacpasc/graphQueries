//
// Created by cse310 on 4/17/22.
//

#include <fstream>
#include <sstream>
#include <cmath>
#include "Utilities.h"

int getYear(std::string commands, bool isStartYear) {
    std::ifstream inFile;
    std::string year;
    inFile.open(commands);
    std::string line;

    getline(inFile, line);
    if (isStartYear) {
        year += line[12];
        year += line[13];
        year += line[14];
        year += line[15];
    } else {
        year += line[17];
        year += line[18];
        year += line[19];
        year += line[20];
    }

    inFile.close();
    return getIntFromString(year);
}

int getVertexArrayLength(std::string dates, int startYear, int endYear) {
    std::ifstream inFile;
    int vertexCount = 0;
    inFile.open(dates);
    std::string line;

    while(inFile.good()) {
        getline(inFile, line);
        std::string year;
        bool yearStarts = false;
        for (int i = 0; i < line.length(); i++) {
            if (i == line.length() - 1) {
                year += line[i];
                if (getIntFromString(year) >= startYear && getIntFromString(year) <= endYear) {
                    vertexCount++;
                }
                continue;
            }
            if (line[i] == '\t') {
                yearStarts = true;
                year = "";
                continue;
            }
            if (yearStarts) {
                year += line[i];
            }
        }
    }

    inFile.close();
    return vertexCount;
}

void buildVertexArray(std::string dates, int* vertexArr, int startYear, int endYear) {
    std::ifstream inFile;
    inFile.open(dates);
    std::string line;
    int index = 0;
    while(inFile.good()) {
        getline(inFile, line);
        std::string year;
        std::string id;
        bool isYear = false;
        for(int i = 0; i < line.length(); i++) {
            if (i == line.length() - 1) {
                year += line[i];
                if (getIntFromString(year) >= startYear && getIntFromString(year) <= endYear) {
                    vertexArr[index] = getIntFromString(id);
                }
                year = "";
                id = "";
                index++;
                continue;
            }
            if (line[i] == '\t') {
                isYear = true;
                continue;
            }
            if (isYear) {
                year += line[i];
            } else {
                id += line[i];
            }
        }
    }
    inFile.close();
}

int getIntFromString(std::string str) {
    std::stringstream ss(str);
    std::string tmp;
    while (ss.good()) {
        std::string substr;
        getline(ss, substr, ',');
        tmp += substr;
    }
    int num;
    std::stringstream n;
    n << tmp;
    n >> num;
    return num;
}

void merge(int* vertexArr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = vertexArr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = vertexArr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            vertexArr[k] = L[i];
            i++;
        }
        else {
            vertexArr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        vertexArr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        vertexArr[k] = R[j];
        j++;
        k++;
    }
}

void sortVertexArray(int* vertexArr, int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;

        sortVertexArray(vertexArr, l, m);
        sortVertexArray(vertexArr, m + 1, r);

        merge(vertexArr, l, m, r);
    }
}

bool testForPrime(int val) {
    int limit, factor = 2;

    limit = (long)( sqrtf( (float) val ) + 0.5f );
    while( (factor <= limit) && (val % factor) )
        factor++;

    return( factor > limit );
}

std::string trimWhiteSpace(std::string command) {
    std::string result;
    for (int i = 0; i < command.length(); i++) {
        int charAsciiVal = int(command[i]);
        if (charAsciiVal < 65 && charAsciiVal != 45) {
            break;
        }
        result += command[i];
    }
    return result;
}

void buildOutDegreeArr(int* outDegreeArr, int length, graphNode** adjacencyList) {
    for (int i = 0; i < length; i++) {
        outDegreeArr[i] = 0;
    }
    for (int i = 0; i < length; i++) {
        graphNode* tmp = adjacencyList[i];
        int edgeCounter = 0;
        if (!tmp) {
            outDegreeArr[edgeCounter]++;
        }
        while(tmp) {
            edgeCounter++;
            if (!tmp->next) {
                outDegreeArr[edgeCounter]++;
                break;
            }
            tmp = tmp->next;
        }
    }
}

void mergeFinishedTime(int* finishedTimeArr, int* indexArr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    int Li[n1], Ri[n2];

    for (i = 0; i < n1; i++) {
        L[i] = finishedTimeArr[l + i];
        Li[i] = indexArr[l + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = finishedTimeArr[m + 1 + j];
        Ri[j] = indexArr[m + 1 + j];
    }

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] >= R[j]) {
            finishedTimeArr[k] = L[i];
            indexArr[k] = Li[i];
            i++;
        }
        else {
            finishedTimeArr[k] = R[j];
            indexArr[k] = Ri[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        finishedTimeArr[k] = L[i];
        indexArr[k] = Li[i];
        i++;
        k++;
    }

    while (j < n2) {
        finishedTimeArr[k] = R[j];
        indexArr[k] = Ri[j];
        j++;
        k++;
    }
}

void sortFinishedTimeArr(int* finishedTimeArr, int* indexArr, int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;

        sortFinishedTimeArr(finishedTimeArr, indexArr, l, m);
        sortFinishedTimeArr(finishedTimeArr, indexArr, m + 1, r);

        mergeFinishedTime(finishedTimeArr, indexArr, l, m, r);
    }
}