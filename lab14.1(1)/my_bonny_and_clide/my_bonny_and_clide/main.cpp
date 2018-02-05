/*
14.1. Бонни и Клайд (6)
Бонни и Клайд задумали ограбить в некотором городе два банка. Все N банков в этом городе находятся на его главной улице. Для каждого i-го банка известны расстояние от начала улицы Xi и имеющаяся сумма денег Wi. Чтобы было меньше шума, Бонни и Клайд собираются выбрать такую пару банков, чтобы расстояние между ними было не менее d. Вместе с тем они хотят, чтобы сумма денег в обоих банках оказалась максимальной. Как это сделать?
Ввод из файла INPUT.TXT. В первой строке указаны  через пробел целые значения N и d - число банков и минимально допустимое расстояние между парой банков, которые можно грабить (2 ≤ N ≤ 2•105, 1 ≤ d ≤ 108). В каждой из следующих N строк содержится через пробел два целых числа Xi и Wi - расстояние от начала улицы до банка и имеющаяся в банке наличность (1 ≤ Xi, Wi ≤ 108). Строки следуют в порядке увеличения расстояний Xi.
Вывод в файл OUTPUT.TXT. В первой строке вывести сумму денег в выбранных банках. Во второй строке вывести через пробел в любом порядке номера двух требуемых банков. Если имеется несколько решений, вывести любое из них. Если решений нет, вывести строку -1 -1.

Степанова Н ПС-22

Visual studio 2015
*/

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

const int MAX_BANK_COUNT = 2*pow(10, 5), MIN_BANK_COUNT = 2;
const int MAX_D = pow(10,8), MIN_D = 1;

using namespace std;

enum { empty_err = 1, struct_err, content_err, param_err=5, find_err };


void ReadFirstLine(ifstream &fin, int &num1, int &num2, bool &haveError, string fileName, int &lineCount);
void ReadOtherLines(ifstream &fin, int *distances, int *money_count, bool &haveError, int n, string fileName, int &lineCount);
void PrintMatrix(int **a, int **b, int n);
void ParseLine(int &firstNum, int &secondNum, string fileLine, bool &haveError, int lineCount);
void SearchSolution(int **distance_matrix, int **max_sum_matrix, int n, int dist, char *name);
void ErrorMessage(int code, string filename);
void ValueVerification(int resultNum1, int resultNum2, int &firstNum, int &secondNum, bool &haveError, int lineCount);

int main(int argc, char *argv[])
{
	bool haveErrors = false;
	if (argc == 3)
	{
		string inputFileName = argv[1];
		ifstream fin(inputFileName);
		if (fin.is_open())
		{
			//обработка первой строки
			int number1 = 0, number2 = 0, lineCount = 0;
			ReadFirstLine(fin, number1, number2, haveErrors, inputFileName, lineCount);
			if (haveErrors == false)
			{
				int n = number1;
				int dd = number2;

				//обработка остальных строк
				int *pDistances = new int[n];
				int *pMoneyCount = new int[n];
				ReadOtherLines(fin, pDistances, pMoneyCount, haveErrors, n, inputFileName, lineCount);
				if (haveErrors == false)
				{
				/*	for (int j = 0; j < n; j++)
					{
						cout << pDistances[j] << "  " << pMoneyCount[j] << endl;
					}
				*/

					//создаются матрицы с расстояниями между парами банков(distance) где расстояние >= допустимого
					//и матрица общей суммы денег в паре банков
					int **distance_matrix = new int *[n];
					int **max_sum_matrix = new int *[n];

					for (int i = 0; i < n; i++)
					{
						distance_matrix[i] = new int[n];
						max_sum_matrix[i] = new int[n];
					}

					for (int i = 0; i < n; i++)
						for (int j = 0; j < n; j++)
						{
							distance_matrix[i][j] = 0;
							max_sum_matrix[i][j] = 0;
						}

					for (int i = 0; i < n; i++)
						for (int j = i + 1; j < n; j++)
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
					//PrintMatrix(distance_matrix, max_sum_matrix, n);
				}
			}
		}
		else
			ErrorMessage(find_err, inputFileName);
	}
	else
		ErrorMessage(param_err, "");

	system("pause");
	return 0;
}

void ReadFirstLine(ifstream &fin, int &num1, int &num2, bool &haveError, string fileName, int &lineCount)
{
	string line = "";
	string firstNumStr = "", secondNumStr = "";

	if (getline(fin, line))
	{
		lineCount++;
		ParseLine(num1, num2, line, haveError, lineCount);
	}
	else
	{
		ErrorMessage(empty_err, fileName);
		haveError = true;
	}
}

void ReadOtherLines(ifstream &fin, int *distances, int *money_count, bool &haveError, int n, string fileName, int &lineCount)
{
	int k = 0;//, lineCount = 0;
	int num1 = 0, num2 = 0;
	string firstNumStr = "", secondNumStr = "";
	do
	{
		string line = "";

		if (lineCount<=n)
		{
			if (getline(fin, line))
			{
				lineCount++;
				ParseLine(num1, num2, line, haveError, lineCount);
				if (haveError == false)
				{
					distances[k] = num1;
					money_count[k] = num2;
					k++;
				}
				else break;
			}
			else
			{
				haveError = true;
				ErrorMessage(struct_err, fileName);
				break;
			}
		}
	} while ((lineCount<=n) && (haveError==false));
	
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

void ParseLine(int &firstNum, int &secondNum, string fileLine, bool &haveError, int lineCount)
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
			else
			{
				haveError = true;
				ErrorMessage(struct_err, "");
				break;
			}
		}

		if (takeX == true)
		{
			if (isdigit(fileLine[i]))
			{
				firstNumStr += fileLine[i];
			}
			else
			{
				haveError = true;
				ErrorMessage(content_err, "");
				break;
			}
		}
		else if (takeW == true)
		{
			if (isdigit(fileLine[i]))
				secondNumStr += fileLine[i];
			else
			{
				haveError = true;
				ErrorMessage(content_err, "");
				break;
			}
		}

	}

	int resultNum1 = atoi(firstNumStr.c_str());
	int resultNum2 = atoi(secondNumStr.c_str());

	ValueVerification(resultNum1, resultNum2, firstNum, secondNum, haveError, lineCount);
	firstNumStr = "";
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

	if (fout.is_open())
	{
	/*	if (distance_matrix[max_i][max_j] < dist)
		{
			bank1 = bank2 = -1;
		}
		else*/
		if (distance_matrix[max_i][max_j] >= dist)
		{
			bank1 = max_i + 1;
			bank2 = max_j + 1;
		}
		else 
			bank1 = bank2 = -1;
		if (max_sum > 0)
			fout << max_sum << endl;
		fout << bank1 << "  " << bank2 << endl;

		fout.close();
	}
	else
		ErrorMessage(content_err, name);
}

void ErrorMessage(int code, string fileName)
{
	switch (code)
	{
		case 1:
		{
			cout << "File is empty: " << fileName << endl;
			break;
		}
		case 2:
		{	
			cout << "Incorrect file structure: " <<fileName<< endl;
			break;
		}
		case 3:
		{
			cout << "Incorrect file content" << fileName << endl;
			break;
		}
		case 5:
		{
			cout << "Not enough parameters" << endl;
			break;
		}
		case 6:
		{
			cout << "File not found: "<<fileName << endl;
			break;
		}
	}
}

void ValueVerification(int resultNum1, int resultNum2, int &firstNum, int &secondNum, bool &haveError, int lineCount)
{
	if (lineCount == 1)
	{
		if ((resultNum1 >= 2) && (resultNum1 <= MAX_BANK_COUNT) && (resultNum2 >= 1) && (resultNum2 <= MAX_D))
		{
			firstNum = resultNum1;
			secondNum = resultNum2;
		}
		else
		{
			ErrorMessage(content_err, "");
			haveError = true;
		}
	}
	else
	{
		if ((resultNum1 > 0) && (resultNum2 <= pow(10, 8)))
		{
			firstNum = resultNum1;
			secondNum = resultNum2;
		}
		else
		{
			ErrorMessage(content_err, "");
			haveError = true;
		}
	}
}