

#include "sort.h"

using namespace std;

int *patienceSort(const int * const Arr, const int n) {
	vector<stack<int>> Lst;

	for (int i = 0; i < n; i++) {
		bool isNotPushed = true;
		for (vector<stack<int>> ::iterator iter = Lst.begin(); iter != Lst.end(); iter++) {
			if (Arr[i] < (*iter).top()) {
				(*iter).push(Arr[i]);
				isNotPushed = false;
				break;
			}
		}
		if (isNotPushed) {
			stack<int> *newStack = new stack<int>;
			newStack->push(Arr[i]);
			Lst.push_back(*newStack);
		}
	}

	int *ordArr = new int[n];

	for (int i = 0; i < n; i++) {
		int min;
		int maxInd;
		int empty = true;
		int j = 0;
		for (vector<stack<int>> ::iterator iter = Lst.begin(); iter != Lst.end(); iter++, j++) {
			if (!(*iter).empty() && (empty || (*iter).top() < min)) {
				min = (*iter).top();
				maxInd = j;
				empty = false;
			}
		}

		ordArr[i] = min;
		Lst[maxInd].pop();
	}

	return ordArr;
}

int *gnomeSort(const int * const Arr, const int n) {
	int *ordArr = new int[n];

	for (int i = 0; i < n; i++) {
		ordArr[i] = Arr[i];
	}

	int i = 1;
	while (i < n) {
		if (i == 0 || ordArr[i - 1] <= ordArr[i]) {
			i++;
		}
		else {
			int tmp = ordArr[i - 1];
			ordArr[i - 1] = ordArr[i];
			ordArr[i] = tmp;
			i--;
		}
	}

	return ordArr;
}


void qsstep(int * ordArr, const int st, const int end)
{
	int supp = ordArr[rand() % (end - st) + st];

	int l = st, r = end;
	for (; l <= r;)
	{
		while (ordArr[l] < supp)
		{
			l++;
		}
		while (ordArr[r] > supp)
		{
			r--;
		}
		if (l <= r)
		{
			swap(ordArr[l++], ordArr[r--]);
		}
	}

	if (st < r)
	{
		qsstep(ordArr, st, r);
	}
	if (end > l)
	{
		qsstep(ordArr, l, end);
	}

}

int * qs(const int * const Arr, const int n)
{
	int *ordArr = new int[n];

	for (int i = 0; i < n; i++) {
		ordArr[i] = Arr[i];
	}

	qsstep(ordArr, 0, n - 1);


	return ordArr;
}

int * sortcomb(const int * const Arr, int n)
{
	int *ordArr = new int[n];

	for (int i = 0; i < n; i++) {
		ordArr[i] = Arr[i];
	}

	int temp, k;
	int s = n;

	while (n > 1) 
	{
		s *= 0.8;

		if (s < 1) s = 1;
		k = 0;
		for (int i = 0; i + s < n; i++)
		{
			if (ordArr[i]> ordArr[i + s])
			{
				temp = ordArr[i];
				ordArr[i] = ordArr[i + s];
				ordArr[i + s] = temp;
				k = i;
			}
		}
		if (s == 1)
		{
			n = k + 1;
		}
	}

	return ordArr;
}

