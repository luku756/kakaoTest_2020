#include <string>
#include <stdio.h>

#define MAXCHILD 26
struct Trie {

	bool finish;	//�� ������ true�̸� �� ��忡�� ������ �ܾ ������.
	Trie* next[MAXCHILD];

	//������, finish �� next�� �ʱ�ȭ
	Trie() : finish(false) {
		memset(next, 0, sizeof(next));
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
		if (*input == 0) {
			finish = true;
		}
		else {
			int index = *input - 'a';
			if (next[index] == 0) {//�� ���ڷ� �̾����� ��尡 ������ ����
				next[index] = new Trie();
			}
			next[index]->insert(input + 1);//���� ���� ����	
		}

	}

	//�� �ܾ�� �����ϴ� ���� �ִ����� Ȯ��, ex) abc, abde �� ������� ��� ab�� find ������ exist ���� ����.
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

	//�� �ܾ ��Ȯ�ϰ� Ʈ���� ���ԵǾ� �ִ��� Ȯ��.
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