#include <string>
#include <stdio.h>

#define MAXCHILD 26
struct Trie {

	bool finish;	//이 변수가 true이면 이 노드에서 끝나는 단어가 존재함.
	Trie* next[MAXCHILD];

	//생성자, finish 와 next를 초기화
	Trie() : finish(false) {
		memset(next, 0, sizeof(next));
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
		if (*input == 0) {
			finish = true;
		}
		else {
			int index = *input - 'a';
			if (next[index] == 0) {//이 글자로 이어지는 노드가 없으면 생성
				next[index] = new Trie();
			}
			next[index]->insert(input + 1);//다음 노드로 진행	
		}

	}

	//이 단어로 시작하는 것이 있는지만 확인, ex) abc, abde 만 들어있을 경우 ab는 find 되지만 exist 하지 않음.
	Trie* find(const char* key) {
		if (*key == 0) {
			return this;
		}
		else {
			int index = *key - 'a';
			if (next[index] == 0)
				return NULL;
			return next[index]->find(key + 1);
		}
	}

	//이 단어가 명확하게 트리에 포함되어 있는지 확인.
	bool isExist(const char* key) {
		if (*key == 0 && finish == true) {
			return true;
		}
		else {
			int index = *key - 'a';
			if (next[index] == 0)
				return NULL;
			return next[index]->isExist(key + 1);
		}
	}
};

int main() {

	Trie * root = new Trie();

	const char * words[5] = { "be", "bee", "can", "cat", "cd" };

	for (int i = 0; i < 5; ++i) {
		printf("insert: %s\n", words[i]);
		root->insert(words[i]);
	}

	printf("\n");

	printf("%s: be\n", root->find("be") != 0 ? "Prefix Exist" : "Prefix Not Exist");
	printf("%s: can\n", root->find("can") != 0 ? "Prefix Exist" : "Prefix Not Exist");
	printf("%s: a\n", root->find("a") != 0 ? "Prefix Exist" : "Prefix Not Exist");
	printf("%s: cat\n", root->find("cat") != 0 ? "Prefix Exist" : "Prefix Not Exist");
	printf("%s: c\n", root->find("c") != 0 ? "Prefix Exist" : "Prefix Not Exist");

	printf("\n");

	printf("%s: c\n", root->isExist("c") != 0 ? "String Exist" : "String Not Exist");
	printf("%s: be\n", root->isExist("be") != 0 ? "String Exist" : "String Not Exist");
	printf("%s: bee\n", root->isExist("bee") != 0 ? "String Exist" : "String Not Exist");
	printf("%s: candy\n", root->isExist("candy") != 0 ? "String Exist" : "String Not Exist");
	printf("%s: cd\n", root->isExist("cd") != 0 ? "String Exist" : "String Not Exist");

	delete root;

	return 0;

}