#include "tcframe/runner.hpp"
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

class Problem : public BaseProblem {
protected:
    int N, K, T;
    vector<int> A,B,C;
    int H_MIN, H_MAX;
    void Config() {
        setSlug("menara");
        setTimeLimit(3);
        setMemoryLimit(256);
        setMultipleTestCasesCount(T);
    }

    void InputFormat() {
        LINE(N);
        LINES(A , B , C) % SIZE(N);
    }

    void OutputFormat() {
        LINE(H_MIN, H_MAX);
    }

    void Constraints() {
        CONS(1 <= N && N <= 100);
        CONS(eachElementBetween(A,1,1000));
        CONS(eachElementBetween(B,1,1000));
        CONS(eachElementBetween(C,1,1000));
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
        SAMPLE_CASE({"3","1 2 3","5 4 6","9 8 7"});
        SAMPLE_CASE({"1","6 6 6"});
        SAMPLE_CASE({"2","1 1 1","10 20 30"});
    }

    void TestCases() {
       for (int i=0;i<10;i++) CASE(N = rnd.nextInt(90,100), randomNumbers(A, 1,30),randomNumbers(B, 1,30),randomNumbers(C, 1,30));
       for (int i=0;i<10;i++) CASE(N = rnd.nextInt(90,100),randomNumbers(A, 1,1000),randomNumbers(B, 1,1000),randomNumbers(C, 1,1000));
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
