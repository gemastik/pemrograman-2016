#include <bits/stdc++.h>
using namespace std;

vector<int> solutions[5000001];
int offset = 2500000;
int best_panjang;
int sum;
long long sol;
int N,T,P;
int tiang[30];

void cout_opsi(int p1,int p2){
	printf("   ( %d x %d ) = %d\n",p1+p2, (sum-p1-p2)/2 ,(p1+p2) * (sum-p1-p2)/2);
}


void find_best(int tinggi, int panjang){
	tinggi += offset;
	//cout<<"mencari "<<tinggi - offset<<" panjang = "<<panjang<<endl;
	//cout<<" cari di "<<best_panjang - panjang<<endl;
	if (solutions[tinggi].size() == 0)
		return;

	int id = lower_bound(solutions[tinggi].begin(), solutions[tinggi].end(), best_panjang - panjang) - solutions[tinggi].begin();
	if (id < N){
		sol = max(sol, (long long)(solutions[tinggi][id] + panjang)* (sum - solutions[tinggi][id] - panjang)/2);
		//cout_opsi(panjang,solutions[tinggi][id]);
	}
	if (id - 1 > 0){
		sol = max(sol, (long long)(solutions[tinggi][id - 1] + panjang) * (sum - solutions[tinggi][id - 1] - panjang)/2);
		//cout_opsi(panjang,solutions[tinggi][id]);
	}
}

void generate(int pos, int tinggi, int panjang,int mode) {
	if (mode == 0 && pos == P){
		solutions[tinggi + offset].push_back(panjang);
		//cout<<"add "<<tinggi<<" = "<<panjang<<endl;
		return;
	}
	if (mode ==1 && pos == N){
		find_best(-tinggi,panjang);
		return;
	}
	//kanan
	generate(pos + 1, tinggi + tiang[pos], panjang,mode);
	//kiri
	generate(pos + 1, tinggi - tiang[pos], panjang,mode);
	//tinggi
	generate(pos + 1, tinggi, panjang + tiang[pos],mode);
}

int main() {
	scanf("%d",&T);
	while (T--){
		sol = 0;
		sum = 0;
		memset(solutions, 0, sizeof solutions);
		scanf("%d",&N);
		for (int i=0;i<N;i++){
			scanf("%d",&tiang[i]);
			sum += tiang[i];
		}
	
		best_panjang = sum / 2;
		//meet in the middle 
		P = N/2;
		//cout<<"A"<<endl;
		generate(0, 0, 0, 0);
		for (int i=0;i<=5000000;i++)
			sort(solutions[i].begin(), solutions[i].end());
		//cout<<"A"<<endl;

		generate(P,0,0,1);
		cout<<sol<<endl;
	}
}