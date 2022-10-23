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

bool task3(const vector<vector<int>>& g, unsigned from, unsigned to) {
	return false;
}

string task4 (const string& input) {
    return "";
}

bool task5(vector<vector<int>>g, unsigned from, unsigned to) {
	return false;
}

bool task6(const string& a, const string& b) {
	return false;
}