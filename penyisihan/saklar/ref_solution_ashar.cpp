#include <bits/stdc++.h>
using namespace std;

int T;
int L, B;

bool can(int cP, int cT) {
	int l = L, b = B;
	int bP = min(b, cP);
	b -= bP;
	cP -= bP;

	int bT = min(b, cT / 2);
	b -= bT;
	cT -= 2 * bT;

	return b == 0 && l <= cP + cT;
}

int solve() {
	int cP = 2;
	int cT = 2;
	for (int res = 1;; res++) {
		if (can(cP, cT)) {
			return res;
		}
		cT++;
		cP += 2;
	}
}

int main() {
	cin >> T;
	while (T--) {
		cin >> L >> B;
		cout << solve() << endl;
	}
}
