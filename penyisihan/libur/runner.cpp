#include "tcframe/runner.hpp"
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

class Problem : public BaseProblem {
protected:
    int N, S, P, T;
    vector<int> K,V;
    int RES;
    void Config() {
        setSlug("libur");
        setTimeLimit(3);
        setMemoryLimit(64);
        setMultipleTestCasesCount(T);
    }

    void InputFormat() {
        LINE(N, S, P);
        LINES(K, V) % SIZE(N-1);
    }

    void OutputFormat() {
        LINE(RES);
    }

    void Constraints() {
        CONS(2 <= N && N <= 1000);
        CONS(0 <= P && P <= 1000);
        CONS(0 <= S && S <= 1000);
        CONS(eachElementBetween(K,0,1000));
        CONS(eachElementBetween(V,0,1000));
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
        SAMPLE_CASE({
            "5 10 5",
            "1 3",
            "5 4",
            "12 3",
            "4 6"
        });
        SAMPLE_CASE({
            "3 10 11",
            "2 10",
            "9 10"
        });
        SAMPLE_CASE({
            "4 10 3",
            "6 10",
            "5 12",
            "7 9"
        });
    }

    void TestGroup1() {
        assignToSubtasks({-1});
        //tricky #1: can't reach the destination except flight
        CASE(N = 100, S = 100, P = 100 , randomNumbers(K, 11,11),randomNumbers(V, 1,1000));
        //tricky #2: impossible
        CASE(N = 200, S = 200, P = 201 , randomNumbers(K, 11,11),randomNumbers(V, 1,1000));
        //tricky #3: fly to N-1, then train
        CASE(N = 5, S = 2, P = 1 , K = {1,1,1,1} , V = {1,2,3,4});
        //tricky #4: index meledak
        CASE(N = 2, S = 0, P = 1000, K = {999} , V = {1000});
        //tricky #5: gratisan
        CASE(N = 1000, S = 0, P = 0, randomNumbers(K, 0,0),randomNumbers(V, 1,1000));
        //tricky #6: gratisan, ga ada indah2nya
        CASE(N = 1000, S = 0, P = 0, randomNumbers(K, 0,0),randomNumbers(V, 0,0));  
        // cheap train, cheap flight
        for (int i=0;i<4;i++) CASE(N = rnd.nextInt(900,1000), S = rnd.nextInt(900,1000), P = rnd.nextInt(50,100),randomNumbers(K, 0,10),randomNumbers(V, 0,1000));
       // expensive flight mode
    }
    void TestGroup2(){
        assignToSubtasks({-1});
        for (int i=0;i<4;i++) CASE(N = rnd.nextInt(900,1000), S = rnd.nextInt(900,1000), P = rnd.nextInt(500,1000),randomNumbers(K, 0,100),randomNumbers(V, 0,1000));
        // super cheap flight mode
        for (int i=0;i<4;i++) CASE(N = rnd.nextInt(900,1000), S = rnd.nextInt(900,1000), P = rnd.nextInt(1,10),randomNumbers(K, 0,100),randomNumbers(V, 0,1000));
        //full random
        CASE(N = rnd.nextInt(900,1000), S = rnd.nextInt(900,1000), P = rnd.nextInt(1,1000),randomNumbers(K, 0,1000),randomNumbers(V, 0,1000));    
        CASE(N = 1000, S = 1000, P = 10,randomNumbers(K, 0,1000),randomNumbers(V, 0,1000));
   
    }

    void TestGroup3() {
        assignToSubtasks({-1});
        //high beauty
        for (int i=0;i<5;i++) CASE(N = rnd.nextInt(900,1000), S = rnd.nextInt(900,1000), P = 20,randomNumbers(K, 0,100),randomNumbers(V, 500,1000));
        //low beauty
        for (int i=0;i<5;i++) CASE(N = rnd.nextInt(900,1000), S = rnd.nextInt(900,1000), P = 20,randomNumbers(K, 0,100),randomNumbers(V, 1,10));
        //cheap flight, expensive train
    }

    void TestGroup4(){
        assignToSubtasks({-1});
        for (int i=0;i<5;i++) CASE(N = rnd.nextInt(900,1000), S = rnd.nextInt(900,1000), P = rnd.nextInt(50,100),randomNumbers(K, 100,1000),randomNumbers(V, 0,1000));
        // super cheap flight mode
        for (int i=0;i<5;i++) CASE(N = rnd.nextInt(900,1000), S = rnd.nextInt(900,1000), P = rnd.nextInt(1,10),randomNumbers(K, 0,100),randomNumbers(V, 0,1000));
    }

    private:
        void randomNumbers(vector<int>& v, int minElem, int maxElem){
            v.clear();
            for (int i = 1; i < N; i++) {
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
