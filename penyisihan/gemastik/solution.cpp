#include <bits/stdc++.h>
using namespace std;

int f_gemas[500001], f_cantik[500001], v[12];
pair<int,int> gemas[50001], cantik[50001];
char nama[50001][10];
int best;
int a,b,c,d,e,f;

void coba(int i,int j,int k,int x,int y,int z){
        if (i == j || i == k || i == x || i == y || i == z)
                return;
        if (j == k || j == x || j == y || j == z)
                return;
        if (k == x || k == y || k == z)
                return;
        if (x == y || x == z)
                return;
        if (y == z)
                return;
        int res = (f_gemas[i] * f_gemas[j] * f_gemas[k]) + (f_cantik[x] * f_cantik[y] * f_cantik[z]);
        if (res > best){
                best = res;
                a = i; b = j; c = k;
                d = x; e = y; f = z;
        }
}

int main() {
        int T;
        int N;
        scanf("%d",&T);
        while (T--) {
                scanf("%d",&N);
                for (int i=0;i<N;i++){
                        scanf("%s%d%d",nama[i],&a,&b);
                        f_gemas[i] = a;
                        f_cantik[i] = b;

                        gemas[i].first = a;
                        gemas[i].second = i;
                        cantik[i].first = b;
                        cantik[i].second = i;
                }

                sort(gemas, gemas + N, std::greater<pair<int,int> >());
                sort(cantik, cantik + N, std::greater<pair<int,int> >());
                for (int i=0;i<6;i++){
                        v[i*2] = gemas[i].second;
                        v[i*2 + 1] = cantik[i].second;
                }
                sort(v, v + 12);
                int SZ = unique (v, v + 12) - v;

                best = 0;
                for (int i = 0;i<SZ;i++)
                        for (int j=0;j<SZ;j++)
                                for (int k=0;k<SZ;k++)
                                        for (int x=0;x<SZ;x++)
                                                for (int y=0;y<SZ;y++)
                                                        for (int z=0;z<SZ;z++){
                                                                coba(i,j,k,x,y,z);
                                                        }
                cout<<best<<endl;
                cout<<nama[a]<<" "<<nama[b]<<" "<<nama[c]<<endl;
                cout<<nama[d]<<" "<<nama[e]<<" "<<nama[f]<<endl;
        }
}