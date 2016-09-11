#include <bits/stdc++.h>
#define MAX_TIME 90000
#define MAX_N 100010
#define debug 0
using namespace std;

int terjauh[MAX_TIME];
int terjauh_id[MAX_TIME];

int st[MAX_N];
int ed[MAX_N];
int res[MAX_N];


pair<int,int> points[2*MAX_N];

int N,T;

int read_date(){
	int h,m,s;
	scanf("%d:%d:%d",&h,&m,&s);
	return (h * 60 * 60) + (m * 60) + s;
}

int main() {
	scanf("%d",&T);
	while(T--){
		memset(terjauh, 0, sizeof terjauh);
		memset(terjauh_id, 0, sizeof terjauh_id);
		memset(st, 0, sizeof st);
		memset(ed, 0, sizeof ed);
		memset(res, 0, sizeof res);
		memset(points, 0, sizeof points);

		scanf("%d", &N);
		for (int i = 1; i <= N; i++){
			st[i] = read_date();
			ed[i] = read_date();

			points[i*2 - 2] = make_pair( st[i] , i); // positive index = start point
			points[i*2 - 1] = make_pair( ed[i] , -i); // negative index = end point

			if (terjauh[st[i]] == ed[i]) {
				terjauh_id[st[i]] = -1; // negative index = duplicate lines
			}
			if (terjauh[st[i]] < ed[i]) {
				terjauh_id[st[i]] = i;
				terjauh[st[i]] = ed[i];
			}
		}
		sort(points , points + N*2);

		int longest = -1;
		int longest_id = 0;
		int curr_size = 0;
		int i = 0;
		for (int t = 0; t < MAX_TIME; t++){
			if (longest < terjauh[t]) {
				longest = terjauh[t];
				longest_id = terjauh_id[t];
			}

			while(i < N*2 && points[i].first == t){
				bool is_end = 0;
				int id = points[i].second;
				if (id < 0) {
					id *= -1;
					is_end = 1;
					curr_size--;
				} else {
					if (debug) cout<<"Now in "<<st[id]<<endl;
					if (debug) cout<<"longest point from here : "<<longest<<endl;
					curr_size++;
				}

				if (!is_end && ed[id] <= longest && id != longest_id){
					res[id] = -1;
					if (debug) cout<<id<<" taken by "<<longest_id<<endl;
				}

				i++;
			}
			if (curr_size == 1)
				res[longest_id] = 1;
		}

		for (int i = 1; i <= N; i++) {
			printf("%d\n",(res[i]!=0)?res[i]:2);
		}

	}
}