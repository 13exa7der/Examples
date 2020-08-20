#include <iostream>
#include <vector>
#include <ctime>


using namespace std;



//��������������� ������ ��� �������� ������ ����������

void swap(vector <int> &a, int i, int j); //�������� ������� ��� ����� � �������
bool NextSet(vector <int> &a, int size); // ��������� ��� ��������� ������������


class Combination
{
public:
	vector <int> seq; // ������������������ ���������
	int first; //��������� ����� ������ ��� �����
	int second; //��������� ����� ����� ��� ������
	Combination(vector <int> seq)
	{
		this->seq = seq;
		first = second = 0;

		int temp = 0;
		for (auto i = seq.begin(); i != seq.end(); i++)  //������� first ��� ����������
		{
			if ((*i) > temp)
			{
				temp = (*i);
				first++;
			}
		}

		temp = 0;
		for (auto i = seq.rbegin(); i != seq.rend(); i++) //������� second ��� ����������
		{
			if ((*i) > temp)
			{
				temp = (*i);
				second++;
			}
		}

	}
};




class Board
{
	int size;
	int mode;
	vector <vector <int>> data; //�������� ������ ����
	vector <int> outside; // ������� ��� ��������� ��� ���� (��������� �����: ����->����->�����->���)
	vector <Combination> combinations; //������ ���������� ��� ��������� ����������
	bool decided; // ����� �� ������ ������� �� ������ ������? 

	void Fill(int row, vector <Combination> combinations); // ���������� ����
	bool Horizontal�heck(int row, vector <Combination> &newcombinations); // �������� � ������� �� ������������
	void ValueSpace(int value); //��������������� ����� ��� Print 

public:
	Board(int size, int mode);
	void Fill()
	{
		int row = 0;
		Fill(row, combinations);
	}

	void Change();
	void FillOutside();
	bool Check();
	void Game();

	void CleanData()
	{
		data.clear();
		data.resize(size);
		for (int i = 0; i < size; i++)
		{
			data[i].resize(size);
		}
	}


	bool GetDecided() { return decided; }
	void PrintResult(); //����� ��� ������ �����������
};


int main()
{

	setlocale(LC_ALL, "Rus");

	srand(time(NULL));

	for (int i = 1; i != 0;)
	{
		cout << "������� ������ ����" << endl;
		int size;
		cin >> size; //���� ������� ���� ��� ����
		cout << "�������� �����:\n1.����\n2.�������" << endl;
		int mode = 1;
		cin >> mode;
		Board board(size, mode);

		switch (mode)
		{
		case 1:
			board.Fill();
			board.Change();
			board.FillOutside();
			board.CleanData();
			board.PrintResult();
			board.Game();
			break;
		case 2:

			board.PrintResult(); // ����� ������� ����
			board.Fill();

			if (board.GetDecided())
			{
				board.PrintResult(); //���� ���� �������, ����� ������������ ����
			}
			else
			{
				cout << "��� �������" << endl;
			}
			break;
		default:
			cout << "������� �����" << endl;
			break;
		}
		cout << "��� ���? (������� 0 ��� ������, 1 ��� �����������)" << endl;
		cin >> i;
	}

	return 0;
}



void swap(vector <int> &a, int i, int j)
{
	int s = a[i];
	a[i] = a[j];
	a[j] = s;
}
bool NextSet(vector <int> &a, int size)
{
	int j = size - 2;
	while (j != -1 && a[j] >= a[j + 1]) j--;
	if (j == -1)
		return false; // ������ ������������ ���
	int k = size - 1;
	while (a[j] >= a[k]) k--;
	swap(a, j, k);
	int l = j + 1, r = size - 1; // ��������� ���������� ����� ������������������
	while (l < r)
		swap(a, l++, r--);
	return true;
}


void Board::Change()
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (rand() % 2)
			{
				vector <int> temp = data[i];
				data[i] = data[j];
				data[j] = temp;
			}
		}
	}

	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (rand() % 2)
			{
				for (int k = 0; k < size; k++)
				{
					int temp = data[k][i];
					data[k][i] = data[k][j];
					data[k][j] = temp;
				}
			}
		}
	}

}
void Board:: FillOutside()
{
	outside.clear();
	for (int i = 0; i < size; i++)
	{
		int temp = 1;
		int max = data[0][i];
		for (int j = 1; j < size; j++)
		{
			if (data[j][i] > max)
			{
				max = data[j][i];
				temp++;
			}
		}
		if (rand() % 3)
		{
			outside.push_back(temp);
		}
		else
		{
			outside.push_back(0);
		}
	}

	for (int i = 0; i < size; i++)
	{
		int temp = 1;
		int max = data[i][0];
		for (int j = 1; j < size; j++)
		{
			if (data[i][j] > max)
			{
				max = data[i][j];
				temp++;
			}
		}
		if (rand() % 3)
		{
			outside.push_back(temp);
		}
		else
		{
			outside.push_back(0);
		}
	}

	for (int i = 0; i < size; i++)
	{
		int temp = 1;
		int max = data[i][size - 1];
		for (int j = size - 2; j >= 0; j--)
		{
			if (data[i][j] > max)
			{
				max = data[i][j];
				temp++;
			}
		}
		if (rand() % 3)
		{
			outside.push_back(temp);
		}
		else
		{
			outside.push_back(0);
		}
	}

	for (int i = 0; i < size; i++)
	{
		int temp = 1;
		int max = data[size - 1][i];
		for (int j = size - 2; j >= 0; j--)
		{
			if (data[j][i] > max)
			{
				max = data[j][i];
				temp++;
			}
		}
		if (rand() % 3)
		{
			outside.push_back(temp);
		}
		else
		{
			outside.push_back(0);
		}
	}
}
bool Board::Check()
{
	int o = 0;
	bool check = 1;
	for (int i = 0; i < size; i++)
	{
		int temp = 1;
		int max = data[0][i];
		vector <int> temp_comb;
		temp_comb.push_back(data[0][i]);
		for (int j = 1; j < size; j++)
		{
			temp_comb.push_back(data[j][i]);
			if (data[j][i] > max)
			{
				max = data[j][i];
				temp++;
			}
		}
		auto it = combinations.begin();
		for (it; it != combinations.end(); it++)
		{
			if ((*it).seq == temp_comb)
			{
				break;
			}
		}
		if (it == combinations.end() || (outside[o] != 0 && temp != outside[o]))
		{
			check = 0;
		}
		o++;
	}

	for (int i = 0; i < size; i++)
	{
		int temp = 1;
		int max = data[i][0];
		vector <int> temp_comb;
		temp_comb.push_back(data[i][0]);
		for (int j = 1; j < size; j++)
		{
			temp_comb.push_back(data[i][j]);
			if (data[i][j] > max)
			{
				max = data[i][j];
				temp++;
			}
		}
		auto it = combinations.begin();
		for (it; it != combinations.end(); it++)
		{
			if ((*it).seq == temp_comb)
			{
				break;
			}
		}
		if (it == combinations.end() || (outside[o] != 0 && temp != outside[o]))
		{
			check = 0;
		}
		o++;
	}

	for (int i = 0; i < size; i++)
	{
		int temp = 1;
		int max = data[i][size - 1];
		for (int j = size - 2; j >= 0; j--)
		{
			if (data[i][j] > max)
			{
				max = data[i][j];
				temp++;
			}
		}
		if ((outside[o] != 0 && temp != outside[o]))
		{
			check = 0;
		}
		o++;
	}

	for (int i = 0; i < size; i++)
	{
		int temp = 1;
		int max = data[size - 1][i];
		for (int j = size - 2; j >= 0; j--)
		{
			if (data[j][i] > max)
			{
				max = data[j][i];
				temp++;
			}
		}
		if ((outside[o] != 0 && temp != outside[o]))
		{
			check = 0;
		}
		o++;
	}

	if (check)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void  Board::Game()
{
	cout << "��������� ������� ������, ����� ���������� � �������� ������� -1" << endl << endl;
	while (1)
	{
		int column = 0;
		int row = 0;
		int value = 0;
		do
		{
			cout << "�������� �������" << endl;
			cin >> column;
			if (column == -1) { break; }
		} while (column < 0 || column > size);
		if (column == -1) { break; }
		do
		{
			cout << "�������� ������" << endl;
			cin >> row;
			if (row == -1) { break; }
		} while (row < 0 || row > size);
		if (row == -1) { break; }
		do
		{
			cout << "�������� ��������" << endl;
			cin >> value;
			if (value == -1) { break; }
		} while (value < 0 || value > size);
		if (value == -1) { break; }

		data[row - 1][column - 1] = value;
		PrintResult();
	}
	if (Check())
	{
		cout << "���������� �� ��������" << endl;
	}
	else
	{
		cout << "� ���������, �� ���������" << endl;
	}
}

Board::Board(int size, int mode)
{
	this->size = size;
	this->mode = mode;
	decided = 0;

	data.resize(size);
	for (int i = 0; i < size; i++)
	{
		data[i].resize(size);
	}
	outside.resize(4 * size, 0);

	// ���������� ����������
	vector <int> temp;
	for (int i = 0; i < size; i++)
	{
		temp.push_back(i + 1);
	}
	combinations.push_back(temp);
	while (NextSet(temp, size))
	{
		combinations.push_back(temp);
	}


	//���������� ����� ��� ����
	if (mode == 2)
	{
		cout << "������� ��������������� ����� ��� ������ ��� ���� (�������->�����->������->������)" << endl;
		for (int i = 0; i < 4 * size; i++)
		{
			int temp;
			cin >> temp;
			outside[i] = temp;
		}
	}
	else
	{
		outside.resize(size * 4);
	}

}
bool Board::Horizontal�heck(int row, vector <Combination> &newcombinations) // �������� � �������
{
	int column = 0;
	for (int i = 0; i < size; i++) //��������� ��� ������� �������
	{
		vector <int> temp;
		for (int j = 0; j < row; j++) //���������� ������ ������� �������
		{
			temp.push_back(data[j][i]);
		}

		auto it = combinations.begin();

		vector <int> temp_for_comb; //������ ��� ��������� ��������� ��������� � �������

		for (it; it != combinations.end(); it++) //������� ���� ����������
		{
			int j = 0;
			for (j; j < row; j++)  //������������ ���������� ���� ��� �� ������������� ������ ��������� � �������
			{
				if (it->seq[j] != temp[j])
				{
					break;
				}
			}

			if (j == row) // �������� �� ���������
			{
				if ((it->first == outside[column] || outside[column] == 0) && (it->second == outside[size * 3 + column] || outside[size * 3 + column] == 0))
				{
					temp_for_comb.push_back(it->seq[row]);
				}
			}
		}



		for (int c = 0, size = newcombinations.size(); c < size; c++) //������������ ���������� ������� ���������� ��� ���������� ����
		{
			auto j = temp_for_comb.begin();
			for (j; j != temp_for_comb.end(); j++)
			{
				if (*j == newcombinations[c].seq[column])
				{
					break;
				}
			}
			if (j == temp_for_comb.end())
			{
				auto it = newcombinations.begin();
				it += c;
				newcombinations.erase(it);
				c--;
				size--;
			}
		}

		if (newcombinations.size() == 0) //���� ��� ��������� ���������� ��� ���������� ����
		{
			return 0;
		}
		column++;
	}

	return 1;
}
void Board::Fill(int row, vector <Combination> combinations) // ���������� ����
{
	if (row == size) //���� ���� ���������, ��������� ���������
	{
		int column = 0;
		for (int i = 0; i < size; i++)
		{
			vector <int> temp;
			for (int j = 0; j < size; j++)
			{
				temp.push_back(data[j][i]);
			}

			auto it = combinations.begin();

			for (it; it != combinations.end(); it++)
			{
				if (it->seq == temp)
				{
					if ((it->first == outside[column] || outside[column] == 0) && (it->second == outside[size * 3 + column] || outside[size * 3 + column] == 0))
					{
						break;
					}
					else
					{
						return;
					}
				}
			}
			column++;
			if (it == combinations.end())
			{
				return;
			}
		}
		decided = true;
		return;
	}

	for (auto i : combinations) //��������� ������� ������
	{
		if ((i.first == outside[size + row] || outside[size + row] == 0) && (i.second == outside[size * 2 + row] || outside[size * 2 + row] == 0)) //�������� ������������ ������ ��� ����
		{
			data[row] = i.seq;
			row++;


			vector <Combination> newcombinations = this->combinations;

			if (row != size)
			{
				if (!Horizontal�heck(row, newcombinations)) //�������� �����������
				{
					row--;
					continue; //���� �� ������� ����������� - ������ ������
				}
			}

			Fill(row, newcombinations); //��������� ��������� ������ ����������
			if (decided) { return; }
			row--;
		}

	}
}

void Board::PrintResult()
{
	cout << "    ";
	for (int i = 0; i < size; i++)
	{
		if (outside[i] == 0)
		{
			cout << "     ";
		}
		else
		{
			cout << " ";
			ValueSpace(outside[i]);
		}
	}
	cout << endl;

	for (int j = 0; j < size; j++)
	{
		cout << "    ";
		for (int i = 0; i < size; i++)
		{
			cout << " ----";
		}
		cout << endl;

		if (outside[size + j] == 0)
		{
			cout << "    ";
		}
		else
		{
			ValueSpace(outside[size + j]);
		}

		for (int i = 0; i < size; i++)
		{
			if (data[j][i] == 0)
			{
				cout << "|    ";
			}
			else
			{
				cout << "|";
				ValueSpace(data[j][i]);
			}
		}

		if (outside[size * 2 + j] == 0)
		{
			cout << "|";
		}
		else
		{
			cout << "|";
			ValueSpace(outside[size * 2 + j]);
		}
		cout << endl;


	}
	cout << "    ";
	for (int i = 0; i < size; i++)
	{
		cout << " ----";
	}
	cout << endl;

	cout << "    ";
	for (int i = size * 3; i < size * 4; i++)
	{
		if (outside[i] == 0)
		{
			cout << "     ";
		}
		else
		{
			cout << " ";
			ValueSpace(outside[i]);
		}
	}
	cout << endl;

}
void Board::ValueSpace(int value) //��������������� ����� ��� Print 
{
	if (value / 1000)
	{
		cout << value;
	}
	else if (value / 100)
	{
		cout << " " << value;
	}
	else if (value / 10)
	{
		cout << " " << value << " ";
	}
	else
	{
		cout << "  " << value << " ";
	}
}