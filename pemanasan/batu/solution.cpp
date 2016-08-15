/* 
 * Computer Festival 2013 Competitive Programming
 * Lorong Batu
 * Ashar Fuadi
 * Template by Ashar Fuadi
 */

#include <cstdio>
#include <cstring>

#include <vector>
#include <string>
#include <set>
#include <map>
#include <utility>
#include <iostream>
#include <algorithm>

using namespace std;

#define REP(i,n) for (int i = 0; i < (int)n; i++)
#define FOR(i, a, b) for (int i = (int)a; i <= (int)b; i++)
#define FOREACH(i,c) for (typeof((c).end()) i = (c).begin(); i != (c).end(); ++i)
#define RESET(c,v) memset(c, v, sizeof(c))

#define pb push_back
#define mp make_pair

int n,nkasus;
int tot,ans;
char m[2][1002];
int dr[] = {-1, 0, 1, 0, 1, 1, -1, -1};
int dc[] = {0, 1, 0, -1, -1, 1, -1, 1};

void ff(int a, int b){
   m[a][b] = '0';
   tot++;
   
   //overkill
   REP(i,8){
      int na = a + dr[i];
      int nb = b + dc[i];
      
      if ((0 <= na) && (na < 2) && (0 <= nb) && (nb < n)){
         if (m[na][nb] == '1'){
            ff(na, nb);
         }
      }
   }
}

int main()
{
   scanf("%d", &nkasus);
   REP(jt,nkasus){
      scanf("%d", &n);
      REP(i,2){
         scanf("%s", m[i]);
      }
      
      ans = 0;
      REP(i,2){
         REP(j,n){
            if (m[i][j] == '1'){
               tot = 0;
               ff(i,j);
               
               ans += (tot/2 + tot%2);
            }           
         }
      }
      
      printf("%d\n", ans);
   }	
}
