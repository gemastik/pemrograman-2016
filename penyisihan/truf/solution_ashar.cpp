#include <bits/stdc++.h>
using namespace std;

int T;

double comb[53][53];
string card[13];
int val[256];
bool have[256][13];

double solve(int lo, int hi, int x, int wow) {
    if (x == 3) {
        return 1;
    }

    double res = 0;
    for (int l = 0; l <= lo; l++) {
        for (int h = 0; h <= hi; h++) {
            if (l || h == 0) {
                res += comb[lo][l] * comb[hi][h] * comb[wow][13-l-h] * solve(lo-l, hi-h, x+1, wow - (13-l-h));
            }
        }
    }
    return res;
}

void solve(int lo, int hi) {
    double num = solve(lo, hi, 0, 39 - lo - hi);
    double denom = comb[39][13] * comb[26][13] * comb[13][13];

    double res = num * 100 / denom;
    printf("%.5lf%%", res);
}

int main() {
    for (int i = 0; i <= 52; i++) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            comb[i][j] = comb[i-1][j] + comb[i-1][j-1];
        }
    }

    for (char c = '2'; c <= '9'; c++) {
        val[c] = c - '2';
    }
    val['T'] = 8;
    val['J'] = 9;
    val['Q'] = 10;
    val['K'] = 11;
    val['A'] = 12;

    cin >> T;
    for (int tc = 0; tc < T; tc++) {
        if (tc) {
            cout << endl;
        }
        memset(have, false, sizeof have);
        for (int i = 0; i < 13; i++) {
            cin >> card[i];
            int v = val[card[i][0]];
            int s = card[i][1];
            have[s][v] = true;
        }

        for (int i = 0; i < 13; i++) {
            int hi = 0, lo = 0;

            int v = val[card[i][0]];
            int s = card[i][1];

            for (int i = 0; i < v; i++) {
                lo += !have[s][i];
            }
            for (int i = v+1; i < 13; i++) {
                hi += !have[s][i];
            }

            cout << card[i] << ": ";
            solve(lo, hi);
            cout << endl;
        }
    }
}
