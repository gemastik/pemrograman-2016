#include <bits/stdc++.h>
using namespace std;

int T;
int N;

int compute_grundy(int x) {
    int res = 0;
    for (int i = 2; i*i <= x; i++) {
        while (x % i == 0) {
            res++;
            x /= i;
        }
    }
    if (x > 1) {
        res++;
    }
    return res;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		int grundy = 0;
		for (int i = 0; i < N; i++) {
			int x;
			scanf("%d", &x);
			grundy ^= compute_grundy(x);
		}
		puts(grundy ? "TIDAK" : "YA");
	}
}
