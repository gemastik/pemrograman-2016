#include "tcframe/runner.hpp"
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

class Problem : public BaseProblem {
protected:
    int N, K, T;
    vector<int> A;
    string RES;

    void Config() {
        setSlug("rotation");
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
        CONS(3 <= N && N <= 50000);
        CONS(eachElementBetween(A,1,N));
    }

    void MultipleTestCasesConstraints() {
        CONS(T <= 40);
    }

private:
    bool eachElementBetween(const vector<int>& A, int lo, int hi) {
        return all_of(A.begin(), A.end(), [lo, hi](int a) {return lo <= a && a <= hi;});
    }
};

class Generator : public BaseGenerator<Problem> {
protected:
    void SampleTestCases() {
        SAMPLE_CASE({"4", "3" , "4" , "2" , "1"});
        SAMPLE_CASE({"3","3", "1", "2"});
        SAMPLE_CASE({"5","1", "4" , "3" , "2" , "5"});
    }

    void TestCases() {
       for (int i=0;i<40;i++) CASE(N = rnd.nextInt(40000,50000), doRandomPermutation());
    }

    private:
        void doRandomPermutation(){
            A.clear();
            for (int i=0;i<N;i++)
                A.push_back(i+1);

            random_shuffle(A.begin(), A.end());
        }
};

int main(int argc, char* argv[]) {
    Runner<Problem> runner(argc, argv);

    runner.setGenerator(new Generator());
    return runner.run();
}
