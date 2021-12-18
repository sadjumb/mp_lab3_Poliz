#pragma once
#include <string>

class TRecord
{
public:
	TRecord(std::string _name = "", int _value = 0)
	{
		name = _name;
		value = _value;
	}
	TRecord(const TRecord& copy)
	{
		name = copy.name;
		value = copy.value;
	}
	TRecord& operator=(const TRecord& copy)
	{
		name = copy.name;
		value = copy.value;
		return *this;
	}
	std::string getName()
	{
		return name;
	}
	int getValue() const
	{
		return value;
	}

	void setValue(int _value)
	{
		value = _value;
	}

private:
	std::string name;
	int value;
};

