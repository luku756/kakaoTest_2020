#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int calc(int n, vector<int> list, vector<int> dist) {

	int now = list[0];
	int work;
	int cnt = 0;
	int i;
	for (i = 0; i < dist.size(); i++) {
		now = list[cnt];
		work = dist[i];
		now += work;
		while (1) {
			if (list[cnt] <= now) {
				cnt++;
			}
			else
				break;
			if (cnt == list.size())
				return i+1;
		}
		if (cnt == list.size())
			return i + 1;
	}

	return i + 1;

}

int solution(int n, vector<int> weak, vector<int> dist) {
	int answer = dist.size()+1;

	for (int index = 0; index < weak.size(); index++) {
		vector<int> list;
		vector<int> friends;

		for (int i = index; i < weak.size(); i++) {
			list.push_back(weak[i]);
		}

		for (int i = 0; i < index; i++) {
			list.push_back(weak[i]+n);
		}

		for (int i = 0; i < dist.size(); i++) {
			friends.push_back(dist[i]);
		}

		do {
			int res = calc(n,list,friends);
			if (res < answer)
				answer = res;

		} while (next_permutation(friends.begin(), friends.end()));
	}

	if (answer > dist.size())
		return -1;

	return answer;
}

int main() {

	//int weaks[] = { 1,5,6,10 };
	//int dists[] = {1,2,3,4};
	//int weaks[] = {1,3,5,9,11 };
	//int dists[] = {1,1, 1, 1, 1};
	int weaks[] = {1,3,4,9,10 };
	int dists[] = {1,3,7};
	//int weaks[] = { 1,8 };
	//int dists[] = { 1,1};
	int n = 12;

	//zint weaks[] = { 0,3,11,21 };
	//zint dists[] = { 4,10 };
	//zint n = 30;
	vector<int> weak(weaks, weaks + 5);
	vector<int> dist(dists, dists + 3);
	int res = solution(n, weak, dist);

	printf("%d \n", res);


	return 0;

}