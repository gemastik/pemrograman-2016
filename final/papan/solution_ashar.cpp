#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct SegmentTree {
private:
	int N;
	int sign;
	ll* offset;
	ll* step;

	void update(int node, int b, int e, int i, int j, int x) {
		if (e < i || j < b) {
			return;
		}
		if (i <= b && e <= j) {
			step[node]++;
			offset[node] += x + sign * (b-i);
		} else {
			update(2*node, b, (b+e)/2, i, j, x);
			update(2*node+1, (b+e)/2+1, e, i, j, x);
		}
	}

	ll query(int node, int b, int e, int i) {
		if (e < i || i < b) {
			return 0;
		}
		if (b == e) {
			return offset[node];
		}
		step[2*node] += step[node];
		step[2*node+1] += step[node];

		offset[2*node] += offset[node];
		offset[2*node+1] += offset[node] + sign * step[node] * ((b+e)/2+1-b);
		offset[node] = 0;
		step[node] = 0;

		return query(2*node, b, (b+e)/2, i) + query(2*node+1, (b+e)/2+1, e, i);
	}

public:
	SegmentTree(int N, int sign) {
		this->N = N;
		this->sign = sign;
		this->offset = new ll[4*N+42];
		this->step = new ll[4*N+42];

		for (int i = 0; i < 4*N + 42; i++) {
			offset[i] = step[i] = 0;
		}
	}

	~SegmentTree() {
		delete[] offset;
		delete[] step;
	}

	void update(int i, int j, int x) {
		update(1, 1, N, i, j, x);
	}

	ll query(int i) {
		return query(1, 1, N, i);
	}
};

int T;
int N, M;

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &N, &M);
		SegmentTree pos(N, 1), neg(N, -1);

		for (int i = 0; i < M; i++){
			int x, k;
			scanf("%d %d", &x, &k);

			int a = max(1, x-k+1);
			int h = max(1, k-x+1);
			pos.update(a, x, h);

			if (k > 1) {
				int b = min(N, x+k-1);
				neg.update(x+1, b, k-1);
			}
		}

		for (int i = 1; i <= N; i++) {
			printf("%lld", pos.query(i) + neg.query(i));
			printf("%c", i == N ? '\n' : ' ');
		}
	}
}
