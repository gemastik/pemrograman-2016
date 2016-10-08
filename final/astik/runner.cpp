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
        setSlug("astik");
        setTimeLimit(2);
        setMemoryLimit(64);
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
        CONS(permutation(A,N));
    }

    void MultipleTestCasesConstraints() {
        CONS(1 <= T && T <= 40);
    }

private:
    bool permutation(const vector<int>& a, int n) {
        set<int> s;
        for (int x : a) {
            if (x < 1 || x > n || s.count(x)) {
                return false;
            }
            s.insert(x);
        }
        return true;
    }
};

class Generator : public BaseGenerator<Problem> {
protected:
    void SampleTestCases() {
        SAMPLE_CASE({"5", "2" , "3" , "5" , "1" , "4"});
        SAMPLE_CASE({"5","1", "4" , "3" , "2" , "5"});
    }

    void TestCases() {
        CASE(N = 4, A = {3, 4, 2, 1});
        for (int i=0;i<19;i++) CASE(N = rnd.nextInt(1,1000), doRandomPermutation());
        for (int i=0;i<19;i++) CASE(N = rnd.nextInt(40000,50000), doRandomPermutation());
        CASE(N = 50000, doRandomPermutation());
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
