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
//priority!
int dr[] = {-1, 1, 0, 0, 1, 1, -1, -1};
int dc[] = {0, 0, 1, -1, -1, 1, -1, 1};

int main()
{
   scanf("%d", &nkasus);
   REP(jt,nkasus){
      scanf("%d", &n);
      REP(i,2){
         scanf("%s", m[i]);
      }
      
      ans = 0;
      REP(j,n){
         REP(i,2){
            if (m[i][j] == '1'){
               m[i][j] = '0';
               ans++;
               
               //deactivate nearest neighbour
               REP(k,8){
                  int na = i + dr[k];
                  int nb = j + dc[k];
                  
                  if ((0 <= na) && (na < 2) && (0 <= nb) && (nb < n)){
                     if (m[na][nb] == '1'){
                        //diffused!
                        m[na][nb] = '0';
                        break;
                     }
                  }
               }
            /*
               REP(ii,2){
                  printf("%s\n", m[ii]);
               }
               printf("\n");
            */
            }
         }
      }
      
      printf("%d\n", ans);
   }	
}
