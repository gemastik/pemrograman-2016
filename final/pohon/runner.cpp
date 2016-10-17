#include "tcframe/runner.hpp"
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

class Problem : public BaseProblem {
protected:
    int T;
    int N;
    vector<int> A,B;
    int RES;
    void Config() {
        setSlug("pohon");
        setTimeLimit(10000);
        setMemoryLimit(256);
        setMultipleTestCasesCount(T);
    }

    void InputFormat() {
        LINE(N);
        LINES(A,B) % SIZE(N - 1);
    }

    void OutputFormat() {
        LINE(RES);
    }

    void Constraints() {

        CONS(0 < N && N <= 50000);
        CONS(eachElementBetween(A,1,N));
        CONS(eachElementBetween(B,1,N));
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
        SAMPLE_CASE({"4",
                    "1 2",
                    "1 3",
                    "4 1"});
        SAMPLE_CASE({"5",
                    "1 2", 
                    "2 3",
                    "3 4",
                    "4 5"});
        SAMPLE_CASE({"6",
                    "2 1",
                    "1 3",
                    "3 4",
                    "3 5",
                    "2 6"});
    }

    // random, dengan interval paling panjang 100 atau 1000. 0.0001% interval TIDAK mengikuti aturan tsb.
    void TestGroup1() {
        assignToSubtasks({-1});
        //full random testcases
        for (int i=0;i<9;i++){
            CASE(N = rnd.nextInt(45000, 50000), randomTree());
        }
        CASE(N = 50000, randomTree());
    }

    void TestGroup2() {
        assignToSubtasks({-1});
        CASE(N = rnd.nextInt(45000, 50000), n_ary_tree(1)); //chain
        CASE(N = rnd.nextInt(45000, 50000), n_ary_tree(2)); //binary
        CASE(N = rnd.nextInt(45000, 50000), n_ary_tree(3)); //trinary
        CASE(N = rnd.nextInt(45000, 50000), n_ary_tree(1000)); //lebar
        CASE(N = rnd.nextInt(45000, 50000), n_ary_tree(999999)); //star
        CASE(N = 1, A = {}, B = {});
        CASE(N = 2, A = {1}, B = {2});
        CASE(N = 3, A = {1,3}, B = {2,1});
        CASE(N = 3, A = {1,2}, B = {2,3});
    }

private:
    void randomTree(){
        A.clear();
        B.clear();
        for (int i=2;i<=N;i++){
            int x = rnd.nextInt(1,N);
            while (x == i) 
                x = rnd.nextInt(1,N);
            A.push_back(x);
            B.push_back(i);
        }
    }

    void n_ary_tree(int n){
        A.clear();
        B.clear();
        int now = 1;
        int ct = 0;
        for (int i=2;i<=N;i++){
            ct++;
            A.push_back(now);
            B.push_back(i);
            if (ct == n){
                ct = 0;
                now++;
            }
        }
    }
};

int main(int argc, char* argv[]) {
    Runner<Problem> runner(argc, argv);

    runner.setGenerator(new Generator());
    return runner.run();
}
