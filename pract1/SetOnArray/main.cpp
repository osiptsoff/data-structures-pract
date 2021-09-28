#include <iostream>
#include <time.h>

using std::cout;
using std::rand;

char* GenerateRandomSet()
{
	static const char* universe = "abcdefghijklmnopqrstuvwxyz";
	static const int universeSize = strlen(universe);

	char* result = new char[universeSize + 1];
	int sizeFact = 0;
	int word = rand() % (1 << universeSize);

	for (int i = 0; i < universeSize; ++i)
		if ((word & (1 << i)) > 0)
		{
			result[sizeFact] = universe[i];
			++sizeFact;
		}

	result[sizeFact] = '\0';

	return result;
}

int main()
{
	const int SetsExist = 4;
	const int SetSize = 27;

	char* setA, * setB, * setC, * setD;
	char* result = nullptr;;
	int resultIndex;

	int executions = 1000000;

	srand(time(nullptr));

	setA = GenerateRandomSet();
	cout << "Set A: " << setA << std::endl;
	setB = GenerateRandomSet();
	cout << "Set B: " << setB << std::endl;
	setC = GenerateRandomSet();
	cout << "Set C: " << setC << std::endl;
	setD = GenerateRandomSet();
	cout << "Set D: " << setD << std::endl;

	time_t start = clock();
	for (int i = 0; i < executions; ++i)
	{
		//delete[] result;
		//result = nullptr;

		result = new char[SetSize];
		resultIndex = 0;

		for (int aIndex = 0; setA[aIndex] != '\0'; ++aIndex)
			for (int bIndex = 0; setB[bIndex] != '\0'; ++bIndex)
				if (setA[aIndex] == setB[bIndex])
				{
					int cIndex;
					for (cIndex = 0;  setC[cIndex] != setA[aIndex] && setC[cIndex] != '\0'; ++cIndex);
					if (setC[cIndex] == '\0')
					{
						result[resultIndex] = setA[aIndex];
						++resultIndex;
					}

				}

		for (int dIndex = 0; setD[dIndex] != '\0'; ++dIndex)
		{
			int resIndex;
			for (resIndex = 0;  resIndex < resultIndex && result[resIndex] != setD[dIndex]; ++resIndex);
			if (resIndex == resultIndex)
			{
				result[resultIndex] = setD[dIndex];
				++resultIndex;
			}
		}
	}
	result[resultIndex] = '\0';
	start = clock() - start;
	cout << "Time taken: " << start / (float)CLOCKS_PER_SEC << std::endl;

	cout << "Result: " << result << std::endl;

	return 0;
}
