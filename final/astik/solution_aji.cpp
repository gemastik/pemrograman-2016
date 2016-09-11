#include <bits/stdc++.h>
using namespace std;
const int MAX_BIT = 200001;
int bit[MAX_BIT];
int isi[MAX_BIT];
int N,T;

int get(int pos) {
	int res = 0;
	for (int i = pos;i > 0;i-=(i & -i))
		res+= bit[i];
	return res;
}

void update(int pos, int val) {
	for (int i = pos; i < MAX_BIT; i+=(i & -i))
		bit[i] += val;
}

int main() {
	scanf("%d",&T);
	while (T--){
		scanf("%d",&N);
		for (int i=0;i<N;i++){
			scanf("%d",&isi[i]);
		}

		memset(bit, 0, sizeof bit);

		int inverse = 0;
		for (int i=N-1;i>=0;i--){
			inverse += get(isi[i]);
			update(isi[i], 1);
		}
		if (inverse % 2)
			printf("YA\n");
		else
			printf("TIDAK\n");
	}
}