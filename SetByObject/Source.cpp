#include <iostream>
#include <time.h>
#include "Set.h"

using namespace std;

int main()
{
	const int setsExist = 4;
	const int executions = 1000000;
	float averagePower = 0;

	srand(time(nullptr));
	Set setA = Set();
	setA.Print();
	Set setB = Set();
	setB.Print();
	Set setC = Set();
	setC.Print();
	Set setD = Set();
	setD.Print();
	Set* result = nullptr;
	
	time_t start = clock();
	for (int i = 0; i < executions; i++) {
		delete result;
		result = nullptr;
		result = new Set(((setA & setB) & ~setC) | setD);
	}
	start = clock() - start;

	averagePower = (setA.GetPower() + setB.GetPower() + setC.GetPower() + setD.GetPower() + result->GetPower()) / 5;
	cout << "\nTime taken: " << (start / (float)CLOCKS_PER_SEC) << "\nAverage power: " << averagePower << "\n";
	result->Print();

	return 0;
}
