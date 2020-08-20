
#include "Matrix.h"

int main()
{

	Matrix arr[3] {Matrix(3,3), Matrix(3,3)};



	cout << "Enter third matrix (rows->columns->values):" << endl;
	cin >> arr[2];

	
	cout << "Second matrix:\n" << arr[1];
	cout << "Change second matrix (rows->columns->values):" << endl;
	cin >> arr[2];


	cout << "All Matrix" << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << arr[i] << endl;
	}

	cout << "third*3:" << endl;
	(arr[2] * 3).Show();

	cout << "first+first:" << endl;
	(arr[0] + arr[0]).Show();


	Matrix *q;
	q = (Matrix*)q->operator new(1);

	cout << "Change new matrix (rows->columns->values):" << endl;
	cin >> q[0];


	cout << "New matrix:\n" << *q;
	
	q->operator delete(q);

	return 0;
}