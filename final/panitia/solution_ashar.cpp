#include <bits/stdc++.h>
using namespace std;

const int MAX = 55;

int T;
int N, M;
int C[MAX], P[MAX];
double dp[MAX][MAX][MAX];
double prob[MAX];

double compute_prob(const vector<pair<int, int>>& combs) {
	vector<int> num, denom;

	for (int x = 0; x < 2; x++) {
		for (int i = 1; i <= combs[x].second; i++) {
			denom.push_back(i);
			num.push_back(combs[x].first-i+1);
		}
	}
	for (int i = 1; i <= combs[2].second; i++) {
		num.push_back(i);
		denom.push_back(combs[2].first-i+1);
	}

	double res = 1;
	int nn = num.size(), nd = denom.size();
	int in = 0, id = 0;
	while (in < nn || id < nd) {
		if (res > 1 && id < nd) {
			res /= denom[id++];
		} else if (in < nn) {
			res *= num[in++];
		} else if (id < nd) {
			res /= denom[id++];
		}
	}
	return res;
}

int main() {
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

		memset(dp, 0, sizeof dp);
		dp[0][0][0] = 1;
		for (int i = 0; i <= N; i++) {
			for (int j = 0; j <= N; j++) {
				int n = N-j;

				for (int k = 0; k <= P[i] && k <= n; k++) {
					prob[k] = compute_prob({ {P[i], k}, {M-P[i], n-k}, {M, n} });
					//prob[k] = comb[P[i]][k] * comb[M-P[i]][n-k] / comb[M][n];
				}

				for (int k = 0; k <= j; k++) {
					if (!dp[i][j][k]) {
						continue;
					}

					for (int l = 0; l <= P[i] && l <= n; l++) {
						int kena = min(C[i], l);
						dp[i+1][j+l][k+kena] += prob[l] * dp[i][j][k];
					}
				}
			}
			M -= P[i];
		}

		double res = 0;
		for (int k = 0; k <= N; k++) {
			res += dp[N+1][N][k] * k / (2*N - k);
		}

		printf("%.3lf\n", res);
	}
}
