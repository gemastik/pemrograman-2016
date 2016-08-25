#include "tcframe/runner.hpp"
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

class Problem : public BaseProblem {
protected:
    int N, K, T;
    vector<int> G , C;
    vector<string> I;

    string nama[6];
    long long RES;
    void Config() {
        setSlug("gemas");
        setTimeLimit(3);
        setMemoryLimit(256);
        setMultipleTestCasesCount(T);
    }

    void InputFormat() {
        LINE(N);
        LINES(I, G, C) % SIZE(N);
    }

    void OutputFormat() {
        LINE(RES);
        LINE(nama[0], nama[1], nama[2]);
        LINE(nama[3], nama[4], nama[5]);
    }

    void Constraints() {
        CONS(6 <= N && N <= 50000);
        CONS(eachElementLengthBetween(I,1,8));
        CONS(eachElementBetween(G,1,100000));
        CONS(eachElementBetween(C,1,100000));
    }

    void MultipleTestCasesConstraints() {
        CONS(T <= 10);
    }

private:
    bool eachElementBetween(const vector<int>& A, int lo, int hi) {
        return all_of(A.begin(), A.end(), [lo, hi](int a) {return lo <= a && a <= hi;});
    }

    bool eachElementLengthBetween(const vector<string>& S, int lo, int hi) {
        return all_of(S.begin(), S.end(),[lo, hi](string s) {return lo <= s.size() && s.size() <= hi;});
    }
};

class Generator : public BaseGenerator<Problem> {
protected:
    void SampleTestCases() {
        SAMPLE_CASE({"6",
            "dana 10 9",
            "dini 10 9",
            "dani 10 9",
            "dono 9 10",
            "dona 9 10",
            "dina 9 10"
        });
        SAMPLE_CASE({"9",
            "abdul 3 3",
            "afaji 7 6",
            "alham 10 6",
            "alice 7 10",
            "budi 5 3",
            "jack 3 10",
            "kwak 10 10",
            "kwek 2 6",
            "kwok 5 8"
        });

        SAMPLE_CASE({"11",
            "charlie 11 60",
            "eko 70 32",
            "fauzan 101 101",
            "victor 99 103",
            "halim 103 10",
            "mona 16 100",
            "ridho 20 64",
            "sherly 54 85",
            "ahmad 100 3",
            "bambang 40 23",
            "wawan 74 19"
        });
    }


    void TestGroup1() {
        assignToSubtasks({-1});
        CASE(maut());
        CASE(N = 10, randomNames() , G = {5,5,5,6,6,6,1,1,1,3} , C = {5,5,5,1,1,1,6,6,6,3});
        CASE(N = 10, randomNames(), G = {10,10,10,1,1,1,3,4,2,2} , C = {9,9,9,8,8,8,5,4,2,1} );
        CASE(N = 10, randomNames(), G = {9,9,9,8,8,8,5,4,2,1} , C = {10,10,10,1,1,1,3,4,2,2} );
        CASE(N = 6, randomNames() , G = {5,4,3,2,1,1} , C = {1000,1000,1000,1,1,1} );
        CASE(N = 6, randomNames() , G = {100,1,1,99,99,99} , C = {99,99,99,1,1,1} );
        CASE(N = 9, randomNames() , G = {5,5,5,9,9,9,9,9,9} , C = {5,5,5,1,1,1,1,1,1});
        CASE(N = 6, randomNames() , G = {1000,1000,1000,1,1,1} , C = {5,4,3,2,1,1});
        CASE(N = 6, randomNames() , G = {99,99,99,1,1,1}, C = {100,1,1,99,99,99} );
        CASE(N = 9, randomNames() , G = {5,5,5,1,1,1,1,1,1}, C = {5,5,5,9,9,9,9,9,9});
    }

    void TestGroup2(){
        assignToSubtasks({-1});
        CASE(N = 50000, randomNames() , randomNumbers(G, 100000,100000), randomNumbers(C, 100000,100000)); //extreme case
        CASE(N = 50000, randomNames() , randomNumbers(G, 1,1), randomNumbers(C, 1,1)); //extreme case
        for (int i=0;i<2;i++) CASE(N = rnd.nextInt(40000,50000), randomNames() , randomNumbers(G, 1,100000), randomNumbers(C, 1,100000));
        //yg jago cuman 20 orang. konflik.
        for (int i=0;i<6;i++) CASE(N = 20, randomNumbers(G, 50,100), randomNumbers(C, 50,100), add_useless(50000 - N) , N = 50000, randomNames());
    }
    
    void TestGroup3() {
        assignToSubtasks({-1});
        for (int i=0;i<5;i++) {
            //yg jago cuman (1-10) orang. konflik.
            CASE(N = rnd.nextInt(1,10), randomNumbers(G, 990,1000), randomNumbers(C, 990,1000), add_useless(50000 - N) , N = 50000, randomNames());
            //yg jago cuman (20-30) orang. konflik.
            CASE(N = rnd.nextInt(20,30), randomNumbers(G, 1,10), randomNumbers(C, 1,10), add_useless(50000 - N) , N = 50000, randomNames());
        
        }
    }
    
    void TestGroup4(){
        assignToSubtasks({-1});
        for (int i=0;i<5;i++) {
            //yg jago cuman i orang. konflik.
            CASE(N = rnd.nextInt(1,30), randomNumbers(G, 10,20), randomNumbers(C, 990,1000), add_useless(50000 - N) , N = 50000, randomNames());
            CASE(N = rnd.nextInt(1,30), randomNumbers(G, 990,1000), randomNumbers(C, 10,20), add_useless(50000 - N) , N = 50000, randomNames());
        }
    }

    private:
        void add_weighted_data(int min_G,int max_G, int min_C, int max_C, int potential){
            
        }

        void add_useless(int n) {
            for (int i=0;i<n;i++){
                add_data(1,1);
            }
        }

        void add_data(int g,int c) {
            G.push_back(g);
            C.push_back(c);
        }
        void maut() {
            N = 616;
            randomNames();
            G.clear();
            C.clear();
            //random
            for (int i=0;i<110;i++) add_data(94,96);

            //gemas
            add_data(95,1);
            add_data(100,99);
            add_data(99,100);

            //cantik
            add_data(99,101);
            add_data(1,98);
            add_data(1,97);
            
            for (int i=0;i<100;i++) add_data(90,90);
            for (int i=0;i<100;i++) add_data(94,2);
            for (int i=0;i<100;i++) add_data(2,95);
            for (int i=0;i<100;i++) add_data(93,93);
            for (int i=0;i<100;i++) add_data(2,2);
        }


        string get_string(int x){
            string res = to_string(x);
            for (int i=0;i<res.size();i++)
                res[i] += 'a' - '0';
            return res;
        }

        void randomNames() {
            I.clear();
            for (int i=0;i<N;i++){
                I.push_back(get_string(i));
            }
            sort(I.begin(), I.end());
        }

        void randomNumbers(vector<int>& v, int minElem, int maxElem){
            v.clear();
            for (int i = 0; i < N; i++) {
                int budget = rnd.nextInt(minElem, maxElem);
                v.push_back(budget);
            }
        }
};

int main(int argc, char* argv[]) {
    Runner<Problem> runner(argc, argv);

    runner.setGenerator(new Generator());
    return runner.run();
}
