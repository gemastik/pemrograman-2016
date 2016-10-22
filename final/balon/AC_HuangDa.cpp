# include <stdio.h>

int tc, k;
long long n;

int main()
{
  // freopen("a.txt", "r", stdin);

  scanf("%d", &tc);

  while (tc --)
  {
    scanf("%lld%d", &n, &k);

    if (k <= n)
    {
      printf("%d\n", 0);
    } else
    {
      long long x = 1;
      for (long long i = 1; i <= n; i ++)
      {
        x = (x * i) % k;
      }

      printf("%lld\n", x);
    }
  }
}
