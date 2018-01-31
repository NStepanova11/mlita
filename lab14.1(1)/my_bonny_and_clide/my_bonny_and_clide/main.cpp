#include <iostream>
#include <fstream>
#include <string>

const int BANK_COUNT = 6;
const int D = 3;

using namespace std;

void PrintMatrix(int a[BANK_COUNT][BANK_COUNT], int b[BANK_COUNT][BANK_COUNT]);
void ParseLine(int lineCount, string fileLine, int &firstNum, int &secondNum);

int main(int argc, char *argv[])
{
	int distance[BANK_COUNT] = { 0 };//{ 1,3,4,6,10,11 };
	int money_count[BANK_COUNT] = { 0 };//{ 1,5,8,4,3,2 };
	int distance_matrix[BANK_COUNT][BANK_COUNT] = { 0 };
	int max_sum_matrix[BANK_COUNT][BANK_COUNT] = { 0 };

	//чтение данных из файла
	string fileName=argv[1];
	ifstream fin(fileName);
	
	bool haveLine = false;
	string line="";
	int lineCount = 0;
	int n = 0, dd = 0, k = 0;

	do
	{
		int num1 = 0, num2 = 0;
		if (getline(fin, line))
		{
			haveLine = true;
			lineCount++;
			ParseLine(lineCount, line, num1, num2);
			if (lineCount == 1)
			{
				n = num1;
				dd = num2;
			}
			else
			{
				distance[k] = num1;
				money_count[k] = num2;
				k++;
			}
		}
		else
			haveLine = false;
	} while (haveLine);

	
	//создаются матрицы с расстояниями между парами банков(distance) где расстояние >= допустимого
	//и матрица общей суммы денег в паре банков
	for(int i=0; i<BANK_COUNT; i++)
		for (int j=i+1; j < BANK_COUNT; j++)
		{
			if (distance[j] - distance[i] >= D)
			{
				distance_matrix[i][j] = distance[j] - distance[i];
				max_sum_matrix[i][j] = money_count[i] + money_count[j];
			}
		}

	//печать матриц денег и расстояний на экран
	PrintMatrix(distance_matrix, max_sum_matrix);

	int max_i = 0, max_j=0;
	int max_sum = 0;

	//поиск максимальной суммы денег и пары банков
	for (int i = 0; i < BANK_COUNT; i++)
	{
		for (int j = 0; j < BANK_COUNT; j++)
			if (max_sum_matrix[i][j]>max_sum)
			{
				max_sum = max_sum_matrix[i][j];
				max_i = i;
				max_j = j;
			}
	}

	int bank1 = 0, bank2 = 0;
	if (distance_matrix[max_i][max_j] < D)
	{
		bank1 = bank2 = -1;
	}
	else
	{
		bank1 = max_i+1;
		bank2 = max_j+1;
	}
	cout << max_sum_matrix[max_i][max_j] << endl;
	cout << bank1 << "  "<< bank2 << endl;

	system("pause");
	return 0;
}

void PrintMatrix(int a[BANK_COUNT][BANK_COUNT], int b[BANK_COUNT][BANK_COUNT])
{
	for (int i = 0; i < BANK_COUNT; i++)
	{
		for (int j = 0; j < BANK_COUNT; j++)
			cout << a[i][j] << ' ';
		cout << endl;
	}

	cout << endl;

	for (int i = 0; i < BANK_COUNT; i++)
	{
		for (int j = 0; j < BANK_COUNT; j++)
			cout << b[i][j] << ' ';
		cout << endl;
	}
}

void ParseLine(int lineCount, string fileLine, int &firstNum, int &secondNum)
{
	bool takeX = true, takeW = false;
	string firstNumStr = "", secondNumStr = "";

	for (int i = 0; i < fileLine.size(); i++)
	{
		if (fileLine[i] == ' ')
		{
			takeX = false;
			takeW = true;
			i++;
		}

		if (takeX==true)
		{
			firstNumStr += fileLine[i];
		}
		else if (takeW==true)
		{
			secondNumStr += fileLine[i];
		}
	}

//	if (lineCount == 1)
	{
		//что будет если строка первая
		firstNum = atoi(firstNumStr.c_str());
		secondNum = atoi(secondNumStr.c_str());
	}

}