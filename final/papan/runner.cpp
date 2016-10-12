#include "tcframe/runner.hpp"
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class Problem : public BaseProblem {
protected:
    int T;
    int N, M;
    vector<int> X, K;
    vector<ll> RES;

    void Config() {
        setSlug("papan");
        setTimeLimit(2);
        setMemoryLimit(64);
        setMultipleTestCasesCount(T);
    }

    void InputFormat() {
        LINE(N, M);
        LINES(X, K) % SIZE(N);
    }

    void OutputFormat() {
        LINE(RES);
    }

    void Constraints() {
        CONS(1 <= N && N <= 50000);
        CONS(1 <= M && M <= 50000);
        CONS(eachElementBetween(X, 1, N));
        CONS(eachElementBetween(K, 1, 50000));
    }

    void MultipleTestCasesConstraints() {
        CONS(1 <= T && T <= 5);
    }

private:
    bool eachElementBetween(const vector<int>& A, int lo, int hi) {
        return all_of(A.begin(), A.end(), [lo, hi](int a) {return lo <= a && a <= hi;});
    }
};

class Generator : public BaseGenerator<Problem> {
protected:
    void SampleTestCases() {
        SAMPLE_CASE({
            "7 4",
            "4 3",
            "1 2",
            "5 1",
            "4 2",
            "2 2"
        });
        SAMPLE_CASE({
            "1 100",
            "2 100"
        });
    }

    void TestGroup1() {
        assignToSubtasks({-1});

        CASE(N = 1, M = 1, X = {1}, K = {42});
        CASE(N = 5, M = 5, X = {1, 2, 3, 4, 5}, K = {1, 1, 1, 1, 1});
        CASE(N = 100, M = 50, randomCase());
        CASE(N = 100, M = 100, randomCase());
        CASE(N = 100, M = 200, randomKillerCase());
    }

    void TestGroup2() {
        assignToSubtasks({-1});

        CASE(N = 100, M = 300, randomSmallTaburanCase());
        CASE(N = 100, M = 50000, randomCase());
        CASE(N = 100, M = 50000, randomKillerCase());
        CASE(N = 100, M = 50000, randomSmallTaburanCase());
        CASE(N = 1000, M = 1000, randomCase());
    }

    void TestGroup3() {
        assignToSubtasks({-1});

        CASE(N = 50000, M = 50000, randomCase());
        CASE(N = 50000, M = 50000, randomCase());
        CASE(N = 50000, M = 50000, randomCase());
        CASE(N = 50000, M = 50000, randomSmallTaburanCase());
        CASE(N = 50000, M = 50000, randomSmallTaburanCase());
    }

    void TestGroup4() {
        assignToSubtasks({-1});

        CASE(N = 50000, M = 50000, randomKillerCase());
        CASE(N = 50000, M = 50000, randomKillerCase());
        CASE(N = 50000, M = 50000, randomKillerCase());
        CASE(N = 50000, M = 50000, randomKillerCase());
        CASE(N = 50000, M = 50000, randomKillerCase());
    }

private:
    void randomCase() {
        X.clear();
        K.clear();
        for (int i = 0; i < M; i++) {
            int x = rnd.nextInt(N) + 1;
            int k = rnd.nextInt(50000) + 1;
            X.push_back(x);
            K.push_back(k);
        }
    }

    void randomKillerCase() {
        X.clear();
        K.clear();
        for (int i = 0; i < M; i++) {
            int x = rnd.nextInt(N) + 1;
            int k;

            if (i < M/4) {
                k = N/2 - rnd.nextInt(42);
            } else {
                k = N - rnd.nextInt(42);
            }
            X.push_back(x);
            K.push_back(k);
        }
    }

    void randomSmallTaburanCase() {
        X.clear();
        K.clear();
        for (int i = 0; i < M; i++) {
            int x = rnd.nextInt(N) + 1;
            int k;

            if (i < M/4) {
                k = rnd.nextInt(N) + 1;
            } else {
                k = rnd.nextInt(10);
            }
            X.push_back(x);
            K.push_back(k);
        }
    }
};

int main(int argc, char* argv[]) {
    Runner<Problem> runner(argc, argv);

    runner.setGenerator(new Generator());
    return runner.run();
}
