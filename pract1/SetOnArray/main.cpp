#include <iostream>

using std::cin;
using std::cout;

int main()
{
	const int SetsExist = 4;
	const int SetSize = 15;

	char* sets[SetsExist];
	char* result;
	int counter, resultIndex;

	for (int i = 0; i < SetsExist; i++)
	{
		sets[i] = new char[SetSize];
		cin >> sets[i];
	}
	result = new char[SetSize];
	resultIndex = 0;

	for (int aIndex = 0; sets[0][aIndex] != '\0'; ++aIndex)
		for (int bIndex = 0; sets[1][bIndex] != '\0'; ++bIndex)
			if (sets[0][aIndex] == sets[1][bIndex])
			{
				for (counter = 0; sets[2][counter] != '\0' && sets[2][counter] != sets[0][aIndex]; ++counter);
				if (sets[2][counter] == '\0')
				{
					result[resultIndex] = sets[0][aIndex];
					++resultIndex;
					result[resultIndex] = '\0';
				}
			}
	for (int dIndex = 0; sets[3][dIndex] != '\0'; ++dIndex)
	{
		for (counter = 0; (result[counter] != '\0') && (result[counter] != sets[3][dIndex]); ++counter);
		if (result[counter] == '\0')
		{
			result[resultIndex] = sets[3][dIndex];
			++resultIndex;
		}
	}
	result[resultIndex] = '\0';

	cout << "Result: " << result << std::endl;

	return 0;
}