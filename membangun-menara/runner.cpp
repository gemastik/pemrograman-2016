#include "tcframe/runner.hpp"
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

class Problem : public BaseProblem {
protected:
    int N, K, T;
    vector<int> A,B,C;
    int X;
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
        LINE(X);
    }

    void Constraints() {
        CONS(1 <= N && N <= 50000);
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
        SAMPLE_CASE({"2",
                    "1 1 3", "2 3 1"
        });

        SAMPLE_CASE({"5",
            "12 19 9",
            "10 11 13",
            "9 8 7",
            "5 5 5",
            "100 98 101"
        });
    }
    
    void TestCases() {
       for (int i=0;i<10;i++) CASE(N = 40002, randomNumbers(A, 1,30),randomNumbers(B, 1,30),randomNumbers(C, 1,30));
       for (int i=0;i<10;i++) CASE(N = 50000, randomNumbers(A, 1,1000),randomNumbers(B, 1,1000),randomNumbers(C, 1,1000));
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
