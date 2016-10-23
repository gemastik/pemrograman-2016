#include <bits/stdc++.h>
using namespace std;

int n, k, d[300300];
vector <int> a[300300];

void visit(int x, int par, int radius, int &fountains)
{
        int minCovered = radius + 1, maxUncovered = 0;

        for (int i = 0; i < int(a[x].size()); i++)
        {
                int y = a[x][i];
                if (y == par) continue;
                visit(y, x, radius, fountains);
                if (d[y] >= 0) maxUncovered = max(maxUncovered, d[y] + 1);
                else minCovered = min(minCovered, -d[y]);
        }

        if (minCovered <= radius && (!maxUncovered || minCovered + maxUncovered <= radius)) d[x] = -minCovered - 1;
        else
                if (maxUncovered < radius) d[x] = maxUncovered;
                else fountains++, d[x] = -1;
}

int calc(int radius)
{
        int fountains = 0;
        visit(1, 0, radius, fountains);
        fountains += d[1] >= 0;
        return fountains;
}

int main()
{
        int test, x, y;

        cin >> test;
        while (test--)
        {
                cin >> n >> k;
                for (int i = 1; i <= n; i++) a[i].clear();
                for (int i = 1; i < n; i++)
                {
                        cin >> x >> y;
                        a[x].push_back(y);
                        a[y].push_back(x);
                }

                int low = 0, high = n - 1, ans = n;
                while (low <= high)
                {
                        int mid = (low + high) / 2;
                        if (calc(mid) <= k) ans = mid, high = mid - 1;
                        else low = mid + 1;
                }

                cout << ans << endl;
        }
}
