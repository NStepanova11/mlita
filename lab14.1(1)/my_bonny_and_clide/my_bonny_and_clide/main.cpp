#include <iostream>
#include <fstream>
#include <string>
#include <climits>

const int MAX_BANK_COUNT = 20e5, MIN_BANK_COUNT = 2;
const int MAX_D = 10e8, MIN_D = 1;

using namespace std;

void ReadFirstLine(ifstream &fin, int &num1, int &num2);
void ReadOtherLines(ifstream &fin, int *distances, int *money_count);

//void ReadInputFile(char *fileName, int &dist[BANK_COUNT], int &money_sum[BANK_COUNT]);
void PrintMatrix(int **a, int **b, int n);
void ParseLine(string fileLine, int &firstNum, int &secondNum);


int main(int argc, char *argv[])
{
	//int distance[BANK_COUNT] = { 0 };
	//int money_count[BANK_COUNT] = { 0 };
	


	string inputFileName = argv[1];
	ifstream fin(inputFileName);

	//��������� ������ ������
	int number1 = 0, number2 = 0;
	ReadFirstLine(fin, number1, number2);
	int n = number1;
	int dd = number2;
	
	//��������� ��������� �����
	int *pDistances = new int[n];
	int *pMoneyCount = new int[n];
	ReadOtherLines(fin, pDistances, pMoneyCount);
	for (int j = 0; j < n; j++)
	{
		cout << pDistances[j] <<"  "<<pMoneyCount[j]<< endl;
	}



	//��������� ������� � ������������ ����� ������ ������(distance) ��� ���������� >= �����������
	//� ������� ����� ����� ����� � ���� ������
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

	//������ ������ ����� � ���������� �� �����
		
	PrintMatrix(distance_matrix, max_sum_matrix, n);
	/*
	int max_i = 0, max_j=0;
	int max_sum = 0;

	//����� ������������ ����� ����� � ���� ������
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

	//��������� ������ ���������: ���� ����� � ���� ������
	int bank1 = 0, bank2 = 0;
	string outputFileName = argv[2];
	ofstream fout(outputFileName, ios_base::out);

	if (distance_matrix[max_i][max_j] < dd)
	{
		bank1 = bank2 = -1;
	}
	else
	{
		bank1 = max_i+1;
		bank2 = max_j+1;
	}
	fout << max_sum_matrix[max_i][max_j]<<endl;
	fout << bank1 << "  " << bank2 << endl;


	*/
	system("pause");
	return 0;
}

void ReadFirstLine(ifstream &fin, int &num1, int &num2)
{
	string line = "";
	getline(fin, line);
	ParseLine(line, num1, num2);
}

void ReadOtherLines(ifstream &fin, int *distances, int *money_count)
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
			ParseLine(line, num1, num2);
			distances[k] = num1;
			money_count[k] = num2;
			k++;
		}
		else
			haveLine = false;
	} while (haveLine);
}

/*
void ReadInputFile(char *fileName, int &dist[BANK_COUNT], int &money_sum[BANK_COUNT])
{
	//������ ������ �� ����� 
	

	bool haveLine = false;
	string line = "";
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
				dist[k] = num1;
				money_sum[k] = num2;
				k++;
			}
		}
		else
			haveLine = false;
	} while (haveLine);

	fin.close();
}
*/
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

void ParseLine(string fileLine, int &firstNum, int &secondNum)
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
			firstNumStr += fileLine[i];
		
		else if (takeW==true)
			secondNumStr += fileLine[i];
		
	}

		firstNum = atoi(firstNumStr.c_str());
		secondNum = atoi(secondNumStr.c_str());
}