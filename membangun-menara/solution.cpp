#include <bits/stdc++.h>
using namespace std;

int main() {
	int T;
	int N;
	scanf("%d",&T);
	int a[3];

	while (T--) {
		int res = 0;
		scanf("%d",&N);
		for (int i=0;i<N;i++){
			scanf("%d%d%d", &a[0], &a[1], &a[2]);
			sort(a, a+3);
			res+=a[2];
		}
		printf("%d\n",res);
	}
}