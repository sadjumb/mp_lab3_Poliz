#pragma once

#include "TRecord.h"
#include "TStack.h"
#include <stdexcept>

class TTable
{
public:
	TTable(size_t _size = 20) : size(_size), count(0), mem(new TRecord[size]{ TRecord{} }){}
	TTable(const TTable& tmp) : size(tmp.size), count(tmp.count), mem(new TRecord[size]{ TRecord{} })
	{
		for (size_t i = 0; i < size; i++)
		{
			mem[i] = tmp.mem[i];
		}
	}
	~TTable()
	{
		delete[]mem;
	}
	
	TTable& operator=(const TTable& tmp)
	{
		if (this == &tmp)
		{
			return *this;
		}

		if (size != tmp.size)
		{
			delete[] mem;
			size = tmp.size;
			mem = new TRecord[size];
		}

		count = tmp.count;
		for (size_t i = 0; i < size; ++i)
		{
			mem[i] = tmp.mem[i];
		}
		return *this;

	}
	int Search(std::string Key)
	{
		return (SearchNumber(Key) == -1) ? -1 : mem[SearchNumber(Key)].getValue();
	}

	TRecord& operator[](int index)
	{
		if (index < 0 || index > count)
			throw std::out_of_range("Out of range");
		return mem[index];
	}
	void add(std::string Key, int Value)
	{
		if (SearchNumber(Key) != -1)
			return;

		TRecord element(Key, Value);
		if (size <= count)
		{
			TTable tmp(*this);
			delete[] mem;
			++size;
			mem = new TRecord[size];
			for (size_t i = 0; i < size - 1; ++i)
			{
				mem[i] = tmp.mem[i];
			}
		}
		mem[count++] = element;
	}

	void del(std::string Key)
	{
		int index = SearchNumber(Key);
		if (index < 0 || index >= count)
		{
			return;
		}
		for (size_t i = index; i < count - 1; ++i)
		{
			std::swap(mem[i], mem[i + 1]);
		}
		--count;
	}
	bool IsEmpty()
	{
		return count;
	}
	int IsFull()
	{
		return count == size;
	}
	int GetCount() const
	{
		return count;
	}

private:
	size_t size;
	size_t count;
	TRecord* mem;

	int SearchNumber(std::string Key)
	{
		for (int i = 0; i < count; i++)
		{
			if (Key == mem[i].getName())
			{
				return i;
			}
		}
		return -1;
	}
};