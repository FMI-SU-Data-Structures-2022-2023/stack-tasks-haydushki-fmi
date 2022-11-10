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

string task4 (const string& input) {
    return "";
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

bool task6(const string& a, const string& b) {
	return false;
}