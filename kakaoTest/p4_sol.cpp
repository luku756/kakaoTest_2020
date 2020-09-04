#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

/*
��������
�ҹ��� �� ����
�տ���, Ȥ�� �ڿ��� ? �� ������ �� ����


*/

#define MAXCHILD 26
struct Trie {

	int count;	//�� ��带 ������ (��������� ���ڿ��� �����ϴ�) �ܾ��� ��
	Trie* next[MAXCHILD];
	bool finish;	//�� ������ true�̸� �� ��忡�� ������ �ܾ ������.

	//������, finish �� next�� �ʱ�ȭ
	Trie() : finish(false){
		count = 0;
		for (int i = 0; i < MAXCHILD; i++)
			next[i] = NULL;
	}

	//�Ҹ���, ������ ����
	~Trie() {
		for (int i = 0; i < MAXCHILD; i++) {
			if (next[i])
				delete next[i];
		}
	}

	//�� ���ڿ� ����
	void insert(const char* input) {
		count++;
		int index = *input - 'a';
		if (*input == 0) {
			finish = true;
		}
		else {
			if (next[index] == 0) {//�� ���ڷ� �̾����� ��尡 ������ ����
				next[index] = new Trie();
			}
			next[index]->insert(input + 1);//���� ���� ����	
		}
	}

	//�� ���ڿ��� ���λ�� �ϴ� �ܾ��� �� ����
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