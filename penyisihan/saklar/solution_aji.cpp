#include <bits/stdc++.h>
using namespace std;
int L, B, T;
int dp[202][101][101];


bool can(int P, int TF, int TH){

	int tB = B;

	int tmp;

	tmp = min(tB , P);
	P -= tmp;
	tB -= tmp;

	tmp = min(tB, TF);
	TF -= tmp;
	tB -= tmp;
	return (tB == 0) && (P + TH + (2 * TF) >= L);
}

int wow(int pinggir, int tengah_full, int tengah_half){
	
	if (dp[pinggir][tengah_full][tengah_half] != -1)
		return dp[pinggir][tengah_full][tengah_half];

	if (can(pinggir, tengah_full, tengah_half)){
		dp[pinggir][tengah_full][tengah_half] = 0;
		return 0;
	}
	int res = 9999999;
	res = min( res , 1 + wow(pinggir + 1 , tengah_full + 1 , tengah_half) ); //colok di pinggir
	if (tengah_half)
		res = min( res , 1 + wow(pinggir + 2 , tengah_full + 1 , tengah_half - 1) ); //colok di tengah yg masih kosong
	if (tengah_full)
		res =  min( res , 1 + wow(pinggir + 2 , tengah_full , tengah_half + 1) ); //colok di tengah yg udah dicolok sampingnya
	
	dp[pinggir][tengah_full][tengah_half] = res;
	return res;
}

int main(){
	cin >> T;
	while (T--) {
		cin >> L >> B;
		memset(dp,-1,sizeof dp);
		cout << 1 + wow(2,1,0) << endl;
	}
}