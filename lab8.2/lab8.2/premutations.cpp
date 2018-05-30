#include "stdafx.h"
#include "premutations.h"

//ввод перестановки А
vector <int> EnterPremutationA()
{
	string A;
	vector <int> premutationA;

	cout << "Enter the premutation A: ";
	getline(cin, A);
	stringstream ssA(A);
	copy(istream_iterator<int>(ssA), istream_iterator<int>(), back_inserter(premutationA));
	return premutationA;
}

//вычисление обратной перестановки А
void CalculateInverPremutationA(vector <int> &premutationA, vector <int> &inversePremA)
{
	int n = premutationA.size();
	for (size_t elem = 1; elem <= n; elem++)
	{
		int index = distance(premutationA.begin(), find(premutationA.begin(), premutationA.end(), elem)) + 1;
		inversePremA.push_back(index);
	}
	cout << "Inverse Premutation: ";
	copy(inversePremA.begin(), inversePremA.end(), ostream_iterator<int>(cout, " "));
}

//вычисление перестановки В
vector <int> EnterPremutationB()
{
	string B;
	vector <int> premutationB;

	cout << "Enter the premutation B: ";
	getline(cin, B);
	stringstream ssB(B);
	copy(istream_iterator<int>(ssB), istream_iterator<int>(), back_inserter(premutationB));
	return premutationB;
}

//умножение перестановки В на обратную А
void MultiplyInversToB(vector <int> &premB, vector <int> &inversePremA)
{
	vector <int> premX;

	for (int elem : premB)
	{
		int index = elem - 1;
		int newElemX = inversePremA[index];
		premX.push_back(newElemX);
	}
	cout << endl;
	cout << "X Premutation: ";
	copy(premX.begin(), premX.end(), ostream_iterator<int>(cout, " "));
}

void CalculatePremutationX()
{
	vector <int> premA = EnterPremutationA();
	vector <int> premB = EnterPremutationB();
	vector <int> inversePremA;
	CalculateInverPremutationA(premA, inversePremA);
	MultiplyInversToB(premB, inversePremA);
}

string ChoiseMenuItem()
{
	cout << endl;
	cout << "1 - Calculate X premutation" << endl;
	cout << "2 - Next k premutations" << endl;
	cout << "3 - Restore vector from inversion" << endl;
	cout << "> ";
	string item;
	getline(cin, item);
	return item;
}

void PerformFunction(int &menuItem)
{
	switch (menuItem)
	{
	case getPremX:
	{
		CalculatePremutationX();
	}
	case nextPrems:
	{
		CalculateNextPremutations();
	}
	case inversionVector:
	{
		RestablishVector();
	}
	}
}

void CalculateNextPremutations()
{
	vector <int> premA = EnterPremutationA();
	int k;
	cout << "Enter k: ";
	cin >> k;
	cin.get();
	int i = 0;
	while (NewPremutation(premA) && (i < k))
	{
		//Print(premA);
		cout << ++i<<".   ";
		copy(premA.begin(), premA.end(), ostream_iterator<int>(cout, " "));
		cout << endl;
	}
}

bool NewPremutation(vector <int> &premutationA)
{
	int sizeA = premutationA.size();
	int left = sizeA - 2;
	while (left != -1 && premutationA[left] >= premutationA[left + 1])
		left--;
	if (left == -1)
		return false; 

	int right = sizeA - 1;
	while (premutationA[left] >= premutationA[right])
		right--;
	Swap(premutationA, left, right);
	int l = left + 1, r = sizeA - 1;
	while (l < r)
	{
		Swap(premutationA, l, r);
		l++;
		r--;
	}
	return true;
}

void Swap(vector <int> &premutationA, int left, int right)
{
	int s = premutationA[left];
	premutationA[left] = premutationA[right];
	premutationA[right] = s;
}

vector <int> GetInversionVector(vector <int> premA)
{
	vector <int> inversionA;
	
	for (int i = 0; i < premA.size(); i++)
	{
		int maxCount = 0;
		for (int j=0; j<=i; j++)
		{
			if (premA[j] > premA[i])
				maxCount++;
		}
		inversionA.push_back(maxCount);
	}
	
	return inversionA;
}

void RestablishVector()
{
	vector <int> premA = EnterPremutationA();
	vector <int> inversionA = GetInversionVector(premA);

	cout << endl;
	cout << "Inversion vector: ";
	copy(inversionA.begin(), inversionA.end(), ostream_iterator<int>(cout, " "));
	GetVectorFromInversion(premA, inversionA);
}


//1 2 3 4 5
//берем число с конца вектора
//прибавляем единицу
// находим с конца элемент в данной позиции
// помещаем впепред нового вектора
void GetVectorFromInversion(vector <int> &premA, vector <int> &inversionA)
{
	cout << endl;
	vector <int> restoredA;
	sort(premA.begin(), premA.end());
	//for (size_t i = inversionA.size()-1; i >=0; i--)
	int n = inversionA.size();
	int i = n - 1;
	
	while (i >= 0)
	{
		//cout << "inv size " << i << endl;
		int step = inversionA[i] + 1;
		int index = premA.size() - step;
		restoredA.push_back(premA[index]);
		premA.erase(premA.begin()+index);
		i--;
	} 
	reverse(restoredA.begin(), restoredA.end());
	cout << "Restored A: ";
	copy(restoredA.begin(), restoredA.end(), ostream_iterator<int>(cout, " "));
}
