#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

//int mode -> 0:가로, 1:세로

int visit_width[101][101];
int visit_height[101][101];

struct __stat {
	int time, mode, x, y;
};

typedef struct __stat statss;

bool checkpos(int x, int y, int mode, int n, vector<vector<int>> board) {

	if (!(0 <= x && x < n && 0 <= y && y < n)) {
		return false;
	}

	if (mode == 0) {//가로
		if (visit_width[y][x] == 1)
			return false;
		if (board[y][x] == 1)
			return false;
		if (x ==n-1 || board[y][x+1] == 1)
			return false;
	}

	else if (mode == 1) {//세로
		if (visit_height[y][x] == 1)
			return false;
		if (board[y][x] == 1)
			return false;
		if (y== n - 1 || board[y+1][x] == 1)
			return false;
	}

	return true;
}

bool checkmove(int x, int y, int mode, int n, vector<vector<int>> board) {

	if (!(0 <= x && x < n && 0 <= y && y < n)) {
		return false;
	}

	if (mode == 0) {//가로
		if (board[y][x] == 1)
			return false;
		if (x == n - 1 || board[y][x + 1] == 1)
			return false;
	}

	else if (mode == 1) {//세로
		if (board[y][x] == 1)
			return false;
		if (y == n - 1 || board[y + 1][x] == 1)
			return false;
	}

	return true;
}
int calc(vector<vector<int>> board, int n) {

	statss nowstat;
	queue<statss> que;
	nowstat.time = 0; nowstat.mode = 0; nowstat.x = 0; nowstat.y = 0;

	que.push(nowstat);

	int time,  mode,  x,  y;
	int newx, newy;

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
		
		if (mode == 0) {//가로
			visit_width[y][x] = 1;

			//상하좌우
			//위로 90도 좌우
			//아래로 90도 좌우

			//위
			newx = x; newy = y - 1;
			if (checkpos(newx,newy,mode,n,board)) {
				statss newstat;
				newstat.mode = mode; newstat.time = time + 1; newstat.x = newx; newstat.y = newy;
				que.push(newstat);
			}

			//아래
			newx = x; newy = y + 1;
			if (checkpos(newx, newy, mode, n, board)) {
				statss newstat;
				newstat.mode = mode; newstat.time = time + 1; newstat.x = newx; newstat.y = newy;
				que.push(newstat);
			}

			//좌
			newx = x-1; newy = y;
			if (checkpos(newx, newy, mode, n, board)) {
				statss newstat;
				newstat.mode = mode; newstat.time = time + 1; newstat.x = newx; newstat.y = newy;
				que.push(newstat);
			}

			//우
			newx = x + 1; newy = y;
			if (checkpos(newx, newy, mode, n, board)) {
				statss newstat;
				newstat.mode = mode; newstat.time = time + 1; newstat.x = newx; newstat.y = newy;
				que.push(newstat);
			}

			//위로 90도, 좌 축
			newx = x; newy = y-1;
			if (checkpos(newx, newy, 1, n, board) && checkmove(x, y-1, mode, n, board)) {
				statss newstat;
				newstat.mode = 1; newstat.time = time + 1; newstat.x = newx; newstat.y = newy;
				que.push(newstat);
			}
			//위로 90도, 우 축
			newx = x+1; newy = y - 1;
			if (checkpos(newx, newy, 1, n, board) && checkmove(x, y - 1, mode, n, board)) {
				statss newstat;
				newstat.mode = 1; newstat.time = time + 1; newstat.x = newx; newstat.y = newy;
				que.push(newstat);
			}
			//아래로 90도, 좌 축
			newx = x; newy = y;
			if (checkpos(newx, newy, 1, n, board) && checkmove(x, y + 1, mode, n, board)) {
				statss newstat;
				newstat.mode = 1; newstat.time = time + 1; newstat.x = newx; newstat.y = newy;
				que.push(newstat);
			}
			//아래로 90도, 우 축
			newx = x+1; newy = y;
			if (checkpos(newx, newy, 1, n, board) && checkmove(x, y + 1, mode, n, board)) {
				statss newstat;
				newstat.mode = 1; newstat.time = time + 1; newstat.x = newx; newstat.y = newy;
				que.push(newstat);
			}
		}

		else if (mode == 1) {//세로
			visit_height[y][x] = 1;

			//상하좌우
			//위로 90도 좌우
			//아래로 90도 좌우

			//위
			newx = x; newy = y - 1;
			if (checkpos(newx, newy, mode, n, board)) {
				statss newstat;
				newstat.mode = mode; newstat.time = time + 1; newstat.x = newx; newstat.y = newy;
				que.push(newstat);
			}

			//아래
			newx = x; newy = y + 1;
			if (checkpos(newx, newy, mode, n, board)) {
				statss newstat;
				newstat.mode = mode; newstat.time = time + 1; newstat.x = newx; newstat.y = newy;
				que.push(newstat);
			}

			//좌
			newx = x - 1; newy = y;
			if (checkpos(newx, newy, mode, n, board)) {
				statss newstat;
				newstat.mode = mode; newstat.time = time + 1; newstat.x = newx; newstat.y = newy;
				que.push(newstat);
			}

			//우
			newx = x + 1; newy = y;
			if (checkpos(newx, newy, mode, n, board)) {
				statss newstat;
				newstat.mode = mode; newstat.time = time + 1; newstat.x = newx; newstat.y = newy;
				que.push(newstat);
			}

			//좌로 90도, 상 축
			newx = x-1; newy = y ;
			if (checkpos(newx, newy, 0, n, board) && checkmove(x-1, y , mode, n, board)) {
				statss newstat;
				newstat.mode = 0; newstat.time = time + 1; newstat.x = newx; newstat.y = newy;
				que.push(newstat);
			}
			//우로 90도, 상 축
			newx = x; newy = y;
			if (checkpos(newx, newy, 0, n, board) && checkmove(x + 1, y, mode, n, board)) {
				statss newstat;
				newstat.mode = 0; newstat.time = time + 1; newstat.x = newx; newstat.y = newy;
				que.push(newstat);
			}
			//좌로 90도, 하 축
			newx = x-1; newy = y+1;
			if (checkpos(newx, newy, 0, n, board) && checkmove(x - 1, y, mode, n, board)) {
				statss newstat;
				newstat.mode = 0; newstat.time = time + 1; newstat.x = newx; newstat.y = newy;
				que.push(newstat);
			}
			//우로 90도, 하 축
			newx = x ; newy = y+1;
			if (checkpos(newx, newy, 0, n, board) && checkmove(x + 1, y, mode, n, board)) {
				statss newstat;
				newstat.mode = 0; newstat.time = time + 1; newstat.x = newx; newstat.y = newy;
				que.push(newstat);
			}
		}


	}

}

int solution(vector<vector<int>> board) {
	int answer = 0;

	int n = board.size();

	vector<vector<int>> board_big;
	for (int i = 0; i < n+1; i++) {

		vector<int > board1;
		board1.resize(n+1);
		board_big.push_back(board1);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			board_big[i][j] = board[i][j];
		}
	}
	for (int i = n; i <= n; i++) {
		for (int j = n; j <= n; j++) {
			board_big[i][j] = 1;
		}
	}

	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <=n; j++) {
			visit_width[i][j] = 0;
			visit_height[i][j] = 0;
		}
	}

	return calc(board_big,n);
}

int main() {
	vector<vector<int>> board;
	
	//int in[] = {0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0};
	//int n=5;

	//int in[] = { 0, 0, 0, 0, 0, 0, 1,1, 1, 1, 1, 0, 0, 1,0, 0, 0, 0, 0, 0, 0,0, 0, 1, 1, 1, 1, 0,0, 1, 1, 1, 1, 1, 0,0, 0, 0, 0, 0, 1, 1,0, 0, 1, 0, 0, 0, 0 };
	int in[] = { 0, 0, 0, 0, 0, 0, 1 , 1, 1, 1, 1, 0, 0, 1 , 0, 0, 0, 0, 0, 0, 0 , 0, 0, 1, 1, 1, 0, 0 , 0, 1, 1, 1, 1, 1, 0 , 0, 0, 0, 0, 0, 1, 0 , 0, 0, 1, 0, 0, 0, 0 };
	int n = 7;
	for (int i = 0; i < n; i++) {

		vector<int > board1;
		board1.resize(n);
		board.push_back(board1);
		for (int j = 0; j < n; j++) {
			board1.push_back(in[i*n+j]);
		}
	}

	int res = solution(board);

	printf("%d \n", res);


	return 0;

}