#include <cstdio>
using namespace std;

int i, TC, N, V, ans; // WA if we do not use long long

int main() {
  scanf("%d", &TC);
  while (TC--) {
    scanf("%d %d", &N, &V);
    if (N > V)
      printf("0\n"); // obvious
    else { // N <= V <= 10^5, doable
      for (ans = i = 1; i <= N; i++)
        ans = (ans * i) % V;
      printf("%d\n", ans);
    }
  }

  return 0;
}
