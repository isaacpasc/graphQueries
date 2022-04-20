//
// Created by cse310 on 4/17/22.
//

#ifndef P3_UTILITIES_H
#define P3_UTILITIES_H
#include <string>
#include "defns.h"
int getYear(std::string, bool);
int getVertexArrayLength(std::string, int, int);
void buildVertexArray(std::string, int*, int, int);
void sortVertexArray(int*, int, int);
void merge(int*, int, int, int);
int getIntFromString(std::string);
bool testForPrime(int);
std::string trimWhiteSpace(std::string);
void buildOutDegreeArr(int*, int, graphNode**);
void mergeFinishedTime(int*, int*, int, int, int);
void sortFinishedTimeArr(int*, int*, int, int);
#endif //P3_UTILITIES_H
