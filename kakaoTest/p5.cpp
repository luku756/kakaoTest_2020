#include <string>
#include <vector>

using namespace std;


int stick[101][101];
int wall[101][101];

bool check_build_stick(int x, int y, int n) {
	if (y == 0)
		return true;

	if (wall[y][x] == 1)
		return true;
	if (x > 0 && wall[y][x - 1] == 1)
		return true;
	if (y > 0 && stick[y - 1][x] == 1)
		return true;

	return false;
}
bool check_build_wall(int x, int y, int n) {

	if (y > 0 && stick[y - 1][x] == 1)
		return true;


	if (y > 0 && x < n && stick[y - 1][x+1] == 1)
		return true;

	if(x > 0 && x <n && wall[y][x-1] == 1 && wall[y][x + 1] == 1)
		return true;


	return false;
}

bool check_all(int x, int y, int n) {

	bool res;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			if (stick[i][j] == 1) {

				stick[i][j] = 0;
				res = check_build_stick(j, i, n);
				stick[i][j] = 1;
				if (!res)
					return false;
			}

			if (wall[i][j] == 1) {

				wall[i][j] = 0;
				res = check_build_wall(j, i, n);
				wall[i][j] = 1;
				if (!res)
					return false;
			}
		}
	}

	return true;
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {

	vector<vector<int>> answer;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			stick[i][j] = 0;
			wall[i][j] = 0;
		}
	}
	int x, y, a, b;
	bool check;
	for (int q = 0; q < build_frame.size(); q++) {
		x = build_frame[q][0];
		y = build_frame[q][1];
		a = build_frame[q][2];
		b = build_frame[q][3];
		if (b == 1) {//¼³Ä¡
			if (a == 0) {//±âµÕ
				check = check_build_stick(x, y, n);
				if (check) {
					//printf("build stick %d %d\n",x,y);

					stick[y][x] = 1;
				}
				else {
					//printf("build stick %d %d Fail!\n", x, y);

				}
			}
			else {//º¸
				check = check_build_wall(x, y, n);
				if (check) {
					//printf("build wall %d %d\n", x, y);
					wall[y][x] = 1;
				}
				else {
					//printf("build stick %d %d Fail!\n", x, y);

				}
			}

		}
		else if (b == 0) {//»èÁ¦
			if (a == 0) {//±âµÕ
				stick[y][x] = 0;
				check = check_all(x, y, n);
				if (!check) {
					stick[y][x] = 1;
					//printf("remove stick %d %d Fail!\n", x, y);
				}
				else {
					//printf("remove stick %d %d!\n", x, y);

				}
			}
			else {//º¸
				wall[y][x] = 0;
				check = check_all(x, y, n);
				if (!check) {
					wall[y][x] = 1;
					//printf("remove wall %d %d Fail!\n", x, y);
				}

				else {
					//printf("remove wall %d %d!\n", x, y);

				}
			}
		}
	}



	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			if (stick[j][i] == 1) {
				vector<int> tmp;
				tmp.push_back(i);
				tmp.push_back(j);
				tmp.push_back(0);
				answer.push_back(tmp);
			}
			if (wall[j][i] == 1) {
				vector<int> tmp;
				tmp.push_back(i);
				tmp.push_back(j);
				tmp.push_back(1);
				answer.push_back(tmp);
			}
		}
		
	}

	return answer;
}

int main() {

	int arr[8][4] = { {1, 0, 0, 1},{1, 1, 1, 1 }, {2, 1, 0, 1}, {2, 2, 1, 1}, {5, 0, 0, 1}, {5, 1, 0, 1}, {4, 2, 1, 1}, {3, 2, 1, 1} };
	//int arr[10][4] = {{0, 0, 0, 1},{2, 0, 0, 1},{4, 0, 0, 1},{0, 1, 1, 1},{1, 1, 1, 1},{2, 1, 1, 1},{3, 1, 1, 1},{2, 0, 0, 0},{1, 1, 1, 0},{2, 2, 0, 1}};

	vector<vector<int>> build_frame;

	for (int i = 0; i < 8; i++) {
		vector<int> a;
		for (int j = 0; j < 4; j++) {
			a.push_back(arr[i][j]);
		}
		build_frame.push_back(a);
	}


	vector<vector<int>> res = solution(5, build_frame);

	for (int i = 0; i < res.size(); i++) {

		for (int j = 0; j < res[i].size(); j++) {
			printf("%d ", res[i][j]);

		}
		printf("\n");
	}

	return 0;

}