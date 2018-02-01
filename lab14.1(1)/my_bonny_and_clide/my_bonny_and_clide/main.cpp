#include <iostream>
#include <fstream>
#include <string>

const int MAX_BANK_COUNT = 2*10e5, MIN_BANK_COUNT = 2;
const int MAX_D = 10e8, MIN_D = 1;

using namespace std;

void ReadFirstLine(ifstream &fin, int &num1, int &num2, bool &haveError);
void ReadOtherLines(ifstream &fin, int *distances, int *money_count, bool &haveError);
void PrintMatrix(int **a, int **b, int n);
void ParseLine(string fileLine, int &firstNum, int &secondNum, bool &haveError);
void SearchSolution(int **distance_matrix, int **max_sum_matrix, int n, int dist, char *name);
void ErrorMessage(int code);

int main(int argc, char *argv[])
{
	string inputFileName = argv[1];
	ifstream fin(inputFileName);

	bool haveErrors = false;

	//обработка первой строки
	int number1 = 0, number2 = 0;
	ReadFirstLine(fin, number1, number2, haveErrors);
	int n = number1;
	int dd = number2;
	
	//обработка остальных строк
	int *pDistances = new int[n];
	int *pMoneyCount = new int[n];
	ReadOtherLines(fin, pDistances, pMoneyCount, haveErrors);
	for (int j = 0; j < n; j++)
	{
		cout << pDistances[j] <<"  "<<pMoneyCount[j]<< endl;
	}

	//создаются матрицы с расстояниями между парами банков(distance) где расстояние >= допустимого
	//и матрица общей суммы денег в паре банков
	int **distance_matrix = new int *[n];
	int **max_sum_matrix = new int *[n];

	for (int i = 0; i < n; i++)
	{
		distance_matrix[i] = new int[n];
		max_sum_matrix[i] = new int[n];
	}

	for (int i = 0; i<n; i++)
		for (int j = 0; j < n; j++)
		{
			distance_matrix[i][j] = 0;
			max_sum_matrix[i][j] = 0;
		}

	for(int i=0; i<n; i++)
		for (int j=i+1; j < n; j++)
		{
			if (pDistances[j] - pDistances[i] >= dd)
			{
				distance_matrix[i][j] = pDistances[j] - pDistances[i];
				max_sum_matrix[i][j] = pMoneyCount[i] + pMoneyCount[j];
			}
		}

	delete pDistances;
	delete pMoneyCount;

	//поиск решения
	SearchSolution(distance_matrix, max_sum_matrix, n, dd, argv[2]);

	//печать матриц денег и расстояний на экран
	PrintMatrix(distance_matrix, max_sum_matrix, n);
	
	system("pause");
	return 0;
}

void ReadFirstLine(ifstream &fin, int &num1, int &num2, bool &haveError)
{
	string line = "";
	if (getline(fin, line))
		ParseLine(line, num1, num2, haveError);
	else
	{
		//ErrorMessage(1);
		//haveError = true;
	}
}

void ReadOtherLines(ifstream &fin, int *distances, int *money_count, bool &haveError)
{
	bool haveLine = false;
	int k = 0;
	int num1 = 0, num2 = 0;

	do
	{
		string line = "";

		if (getline(fin, line))
		{
			haveLine = true;
			ParseLine(line, num1, num2, haveError);
			distances[k] = num1;
			money_count[k] = num2;
			k++;
		}
		else
		{
			haveLine = false;
			//haveError = true;
			//ErrorMessage(1);
			break;
		}

	} while (haveLine);
	
	fin.close();
}


void PrintMatrix(int **a, int **b, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << a[i][j] << ' ';
		cout << endl;
	}

	cout << endl;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << b[i][j] << ' ';
		cout << endl;
	}
}

void ParseLine(string fileLine, int &firstNum, int &secondNum, bool &haveError)
{
	bool takeX = true, takeW = false;
	string firstNumStr = "", secondNumStr = "";

	for (int i = 0; i < fileLine.size(); i++)
	{
		if (fileLine[i] == ' ')
		{
			if (firstNumStr != "")
			{
				takeX = false;
				takeW = true;
				i++;
			}
		}
		
		if (takeX == true)
		{
			if (isdigit(fileLine[i]))
			{
				firstNumStr += fileLine[i];
			}
			else
				haveError = true;
		}
		else if (takeW == true)
		{
			if (isdigit(fileLine[i]))
				secondNumStr += fileLine[i];
			else
				haveError = true;
		}
	}
		
	firstNum = atoi(firstNumStr.c_str());
	firstNumStr = "";
	secondNum = atoi(secondNumStr.c_str());
	secondNumStr = "";
}

void SearchSolution(int **distance_matrix, int **max_sum_matrix, int n, int dist, char *name)
{
	int max_i = 0, max_j=0;
	int max_sum = 0;

	//поиск максимальной суммы денег и пары банков
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			if (max_sum_matrix[i][j]>max_sum)
			{
				max_sum = max_sum_matrix[i][j];
				max_i = i;
				max_j = j;
			}
	}

	//результат работы программы: макс сумма и пара банков
	int bank1 = 0, bank2 = 0;
	string outputFileName = name;
	ofstream fout(outputFileName, ios_base::out);

	if (distance_matrix[max_i][max_j] < dist)
	{
		bank1 = bank2 = -1;
	}
	else
	{
		bank1 = max_i+1;
		bank2 = max_j+1;
	}
	if (max_sum>0)
		fout << max_sum<<endl;
	fout << bank1 << "  " << bank2 << endl;

	fout.close();
}

void ErrorMessage(int code)
{
	switch (code)
	{
		case 1:
		{
			cout << "File don't have the lines" << endl;
			break;
		}
		case 2:
		{	
			cout << "Incorrect file structure" << endl;
			break;
		}
		case 3:
		{
			cout << "Input file error" << endl;
			break;
		}
		case 4:
		{
			cout << "Output file error" << endl;
			break;
		}
	}
}