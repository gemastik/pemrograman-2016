#include <bits/stdc++.h>
using namespace std;

const int MAX = 55;

int T;
int N, M;
int C[MAX], P[MAX];
double comb[105][105];

double expected_value(int c) {
	double res = 0;
	for (int i = 0; i <= P[c] && i <= N; i++) {
		res += min(i, C[c]) * comb[P[c]][i] * comb[M-i][N-i];
	}
	return res / comb[M][N];
}

int main() {
	for (int i = 0; i <= 100; i++) {
		comb[i][0] = 1;
		for (int j = 1; j <= i; j++) {
			comb[i][j] = comb[i-1][j] + comb[i-1][j-1];
		}
	}

	scanf("%d", &T);
	for (int tc = 0; tc < T; tc++) {
		scanf("%d", &N);
		memset(C, 0, sizeof C);
		for (int i = 0; i < N; i++) {
			int c;
			scanf("%d", &c);
			C[c-1]++;
		}
		M = 0;
		for (int c = 0; c <= N; c++) {
			scanf("%d", &P[c]);
			M += P[c];
		}

		double x = 0;
		for (int c = 0; c <= N; c++) {
			x += expected_value(c);
		}

		printf("%.5lf\n", x / (2*N - x));
	}
}
