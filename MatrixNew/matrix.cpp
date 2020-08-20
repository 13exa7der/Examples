
#include "Matrix.h"


Matrix::Matrix() : rows(0), columns(0)
{
	p = nullptr;
}

Matrix::Matrix(int rows, int columns) : rows(rows), columns(columns)
{
	p = new int*[rows];
	cout << "Fill Matrix:" << endl;
	for (int i = 0; i < rows; i++)
	{
		p[i] = new int[columns];
		for (int j = 0; j < columns; j++)
		{
			cin >> p[i][j];
		}
	}
}

Matrix::Matrix(const Matrix &other)
{
	rows = other.rows;
	columns = other.columns;

	p = new int*[rows];
	for (int i = 0; i < rows; i++)
	{
		p[i] = new int[columns];
		for (int j = 0; j < columns; j++)
		{
			p[i][j] = other.GetValue(i + 1, j + 1);
		}
	}
}

Matrix & Matrix::operator= (const Matrix &other)
{
	rows = other.rows;
	columns = other.columns;
	if (p != 0)
	{
		for (int i = 0; i < rows; i++)
		{
			delete[] p[i];
		}
		delete[] p;
	}
	p = new int*[rows];
	for (int i = 0; i < rows; i++)
	{
		p[i] = new int[columns];
		for (int j = 0; j < columns; j++)
		{
			p[i][j] = other.GetValue(i + 1, j + 1);
		}
	}
	return *this;
}

bool Matrix::operator== (const Matrix &other) const
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (!(p[i][j] == other.GetValue(i + 1, j + 1)))
			{
				return 0;
			}
		}
	}
	return 1;
}

Matrix Matrix::operator* (const int &value) const
{
	Matrix temp;
	temp.rows = rows;
	temp.columns = columns;
	temp.p = new int *[rows];
	for (int i = 0; i < rows; i++)
	{
		temp.p[i] = new int[columns];
		for (int j = 0; j < columns; j++)
		{
			temp.p[i][j] = p[i][j] * value;
		}
	}
	return temp;
}

Matrix Matrix::operator+ (const Matrix &other) const
{
	Matrix temp;
	temp.rows = rows;
	temp.columns = columns;
	temp.p = new int *[rows];
	for (int i = 0; i < rows; i++)
	{
		temp.p[i] = new int[columns];
		for (int j = 0; j < columns; j++)
		{
			temp.p[i][j] = this->p[i][j] + other.GetValue(i + 1, j + 1);
		}
	}
	return temp;
}

int Matrix::GetValue(int row, int column) const
{
	return p[row - 1][column - 1];
}

void Matrix::Show() const
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			cout << p[i][j] << " ";
		}
		cout << endl;
	}
}

Matrix::~Matrix()
{
	if (p != nullptr)
	{
		for (int i = 0; i < rows; i++)
		{
			delete[] p[i];
		}
		delete[] p;
	}
}

ostream& operator<<(ostream&output, const Matrix& m)
{
	if (m.GetSize() == 0)
	{
		output << "Matrix is empty\n";
	}
	else
	{
		m.Show();
	}
	return output;
}


istream& operator >>(istream &input, Matrix &m)
{

	if (m.GetSize())
	{
		for (int i = 0; i < m.rows; i++)
		{
			delete[] m.p[i];
		}
		delete[] m.p;
	}

	input >> m.rows;
	input >> m.columns;

	m.p = new int*[m.rows];
	for (int i = 0; i < m.rows; i++)
	{
		m.p[i] = new int[m.columns];
		for (int j = 0; j < m.columns; j++)
		{
			input >> m.p[i][j];
		}
	}
	return input;
}

void* Matrix::operator new(std::size_t size)
{
	cout << "\n New memory \n";
	Matrix *p = new Matrix[size];
	if (!p)
		cout << "Not memory \n";
	return p;
}

void Matrix::operator delete(void* p)
{
	cout << "Delete memory\n";
	delete[](Matrix*)p;
}

int Matrix::GetSize() const
{
	return rows * columns;
}

int * Matrix::operator [] (int value) const
{
	return p[value];
}

void Matrix::operator () (int value)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			p[i][j] *= value;
		}
	}
}

