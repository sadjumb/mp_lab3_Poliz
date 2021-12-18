#pragma once
#include "TRecord.h"

template <class T>
class TStack
{
public:
	TStack() : size(20), count(0), mem(new T[20]{ T {} }) {}
	TStack(int _size) : size(_size), count(0), mem(new T[size]{ T{} }) {}
	TStack(const TStack& r) : size(r.size), count(r.count), mem(new T[size]{})
	{
		for (size_t i = 0; i < size; ++i)
			mem[i] = r.mem[i];

	}
	TStack& operator=(const TStack& r)
	{
		if (this == &r)
			return *this;
		if (size != r.size)
		{
			delete[] mem;
			mem = new T[r.size];
			size = r.size;
		}
		count = r.count;
		for (size_t i = 0; i < count; ++i)
			mem[i] = r.mem[i];
		return *this;
	}

	void add(const T& right)
	{
		if (count < size)
		{
			mem[count] = right;
			++count;
		}
		else
		{
			T* tmp = new T[size + 1];
			for(size_t i = 0; i < size; ++i)
			{
				tmp[i] = mem[i];
			}
			tmp[size] = right;
			++count;
			delete[] mem;
			mem = tmp;
		}
	}
	bool isEmty() const
	{
		return count == 0 ? true : false;
	}
	T top() const
	{
		return isEmty() ? throw "Stack empty" : mem[count - 1];
	}
	void pop()
	{
		if(!isEmty())
		{
			--count;
		}
		else
		{
			throw "Stack empty";
		}
	}
	~TStack()
	{
		size = 0;
		count = 0;
		delete[] mem;
		mem = nullptr;
	}

private:
	int size;
	int count;
	T* mem;
};

