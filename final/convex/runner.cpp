#include "tcframe/runner.hpp"
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class Problem : public BaseProblem {
protected:
    int T;
    int N, Q;
    vector<int> X, Y;
    vector<int> X1, X2;
    vector<double> RES;

    void Config() {
        setSlug("convex");
        setTimeLimit(2);
        setMemoryLimit(64);
        setMultipleTestCasesCount(T);
    }

    void InputFormat() {
        LINE(N);
        LINES(X, Y) % SIZE(N);
        LINE(Q);
        LINES(X1, X2) % SIZE(Q);
    }

    void OutputFormat() {
        LINES(RES) % SIZE(Q);
    }

    void Constraints() {
        CONS(1 <= N && N <= 100000);
        CONS(1 <= Q && Q <= 100000);
        CONS(eachElementBetween(X, 1, 1000000000));
        CONS(eachElementBetween(Y, 1, 1000000000));
        CONS(eachElementBetween(X1, 0, 1000000000));
        CONS(eachElementBetween(X2, 0, 1000000000));
        CONS(X1NotGreaterThanX2());
        CONS(isUnique(X));
        CONS(isUnique(Y));
    }

    void MultipleTestCasesConstraints() {
        CONS(1 <= T && T <= 5);
    }

private:
    bool eachElementBetween(const vector<int>& A, int lo, int hi) {
        return all_of(A.begin(), A.end(), [lo, hi](int a) {return lo <= a && a <= hi;});
    }

    bool X1NotGreaterThanX2() {
        for (int i = 0; i < Q; i++) {
            if (X1[i] > X2[i]) {
                return false;
            }
        }
        return true;
    }

    bool isUnique(const vector<int>& v) {
        set<int> s(v.begin(), v.end());
        return s.size() == v.size();
    }
};

class Generator : public BaseGenerator<Problem> {
protected:
    void SampleTestCases() {
        SAMPLE_CASE({
            "9",
            "1 8",
            "3 4",
            "5 3",
            "2 9",
            "4 7",
            "6 5",
            "9 2",
            "10 1",
            "12 6",
            "6",
            "0 2",
            "3 7",
            "5 14",
            "5 10",
            "11 13",
            "7 8"
        });
    }

    void TestGroup1() {
        assignToSubtasks({-1});
        CASE(N = 3, Q = 1, X = {1, 500000000, 1000000000}, Y = {1, 500000000, 2}, X1 = {1}, X2 = {1});
        CASE(N = 1000, Q = 1000, randomCase());
        CASE(N = 1000, Q = 1000, randomCase());
        CASE(N = 5000, Q = 100000, randomCase());
        CASE(N = 100000, Q = 2000, randomCase());
    }

    void TestGroup2() {
        assignToSubtasks({-1});
        CASE(N = 77777, Q = 77777, randomCase());
        CASE(N = 88888, Q = 88888, randomCase());
        CASE(N = 99999, Q = 99999, randomCase());
        CASE(N = 100000, Q = 100000, randomCase());
        CASE(N = 100000, Q = 100000, randomCase());
    }

    void TestGroup3() {
        assignToSubtasks({-1});
        CASE(N = 100000, Q = 100000, randomKillerCase());
        CASE(N = 100000, Q = 100000, randomKillerCase());
        CASE(N = 100000, Q = 100000, randomKillerCase());
        CASE(N = 100000, Q = 100000, randomKillerCase());
        CASE(N = 100000, Q = 100000, randomKillerCase());
    }

private:
    vector<int> genCoord() {
        set<int> seen;
        vector<int> coord;
        for (int i = 0; i < N; i++) {
            int x;
            do {
                x = rnd.nextInt(1000000000) + 1;
            } while (seen.count(x));
            coord.push_back(x);
            seen.insert(x);
        }
        return coord;
    }

    int genPoint(int x) {
        vector<int> xx;
        if (x > 1) {
            xx.push_back(x-1);
        }
        xx.push_back(x);
        if (x < 1000000000) {
            xx.push_back(x+1);
        }

        return xx[rnd.nextInt(xx.size())];
    }

    void randomCase() {
        X = genCoord();
        Y = genCoord();
        X1.clear();
        X2.clear();

        vector<int> S = X;
        sort(S.begin(), S.end());

        for (int q = 0; q < Q; q++) {
            int x1 = genPoint(S[rnd.nextInt(N)]);
            int x2 = genPoint(S[rnd.nextInt(N)]);
            if (x1 > x2) {
                swap(x1, x2);
            }
            X1.push_back(x1);
            X2.push_back(x2);
        }
    }


    void randomKillerCase() {
        X = genCoord();
        Y = genCoord();
        X1.clear();
        X2.clear();

        vector<int> S = X;
        sort(S.begin(), S.end());

        for (int q = 0; q < Q; q++) {
            int a;
            if (rnd.nextInt(100) < 90) {
                a = S[rnd.nextInt(10)];
            } else {
                a = S[rnd.nextInt(N)];
            }
            int b;
            if (rnd.nextInt(100) < 90) {
                b = S[N - rnd.nextInt(10)];
            } else {
                b = S[rnd.nextInt(N)];
            }

            int x1 = genPoint(a);
            int x2 = genPoint(b);
            if (x1 > x2) {
                swap(x1, x2);
            }
            X1.push_back(x1);
            X2.push_back(x2);
        }
    }
};

int main(int argc, char* argv[]) {
    Runner<Problem> runner(argc, argv);

    runner.setGenerator(new Generator());
    return runner.run();
}
