#include <fstream>
#include <iostream>
#include <string>
#include <cstdio>
#include <algorithm>
using namespace std;

int wa() {
    cout << "WA" << endl;
    return 0;
}

int ac() {
    cout << "AC" << endl;
    return 0;
}

int main(int argc, char* argv[]) {
    FILE* tc_in = fopen(argv[1], "r");
    FILE* tc_out = fopen(argv[2], "r");
    FILE* con_out = fopen(argv[3], "r");

    int T;
    fscanf(tc_in, "%d", &T);

    for (int tc = 0; tc < T; tc++) {
        if (tc) {
            fscanf(tc_out, "\n");

            if (fscanf(con_out, "\n") != 0) {
                return wa();
            }
        }
        char tc_suit, tc_value;
        double tc_ans;
        fscanf(tc_out, "%c%c: %lf%%\n", &tc_suit, &tc_value, &tc_ans);

        char con_suit, con_value;
        double con_ans;
        if (fscanf(con_out, "%c%c: %lf%%\n", &con_suit, &con_value, &con_ans) != 3) {
            return wa();
        }

        if (tc_suit != con_suit || tc_value != con_value) {
            return wa();
        }

        if (abs(tc_ans - con_ans) > 1e-5 + 1e-9) {
            return wa();
        }
    }
    return ac();
}
