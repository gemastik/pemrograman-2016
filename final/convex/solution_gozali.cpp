#include <cstdio>
#include <cstring>
#include <cmath>
#include <set>
#include <algorithm>
#include <vector>

#define LL long long
#define FOR(a,b,c) for (int a = b; a <= c; a++)

using namespace std;

const int MAX_LG = 17;
const int MAX_N = 1 << MAX_LG;
const int MIN_X = 0;
const int MIN_Y = 0;
const int MAX_X = 2 * 1000 * 1000;
const int MAX_Y = 2 * 1000 * 1000;

struct point {
  int x, y;
};

int N, Q;
point points[MAX_N];
vector<int> stack;

int parLeft[MAX_N][MAX_LG + 1];
LL areaLeft[MAX_N][MAX_LG + 1];

bool byX(const point &a, const point &b) {
  return (a.x < b.x) || ((a.x == b.x) && (a.y < b.y));
}

LL absLL(LL x) {
  if (x < 0) return -x;
  return x;
}

LL trapeziumArea(const point &a, const point &b) {
  return ((LL)a.y + b.y) * absLL(b.x - a.x);
}

LL det(const point &a, const point &b, const point &c) {
  return ((LL)a.x)*b.y + ((LL)b.x)*c.y + ((LL)c.x)*a.y -
         ((LL)a.x)*c.y - ((LL)b.x)*a.y - ((LL)c.x)*b.y;
}

int findBegin(int x) {
  int l = 0;
  int r = N-1;
  int result = l;
  while (l <= r) {
    int m = (l + r) / 2;

    if (x <= points[m].x) {
      result = m;
      r = m - 1;
    } else {
      l = m + 1;
    }
  }
  return result;
}

void precomputeLeft() {
  // Go left to right
  parLeft[N-1][0] = N-1;
  areaLeft[N-1][0] = 0;

  stack.clear();
  stack.push_back(N-1);
  int sz = 1;
  for (int i = N-2; i >= 0; i--) {
    while ((sz >= 2) && (det(points[stack[sz-2]], points[stack[sz-1]], points[i]) < 0)) {
      stack.pop_back();
      sz--;
    }

    parLeft[i][0] = stack.back();
    areaLeft[i][0] = trapeziumArea(points[stack.back()], points[i]);
    stack.push_back(i);
    sz++;
  }

  FOR(j, 1, MAX_LG-1) {
    FOR(i, 0, N-1) {
      parLeft[i][j] = parLeft[parLeft[i][j-1]][j-1];
      areaLeft[i][j] = areaLeft[i][j-1] + areaLeft[parLeft[i][j-1]][j-1];
    }
  }
}

int getParent(int x, int howFar) {
  int cur = x;
  FOR(i, 0, MAX_LG) {
    if (howFar & (1 << i)) {
      cur = parLeft[cur][i];
    }
  }
  return cur;
}

LL getArea(int x, int howFar) {
  int cur = x;
  LL area = 0;
  FOR(i, 0, MAX_LG) {
    if (howFar & (1 << i)) {
      area += areaLeft[cur][i];
      cur = parLeft[cur][i];
    }
  }
  return area;
}

LL findLeftAreaBf(int startIdx, int endIdx) {
  stack.clear();
  stack.push_back(startIdx);
  int sz = 1;
  FOR(i, startIdx+1, endIdx) {
    while ((sz >= 2) && (det(points[stack[sz-2]], points[stack[sz-1]], points[i]) > 0)) {
      stack.pop_back();
      sz--;
    }
    stack.push_back(i);
    sz++;
  }

  // for (int i = 0; i < sz; i++) {
  //   printf("L %d) %d %d\n", stack[i], points[stack[i]].x, points[stack[i]].y);
  // }

  LL area = 0;
  FOR(i, 1, sz-1) {
    area += trapeziumArea(points[stack[i-1]], points[stack[i]]);
  }

  return area;
}

LL query(int x1, int k) {
  int startIdx = findBegin(x1);
  int endIdx = getParent(startIdx, k-1);

  if (k <= 1) {
    return 0;
  }

  LL area = getArea(startIdx, k-1);
  // LL area = findLeftAreaBf(startIdx, endIdx);

  return area - trapeziumArea(points[startIdx], points[endIdx]);
}

void solve() {
  scanf("%d", &N);
  FOR(i, 0, N-1) {
    scanf("%d %d", &points[i].x, &points[i].y);
  }

  sort(points, points + N, byX);

  precomputeLeft();

  scanf("%d", &Q);
  FOR(q, 0, Q-1) {
    int x1, k;
    scanf("%d %d", &x1, &k);
    if (x1 > points[N-1].x) {
      printf("0.0\n");
      continue;
    }
    LL result = query(x1, k);
    printf("%lld.%d\n", result / 2, result % 2 ? 5 : 0);
    // printf("\n");
  }
}

int main() {
  int T;
  scanf("%d", &T);
  FOR(jt, 0, T-1) {
    solve();
  }
}
