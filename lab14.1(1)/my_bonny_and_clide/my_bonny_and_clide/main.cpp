/*
14.1. Бонни и Клайд (6)
Бонни и Клайд задумали ограбить в некотором городе два банка. Все N банков в этом городе находятся на его главной улице.
Для каждого i-го банка известны расстояние от начала улицы Xi и имеющаяся сумма денег Wi. Чтобы было меньше шума, Бонни 
и Клайд собираются выбрать такую пару банков, чтобы расстояние между ними было не менее d. Вместе с тем они хотят, чтобы
сумма денег в обоих банках оказалась максимальной. Как это сделать?
Ввод из файла INPUT.TXT. В первой строке указаны  через пробел целые значения N и d - число банков и минимально допустимое
расстояние между парой банков, которые можно грабить (2 ≤ N ≤ 2•105, 1 ≤ d ≤ 108). В каждой из следующих N строк содержится 
через пробел два целых числа Xi и Wi - расстояние от начала улицы до банка и имеющаяся в банке наличность (1 ≤ Xi, Wi ≤ 108).
Строки следуют в порядке увеличения расстояний Xi.
Вывод в файл OUTPUT.TXT. В первой строке вывести сумму денег в выбранных банках. Во второй строке вывести через пробел в любом 
порядке номера двух требуемых банков. Если имеется несколько решений, вывести любое из них. Если решений нет, вывести строку 
-1 -1.

Степанова Н ПС-22

Visual studio 2015
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const int MAX_BANK_COUNT = 2*pow(10, 5), MIN_BANK_COUNT = 2;
const int MAX_D = pow(10,8), MIN_D = 1;

using namespace std;

enum { empty_err = 1, struct_err, content_err, param_err=5, find_err };


void ReadFirstLine(ifstream &fin, int &num1, int &num2, bool &haveError, string fileName, int &lineCount);
void ReadOtherLines(ifstream &fin, int *distances, int *money_count, bool &haveError, int n, string fileName, int &lineCount);
void ParseLine(int &firstNum, int &secondNum, string fileLine, bool &haveError, int lineCount);
void SearchSolution(int *distances, int *moneyCount, int dd, int n);
void ErrorMessage(int code, string filename);
void ValueVerification(int resultNum1, int resultNum2, int &firstNum, int &secondNum, bool &haveError, int lineCount);
void SearchMaxMoney(int *moneyCount, int &maxMoney, int &bank1, int n);
void SearchMinMoney(int *moneyCount, int &maxMoney, int &minMoney, int n);

int main()
{
	bool haveErrors = false;
		string inputFileName ="input.txt";
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
					SearchSolution(pDistances, pMoneyCount, dd, n);
				}
			}
		}
		else
			ErrorMessage(find_err, inputFileName);
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

//void SearchSolution(int **distance_matrix, int **max_sum_matrix, int n, int dist, char *name)
void SearchSolution(int *distances, int *moneyCount, int dd, int n)
{
	
	//int minMoney = 0;

	//SearchMaxMoney(moneyCount, maxMoney, bank1, n);
	//SearchMinMoney(moneyCount, maxMoney, minMoney, n);
	
	//cout << "my min money " << minMoney << endl;
	
	//поиск оптимальной пары банков
	//поиск банка с макс колвом денег
	int maxMoney = 0, lastMaxMoney = 0 , maxSum = 0, totalSum = 0;
	int bank1 = n - 1, bank2 = 0;
	bool foundSolution = false;
	int newLength = n;
	int newBank = 0;

	while (newLength > 0 )
	{
		maxMoney = 0;
		
		//поиск макс колва денег в одном банке
		SearchMaxMoney(moneyCount, maxMoney, bank1, n);
		if (maxMoney > lastMaxMoney / 10)
		{
			maxSum = maxMoney;
			moneyCount[bank1] = 0;
			newLength--;
			//cout << newLength << endl;
			bool getNewMax = false;
			int k;

			for (k = 0; k < n; k++)
			{
				if ((moneyCount[k] != 0) && (moneyCount[k] + maxMoney > maxSum) && (abs(distances[k] - distances[bank1]) >= dd))
				{
					maxSum = moneyCount[k] + maxMoney;
					if (maxSum > totalSum)
					{
						newBank = bank1;
						bank2 = k;
						getNewMax = true;
						lastMaxMoney = maxMoney;
						foundSolution=true;
					}
				}
			}

			if (maxSum > totalSum)
			{
				totalSum = maxSum;
				cout << "totalSum" << totalSum << endl;
			}
		}
		else newLength = 0;
	}
	cout << "totalSum" << totalSum << endl;



	string outputFileName = "output.txt";
	ofstream fout(outputFileName, ios_base::out);

	if (fout.is_open())
	{
		if (foundSolution)
		{
			fout << totalSum << endl;
			fout << newBank + 1 << " " << bank2 + 1 << endl;
			fout.close();
		}
		else
		{
			bank1 = bank2 = -1;
			fout << bank1 << " " << bank2 << endl;
		}
	}
	else
		ErrorMessage(find_err, outputFileName);
}

void SearchMaxMoney(int *moneyCount, int &maxMoney, int &bank1, int n)
{
	for (int m = bank1; m >= 0; m--)
	{
		if (moneyCount[m] > maxMoney && moneyCount[m]!=0)
		{
			maxMoney = moneyCount[m];
			bank1 = m;
			//cout << "my max money " << maxMoney << endl;
		}
	}
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