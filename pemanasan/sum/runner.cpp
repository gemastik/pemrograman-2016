#include "tcframe/runner.hpp"
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

class Problem : public BaseProblem {
protected:
    int N, K, T;
    vector<int> A;
    long long RES;
    void Config() {
        setSlug("sum");
        setTimeLimit(3);
        setMemoryLimit(256);
        setMultipleTestCasesCount(T);
    }

    void InputFormat() {
        LINE(N);
        LINES(A) % SIZE(N);
    }

    void OutputFormat() {
        LINE(RES);
    }

    void Constraints() {
        CONS(1 <= N && N <= 100000);
        CONS(eachElementBetween(A,1,1000000000));
    }

    void MultipleTestCasesConstraints() {
        CONS(T <= 20);
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
            "3",
            "100",
            "200",
            "300"
        });
        SAMPLE_CASE({
            "5",
            "923082016",
            "927082016",
            "922092016",
            "923092016",
            "924092016"
        });
    }

    void TestCases() {
       for (int i=0;i<5;i++) CASE(N = rnd.nextInt(100,1000), randomNumbers(A, 1,1000000));
       for (int i=0;i<14;i++) CASE(N = rnd.nextInt(99000,100000), randomNumbers(A, 500000000,1000000000));
       CASE(N = 100000, randomNumbers(A, 500000000,1000000000));
    }

    private:
        void randomNumbers(vector<int>& v, int minElem, int maxElem){
            v.clear();
            for (int i = 0; i < N; i++) {
                int block_size = rnd.nextInt(minElem, maxElem);
                v.push_back(block_size);
            }
        }
};

int main(int argc, char* argv[]) {
    Runner<Problem> runner(argc, argv);

    runner.setGenerator(new Generator());
    return runner.run();
}
