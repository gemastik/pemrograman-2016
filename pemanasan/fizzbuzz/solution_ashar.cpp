#include <bits/stdc++.h>
using namespace std;

int T;
int N, K;
int M[20];
string S[20];

int main() {
	cin >> T;
	while (T--) {
		cin >>  N >> K;
		for (int i = 0; i < K; i++) {
			cin >> M[i] >> S[i];
		}

		for (int i = 1; i <= N; i++) {
			bool fizzbuzz = false;
			for (int j = 0; j < K; j++) {
				if (i % M[j] == 0) {
					fizzbuzz = true;
					cout << S[j];
				}
			}
			if (!fizzbuzz) {
				cout << i;
			}
			cout << endl;
		}
	}
}
