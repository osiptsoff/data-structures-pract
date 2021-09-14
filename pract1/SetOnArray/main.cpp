#include <iostream>
#include <time.h>

using std::cin;
using std::cout;
using std::rand;


bool IsIn(char* set, char node)
{
	int index;

	for (index = 0; set[index] != node && set[index] != '\0'; ++index);
	return set[index] == node;
}

char* GenerateRandomSet(int MaxSize)
{
	char* result = new char[MaxSize];
	char letter;
	int sizeFact = rand() % MaxSize;

	for (int i = 0; i < sizeFact; ++i)
	{
		result[i + 1] = '\0';
		do
			letter = rand() % ('z' - 'a' + 1) + 'a';
		while (IsIn(result, letter));
		result[i] = letter;
	}
	result[sizeFact] = '\0';

	return result;
}

int main()
{
	const int SetsExist = 4;
	const int SetSize = 15;

	char* sets[SetsExist];
	char* result;
	int counter, resultIndex;

	srand(time(nullptr));
	for (int i = 0; i < SetsExist; i++)
	{
		sets[i] = GenerateRandomSet(SetSize);
		cout << "Set " << (char)('A' + i) << ": " << sets[i] << std::endl;
	}
	result = new char[SetSize];
	resultIndex = 0;

	for (int aIndex = 0; sets[0][aIndex] != '\0'; ++aIndex)
		if(IsIn(sets[1], sets[0][aIndex]))
			if(!IsIn(sets[2], sets[0][aIndex]))
			{
				result[resultIndex] = sets[0][aIndex];
				++resultIndex;
				result[resultIndex] = '\0';
			}

	for (int dIndex = 0; sets[3][dIndex] != '\0'; ++dIndex)
		if(!IsIn(result, sets[3][dIndex]))
		{
			result[resultIndex] = sets[3][dIndex];
			++resultIndex;
		}
	result[resultIndex] = '\0';

	cout << "Result: " << result << std::endl;

	return 0;
}
