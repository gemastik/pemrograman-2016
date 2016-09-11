#include <bits/stdc++.h>
using namespace std;

int main() {
        int T;
        int N;
        scanf("%d",&T);


        while (T--) {
                long long res = 0;
                scanf("%d",&N);
                for (int i=0;i<N;i++){
                        int x;
                        scanf("%d",&x);
                        res += x;
                }
                cout<<res<<endl;
        }
}