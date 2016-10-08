#include <bits/stdc++.h>
using namespace std;

int T, N;
int S[50005];
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		int res = 0;
		for (int i = 0; i < N; i++) {
			scanf("%d", &S[i]);
			for (int j = 0; j < i; j++) {
				res += S[i] < S[j];
			}
		}
		puts(res % 2 ? "TIDAK" : "YA");
	}
}
