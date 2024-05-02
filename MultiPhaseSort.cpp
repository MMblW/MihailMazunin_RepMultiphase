#include <iostream>
#include <vector>
#define lenght_mas 25

using namespace std;

template <typename T>
void print_mas(T mas)
{
	cout << mas[0];
	for (int i = 1; i < lenght_mas; i++)
	{
		cout << ' ' << mas[i];
	}
	cout << endl;
}
void natural_merge(vector<int>& vect1, vector<int>& vect2)
{
	for (int i = 0; i < vect2.size(); i++)
	{
		vect1.push_back(vect2[i]);
		for (int j = vect1.size() - 1; j > 0; j--)
		{
			if (vect1[j] < vect1[j - 1])
			{
				swap(vect1[j], vect1[j - 1]);
			}
			else
			{
				j = 0;
			}
		}
	}
}
void natural_merge_sort(int* mas)
{	
	vector <vector<int>> series;
	vector<int> new_series;
	for (int i = 0; i <= lenght_mas - 1; i++)
	{
		if (i == lenght_mas - 1)
		{
			new_series.push_back(mas[i]);
			series.push_back(new_series);
			new_series.clear();
		}
		else
		{
			new_series.push_back(mas[i]);
			if (mas[i] > mas[i + 1])
			{
				series.push_back(new_series);
				new_series.clear();
			}
		}
	}
	while (series.size() != 1)
	{
		natural_merge(series[0], series[series.size() - 1]);
		series.pop_back();
	}
	for (int i = 0; i < lenght_mas; i++)
	{
		mas[i] = series[0][i];
	}
}
pair<int, int> ideal_series(pair<int, int> last_count_series, int count_all_series)
{
	int current_num = last_count_series.first + last_count_series.second;
	if (count_all_series > current_num)
	{
		ideal_series({ last_count_series.second, current_num }, count_all_series);
	}
	else
	{
		return last_count_series;
	}
}
void series_merge(vector <vector<int>>& series_1, vector <vector<int>>& series_2, vector <vector<int>>& series_3)
{
	if (series_1.size() == 1 && series_2.size() == 0 && series_3.size() == 0)
	{
		return;
	}
	else if (series_2.size() == 1 && series_1.size() == 0 && series_3.size() == 0)
	{
		return;
	}
	else if (series_3.size() == 1 && series_1.size() == 0 && series_2.size() == 0)
	{
		return;
	}
	int i = series_1.size()-1;
	int j = series_2.size()-1;
	while (j != -1)
	{
		natural_merge(series_1[i], series_2[j]);
		series_3.push_back(series_1[i]);
		series_1.pop_back();
		series_2.pop_back();
		i--;
		j--;
	}
	series_merge(series_3, series_1, series_2);
}
void multiphase_merge_sort(int* mas)
{
	pair <int, int> ideal_pair;
	vector <int> new_series;
	vector <vector<int>> series, series_1, series_2, series_3;
	for (int i = 0; i <= lenght_mas - 1; i++)
	{
		if (i == lenght_mas - 1)
		{
			new_series.push_back(mas[i]);
			series.push_back(new_series);
			new_series.clear();
		}
		else
		{
			new_series.push_back(mas[i]);
			if (mas[i] > mas[i + 1])
			{
				series.push_back(new_series);
				new_series.clear();
			}
		}
	}
	ideal_pair = ideal_series({ 0, 1 }, series.size());
	for (int i = 0; i < ideal_pair.second; i++)
	{
		series_1.push_back(series[i]);
	}
	for (int i = 0; i < ideal_pair.first; i++)
	{
		if (series_1.size() + i + 1 > series.size())
		{
			series_2.push_back({});
		}
		else
		{
			series_2.push_back(series[series_1.size() + i]);
		}
	}
	series_merge(series_1, series_2, series_3);
	for (int i = 0; i < lenght_mas; i++)
	{
		mas[i] = series_1[0][i];
	}
}

int main()
{
	system("chcp 1251");
	int mas_multiphase_merge[] = { 178, 14, -15, -5, 23, -56, 100, -32, -4, 31, 3, 20, 0, -100, -35, -65, 75, -18, 65, 1, -6, 32, 7, -15, 5 };
	cout << "Исходный массив: ";
	print_mas(mas_multiphase_merge);
	multiphase_merge_sort(mas_multiphase_merge);
	cout << "Отсортированный массив: ";
	print_mas(mas_multiphase_merge);
	return 0;
}