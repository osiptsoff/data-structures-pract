#pragma once

#include <iostream>

class Set
{
	private:
		const static char universe[];
		const static int universeSize;
		static int setsExist;

		char* set;
		char tag;
		int power;
	public:
		Set() : set(new char[universeSize + 1]), tag('A' + setsExist++), power(0) { set[0] = '\0'; };
		Set(char);
		Set(const Set&);
		Set(Set&& other) noexcept : set(other.set), tag('A' + setsExist++), power(other.power) { other.set = nullptr; }
		~Set() { delete[] set; --setsExist; };

		int GetPower() { return power; };
		void Print() { std::cout << tag <<  ": [" << set << "]\n"; };

		Set operator|(const Set&) const;
		Set operator&(const Set&) const;
		Set operator~() const;
		Set operator=(const Set&);
		Set operator=(Set&&) noexcept;
};

const char Set::universe[] = "abcdefghijklmnopqrstuvwxyz";
const int Set::universeSize = strlen(universe);
int Set::setsExist = 0;

Set::Set(char) : Set()
{
	int word = rand() | (rand() << 15);

	for (int i = 0; i < universeSize; ++i)
		if ((word & (1 << i)) > 0)
		{
			set[power] = universe[i];
			++power;
		}

	set[power] = '\0';
}

Set::Set(const Set& other) : set(new char[universeSize + 1]), tag('A' + setsExist++), power(other.power)
{
	for (int i = 0; this->set[i] = other.set[i]; ++i);
	set[power] = '\0';
}

Set Set::operator|(const Set &other) const
{
	Set result = Set(*this);

	for (int otherIndex = 0; other.set[otherIndex] != '\0'; ++otherIndex)
	{
		int thisIndex;
		for (thisIndex = 0; this->set[thisIndex] != '\0' && this->set[thisIndex] != other.set[otherIndex]; ++thisIndex);
		if (this->set[thisIndex] == '\0')
		{
			result.set[result.power] = other.set[otherIndex];
			++result.power;
		}
	}
	result.set[result.power] = '\0';
			
	return result;
}

Set Set::operator&(const Set& other) const
{
	Set result = Set();

	for (int otherIndex = 0; other.set[otherIndex] != '\0'; ++otherIndex)
	{
		int thisIndex;
		for (thisIndex = 0; this->set[thisIndex] != '\0' && this->set[thisIndex] != other.set[otherIndex]; ++thisIndex);
		if (this->set[thisIndex] != '\0')
		{
			result.set[result.power] = other.set[otherIndex];
			++result.power;
		}
	}
	result.set[result.power] = '\0';

	return result;
}

Set Set::operator~() const
{
	Set result = Set();

	for (int universeIndex = 0; universeIndex < universeSize; ++universeIndex)
	{
		int thisIndex;
		for (thisIndex = 0; this->set[thisIndex] != '\0' && this->set[thisIndex] != universe[universeIndex]; ++thisIndex);
		if (this->set[thisIndex] == '\0')
		{
			result.set[result.power] = universe[universeIndex];
			++result.power;
		}
	}
	result.set[result.power] = '\0';

	return result;
}

Set Set::operator=(const Set& other)
{
	if (this != &other)
	{
		this->power = other.power;
		for (int i = 0; this->set[i] = other.set[i]; ++i);
		set[power] = '\0';
	}
	return *this;
}

Set Set::operator=(Set&& other) noexcept
{
	if (this != &other)
	{
		this->power = other.power;
		this->set = other.set;
		other.set = nullptr;
	}
	return *this;
}
