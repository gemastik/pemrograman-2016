#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Point {
	ll x, y;
	Point(ll a=0, ll b=0) : x(a), y(b){}
	bool operator<(Point o) const {
		return (x < o.x) || ((x == o.x) && (y < o.y));
	}
	Point operator+(Point o) {return Point(x+o.x, y+o.y);}
	Point operator-(Point o) {return Point(x-o.x, y-o.y);}
};

int T;
int N, Q;
Point data[100005];
Point temp[100005];

ll cp(Point a, Point b) {return a.x*b.y - a.y*b.x;}
ll cp(Point o, Point a, Point b) {return cp(a-o, b-o);}

ll solve(int a, int cnt) {
	int k = 0;
	for (int i = N-1; i >= a; i--) {
		while (k >= 2 && cp(temp[k-2], temp[k-1], data[i]) <= 0) {
			k--;
		}
		temp[k++] = data[i];
	}

	reverse(temp, temp + k);
	cnt = min(cnt, k);

	ll area = 0;
	for (int i = 1; i < cnt-1; i++) {
		area += cp(temp[0], temp[i], temp[(i+1)%cnt]);
	}
	return abs(area);
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			ll x, y;
			scanf("%lld %lld", &x, &y);
			data[i] = Point(x, y);
		}
		sort(data, data+N);
		scanf("%d", &Q);
		for (int i = 0; i < Q; i++) {
			int x1, k;
			scanf("%d %d", &x1, &k);
			int a = -1;
			for (int j = 0; j < N; j++) {
				if (data[j].x >= x1) {
					a = j;
					break;
				}
			}
			if (a == -1) {
				printf("0.0\n");
				continue;
			}
			ll res = solve(a, k);
			printf("%lld.%d\n", res/2, res % 2 ? 5 : 0);
		}
	}
}
