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
        return make_tuple(x, type, -E[id]) < make_tuple(o.x, o.type, -E[o.id]);
    }
};
event M[2*MAXN];

int bit[MAXM];
void setb(int x) {
    for (int i = x; i <= MAXM; i += i & -i) {
        bit[i]++;
    }
}
int getb(int x) {
    int res = 0;
    for (int i = x; i; i -= i & -i) {
        res += bit[i];
    }
    return res;
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
            int a, b, c, d, e, f;
            scanf("%d:%d:%d %d:%d:%d", &a, &b, &c, &d, &e, &f);
            S[i] = a * 60 * 60 + b * 60 + c;
            E[i] = d * 60 * 60 + e * 60 + f;
            M[2*i] = (event) {i, S[i], START};
            M[2*i+1] = (event) {i, E[i], END};
            ans[i] = 2;
        }

        sort(M, M+2*N);
        memset(bit, 0, sizeof bit);

        int last = -1;
        set<int> kagi;
        for (int i = 0; i < 2*N; i++) {
            if (M[i].x != last && kagi.size() == 1) {
                ans[*kagi.begin()] = 1;
            }

            if (M[i].type == START) {
                if (getb(MAXM) - getb(E[M[i].id]-1)) {
                    ans[M[i].id] = -1;
                }
                setb(E[M[i].id]);
                kagi.insert(M[i].id);
            } else {
                kagi.erase(M[i].id);
            }
            last = M[i].x;
        }
        for (int i = 0; i < N; i++) {
            printf("%d\n", ans[i]);
        }
    }
}
