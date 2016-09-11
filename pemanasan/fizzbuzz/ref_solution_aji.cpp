#include <bits/stdc++.h>
using namespace std;

int T;
int N,K;
int M[22];
char lho[22][22];

int main() {

	scanf("%d",&T);
	while(T--) {
		scanf("%d%d",&N,&K);
		for (int i=0;i<K;i++){
			scanf("%d%s",&M[i],lho[i]);
		}

		for (int i=1;i<=N;i++) {
			bool udah = 0;
			for (int j=0;j<K;j++) {
				if (i % M[j] == 0) {
					cout<<lho[j];
					udah = 1;
				}
			}
			if (!udah)
				cout<<i;
			cout<<endl;
		}
	}
}