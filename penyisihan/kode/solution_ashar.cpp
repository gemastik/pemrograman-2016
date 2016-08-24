#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50005, MAXM = 100005;

int T;
int N;
int S[MAXN], E[MAXN];
int ans[MAXN];

enum {END, START};

struct event {
    int id, x, type;
    bool operator<(const event& o) const {
        return make_tuple(x, type, -E[id], -S[id]) < make_tuple(o.x, o.type, -E[o.id], -S[o.id]);
    }
};
event M[2*MAXN];

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &N);

        map<pair<int, int>, int> dup;
        for (int i = 0; i < N; i++) {
            int a, b, c, d, e, f;
            scanf("%d:%d:%d %d:%d:%d", &a, &b, &c, &d, &e, &f);
            S[i] = a * 60 * 60 + b * 60 + c;
            E[i] = d * 60 * 60 + e * 60 + f;
            M[2*i] = (event) {i, S[i], START};
            M[2*i+1] = (event) {i, E[i], END};
            ans[i] = 2;
            dup[make_pair(S[i], E[i])]++;
        }

        sort(M, M+2*N);

        int last = -1;
        set<pair<int, int>> active;
        for (int i = 0; i < 2*N; i++) {
            if (M[i].x != last && active.size() == 1) {
                ans[active.begin()->second] = 1;
            }

            if (M[i].type == START) {
                if (active.lower_bound(make_pair(E[M[i].id], -1)) != active.end()) {
                    ans[M[i].id] = -1;
                }
                active.insert(make_pair(E[M[i].id], M[i].id));
            } else {
                active.erase(make_pair(E[M[i].id], M[i].id));
            }
            last = M[i].x;
        }

        for (int i = 0; i < N; i++) {
            if (dup[make_pair(S[i], E[i])] > 1) {
                ans[i] = -1;
            }
        }

        for (int i = 0; i < N; i++) {
            printf("%d\n", ans[i]);
        }
    }
}
