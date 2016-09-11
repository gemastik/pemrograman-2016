#include <bits/stdc++.h>
using namespace std;

const int MAX = 50005;

int T;
int N;
list<int> G[MAX];
int dp[MAX][2][3];

int DP(int u, int par, int a, int b) {
	if (dp[u][a][b] != -1) {
		return dp[u][a][b];
	}
	int& res = dp[u][a][b];

	int all_opposites = 0;
	for (int v : G[u]) if (v != par) {
		all_opposites += DP(v, u, 1-a, a);
	}
	res = a + all_opposites;

	if (a != b) {
		for (int v : G[u]) if (v != par) {
			res = min(res, a + all_opposites - DP(v, u, 1-a, a) + DP(v, u, a, a));
		}
	}
	return res;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			G[i].clear();
		}
		for (int i = 1; i < N; i++) {
			int u, v;
			scanf("%d %d", &u, &v);
			u--, v--;
			G[u].push_back(v);
			G[v].push_back(u);
		}
		memset(dp, -1, sizeof dp);
		printf("%d\n", min(DP(0, -1, 0, 2), DP(0, -1, 1, 2)));
	}
}
