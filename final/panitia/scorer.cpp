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
        double tc_ans;
        fscanf(tc_out, "%lf\n", &tc_ans);

        double con_ans;
        fscanf(con_out, "%lf\n", &con_ans);

        if (abs(tc_ans - con_ans) > 1e-5 + 1e-9) {
            return wa();
        }
    }
    return ac();
}
