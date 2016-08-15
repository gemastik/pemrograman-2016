/* 
 * Computer Festival 2013 Competitive Programming

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
#define LL long long
#define MAXN 100001
#define INF 2123123123
#define F first
#define S second

int nkasus;
char sc[100];
pair<int,string> ar[1000];
int n;

int main()
{
   scanf("%d", &nkasus);
	REP(jt,nkasus){
		scanf("%d", &n);
		int p = 0;
		int tot = 0;
		REP(i,n){
		   int a;
		   scanf("%s %d Juta", sc, &a);
		   tot += a;
		   
		   bool ada = 0;
		   string st = sc;
		   REP(j,p){
		      if (st == ar[j].S){
		         ar[j].F += a;
		         ada = 1;
		         break;
		      }
		   }
		   if (!ada){
		      ar[p++] = mp(a, st);
		   }
		}
		
		sort(ar, ar + p);
		
		printf("%d Juta\n", tot - ar[p-1].F - ar[p-2].F);
	}	
}
