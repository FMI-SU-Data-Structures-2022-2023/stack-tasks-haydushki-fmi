#include <stack>
#include <string>
#include <vector>

using namespace std;

int task1(int number)
{
    stack<int> factorials;
    factorials.push(1);

    for (int i = 2; i <= number; ++i) {
        int nextNumber = factorials.top() * i;
        factorials.pop();
        factorials.push(nextNumber);
    }

    return factorials.top();
}

bool task2(const string& list)
{
    stack<char> brackets;

    char current;
    for (size_t i = 0; i < list.length(); i++) {
        current = list[i];
        switch (current) {
        case '(': {
            brackets.push(current);
            break;
        }
        case ')': {
            if (!brackets.empty() && brackets.top() == '(') {
                brackets.pop();
                break;
            }
            return false;
        }
        case '[': {
            brackets.push(current);
            break;
        }
        case ']': {
            if (!brackets.empty() && brackets.top() == '[') {
                brackets.pop();
                break;
            }
            return false;
        }
        case '{': {
            brackets.push(current);
            break;
        }
        case '}': {
            if (!brackets.empty() && brackets.top() == '{') {
                brackets.pop();
                break;
            }
            return false;
        }
        }
    }

    return brackets.empty();
}

void dfsHelper(const vector<vector<int>> &g, unsigned current, unsigned target, std::vector<bool> &visited)
{
    visited[current] = true;
    for (size_t i = 0; i < g[current].size(); i++)
    {
        if (!visited[g[current][i]])
        {
            dfsHelper(g, g[current][i], target, visited);
        }
    }
}

bool task3(const vector<vector<int>> &g, unsigned from, unsigned to)
{
    if (from == to)
    {
        return true;
    }
    std::vector<bool> visited(g.size(), 0);

    visited[from] = true;
    dfsHelper(g, from, to, visited);

    return visited[to];
}

bool isLetter(char ch)
{
    return ch >= 'A' && ch <= 'Z';
}

bool isDigit(char ch)
{
    return ch >= '0' && ch <= '9';
}

bool isOpeningBracket(char ch)
{
    return ch == '(';
}
bool isClosingBracket(char ch)
{
    return ch == ')';
}

string task4(const string &input)
{
    std::stack<int> counts;
    std::string result = "";
    std::string tempResult = "";

    for (size_t i = 0; i < input.size(); i++)
    {
        if (isLetter(input[i]))
        {
            tempResult += input[i];
            if (isClosingBracket(input[i + 1]))
            {
                for (size_t i = 0; i < counts.top(); i++)
                {
                    result.append(tempResult);
                }
                counts.pop();
                tempResult.clear();
            }
        }
        if (isOpeningBracket(input[i]))
        {
            std::stack<char> digitStack;
            for (std::size_t j = 1; j <= i && isDigit(input[i - j]); ++j)
            {
                digitStack.push(input[i - j]);
            }

            std::string digitString;
            while (!digitStack.empty())
            {
                digitString.push_back(digitStack.top());
                digitStack.pop();
            }

            int digit = std::stoi(digitString);
            counts.push(digit);
        }
    }
    while (!counts.empty())
    {
        for (size_t i = 0; i < counts.top() - 1; i++)
        {
            result.append(result);
        }
        counts.pop();
    }

    return result;
}

bool task5(vector<vector<int>> g, unsigned from, unsigned to)
{
    if (from == to)
    {
        return true;
    }
    std::vector<bool> visited(g.size(), 0);
    std::stack<int> stack;

    visited[from] = true;
    stack.push(from);
    while ((!stack.empty()))
    {
        int current = stack.top();
        stack.pop();
        visited[current] = true;
        for (size_t i = 0; i < g[current].size(); i++)
        {
            if (current == to)
            {
                return true;
            }
            if (!visited[g[current][i]])
            {
                stack.push(g[current][i]);
            }
        }
    }

    return false;
}

bool isPositiveSign(char ch)
{
    return ch == '+';
}

bool isNegativeSign(char ch)
{
    return ch == '-';
}

bool isSign(char ch)
{
    return isPositiveSign(ch) || isNegativeSign(ch);
}

bool isSmallLetter(char ch)
{
    return ch >= 'a' && ch <= 'z';
}

char flipSign(char ch)
{
    if(isPositiveSign(ch))
        {
            return '-';
        }
    return '+';
}

std::string simplifyExpression(const std::string& expression)
{
    int values[26];
    char letters[26];
    for(std::size_t i = 0; i < 26; ++i)
        {
            values[i] = 0;
        }
    std::size_t valueIndex = 0;
    std::stack<char> operations;

    operations.push('+');
    for(int i = 0; i < expression.size(); ++i)
        {
            // Change global sign
            if(isOpeningBracket(expression[i]))
                {
                    if(isNegativeSign(operations.top()))
                        {
                            operations.push(flipSign(expression[i - 1]));
                        }
                    else
                        {
                            operations.push(expression[i - 1]);
                        }
                }
            // Restore to previous global sign
            if(isClosingBracket(expression[i]))
                {
                    operations.pop();
                }
            // If it's a letter calculate it's sign and put it into
            if(isSmallLetter(expression[i]))
                {
                    if(i == 0)
                        {
                            values[valueIndex] += 1;
                            letters[valueIndex] = expression[i];
                            valueIndex++;
                            continue;
                        }
                    if(!isSign(expression[i - 1])) // If there's no sign before the letter, assume it's the last global
                                                   // sign.
                        {
                            if(isPositiveSign(operations.top()))
                                {
                                    values[valueIndex] += 1;
                                    letters[valueIndex] = expression[i];
                                }
                            else
                                {
                                    values[valueIndex] -= 1;
                                    letters[valueIndex] = expression[i];
                                }
                        }
                    else
                        {
                            char newSign = expression[i - 1];
                            if(isNegativeSign(operations.top()))
                                {
                                    newSign = flipSign(newSign);
                                }

			    if(isPositiveSign(newSign))
				{
				    values[valueIndex] += 1;
				    letters[valueIndex] = expression[i];
				}
			    else
				{
				    values[valueIndex] -= 1;
				    letters[valueIndex] = expression[i];
				}
			}

		    valueIndex++;
		}
	}

    // Generate result
    std::string result;
    for(int i = 0; i < 26; ++i)
        {

	    if(values[i] != 0)
		{
		    if(values[i] > 0)
			{
			    result.push_back('+');
			}
		    else
			{
			    result.push_back('-');
			}
		    result.push_back(letters[i]);
		}
	}
    return result;
}

bool task6(const string& a, const string& b) {
    std::string aSimplified = simplifyExpression(a);
    std::string bSimplified = simplifyExpression(b);

	return aSimplified == bSimplified;
}
