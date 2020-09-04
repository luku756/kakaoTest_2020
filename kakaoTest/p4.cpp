#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

int check_front(vector<string> words, string keyword, int len) {
	
	int cnt = 0;
	int realLen = len-keyword.length();
	int size = words.size();
	for (int i = 0; i < size; i++) {
		string str = words[i].substr(realLen);
		if (words[i].substr(realLen) == keyword) {
			cnt++;
		}
	}

	return cnt;
}
int check_end(vector<string> words, string keyword) {

	int cnt = 0;
	int realLen = keyword.length();
	int size = words.size();
	for (int i = 0; i < size; i++) {
		string str = words[i].substr(0,realLen);
		if (words[i].substr(0,realLen) == keyword) {
			cnt++;
		}
	}

	return cnt;
}

vector<int> solution(vector<string> words, vector<string> queries) {
	vector<int> answer;

	int len, p;
	int type = 0;
	string real;
	vector< vector<string>> word_len;
	word_len.resize(10000);
	for (int i = 0; i < 10000; i++) {
		vector<string> a;
		word_len[i]=a;
	}


	for (int i = 0; i < words.size(); i++) {
		len = words[i].length();
		word_len[len].push_back(words[i]);
	}

	for (int i = 0; i < queries.size(); i++) {

		len = queries[i].length();

		p = queries[i].find('?');
		if (p == 0) {
			type = 1; p = queries[i].find_last_of('?');
			real = queries[i].substr(p + 1);
		}
		else if (p > 0) {
			type = 2;
			real = queries[i].substr(0, p);
		}
		if (type == 1)
			answer.push_back(check_front(word_len[len], real,len));
		else
			answer.push_back(check_end(word_len[len], real));

	}


	return answer;
}

int main() {

	string word[] = { "frodo", "front", "frost", "frozen", "frame", "kakao" };
	string querie[] = { "fro??", "????o", "fr???", "fro???", "pro?" };

	vector<string> words(word, word + 6);
	vector<string> queries(querie, querie+5);
/*
	for (int i = 0; i < 5; i++) {
		check(words, queries[i]);
	}*/

	vector<int>res = solution(words, queries);

	for (int i = 0; i < res.size(); i++)
		printf("%d\n",res[i]);

	return 0;

}