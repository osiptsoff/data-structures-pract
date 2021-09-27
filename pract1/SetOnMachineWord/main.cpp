#include <iostream>

using std::cout;
using std::endl;
using std::rand;

class Set
{
	private:
		static constexpr char universe[] = "abcdefghijklmnopqrstuvwxyz";
		static constexpr int universeSize = 26;
		int set;

		static int CharToOffset(char letter) { return letter - 'a'; };

	public:
		Set(int _set) : set(_set) {};
		Set() : set(0) {};
		Set(char*);
		void Print();

		Set operator&(Set right) { return Set(this->set & right.set); };
		Set operator|(Set right) { return Set(this->set | right.set); };
		Set operator/(Set);
};

Set::Set(char* _set)
{
	set = 0;

	for (int i = 0; _set[i] != '\0'; i++)
		set |=  1 << CharToOffset(_set[i]);
}

void Set::Print()
{
	cout << "{ ";
	for (int i = 0; i < universeSize; i++)
		if ((set & (1 << i)) != 0)
			cout << universe[i] << ' ';
	cout << "}";
}

Set Set::operator/(Set right)
{
	int binarySum = this->set ^ right.set;

	return Set(binarySum - (binarySum & right.set));
}

Set GenerateRandomSet() { return Set(rand() % 67108864); }

int main()
{
	const int SetsExist = 4;

	Set sets[SetsExist];
	Set result;

	srand(time(NULL));

	for (int i = 0; i < SetsExist; i++)
	{
		sets[i] = GenerateRandomSet();
		cout << "Set " << (char)('A' + i) << ": ";
		sets[i].Print();
		cout << endl;
	}

	result = ((sets[0] & sets[1]) / sets[2]) | sets[3];
	cout << "Result: ";
	result.Print();

	return 0;
}
