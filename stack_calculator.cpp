#include "iostream"
#include <stack>
#include <string>
#include <cmath>

int Priority(char ch) {
	switch (ch) {
	case '(':
		return 5;
	case '^':
		return 4;
	case '_':
		return 3;
	case '*':
	case '/':
		return 2;
	case '+':
	case '-':
		return 1;
	default:
		return 0;
	}
}

bool checkBrackets(std::string s) {
	std::stack<char> brackets;
	bool flag = true;
	for (int i = 0; i < s.size() && flag; i++) {
		if (s[i] == '(') {
			brackets.push(s[i]);
		}
		else if (brackets.empty() && s[i] == ')') {
			flag = false;
		}
		else if (!brackets.empty() && s[i] == ')') {
			if (brackets.top() == '(' && s[i] == ')')
				brackets.pop();
			else flag = false;;
		}
	}
	if (!brackets.empty())
		flag = false;
	return flag;
}

bool check(std::string str) {
	bool flag = true;
	if (!checkBrackets(str)) {
		return false;
	}
	else {
		for (int i = 0; i < str.size() && flag; i++) {
			if (!((str[i] >= '0' && str[i] <= '9') || str[i] == '(' || str[i] == ')' || str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*' || str[i] == '^' || str[i] == '.')) {
				return false;
			}
			if (i > 0 && str[i] == '-' && !((str[i - 1] >= '0' && str[i - 1] <= '9') || str[i - 1] == '(' || str[i - 1] == ')')) {
				return false;
			}
			if (i > 0 && (str[i-1] == '+' || str[i-1] == '-' || str[i-1] == '/' || str[i-1] == '*' || str[i-1] == '^') && (str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*' || str[i] == '^') ) {
				return false;
			}
			if (i > 0 && i + 1 < str.size() && str[i] == '.' && !((str[i - 1] >= '0' && str[i - 1] <= '9') && (str[i + 1] >= '0' && str[i + 1] <= '9'))) {
				return false;
			}
				
		}
	}
	return flag;

}
