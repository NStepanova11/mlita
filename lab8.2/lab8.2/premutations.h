#pragma once
#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

enum menuItems{getPremX =1, nextPrems, inversionVector};

vector <int> EnterPremutationA();
void CalculateInverPremutationA(vector <int> &premutationA, vector <int> &inversePremA);
vector <int> EnterPremutationB();
void MultiplyInversToB(vector <int> &premB, vector <int> &inversePremA);
void CalculatePremutationX();
string ChoiseMenuItem();
void PerformFunction(int &menuItem);
void CalculateNextPremutations();
bool NewPremutation(vector <int> &premutationA);
void Swap(vector <int> &premutationA, int i, int j);
void RestablishVector();
void GetVectorFromInversion(vector <int> &premA, vector <int> &inversionA);
vector <int> GetInversionVector(vector <int> premA);