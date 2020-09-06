#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

//int mode -> 0:가로, 1:세로

int visit[101][101][2];

int valid[101][101][2];

struct __stat {
	int time, mode, x, y;
};

typedef struct __stat statss;


int calc(vector<vector<int>> board, int n) {

	statss nowstat;
	queue<statss> que;
	nowstat.time = 0; nowstat.mode = 0; nowstat.x = 0; nowstat.y = 0;

	que.push(nowstat);

	int time, mode, x, y;
	int newx, newy;
	int rollx, rolly;

	while (!que.empty()) {
		nowstat = que.front();
		que.pop();

		time = nowstat.time;
		mode = nowstat.mode;
		x = nowstat.x;
		y = nowstat.y;
		if (x == n - 2 && y == n - 1 && mode == 0)
			return time;

		if (x == n - 1 && y == n - 2 && mode == 1)
			return time;
		
		
		//위
		newx = x; newy = y - 1;
		if ( 0 <= newy  && visit[newy][newx][mode] == 0 && valid[newy][newx][mode] == 1) {
			visit[newy][newx][mode] = 1;
			statss newstat;
			newstat.mode = mode; newstat.time = time + 1; newstat.x = newx; newstat.y = newy;
			que.push(newstat);
		}

		//아래
		newx = x; newy = y + 1;
		if ( newy < n && visit[newy][newx][mode] == 0 && valid[newy][newx][mode] == 1) {
			visit[newy][newx][mode] = 1;
			statss newstat;
			newstat.mode = mode; newstat.time = time + 1; newstat.x = newx; newstat.y = newy;
			que.push(newstat);
		}

		//좌
		newx = x - 1; newy = y;
		if (0 <= newx  &&  visit[newy][newx][mode] == 0 && valid[newy][newx][mode] == 1) {
			visit[newy][newx][mode] = 1;
			statss newstat;
			newstat.mode = mode; newstat.time = time + 1; newstat.x = newx; newstat.y = newy;
			que.push(newstat);
		}

		//우
		newx = x + 1; newy = y;
		if ( newx < n && visit[newy][newx][mode] == 0 && valid[newy][newx][mode] == 1) {
			visit[newy][newx][mode] = 1;
			statss newstat;
			newstat.mode = mode; newstat.time = time + 1; newstat.x = newx; newstat.y = newy;
			que.push(newstat);
		}

		if (mode == 0) {//가로

			//상하좌우
			//위로 90도 좌우
			//아래로 90도 좌우
			int newmode = 1 - mode;
			if (0 <= y - 1 && valid[y - 1][x][mode] == 1) {
				//위로 90도, 좌 축
				newx = x; newy = y - 1;
				if (0 <= newy  && visit[newy][newx][newmode] == 0 && valid[newy][newx][newmode] == 1) {
					visit[newy][newx][newmode] = 1;
					statss newstat;
					newstat.mode = newmode; newstat.time = time + 1; newstat.x = newx; newstat.y = newy;
					que.push(newstat);
				}

				//위로 90도, 우 축
				newx = x + 1; newy = y - 1;
				if ( newx < n && 0 <= newy && visit[newy][newx][newmode] == 0 && valid[newy][newx][newmode] == 1) {
					visit[newy][newx][newmode] = 1;
					statss newstat;
					newstat.mode = newmode; newstat.time = time + 1; newstat.x = newx; newstat.y = newy;
					que.push(newstat);
				}

			}

			if ( y + 1 < n && valid[y + 1][x][mode] == 1) {
				//아래로 90도, 좌 축
				newx = x; newy = y;
				if (visit[newy][newx][newmode] == 0 && valid[newy][newx][newmode] == 1) {
					visit[newy][newx][newmode] = 1;
					statss newstat;
					newstat.mode = newmode; newstat.time = time + 1; newstat.x = newx; newstat.y = newy;
					que.push(newstat);
				}

				//아래로 90도, 우 축
				newx = x + 1; newy = y;
				if ( newx < n  && visit[newy][newx][newmode] == 0 && valid[newy][newx][newmode] == 1) {
					visit[newy][newx][newmode] = 1;
					statss newstat;
					newstat.mode = newmode; newstat.time = time + 1; newstat.x = newx; newstat.y = newy;
					que.push(newstat);
				}
			}


		}

		else if (mode == 1) {//세로

			int newmode = 1 - mode;

			if (0 <= x - 1  && valid[y][x - 1][mode] == 1) {

				//좌로 90도, 상 축
				newx = x - 1; newy = y;
				if (0 <= newx && visit[newy][newx][newmode] == 0 && valid[newy][newx][newmode] == 1) {
					visit[newy][newx][newmode] = 1;
					statss newstat;
					newstat.mode = newmode; newstat.time = time + 1; newstat.x = newx; newstat.y = newy;
					que.push(newstat);
				}


				//좌로 90도, 하 축
				newx = x - 1; newy = y + 1;
				if (0 <= newx && newy < n && visit[newy][newx][newmode] == 0 && valid[newy][newx][newmode] == 1) {
					visit[newy][newx][newmode] = 1;
					statss newstat;
					newstat.mode = newmode; newstat.time = time + 1; newstat.x = newx; newstat.y = newy;
					que.push(newstat);
				}
			}


			if ( x + 1 < n && valid[y][x + 1][mode] == 1) {

				//우로 90도, 상 축
				newx = x; newy = y;
				if (visit[newy][newx][newmode] == 0 && valid[newy][newx][newmode] == 1) {
					visit[newy][newx][newmode] = 1;
					statss newstat;
					newstat.mode = newmode; newstat.time = time + 1; newstat.x = newx; newstat.y = newy;
					que.push(newstat);
				}
				//우로 90도, 하 축
				newx = x; newy = y + 1;
				if (newy < n && visit[newy][newx][newmode] == 0 && valid[newy][newx][newmode] == 1) {
					visit[newy][newx][newmode] = 1;
					statss newstat;
					newstat.mode = newmode; newstat.time = time + 1; newstat.x = newx; newstat.y = newy;
					que.push(newstat);
				}
			}
		}




	}

}

int solution(vector<vector<int>> board) {
	int answer = 0;

	int n = board.size();


	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			visit[i][j][0] = 0;
			visit[i][j][1] = 0;
		}
	}


	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n; j++) {
			if (board[i][j] == 0 && board[i + 1][j] == 0) {
				valid[i][j][1] = 1;
			}
			else
				valid[i][j][1] = 0;

		}
	}


	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - 1; j++) {
			if (board[i][j] == 0 && board[i][j + 1] == 0) {
				valid[i][j][0] = 1;
			}
			else
				valid[i][j][0] = 0;

		}
	}

	return calc(board, n);
}

int main() {
	vector<vector<int>> board;

	//int in[] = {0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0};
	//int n=5;

	//int in[] = { 0, 0, 0, 0, 0, 0, 1 , 1, 1, 1, 1, 0, 0, 1 , 0, 0, 0, 0, 0, 0, 0 , 0, 0, 1, 1, 1, 1, 0 , 0, 1, 1, 1, 1, 1, 0 , 0, 0, 0, 0, 0, 1, 1 , 0, 0, 1, 0, 0, 0, 0 };
	//int in[] = { 0, 0, 0, 0, 0, 0, 1 , 1, 1, 1, 1, 0, 0, 1 , 0, 0, 0, 0, 0, 0, 0 , 0, 0, 1, 1, 1, 0, 0 , 0, 1, 1, 1, 1, 1, 0 , 0, 0, 0, 0, 0, 1, 0 , 0, 0, 1, 0, 0, 0, 0 };

	int in[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 , 1, 1, 1, 1, 1, 1, 1, 0, 0 , 1, 1, 1, 1, 1, 1, 1, 1, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0, 0, 1, 1, 1, 1, 1, 0, 0 , 0, 1, 1, 1, 1, 1, 1, 1, 1 , 0, 0, 1, 1, 1, 1, 1, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0 , 1, 1, 1, 1, 1, 1, 1, 1, 0 };
	int n = 9;
	for (int i = 0; i < n; i++) {

		vector<int > board1;
		for (int j = 0; j < n; j++) {
			board1.push_back(in[i * n + j]);
		}
		board.push_back(board1);
	}


	//int n = 100;
	//for (int i = 0; i < n; i++) {

	//	vector<int > board1;
	//	for (int j = 0; j < n; j++) {
	//		board1.push_back(0);
	//	}
	//	board.push_back(board1);
	//}

	int res = solution(board);

	printf("%d \n", res);


	return 0;

}