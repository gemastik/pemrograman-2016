// coded in about 2-3 minutes only

#include <cstdio>
using namespace std;

int i, TC;
long long N, V, ans;

int main() {
// freopen("in.txt", "r", stdin);

  scanf("%d", &TC);
  while (TC--) {
    scanf("%lld %lld", &N, &V);
    if (N > V)
      printf("0\n"); // obvious
    else { // N <= V <= 10^5, doable
      for (ans = i = 1; i <= N; i++)
        ans = (ans * i) % V;
      printf("%lld\n", ans);
    }
  }

  return 0;
}
