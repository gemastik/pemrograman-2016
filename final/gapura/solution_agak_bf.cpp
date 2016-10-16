#include <bits/stdc++.h>
using namespace std;

const int OFFSET = 2500000;

int T;
int N;

int L[25], nL;
int R[25], nR;

vector<int> right_diff[OFFSET+OFFSET+42];

int total;
int ANS;

void gen_right(int i, int cur_diff, int cur_len) {
	if (i == nR) {
		right_diff[cur_diff + OFFSET].push_back(cur_len);
		return;
	}

	gen_right(i+1, cur_diff+R[i], cur_len);
	gen_right(i+1, cur_diff-R[i], cur_len);
	gen_right(i+1, cur_diff, cur_len+R[i]);
}

void gen_left(int i, int cur_diff, int cur_len) {
	if (i == nL) {
		for (int right_len : right_diff[OFFSET - cur_diff]) {
			int len = cur_len + right_len;
			assert((total - len) % 2 == 0);
			int hi = (total - len) / 2;
			ANS = max(ANS, hi * len);
		}
		return;
	}

	gen_left(i+1, cur_diff+L[i], cur_len);
	gen_left(i+1, cur_diff-L[i], cur_len);
	gen_left(i+1, cur_diff, cur_len+L[i]);
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		nL = N/2;
		nR = N - N/2;
		total = 0;
		for (int i = 0; i < nL; i++) {
			scanf("%d", &L[i]);
			total += L[i];
		}
		for (int i = 0; i < nR; i++) {
			scanf("%d", &R[i]);
			total += R[i];
		}

		for (int i = 0; i < OFFSET+OFFSET+42; i++) {
			right_diff[i].clear();
		}

		ANS = 0;
		gen_right(0, 0, 0);
		gen_left(0, 0, 0);

		printf("%d\n", ANS);
	}
}
