// Authored by dolphinigle

#include <vector>
#include <list>
#include <map>
#include <set>

#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cassert>

#define FORN(X,Y) for (int (X) = 0;(X) < (Y);++(X))
#define REP(X,Y,Z) for (int (X) = (Y);(X) < (Z);++(X))

#define SZ(Z) ((int)(Z).size())
#define ALL(W) (W).begin(), (W).end()
#define PB push_back

#define MP make_pair
#define A first
#define B second

#define INF 1023123123
#define EPS 1e-11

#define MX(Z,Y) Z = max((Z),(Y))
#define MN(X,Y) X = min((X),(Y))

using namespace std;

typedef long long ll;
typedef double db;
typedef vector<int> vint;

const int kMaxN = 305;

int shirts[kMaxN];
int people[kMaxN];
double dp[kMaxN][kMaxN][kMaxN];  // this color now, has taken B shirts, C matches, probability.
double probs[kMaxN];

void AddMultipliers(int upper, int bottom, vector<int>* multis, vector<int>* divids) {
  for (int i = 1; i <= bottom; ++i) divids->push_back(i);
  for (int i = upper; i > upper-bottom; --i) {
    multis->push_back(i);
  }
}

double CalculateDouble(const vector<int>& multipliers, const vector<int>& dividers) {
  // Calculate multipliers mult together over dividers div together.
  double result = 1.0;
  int mi = 0;
  int md = 0;
  while (mi != SZ(multipliers) || md != SZ(dividers)) {
    if (md == SZ(dividers) || (mi != SZ(multipliers) && result <= 1.0)) {
      result *= multipliers[mi];
      ++mi;
    } else {
      result /= dividers[md];
      ++md;
    }
  }
  return result;
}

int main_a() {
  int n;
  scanf("%d", &n);
  FORN(i, n) {
    int a;
    scanf("%d", &a);
    people[a] += 1;
  }
  int total_shirts = 0;
  FORN(i, n+1) {
    int a;
    scanf("%d", &a);
    total_shirts += a;
    shirts[i+1] = a;
  }
  dp[0][0][0] = 1.0;
  int remain_shirts = total_shirts;
  FORN(color, n+2) {
    int rest = remain_shirts - shirts[color];
    for (int taken = 0; taken <= n; ++taken) {
      int remain_take = n-taken;
      if (remain_take > remain_shirts) continue;  // too few t-shirts remaining to take.

      // calculate probabilities of taking 0..n t-shirts.
      // Use a bunch of multipliers and dividers...
      for (int want = 0; want <= n; ++want) {
        if (want > shirts[color] || want > remain_take) {
          probs[want] = 0.0;
          continue;
        }
        vector<int> multis;
        vector<int> divids;
        // Formula is same w/ hypergeometric distribution.
        // Probability of picking exactly k tees is C(shirts[color], want) * C(rest, remain_take-want) / C(remain_shirts, remain_take)
        AddMultipliers(shirts[color], want, &multis, &divids);
        AddMultipliers(rest, remain_take-want, &multis, &divids);
        AddMultipliers(remain_shirts, remain_take, &divids, &multis);
        probs[want] = CalculateDouble(multis, divids);
      }
      for (int matches = 0; matches <= n; ++matches) {
        if (dp[color][taken][matches]) {
          for (int want = 0; want <= (n-taken); ++want) {
            dp[color+1][taken+want][matches+min(want, people[color])] += dp[color][taken][matches] * probs[want];
          }
        }
      }
    }
    remain_shirts = rest;
  }
  double pong = 0.0;
  for (int i = 0; i <= n; ++i) {
    // cout << i << ":" << dp[n+2][n][i] << endl;
    pong += dp[n+2][n][i] * (db)i / (db)(2*n-i);
  }
  printf("%.3lf\n", pong);
  return 0;
}

int main() {
  int t;
  scanf("%d", &t);
  FORN(i, t) {
    memset(shirts, 0, sizeof shirts);
    memset(people, 0, sizeof people);
    memset(dp, 0, sizeof dp);
    memset(probs, 0, sizeof probs);
    main_a();
  }
}






