/* 
 * Computer Festival 2013 Competitive Programming

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

int T, N, Q;
int x,y;

int main()
{
	// reads T
	begin_line();
	read_int(T);
	constraint(1 <= T && T <= 20);
	end_line();
	
	while (T--)
	{
		// reads N
		begin_line();
		read_int(N);
		constraint(2 <= N && N <= 20);
		end_line();
		
		while (N--)
		{
		   int x;
		   char sc[100];
			char juta[100];
			
			begin_line();
			read_string(sc);
         read_int(x);
         read_string(juta);
  			end_line();
  			
			constraint(1 <= strlen(sc) && strlen(sc) <= 10);
			constraint(1 <= x && x <= 10);
			constraint(strcmp(juta, "Juta") == 0);

		}
	}
	
	// check trailing characters
	end_file();
}
