#include "tcframe/runner.hpp"
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

class Problem : public BaseProblem {
protected:
    int T;
    long long N;
    int M;
    int res;

    void Config() {
        setSlug("balon");
        setTimeLimit(2);
        setMemoryLimit(64);
        setMultipleTestCasesCount(T);
    }

    void InputFormat() {
        LINE(N, M);
    }

    void OutputFormat() {
        LINE(res);
    }

    void Constraints() {
        CONS(1ll <= N && N <= LLONG_MAX);
        CONS(1000 <= M && M <= 100000);
    }

    void MultipleTestCasesConstraints() {
        CONS(1 <= T && T <= 20);
    }
};

class Generator : public BaseGenerator<Problem> {
protected:
    void SampleTestCases() {
        SAMPLE_CASE({
            "3 1234"
        });
        SAMPLE_CASE({
            "52 1009"
        });
    }

    void TestCases() {
        CASE(N = 1ll, M = 1000);
        CASE(N = 1ll, M = 100000);
        CASE(N = 2ll, M = 1000);
        CASE(N = 3ll, M = 1000);
        CASE(N = 4ll, M = 1000);
        CASE(N = 5ll, M = 1000);
        CASE(N = 5ll, M = 100000);
        CASE(N = 100ll, M = 96557);
        CASE(N = 9223372036854775807ll, M = 96557);
        CASE(N = 9223372036854775807ll, M = 100000);
        CASE(N = 96560ll, M = 96557);
        CASE(N = 96559ll, M = 96557);
        CASE(N = 96558ll, M = 96557);
        CASE(N = 96557ll, M = 96557);
        CASE(N = 96556ll, M = 96557);
        CASE(N = 96555ll, M = 96557);
        CASE(N = 96554ll, M = 96557);
        CASE(N = 96553ll, M = 96557);
        CASE(N = 96552ll, M = 96557);
        CASE(N = 12345ll, M = 96557);
    }
};

int main(int argc, char* argv[]) {
    Runner<Problem> runner(argc, argv);

    runner.setGenerator(new Generator());
    return runner.run();
}
