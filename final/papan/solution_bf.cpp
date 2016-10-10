#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int T, N, M;
ll S[50005];
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &N, &M);
		memset(S, 0, sizeof S);
		while (M--) {
			int x, k;
			scanf("%d %d", &x, &k);
			x--;
			S[x] += k;
			for (int i = 1; k-i > 0 && (x-i >= 0 || x+i < N); i++) {
				if (x-i >= 0) {
					S[x-i] += k-i;
				}
				if (x+i < N) {
					S[x+i] += k-i;
				}
			}
		}
		for (int i = 0; i < N; i++) {
			printf("%lld%c", S[i], " \n"[i == N-1]);
		}
	}
}
