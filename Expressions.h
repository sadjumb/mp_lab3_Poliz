#pragma once
#include "Poliz.h"
#include "TStack.h"
class Expressions
{
public:
	Expressions() {};
	Expressions(const std::string& str) : pol(str), st() {}
	Expressions(const Expressions& copy) : pol(copy.pol), st(copy.st) {}
	Expressions& operator=(const Expressions& copy)
	{
		if (this == &copy)
			return *this;
		pol = copy.pol;
		st = copy.st;
		return *this;
	}
	~Expressions() = default;
	std::string getPoliz()
	{
		return pol.getPoliz();
	}
	TTable& getTable()
	{
		return pol.getVars();
	}
	const double calculate()
	{
		double left, right;
		std::string zn = "+-*^/";
		std::string str;
		for (size_t i = 0; i < pol.getSize(); ++i)
		{
			int k = 0;
			str = pol[i];
			if (zn.find(str) != std::string::npos)
			{
				if (str != "")
				{
					right = st.top();
					st.pop();
					left = st.top();
					st.pop();
				}
				switch (*str.c_str())
				{
				case '+':
					st.add(left + right);
					break;
				case '-':
					st.add(left - right);
					break;
				case '*':
					st.add(left * right);
					break;
				case '/':
					if (right == 0)
						throw("Error, / on null");
					st.add(left / right);
					break;
				case '^':
					st.add(pow(left, right));
					break;
				default:
					break;
				}
			}
			else
			{
				k = pol.getVars().Search(str);
				st.add(k);
			}
		}
		return st.top();
	}
private:
	Poliz pol;
	TStack<double> st;
};

