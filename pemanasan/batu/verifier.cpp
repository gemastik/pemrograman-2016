/* 
 * Computer Festival 2013 Competitive Programming
 * Lorong Batu
 * Ashar Fuadi
 * Template by Ashar Fuadi
 */

#include <cstdio>
#include <cstring>
#include <cassert>

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

/* ****************************************************************** */

char line[1024], buf[1024];
int pos, add;

#define begin_line() {gets(line); pos = 0;}
#define end_line() {assert(sscanf(line+pos, "%s", buf) == EOF);}
#define end_file() {assert(scanf("%s", buf) == EOF);}
#define read_int(n) {assert(sscanf(line+pos, "%d%n", &n, &add) != EOF); pos += add;}
#define read_long(n) {assert(sscanf(line+pos, "%lld%n", &n, &add) != EOF); pos += add;}
#define read_string(n) {assert(sscanf(line+pos, "%s%n", n, &add) != EOF); pos += add;}
#define constraint(n) assert(n)

/* ****************************************************************** */

int T, N;
char m[2][1005];

int main()
{
	// reads T
	begin_line();
	read_int(T);
	constraint(1 <= T && T <= 20);
	end_line();
	
	while (T--)
	{
		// reads N M
		begin_line();
		read_int(N);
		constraint(1 <= N && N <= 1000);
		end_line();
		
      begin_line();
      read_string(m[0]);
		end_line();
		
		begin_line();
      read_string(m[1]);
		end_line();
		
		constraint(strlen(m[0]) == N);
		constraint(strlen(m[1]) == N); 
		
		REP(i,2){
		   REP(j,N){
		      constraint(m[i][j] == '0' || m[i][j] == '1');
		   }
		}
	}
	
	// check trailing characters
	end_file();
}
