// Выполнил: Осипцов Никита, студент группы 0305, вариант 4

#include <iostream>
#include <random>
#include <time.h>

using std::cout;
using std::endl;

std::random_device rd;
std::mt19937 mersenne(rd());

int GenerateRandomSet(int size) { return mersenne() % (1 << size); }

void Print(const char* universe, int universeSize, int set)
{
	cout << "{ ";
	for (int i = 0; i < universeSize; i++)
		if ((set & (1 << i)) != 0)
			cout << universe[i] << ' ';
	cout << "}";
}

int main()
{
	const char Universe[] = "abcdefghijklmnopqrstuvwxyz";
	const int UniverseSize = 26;
	const int SetsExist = 4;

	float clockSum = 0;
	int executions = 1000000;

	int sets[SetsExist];
	int result;

	srand(time(nullptr));

	for (int i = 0; i < SetsExist; i++)
	{
		sets[i] = GenerateRandomSet(UniverseSize);
		cout << "Set " << (char)('A' + i) << ": ";
		Print(Universe, UniverseSize, sets[i]);
		cout << endl;
	}

	clock_t start = clock();
	for (int i = 0; i < executions; i++)
		result = ((sets[0] & sets[1]) & ~sets[2]) | sets[3];
	start = clock() - start;

	cout << "Time taken: " << start / (float)CLOCKS_PER_SEC << endl;
	cout << "Result: ";
	Print(Universe, UniverseSize, result);;

	return 0;
}
