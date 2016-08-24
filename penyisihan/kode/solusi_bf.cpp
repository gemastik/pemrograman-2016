#include <bits/stdc++.h>
#define MAX_TIME 90000
#define MAX_N 100010
#define debug 0
using namespace std;

int res[MAX_N];


pair<int,pair<int,int> > points[2*MAX_N];

int N,T;

int read_date(){
	int h,m,s;
	scanf("%d:%d:%d",&h,&m,&s);
	return (h * 60 * 60) + (m * 60) + s;
}


int main() {
	scanf("%d",&T);
	while(T--){
		scanf("%d",&N);
		for (int i=0;i<N;i++){
			int a = read_date();
			int b = read_date();
			points[i] = make_pair(a,make_pair(b,i));
			res[i] = 2;
		}

		//cek 1
		for (int i=0;i<MAX_TIME;i++){
			int ada = 0;
			int id = -1;
			for (int j=0;j<N;j++){
				if (points[j].first <= i && i < points[j].second.first){
					ada++;
					id = j;
					if (ada > 1 || res[id] == 1)
						break;
				}
			}
			if (ada == 1){
				res[id] = 1;
			}
		}

		//cek -1
		sort(points, points + N);
		for (int i=0;i<N;i++){
			if (res[points[i].second.second] == 1)
				continue;
			for (int j=0;j<N;j++){
				if (i==j)
					continue;
				if (points[j].first > points[i].first)
					break;

				if (points[i].second.first <= points[j].second.first){
					//printf("%d %d vs %d %d\n",points[i].first,points[i].second, points[j].first,points[j].second);
					res[points[i].second.second] = -1;
					break;
				}
			}
		}
		for (int i=0;i<N;i++)
			printf("%d\n",res[i]);


	}
}