#include "tcframe/runner.hpp"
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

const int MIN_X = 1;
const int MAX_X = 2 * 1000 * 1000 * 1000;
const int MIN_Y = 1;
const int MAX_Y = 2 * 1000 * 1000 * 1000;

typedef long long ll;

class Problem : public BaseProblem {
protected:
    int T;
    int N, Q;
    vector<int> X, Y;
    vector<int> X1, K;
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
        LINES(X1, K) % SIZE(Q);
    }

    void OutputFormat() {
        LINES(RES) % SIZE(Q);
    }

    void Constraints() {
        CONS(1 <= N && N <= 100*1000);
        CONS(1 <= Q && Q <= 100*1000);
        CONS(eachElementBetween(X, MIN_X, MAX_X));
        CONS(eachElementBetween(Y, MIN_Y, MAX_Y));
        CONS(eachElementBetween(X1, MIN_X, MAX_X));
        CONS(eachElementBetween(K, 1, N));
        CONS(isUnique(X));
    }

    void MultipleTestCasesConstraints() {
        CONS(1 <= T && T <= 5);
    }

private:
    bool eachElementBetween(const vector<int>& A, int lo, int hi) {
        return all_of(A.begin(), A.end(), [lo, hi](int a) {return lo <= a && a <= hi;});
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
            "1 2",
            "3 4",
            "5 3",
            "2 9",
            "4 7",
            "6 5",
            "9 8",
            "10 1",
            "12 6",
            "6",
            "1 2",
            "3 3",
            "5 4",
            "5 5",
            "10 3",
            "11 5"
        });
    }

    void TestGroup1() {
        assignToSubtasks({-1});
        CASE(N = 3, Q = 1, X = {1, 500000000, 1000000000}, Y = {1, 500000000, 2}, X1 = {1}, K = {1});
        CASE(N = 1000, Q = 50, randomCase());
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

    void TestGroup4() {
        assignToSubtasks({-1});
        CASE(N = 50000, Q = 50000, paraboleCase());
        CASE(N = 50000, Q = 50000, antiParaboleCase());
        CASE(N = 50000, Q = 50000, multiParaboleCase());
        CASE(N = 50000, Q = 50000, multiAntiParaboleCase());
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

    vector<int> getParaboloidValues(int min, int max) {
        vector<int> values;

        int cur = min;
        int delta = 1;
        while (cur <= max) {
          values.push_back(cur);

          cur += delta;
          delta++;
        }

        return values;
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
        K.clear();

        vector<int> S = X;
        sort(S.begin(), S.end());

        for (int q = 0; q < Q; q++) {
            int x1 = genPoint(S[rnd.nextInt(N)]);
            int k = rnd.nextInt(1, N);
            X1.push_back(x1);
            K.push_back(k);
        }
    }


    void randomKillerCase() {
        X = genCoord();
        Y = genCoord();
        X1.clear();
        K.clear();

        vector<int> S = X;
        sort(S.begin(), S.end());

        for (int q = 0; q < Q; q++) {
            int a;
            if (rnd.nextInt(100) < 90) {
                a = S[rnd.nextInt(10)];
            } else {
                a = S[rnd.nextInt(N)];
            }

            int x1 = genPoint(a);
            int k = rnd.nextInt(1, N);
            X1.push_back(x1);
            K.push_back(k);
        }
    }

    // U n U n
    void paraboleCase() {
        X = genCoord();
        Y.clear();
        X1.clear();
        K.clear();

        sort(X.begin(), X.end());

        vector<int> paraboloidValue = getParaboloidValues(MIN_X, MAX_Y);
        reverse(paraboloidValue.begin(), paraboloidValue.end());

        int p = 0;
        int direction = 1;
        for (int i = 0; i < N; i++) {
          Y.push_back(paraboloidValue[p]);

          if ((p + direction < 0) || (p + direction >= paraboloidValue.size())) {
            direction = -direction;
          }
          p += direction;
        }

        for (int q = 0; q < Q; q++) {
            int x1 = genPoint(X[rnd.nextInt(N)]);
            int k = rnd.nextInt(1, N);
            X1.push_back(x1);
            K.push_back(k);
        }
    }

    // n U n U
    void antiParaboleCase() {
      paraboleCase();

      for (int i = 0; i < N; i++) {
        Y[i] = MAX_Y - (Y[i] - MIN_Y);
      }
    }

    // like a bunch of bananas
    void multiParaboleCase() {
        // number of layer for paraboles
        int layer = 5;
        int layerGap = (MAX_Y - MIN_Y) / layer;

        X = genCoord();
        Y.clear();
        X1.clear();
        K.clear();

        sort(X.begin(), X.end());

        vector<int> paraboloidValue = getParaboloidValues(MIN_X, MAX_Y);
        reverse(paraboloidValue.begin(), paraboloidValue.end());

        int p = 0;
        int i = 0;
        int direction = 1;
        while (1) {
          long long y = paraboloidValue[p];

          for (int l = 0; l < layer; l++) {
            y += l * layerGap;

            // wrap around
            Y.push_back(MIN_Y + y % (MAX_Y - MIN_Y));
            if (Y.size() == N) {
              break;
            }
          }

          if (Y.size() == N) {
            break;
          }

          if ((p + direction < 0) || (p + direction >= paraboloidValue.size())) {
            direction = -direction;
          }
          p += direction;
        }

        for (int q = 0; q < Q; q++) {
            int x1 = genPoint(X[rnd.nextInt(N)]);
            int k = rnd.nextInt(1, N);
            X1.push_back(x1);
            K.push_back(k);
        }
    }

    void multiAntiParaboleCase() {
      multiParaboleCase();

      for (int i = 0; i < N; i++) {
        Y[i] = MAX_Y - (Y[i] - MIN_Y);
      }
    }
};

int main(int argc, char* argv[]) {
    Runner<Problem> runner(argc, argv);

    runner.setGenerator(new Generator());
    return runner.run();
}
