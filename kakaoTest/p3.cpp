#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

bool check(vector<vector<int>> key, vector<vector<int>> lock, int offx, int offy, int N, int M) {
	if (offx == 1 && offy == 1) {
		offx = offy;
	}
	if (offx == 0 && offy == 0) {
		offx = offy;
	}
	int keyx, keyy;
	int lod;
	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++) {
			keyx = x - offx;
			keyy = y - offy;
			if (keyx < 0 || keyx >= M || keyy < 0 || keyy >= M) {
				lod = -100;
			}
			else
				lod = key[keyx][keyy];

			if ((lock[x][y] == 0 && lod + lock[x][y] != 1) || lod + lock[x][y] == 2) {
				return false;
			}

		}
	}
	return true;
}

vector<vector<int>> rotate(vector<vector<int>> input) {
	int size = input.size();
	vector<vector<int>> res;
	for (int i = 0; i < size; i++) {
		vector<int> a;
		a.resize(size);
		res.push_back(a);
	}

	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			res[x][y] = input[y][size-1-x];
		
		}
	}

	return res;
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
	bool answer = true;
	int M = key.size(), N = lock.size();

	int minoff = -M + 1, maxoff = N-1;

	for (int x = minoff; x <= maxoff; x++) {

		for (int y = minoff; y <= maxoff; y++) {
			if (check(key, lock, y, x,N,M)) {
				return true;
			}
		}
	}

	key = rotate(key);

	for (int x = minoff; x <= maxoff; x++) {

		for (int y = minoff; y <= maxoff; y++) {
			if (check(key, lock, y, x, N, M)) {
				return true;
			}
		}
	}


	key = rotate(key);

	for (int x = minoff; x <= maxoff; x++) {

		for (int y = minoff; y <= maxoff; y++) {
			if (check(key, lock, y, x, N, M)) {
				return true;
			}
		}
	}

	key = rotate(key);

	for (int x = minoff; x <= maxoff; x++) {

		for (int y = minoff; y <= maxoff; y++) {
			if (check(key, lock, y, x, N, M)) {
				return true;
			}
		}
	}



	return false;
}

int main() {

	vector<vector<int>> key;
	vector<vector<int>> lock;

	key.resize(3);
	key[0] = vector<int>();
	key[0].push_back(0);
	key[0].push_back(0);
	key[0].push_back(0);
	key[1] = vector<int>();
	key[1].push_back(1);
	key[1].push_back(0);
	key[1].push_back(0);
	key[2] = vector<int>();
	key[2].push_back(0);
	key[2].push_back(1);
	key[2].push_back(1);



	lock.resize(3);
	lock[0] = vector<int>();
	lock[0].push_back(1);
	lock[0].push_back(1);
	lock[0].push_back(1);
	lock[1] = vector<int>();
	lock[1].push_back(1);
	lock[1].push_back(1);
	lock[1].push_back(0);
	lock[2] = vector<int>();
	lock[2].push_back(1);
	lock[2].push_back(0);
	lock[2].push_back(1);

	bool res = solution(key, lock);
	if (res)
		printf("true\n");
	else
		printf("false\n");
	
	return 0;

}