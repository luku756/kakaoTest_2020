#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

int cal(string in, int len) {

	int cnt = 1;
	int offset;
	string ts;
	string result = "";

	ts = in.substr(0, len);
	offset = len;

	string next;
	while (true) {
		next = in.substr(offset, len);
		

		if (ts == next) {
			cnt++;
			offset += len;
		}
		else {

			if (cnt == 1) {
				result += ts;
				offset+=len;
				ts = next;
			}
			else {
				result += to_string(cnt);
				cnt = 1;
				result += ts;
				if (next.length() != 0) {
					offset+=len;
					ts = next;
				}
			}

		}
		if (next.length() == 0 || ts.length() < len) {
			if (ts.length() < len)
				result += ts;
			break;
		}
	}
	int leng = result.length();
	return result.length();
}


int solution(string s) {
	int answer = 0;
	int maxlen = s.length()/2;
	int min = s.length();
	for (int len = 1; len <= maxlen; len++) {
		int tmp = cal(s, len);
		if (tmp < min)
			min = tmp;
	}
	answer = min;
	return answer;
}

int main() {
	string input;
	int res;


	input = "aabbaccc";
	res = solution(input);
	printf("%d\n", res);

	input = "ababcdcdababcdcd";
	res = solution(input);
	printf("%d\n", res);



	input = "abcabcdede";
	res = solution(input);
	printf("%d\n", res);

	input = "abcabcabcabcdededededede";
	res = solution(input);
	printf("%d\n", res);

	input = "xababcdcdababcdcd";
	res = solution(input);
	printf("%d\n", res);



}