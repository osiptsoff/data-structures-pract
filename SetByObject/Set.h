#pragma once

#include <iostream>

class Set
{
	private:
	    static char universe[];
		static int universeSize;
		static int setsExist;

		int word;
		char tag;
		int power;

	public:
		Set(int);
		Set() : Set(rand() | (rand() << 15)) {}
		Set(const Set&);
		//Set(const Set&&) noexcept;

		int GetPower() { return power; }
		void Print();

		Set operator| (const Set& other) const { return Set(this->word | other.word); };
		Set operator& (const Set& other) const { return Set(this->word & other.word); };
		Set operator~ () const { return Set(~(this->word)); };
		Set operator= (const Set&);
		//Set operator= (const Set&&) noexcept;
};

char Set::universe[] = "abcdefghijklmnopqrstuvwxyz";
int Set::universeSize = strlen(universe);
int Set::setsExist = 0;

Set::Set(int word)
{
	this->word = word;
	tag = 'A' + setsExist++;

	power = 0;
	for (int i = 0; i < universeSize; i++)
		power += ((word & (1 << i)) > 0);
}

Set::Set(const Set& other)
{
	this->word = other.word;
	this->power = other.power;
}

void Set::Print()
{
	std::cout << "Set " << tag << ": ";
	std::cout << "[";
	for (int i = 0; i < universeSize; i++)
		if ((word & (1 << i)) > 0)
			std::cout << universe[i];
	std::cout << "]\n";
}

Set Set::operator= (const Set& other)
{
	this->word = other.word;
	this->power = other.power;
	return *this;
}

