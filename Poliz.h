#pragma once
#include "Table.h"
#include <vector>

std::vector<std::string> stringToWord(const std::string& str)
{
	std::vector<std::string> res(1);
	std::string zn = " +-*/^()";
	for (size_t i = 0, k = 0; i < str.length(); ++i)
	{
		if (zn.find(str[i]) == std::string::npos)
		{
			res[k] += str[i];
			continue;
		}
		if (str[i] == ' ')
		{
			continue;
		}
		if (res[k].length() != 0)
		{
			res.push_back(std::string{});
			++k;
		}
		res[k++] = str[i];
		res.push_back(std::string{});
		
	}
	return res;
}

class Poliz
{
public:
	Poliz() {}
	Poliz(const std::string& str) : pol(1)
	{
		madeOper();
		lex = stringToWord(str);
		makePoliz();
	}
	Poliz(const Poliz& copy) : pol(copy.pol), opStack(copy.opStack), operations(copy.operations)
							 , vars(copy.vars), lex(copy.lex){}
	Poliz& operator=(const Poliz& copy)
	{
		if (this == &copy)
			return *this;
		operations = copy.operations;
		pol = copy.pol;
		vars = copy.vars;
		return *this;
	}
	~Poliz() = default;

	const std::string getPoliz() const
	{
		std::string res;
		for (size_t i = 0; i < pol.size(); ++i)
		{
			for (size_t j = 0; j < pol[i].length(); ++j)
				res += pol[i][j];
			res += ' ';
		}
		return res;
	}

	size_t getSize() const
	{
		int res = 0;
		for (size_t i = 0; i < pol.size(); ++i)
		{
			res += pol[i].length();
		}
		return pol.size();
	}

	std::string& operator[](int index)
	{
		if (index < 0 || index >= pol.size())
			throw std::out_of_range("out of range in operator [] Poliz");
		return pol[index];
	}

	TTable& getVars()
	{
		return vars;
	}

private:
	std::vector<std::string> pol;
	TStack<TRecord> opStack;
	TTable operations;
	TTable vars;
	std::vector<std::string> lex;
	size_t k = 0;

private:
	void madeOper()
	{
		operations.add("+", 1);
		operations.add("-", 1);
		operations.add("*", 2);
		operations.add("/", 2);
		operations.add("^", 3);
	}
	void makePoliz()
	{
		for (size_t i = 0; i < lex.size(); ++i)
		{
			if (lex[i] == "(")
			{
				opStack.add(TRecord("("));
			}
			else
			{
				if (lex[i] == ")")
				{
					while (opStack.top().getName() != "(")
					{
						pol[k++] += *opStack.top().getName().c_str();
						pol.push_back(std::string{});
						opStack.pop();
					}
					opStack.pop();
				}
				else
				{
					int index = operations.Search(lex[i]);
					if (index > -1)
					{
						while (!opStack.isEmty() && opStack.top().getValue() >= index)
						{
							pol[k++] += *opStack.top().getName().c_str();
							pol.push_back(std::string{});
							opStack.pop();
						}
						opStack.add(TRecord{ lex[i], index });
					}
					else
					{
						pol[k++] += lex[i];
						pol.push_back(std::string{});
						int value = 0;
						if (lex[i][0] >= '0' && lex[i][0] <= '9')
							value = std::stoi(lex[i]);
						vars.add(lex[i], value);
					}
				}
			}
		}
		while (!opStack.isEmty())
		{
			pol[k++] += *opStack.top().getName().c_str();
			pol.push_back(std::string{});
			opStack.pop();
		}
	}
};

