#include <string>
#include <vector>

using namespace std;

int recv(int n, int nextdist, int walkercnt, int valcnt, vector<int> val, int* distarr, vector<int> dist) {
	
	if (valcnt > val.size())//��
		return walkercnt;

	if (valcnt == val.size())//��
		return walkercnt+1;

	//nextdist == -1, ��ŵ. ���� �ܰ谡 skip �� �ƴϾ��� ���� ȣ��.
	int flag = nextdist;

	   
	while (1) {

		if (valcnt >= val.size())
			return walkercnt+1;

		if (val[valcnt] <= nextdist) {
			nextdist -= val[valcnt];
			valcnt++;
		}
		else
			break;
	}
	int plusw=1;
	//if (flag == nextdist) {//��ȭ ����, �� ������ Ŀ��
	//	plusw = 0;
	//}
	//else {
	//	valcnt++;
	//	if (valcnt >= val.size())
	//		valcnt--;
	//}
	valcnt++;

	int newdistarr[10];
	for (int i = 0; i < dist.size(); i++) {
		newdistarr[i] = distarr[i];
	}


	int minw=dist.size()+1;
	int w;
	for (int i = 0; i < dist.size(); i++) {
		if (newdistarr[i] == 1) {//���� �� ���� ģ��
			newdistarr[i] = 0;
			w = recv(n,dist[i], walkercnt+ plusw,valcnt,val, newdistarr,dist);
			if (w < minw) {
				minw = w;
			}
			newdistarr[i] = 1;
		}
	}
	if (flag != -1) {
		w = recv(n, -1, walkercnt + plusw, valcnt, val, newdistarr, dist);
		if (w < minw) {
			minw = w;
		}
	}

	return minw;
}

int calc(int n, vector<int> val, vector<int> dist) {

	int newdistarr[10];
	for (int i = 0; i < dist.size(); i++) {
		newdistarr[i] = 1;
	}

	int minw = dist.size() + 1;
	int w;
	for (int i = 0; i < dist.size(); i++) {
		newdistarr[i] = 0;
		w = recv(n, dist[i], 0, 0, val, newdistarr, dist);
		if (w < minw) {
			minw = w;
		}
		newdistarr[i] = 1;

	}
	w = recv(n, -1, 0, 0, val, newdistarr, dist);
	if (w < minw) {
		minw = w;
	}
	return minw;

}

int solution(int n, vector<int> weak, vector<int> dist) {
	int answer = 0;

	//��� ģ���� �� ��������� ���.
	//���� �� ������ ������ �κп����� �ݵ�� �� �� �̻��� ���.
	//���������� ���� ����� ���� ����.

	vector<int> interval, inteval_sort;
	weak.push_back(weak[0]+n);

	interval.resize(weak.size() - 1);
	inteval_sort.resize(weak.size() - 2);
	//���� ���ϱ�
	int max=0, maxi=0;
	
	for (int i = 0; i < weak.size()-1; i++) {
		interval[i] = weak[i + 1] - weak[i];
		if (max < interval[i]) {
			max = interval[i];
			maxi = i;
		}
	}
	int id = 0;
	for (int i = maxi+1; i < interval.size(); i++) {
		inteval_sort[id++] = interval[i];
	}

	for (int i = 0; i < maxi; i++) {
		inteval_sort[id++] = interval[i];
	}
	//inteval_sort.push_back(max);
	
	//�ִ�, �ּ� ���
	int total = n - max;
	if (dist[dist.size() - 1] >= total){
		return 1;

		}
	

	

	answer = calc(n,inteval_sort,dist);

	if (answer > dist.size()) {
	
		
		return -1;
	}

	return answer;
}

int main() {

	//int weaks[] = { 1,5,6,10 };
	//int dists[] = {1,2,3,4};
	//int weaks[] = {1,3,5,9,11 };
	//int dists[] = {1,1, 1, 1, 1};
	//int weaks[] = {1,3,4,9,10 };
	//int dists[] = {1,3,6};
	//int weaks[] = { 1,8 };
	//int dists[] = { 1,1};
	//int n = 12;

	int weaks[] = { 0,3,11,21 };
	int dists[] = { 4,10 };
	int n = 30;
	vector<int> weak(weaks, weaks+4);
	vector<int> dist(dists,dists+2);
	int res = solution(n,weak,dist);

			printf("%d \n", res);


	return 0;

}