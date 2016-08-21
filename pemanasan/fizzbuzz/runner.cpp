#include "tcframe/runner.hpp"
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

class Problem : public BaseProblem {
protected:
    int T;
    int N,K;
    vector<int> M;
    vector<string> S;
    vector<string> RES;

    void Config() {
        setSlug("fizzbuzz");
        setTimeLimit(2);
        setMemoryLimit(64);
        setMultipleTestCasesCount(T);
    }

    void InputFormat() {
        LINE(N,K);
        LINES(M,S) % SIZE(K);
    }

    void OutputFormat() {
        LINES(RES) % SIZE(N);
    }

    void Constraints() {
        CONS(1 <= K && K <= 20);
        CONS(1 <= N && N <= 1000);
        CONS(eachElementLengthBetween(S,1,5));
        CONS(validStrings(S));
        CONS(eachElementBetween(M,1,1000));
        CONS(eachElementSortedAscendingly(M));
    }

    void MultipleTestCasesConstraints() {
        CONS(T <= 20);
    }

private:
    bool eachElementSortedAscendingly(const vector<int>& V) {
        int len = V.size();
        for (int i=1;i<len;i++){
            if (V[i] <= V[i - 1])
                return 0;
        }
        return 1;
    }

    bool eachElementBetween(const vector<int>& A, int lo, int hi) {
        return all_of(A.begin(), A.end(), [lo, hi](int a) {return lo <= a && a <= hi;});
    }

    bool eachElementLengthBetween(const vector<string>& S, int lo, int hi) {
        return all_of(S.begin(), S.end(),[lo, hi](string s) {return lo <= s.size() && s.size() <= hi;});
    }

    bool validStrings(const vector<string>& s) {
        for (string t : s) {
            for (char c : t) {
                if (c < 'a' || c > 'z') {
                    return false;
                }
            }
        }
        return true;
    }
};

class Generator : public BaseGenerator<Problem> {
protected:
    void SampleTestCases() {
        SAMPLE_CASE({"10 2" , "3 fizz" , "5 buzz"});
        SAMPLE_CASE({"20 3" , "2 lho" , "4 hai" , "5 halo"});
        SAMPLE_CASE({"5 2" , "1 a" , "2 b"});
    }

    void TestCases() {
        CASE(N = 10, K = 1, M = {999} , S = {"abc"});
        CASE(N = 1000, K = 20, M = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20} , S = {"a","b","a","b","a","b","a","b","a","b","a","b","a","b","a","b","a","b","a","b"});
        for (int i=0;i<18;i++)
            CASE(N = rnd.nextInt(1,1000), K = rnd.nextInt(1,20), randomFizzBuzz());
    }
private:
    void randomFizzBuzz(){
        M.clear();
        S.clear();
        int now = 0;
        for (int i=0;i<K;i++){
            int tmp = rnd.nextInt(now + 1, now + 50);
            now = tmp;
            M.push_back(tmp);
            string s = "";
            s += rnd.nextInt('a','z');
            s += rnd.nextInt('a','z');
            s += rnd.nextInt('a','z');
            S.push_back(s);
        }
    }
};

int main(int argc, char* argv[]) {
    Runner<Problem> runner(argc, argv);

    runner.setGenerator(new Generator());
    return runner.run();
}
