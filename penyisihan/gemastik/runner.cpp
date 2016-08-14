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
        LINE(nama[0], nama[1], nama[2]);
        LINE(nama[3], nama[4], nama[5]);
    }

    void Constraints() {
        CONS(6 <= N && N <= 50000);
        CONS(eachElementLengthBetween(I,1,8));
    }

    void MultipleTestCasesConstraints() {
        CONS(T <= 25);
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
        SAMPLE_CASE({"9",
            "abdul 3 3",
            "afaji 7 6",
            "alham 11 6",
            "alice 7 12",
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

    void TestCases() {
       CASE(N = 10, randomNames() , G = {5,5,5,6,6,6,1,1,1,3} , C = {5,5,5,1,1,1,6,6,6,3});
       CASE(N = 10, randomNames(), G = {10,10,10,1,1,1,3,4,2,2} , C = {9,9,9,8,8,8,5,4,2,1} );
       CASE(N = 10, randomNames(), G = {9,9,9,8,8,8,5,4,2,1} , C = {10,10,10,1,1,1,3,4,2,2} );
       CASE(N = 6, randomNames() , G = {5,4,3,2,1,1} , C = {1000,1000,1000,1,1,1} );
       CASE(N = 6, randomNames() , G = {100,1,1,99,99,99} , C = {99,99,99,1,1,1} );
       CASE(N = 9, randomNames() , G = {5,5,5,9,9,9,9,9,9} , C = {5,5,5,1,1,1,1,1,1});
       CASE(N = 6, randomNames() , G = {1000,1000,1000,1,1,1} , C = {5,4,3,2,1,1});
       CASE(N = 6, randomNames() , G = {99,99,99,1,1,1}, C = {100,1,1,99,99,99} );
       CASE(N = 9, randomNames() , G = {5,5,5,1,1,1,1,1,1}, C = {5,5,5,9,9,9,9,9,9});
       for (int i=0;i<5;i++) CASE(N = 45312, randomNames() , randomNumbers(G, 1,1000000), randomNumbers(C, 1,1000000));
       for (int i=0;i<5;i++) CASE(N = 48999, randomNames() , randomNumbers(G, 1,100), randomNumbers(C, 1,100));
       for (int i=0;i<6;i++) CASE(N = 50000, randomNames() , randomNumbers(G, 1,1000), randomNumbers(C, 1,1000));

    }

    private:
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
