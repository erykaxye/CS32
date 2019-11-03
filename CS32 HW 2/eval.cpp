#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
#include "Map.h" 
using namespace std;

bool isOp(char ch);
bool hasPrecedence(char first, char second);

int evaluate(string infix, const Map& values, string& postfix, int& result)
{
	postfix = ""; //empty postfix?
	if (infix == "")
		return 1;

	string temp = "";
	for (int p = 0; p < infix.size(); p++) //deletes all spaces
	{
		char c = infix[p];
		if (c != ' ')
			temp += c;
	}

	int endparen = 0;
	int beginparen = 0;

	stack<char> operators; //Initialize the operator stack to empty
	for (int i = 0; i < temp.size(); i++) //For each character ch in the infix string
	{
		char ch = temp[i];
		if (islower(ch)) //append ch to end of postfix 
		{
			postfix += ch;
			if (temp.size() > i + 1)
			{
				if (islower(temp[i + 1]))
					return 1;
				if (temp[i + 1] == '(' || temp[i + 1] == ')')
					return 1;
			}
		}
		else if (ch == '(') //case '(': push ch onto the operator stack
		{
			operators.push(ch);
			beginparen++;
		}
		else if (ch == ')' && !operators.empty() && postfix.size() > 0) // pop stack until matching '('  
		{
			while (operators.top() != '(') //While stack top is not '('
			{
				char t = operators.top();
				postfix += t;
				operators.pop();
			}
			operators.pop(); //pop the stack  // remove the '('
			endparen++;
		}
		else if (isOp(ch))
		{
			if (postfix.size() == 0)
				return 1;
			if (temp.size() > i + 1)
				if (isOp(temp[i + 1]))
					return 1;
			if (temp.size() == i + 1)
				return 1;
			while (!operators.empty() && operators.top() != '(' && hasPrecedence(operators.top(), ch))
			{
				char t = operators.top();
				//While the stack is not empty and the stack top is not '('and precedence of ch <= precedence of stack top
				postfix += t;
				operators.pop();
			}
			operators.push(ch);
		}
		else
			return 1;
	}
	while (!operators.empty()) 	//While the stack is not empty
	{
		char t = operators.top();
		postfix += t; 	//append the stack top to postfix
		operators.pop(); //pop the stack 
	}
	
	if (beginparen != endparen)
		return 1;

	stack<char> operand;
	int res = 0;

	for (int j = 0; j < postfix.size(); j++)
	{
		char pf = postfix[j];

		if (islower(pf))
		{
			int num = 0;
			if (!values.get(pf, num))
				return 2;
			values.get(pf, num);
			operand.push(num);
			if (postfix.size() == 1)
			{
				result = num;
				return 0;
			}
		}
		else //check if theres a least 2 numbers?
		{
			int operand2 = operand.top();
			operand.pop();
			int operand1 = operand.top();
			operand.pop();
			if (pf == '+')
				res = operand1 + operand2;
			else if (pf == '-')
				res = operand1 - operand2;
			else if (pf == '*')
				res = operand1 * operand2;
			else if (pf == '/')
			{
				if (operand2 == '0')
					return 3;
				res = operand1 / operand2;
			}
			operand.push(res);
		}
	}
	result = res; //operand.top()
	return 0;
}

bool isOp(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
		return true;
	return false;
}

bool hasPrecedence(char first, char second) //returns true if first has precedence over second, false if not 
{
	if (first == '+' || first == '-')
		if (second == '*' || second == '/')
			return false;
	return true;
}

int main()
{
	assert(hasPrecedence('+', '-'));
	assert(hasPrecedence('-', '-'));
	assert(hasPrecedence('+', '+'));
	assert(hasPrecedence('-', '+'));
	assert(!hasPrecedence('+', '*'));
	assert(!hasPrecedence('+', '/'));
	assert(hasPrecedence('*', '-'));
	assert(hasPrecedence('/', '-'));


	char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
	int  vals[] = { 3,  -9,   6,   2,   4,   1 };
	Map m;
	for (int k = 0; vars[k] != '#'; k++)
		m.insert(vars[k], vals[k]);
	string pf;
	int answer;
	answer = 999;
	assert(evaluate("", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a+ e", m, pf, answer) == 0 && pf == "ae+" && answer == -6);
	answer = 999;
	assert(evaluate("", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a+", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a i", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("ai", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("()", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("y(o+u)", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a+E", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("(a+(i-o)", m, pf, answer) == 1 && answer == 999);
	// unary operators not allowed:
	assert(evaluate("-a", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a*b", m, pf, answer) == 2 &&
		pf == "ab*"  &&  answer == 999);
	assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0 &&
		pf == "yoau-*+"  &&  answer == -1); //
	answer = 999;
	assert(evaluate("o/(y-y)", m, pf, answer) == 3 &&
		pf == "oyy-/"  &&  answer == 999);
	assert(evaluate(" a  ", m, pf, answer) == 0 &&
		pf == "a"  &&  answer == 3);
	assert(evaluate("((a))", m, pf, answer) == 0 &&
		pf == "a"  &&  answer == 3);


	cerr << "Passed all tests" << endl;


}

//still hv to make sure valid?
