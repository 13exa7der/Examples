#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <string>


using namespace std;


bool Check(vector <vector <pair <vector<char>, bool>>> &sudoky)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (sudoky[i][j].first.size() == 1 && sudoky[i][j].second == 0)
			{
				for (int k = 0; k < 9; k++)
				{
					if (k != j)
					{
						for (int z = 0; z < sudoky[i][k].first.size(); z++)
						{
							if (sudoky[i][k].first[z] == sudoky[i][j].first[0])
							{
								auto it = sudoky[i][k].first.begin();
								it += z;
								sudoky[i][k].first.erase(it);
								if (sudoky[i][k].first.size() == 0)
								{
									return 0;
								}
								break;
							}
						}
					}
				}

				for (int k = 0; k < 9; k++)
				{
					if (k != i)
					{
						for (int z = 0; z < sudoky[k][j].first.size(); z++)
						{
							if (sudoky[k][j].first[z] == sudoky[i][j].first[0])
							{
								auto it = sudoky[k][j].first.begin();
								it += z;
								sudoky[k][j].first.erase(it);
								if (sudoky[k][j].first.size() == 0)
								{
									return 0;
								}
								break;
							}
						}
					}
				}

				for (int k = (i / 3) * 3; k < (i / 3) * 3 + 3; k++)
				{
					for (int d = (j / 3) * 3; d < (j / 3) * 3 + 3; d++)
					{
						if (k != i || d != j)
						{
							for (int z = 0; z < sudoky[k][d].first.size(); z++)
							{
								if (sudoky[k][d].first[z] == sudoky[i][j].first[0])
								{
									auto it = sudoky[k][d].first.begin();
									it += z;
									sudoky[k][d].first.erase(it);
									if (sudoky[k][d].first.size() == 0)
									{
										return 0;
									}
									break;
								}
							}
						}
					}
				}


				sudoky[i][j].second = 1;
				i = -1;
				break;
			}
		}

	}
	return 1;
}

bool Work(vector <vector <pair <vector<char>, bool>>> &sudoky, vector <vector <pair <vector<char>, bool>>> ssudoky)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (sudoky[i][j].first.size() != 1)
			{
				for (int k = 0; k < sudoky[i][j].first.size(); k++)
				{
					ssudoky[i][j].first = vector <char>{ sudoky[i][j].first[k] };
					vector <vector <pair <vector<char>, bool>>> copy = ssudoky;
					if (Check(copy))
					{
						if (Work(copy, copy))
						{
							sudoky = copy;
							return 1;
						}
					}

				}
				return 0;
			}
		}
	}
	return 1;
}




int main()
{
	const int SIZE = 9;
	vector <vector <pair <vector<char>, bool>>> sudoky;
	vector <char> allvar{ '1', '2', '3', '4', '5', '6', '7', '8', '9' };


	for (int i = 0; i < SIZE; i++)
	{
		vector <pair <vector <char>, bool>> row;
		for (int j = 0; j < SIZE; j++)
		{
			char temp;
			cin >> temp;
			if (temp == '_')
			{
				row.push_back(pair <vector <char>, bool>(allvar, 0));

			}
			else
			{
				row.push_back(pair <vector <char>, bool>(vector<char> {temp}, 0));
			}
		}
		sudoky.push_back(row);
	}

	Check(sudoky);
	if (Work(sudoky, sudoky))
	{
		for (auto i : sudoky)
		{
			for (auto j : i)
			{
				cout << j.first[0] << " ";
			}
			cout << endl;
		}
	}
	else
	{
		cout << "No solutions" << endl;
	}



	return 0;
}