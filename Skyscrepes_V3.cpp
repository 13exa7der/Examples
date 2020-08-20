#include <iostream>
#include <vector>
#include <ctime>


using namespace std;



//вспомогательные методы для создания класса комбинаций

void swap(vector <int> &a, int i, int j); //поменять местами два числа в векторе
bool NextSet(vector <int> &a, int size); // составить все возможные перестановки


class Combination
{
public:
	vector <int> seq; // последовательность элементов
	int first; //элементов видно сверху или слева
	int second; //элементов видно снизу или справа
	Combination(vector <int> seq)
	{
		this->seq = seq;
		first = second = 0;

		int temp = 0;
		for (auto i = seq.begin(); i != seq.end(); i++)  //подсчет first для комбинации
		{
			if ((*i) > temp)
			{
				temp = (*i);
				first++;
			}
		}

		temp = 0;
		for (auto i = seq.rbegin(); i != seq.rend(); i++) //подсчет second для комбинации
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
	vector <vector <int>> data; //массивых данных поля
	vector <int> outside; // массивы для элементов вне поля (заполнять нужно: верх->лево->право->низ)
	vector <Combination> combinations; //вектор содержащий все возможные комбинации
	bool decided; // ответ на вопрос удалось ли решить задачу? 

	void Fill(int row, vector <Combination> combinations); // заполнение поля
	bool HorizontalСheck(int row, vector <Combination> &newcombinations); // проверка в столбце на соответствие
	void ValueSpace(int value); //вспомогательный метод для Print 

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
	void PrintResult(); //сетка для вывода результатов
};


int main()
{

	setlocale(LC_ALL, "Rus");

	srand(time(NULL));

	for (int i = 1; i != 0;)
	{
		cout << "Введите размер поля" << endl;
		int size;
		cin >> size; //ввод размера поля для игры
		cout << "Выберите режим:\n1.Игра\n2.Решение" << endl;
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

			board.PrintResult(); // вывод пустого поля
			board.Fill();

			if (board.GetDecided())
			{
				board.PrintResult(); //если есть решение, вывод заполненного поля
			}
			else
			{
				cout << "Нет решения" << endl;
			}
			break;
		default:
			cout << "Неверый выбор" << endl;
			break;
		}
		cout << "Ещё раз? (нажмите 0 для выхода, 1 для продолжения)" << endl;
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
		return false; // больше перестановок нет
	int k = size - 1;
	while (a[j] >= a[k]) k--;
	swap(a, j, k);
	int l = j + 1, r = size - 1; // сортируем оставшуюся часть последовательности
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
	cout << "Начинайте вводить данные, чтобы приступить к проверке введите -1" << endl << endl;
	while (1)
	{
		int column = 0;
		int row = 0;
		int value = 0;
		do
		{
			cout << "Выберите столбец" << endl;
			cin >> column;
			if (column == -1) { break; }
		} while (column < 0 || column > size);
		if (column == -1) { break; }
		do
		{
			cout << "Выберите строку" << endl;
			cin >> row;
			if (row == -1) { break; }
		} while (row < 0 || row > size);
		if (row == -1) { break; }
		do
		{
			cout << "Выберите значение" << endl;
			cin >> value;
			if (value == -1) { break; }
		} while (value < 0 || value > size);
		if (value == -1) { break; }

		data[row - 1][column - 1] = value;
		PrintResult();
	}
	if (Check())
	{
		cout << "Поздравляю Вы победили" << endl;
	}
	else
	{
		cout << "К сожалению, Вы проиграли" << endl;
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

	// заполнение комбинаций
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


	//заполнение чисел вне поля
	if (mode == 2)
	{
		cout << "Введите последовательно числа для клеток вне поля (верхние->левые->правые->нижние)" << endl;
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
bool Board::HorizontalСheck(int row, vector <Combination> &newcombinations) // проверка в столбце
{
	int column = 0;
	for (int i = 0; i < size; i++) //выполняем для каждого столбца
	{
		vector <int> temp;
		for (int j = 0; j < row; j++) //записываем начало каждого столбца
		{
			temp.push_back(data[j][i]);
		}

		auto it = combinations.begin();

		vector <int> temp_for_comb; //массив для возможных следующий элементов в столбце

		for (it; it != combinations.end(); it++) //перебор всех комбинаций
		{
			int j = 0;
			for (j; j < row; j++)  //отбрасывание комбинаций если они не соответствуют пермым элементам в столбце
			{
				if (it->seq[j] != temp[j])
				{
					break;
				}
			}

			if (j == row) // проверка на видимость
			{
				if ((it->first == outside[column] || outside[column] == 0) && (it->second == outside[size * 3 + column] || outside[size * 3 + column] == 0))
				{
					temp_for_comb.push_back(it->seq[row]);
				}
			}
		}



		for (int c = 0, size = newcombinations.size(); c < size; c++) //отбрасывание комбинаций которые невозможны для следующего ряда
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

		if (newcombinations.size() == 0) //если нет возможных комбинаций для следующего ряда
		{
			return 0;
		}
		column++;
	}

	return 1;
}
void Board::Fill(int row, vector <Combination> combinations) // заполнение поля
{
	if (row == size) //если поле заполнено, проверяем вертикали
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

	for (auto i : combinations) //заполняем текущую строку
	{
		if ((i.first == outside[size + row] || outside[size + row] == 0) && (i.second == outside[size * 2 + row] || outside[size * 2 + row] == 0)) //проверка соответствия числам вне поля
		{
			data[row] = i.seq;
			row++;


			vector <Combination> newcombinations = this->combinations;

			if (row != size)
			{
				if (!HorizontalСheck(row, newcombinations)) //проверям горизонтали
				{
					row--;
					continue; //если не сошлись горизонтали - меняем строку
				}
			}

			Fill(row, newcombinations); //заполняем следующую строку рекурсивно
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
void Board::ValueSpace(int value) //вспомогательный метод для Print 
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