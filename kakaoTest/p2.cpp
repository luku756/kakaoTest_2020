#include <string>
#include <vector>
#include <stdio.h>

using namespace std;


bool check_nice(string in) {
	int left = 0, right = 0;
	int level = 0;
	for (int i = 0; i < in.length(); i++) {

		if (in[i] == '(') {
			left++;
			level++;
		}
		else if (in[i] == ')') {
			right++;
			level--;
		}

		if (level < 0)
			return false;
	}
	return left == right;

}

string solution(string p) {
	string answer = "";
	if (p.length() == 0)
		return p;

	string u, v;

	int left = 0, right = 0;

	if (p[0] == '(')
		left = 1;
	else if (p[0] == ')')
		right = 1;
	int i;
	for (i = 1; i < p.length(); i++) {

		if (p[i] == '(')
			left ++;
		else if (p[i] == ')')
			right++;

		if (right == left) {
			break;
		}
	}
	u = p.substr(0,i+1);
	v = p.substr(i+1);

	if (check_nice(u)) {
		answer = u + solution(v);
	}
	else {
		string emp = "(";
		emp += solution(v);
		emp += ")";
		for (int j = 1; j < u.length()-1; j++) {

			if (u[j] == '(')
				emp += ")";
			else if (u[j] == ')')
				emp += "(";
		}
		answer = emp;
	}
	return answer;
}

int main() {
	string input;
	string res;

	input = "(()())()";
	res = solution(input);
	printf("%s\n", res.c_str());


	input = ")(";
	res = solution(input);
	printf("%s\n", res.c_str());
	   
	input = "()))((()";
	res = solution(input);
	printf("%s\n", res.c_str());




	return 0;

}