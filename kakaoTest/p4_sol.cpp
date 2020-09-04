#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

/*
전제조건
소문자 만 등장
앞에만, 혹은 뒤에만 ? 가 등장할 수 있음


*/

#define MAXCHILD 26
struct Trie {

	int count;	//이 노드를 지나는 (여기까지의 문자열을 포함하는) 단어의 수
	Trie* next[MAXCHILD];
	bool finish;	//이 변수가 true이면 이 노드에서 끝나는 단어가 존재함.

	//생성자, finish 와 next를 초기화
	Trie() : finish(false){
		count = 0;
		for (int i = 0; i < MAXCHILD; i++)
			next[i] = NULL;
	}

	//소멸자, 데이터 정리
	~Trie() {
		for (int i = 0; i < MAXCHILD; i++) {
			if (next[i])
				delete next[i];
		}
	}

	//새 문자열 삽입
	void insert(const char* input) {
		count++;
		int index = *input - 'a';
		if (*input == 0) {
			finish = true;
		}
		else {
			if (next[index] == 0) {//이 글자로 이어지는 노드가 없으면 생성
				next[index] = new Trie();
			}
			next[index]->insert(input + 1);//다음 노드로 진행	
		}
	}

	//이 문자열을 접두사로 하는 단어의 수 리턴
	int find(const char* key) {
		if (*key == 0) {
			return count;
		}

		else {
			int index = *key - 'a';
			if (next[index] == 0)
				return 0;
			return next[index]->find(key + 1);
		}
	}

};


Trie trie[10001];
Trie trie_rev[10001];


string reverse(string a) {
	string res = "";
	int len = a.length();
	for (int i = 0; i < len; i++) {
		res += a[len - i-1];
	}
	return res;
}

vector<int> solution(vector<string> words, vector<string> queries) {
	vector<int> answer;

	int len, p;
	int type = 0;
	string real;
		

	for (int i = 0; i < words.size(); i++) {
		len = words[i].length();
		trie[len].insert(words[i].c_str());
		trie_rev[len].insert(reverse(words[i]).c_str());
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
		if (type == 1) {
			int res = trie_rev[len].find(reverse(real).c_str());
			//int res = 0;
			answer.push_back(res);

		}
		else {
			int res = trie[len].find(real.c_str());
			//int res = 0;
			answer.push_back(res);
			
		}

	}


	return answer;
}

int main() {

	string word[] = { "frodo", "front", "frost", "frozen", "frame", "kakao" };
	//string querie[] = { "fr???", "fro??", "????o", "fro???", "pro?" };
	string querie[] = { "fro??", "????o", "fr???", "fro???", "pro?" };

	vector<string> words(word, word + 6);
	vector<string> queries(querie, querie + 5);
	/*
		for (int i = 0; i < 5; i++) {
			check(words, queries[i]);
		}*/

	vector<int>res = solution(words, queries);

	for (int i = 0; i < res.size(); i++)
		printf("%d\n", res[i]);

	return 0;

}