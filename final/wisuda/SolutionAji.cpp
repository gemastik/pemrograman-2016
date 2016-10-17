#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;

set <string> orang;

int main() {
	int N,T;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&N);
		int maxneed = 0;
		orang.clear();
		for (int i=0;i<N;i++){
			int x;
			char lho[999];
			scanf("%s%d",lho,&x);
			for (int i=0;i<x;i++){
				char tmp[99];
				scanf("%s",tmp);
				orang.insert(tmp);
			}
			if (lho[0] == 'd') {
				maxneed = max(maxneed , x + 1);
			}
		}
		cout<<max((int) orang.size(), maxneed)<<endl;
	}
}