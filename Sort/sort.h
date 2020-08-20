
#ifndef _Header_
#define _Header_

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <stack>


using namespace std;

int *patienceSort(const int * const Arr, const int n);
int *gnomeSort(const int * const Arr, const int n);
int *qs(const int * const Arr, const int n);
void qsstep(int * ordArr, const int st, const int end);
int * sortcomb(const int * const Arr, int n);

#endif