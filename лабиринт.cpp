#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;



int Work(vector <vector <char>>& m, pair <int, int> pos)
{
	if (m[pos.second][pos.first] == '-')
	{
		return 0;
	}
	m[pos.second][pos.first] = '-';

	if (pos.first == 0 || pos.second == 0 || pos.first == m[0].size()-1 || pos.second == m.size()-1)
	{
		return 1;
	}


	if (m[pos.second + 1][pos.first] == '.')
	{
		if (Work(m, pair<int, int>(pos.first, pos.second + 1)))
		{
			return 1;
		}
	}
	if (m[pos.second - 1][pos.first] == '.')
	{
		if (Work(m, pair<int, int>(pos.first, pos.second - 1)))
		{
			return 1;
		}
	}
	if (m[pos.second][pos.first+1] == '.')
	{
		if (Work(m, pair<int, int>(pos.first+1, pos.second)))
		{
			return 1;
		}
	}
	if (m[pos.second][pos.first-1] == '.')
	{
		if (Work(m, pair<int, int>(pos.first-1, pos.second)))
		{
			return 1;
		}
	}

	return 0;
}


int main()
{
	
	int M, N;
	cin >> M >> N;
	vector <vector <char>> m;
	
	pair <int, int> pos;

	for (int i = 0; i < M; i++)
	{
		vector <char> t(N);
		for (int j = 0; j < N; j++)
		{
			char temp;
			cin >> temp;
			t[j] = temp;
			if (temp == 'x')
			{
				pos.first = j;
				pos.second = i;
			}
		}
		m.push_back(t);
	}


	if (Work(m, pos))
	{
		cout << "Yes" << endl;
	}
	else
	{
		cout << "No" << endl;
	}


	

	return 0;
}