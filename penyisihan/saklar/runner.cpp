#include "tcframe/runner.hpp"
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

class Problem : public BaseProblem {
protected:
    int T;
    int L, B;
    string RES;

    void Config() {
        setSlug("saklar");
        setTimeLimit(2);
        setMemoryLimit(64);
        setMultipleTestCasesCount(T);
    }

    void InputFormat() {
        LINE(L,B);
    }

    void OutputFormat() {
        LINE(RES);
    }

    void Constraints() {
        CONS(0 <= L && L <= 100);
        CONS(0 <= B && B <= 100);
        CONS(2 <= B + L);

    }

    void MultipleTestCasesConstraints() {
        CONS(T <= 20);
    }
};

class Generator : public BaseGenerator<Problem> {
protected:
    void SampleTestCases() {
        SAMPLE_CASE({"4 0"});
        SAMPLE_CASE({"0 4"});
        SAMPLE_CASE({"8 8"});
    }

    void TestGroup1() {
        assignToSubtasks({-1});
        CASE(L = 4, B = 12);
        CASE(L = 12, B = 4);
        CASE(L = 1, B = 1);
        CASE(L = 2, B = 0);
        CASE(L = 0, B = 2);
        CASE(L = 0, B = 100);
        CASE(L = 100, B = 0);
        CASE(L = 100, B = 100);
        for (int i=0;i<6;i++)
            CASE(L = rnd.nextInt(2,100), B = 0);
        for (int i=0;i<6;i++)
            CASE(L = 0, B = rnd.nextInt(2,100));
        
    }

    void TestGroup2() {
        assignToSubtasks({-1});
        for (int i=0;i<10;i++)
            CASE(L = rnd.nextInt(1,100), B = rnd.nextInt(1,100));
        for (int i=0;i<10;i++)
            CASE(L = rnd.nextInt(50,100), B = rnd.nextInt(50,100));
    }
};

int main(int argc, char* argv[]) {
    Runner<Problem> runner(argc, argv);

    runner.setGenerator(new Generator());
    return runner.run();
}
