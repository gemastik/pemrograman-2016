#include <bits/stdc++.h>
using namespace std;
int v[1111],k[1111];
int dp[1111][2222][2];
int N,S,P,T;

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d",&N,&S,&P);
		for (int i=0;i<N-1;i++)
			scanf("%d%d",&v[i], &k[i]);

		for (int i=0;i<N;i++)
			for (int j=0;j<=S+1005;j++){
				dp[i][j][0] = dp[i][j][1] = -999999999;
			}
		dp[0][S][0] = 0;

		for (int i=1;i<N;i++){
			for (int j = 0; j<=S;j++) {
				//naik pesawat
				dp[i][j][1] = max(dp[i-1][j + P][0] , dp[i-1][j][1]);
				//ga naik pesawat
				dp[i][j][0] = k[i-1] + max(dp[i-1][j + v[i-1]][1] , dp[i-1][j + v[i-1]][0]);
			}
		}
		int res = -1;
		for (int i=0;i<=S;i++)
			res = max(res, max(dp[N-1][i][0],dp[N-1][i][1]));

		cout<<res<<endl;
	}
}