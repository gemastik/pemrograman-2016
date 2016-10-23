#include "tcframe/runner.hpp"
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

class Problem : public BaseProblem {
protected:
    int T;
    int N;
    vector<int> L;
    long long RES;
    void Config() {
        setSlug("gapura");
        setTimeLimit(10000);
        setMemoryLimit(256);
        setMultipleTestCasesCount(T);
    }

    void InputFormat() {
        LINE(N);
        LINE(L % SIZE(N));
    }

    void OutputFormat() {
        LINE(RES);
    }

    void Constraints() {

        CONS(2 < N && N <= 25);
        CONS(eachElementBetween(L,1,100000));
    }

    void MultipleTestCasesConstraints() {
        CONS(T <= 10);
    }


private:
    bool eachElementBetween(const vector<int>& A, int lo, int hi) {
        return all_of(A.begin(), A.end(), [lo, hi](int a) {return lo <= a && a <= hi;});
    }
};

class Generator : public BaseGenerator<Problem> {
protected:
    void SampleTestCases() {
        SAMPLE_CASE({"7",
                    "1 1 1 3 2 4 1"});
        SAMPLE_CASE({"3",
                    "3 5 7"
                    });
    }

    // random, dengan interval paling panjang 100 atau 1000. 0.0001% interval TIDAK mengikuti aturan tsb.
    void TestGroup1() {
        assignToSubtasks({-1});
        CASE(N = rnd.nextInt(20, 25), randomLength(1,100000));
        CASE(N = rnd.nextInt(20, 25), randomLength(10,20));
        CASE(N = 25, randomLength(1,1));
        CASE(N = 25, randomLength(1,2));
        CASE(N = 25, randomLength(100000,100000));
        CASE(N = 25, randomLength(99999,100000));
        CASE(N = 25, randomLength(1,10));
        CASE(N = 25, L = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25});
        CASE(N = 14, L = {1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192});
        CASE(N = 24, L = {4,8,16,32,64,128,256,512,1024,2048,4096,8192,4,8,16,32,64,128,256,512,1024,2048,4096,8192});
    }

private:
    void randomLength(int lo, int hi){
        L.clear();
        for (int i=0;i<N;i++)
            L.push_back(rnd.nextInt(lo,hi));
    }

    
};

int main(int argc, char* argv[]) {
    Runner<Problem> runner(argc, argv);

    runner.setGenerator(new Generator());
    return runner.run();
}
