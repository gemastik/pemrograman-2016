#include "tcframe/runner.hpp"
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

class Problem : public BaseProblem {
protected:
    int T;
    int N;
    vector<string> ST,ED;
    string RES;

    void Config() {
        setSlug("kode");
        setTimeLimit(3);
        setMemoryLimit(256);
        setMultipleTestCasesCount(T);
    }

    void InputFormat() {
        LINE(N);
        LINES(ST,ED) % SIZE(N);
    }

    void OutputFormat() {
        LINE(RES);
    }

    void Constraints() {

        CONS(0 < N && N <= 50000);
        CONS(eachElementValidClock(ST));
        CONS(eachElementValidClock(ED));
    }

    void MultipleTestCasesConstraints() {
        CONS(T <= 50);
    }


private:
    bool isValidClock(const string& st){
        try {
            int h,m,s;
            sscanf(&st[0],"%d:%d:%d",&h,&m,&s);
            if (h < 0 || m < 0 || s < 0 || h > 23 || m > 59 || s > 59)
                return 0;
        }
        catch(...){
            return 0;
        }
        return 1;
    }

    bool eachElementValidClock(const vector<string>& V) {
        int N = V.size();
        for (int i=0;i<N;i++){
            if (!isValidClock(V[i]))
                return 0;
        }
        return 1;
    }
};

class Generator : public BaseGenerator<Problem> {
protected:
    void SampleTestCases() {
        SAMPLE_CASE({"4",
                    "08:00:00 09:00:00",
                    "08:20:00 08:45:00",
                    "08:05:00 09:40:00",
                    "08:15:00 10:00:00"});
        SAMPLE_CASE({"2",
                    "00:00:00 00:00:02",
                    "00:00:01 00:00:03"});
    }

    void TestCases() {
        //full random testcases
        for (int i=0;i<30;i++){
            N = rnd.nextInt(45000, 50000);
            clearCase();
            getRandomIntervals(N);
            CASE();
        }
        
        //full random testcases with high collision rate
        for (int i=0;i<10;i++){
            N = rnd.nextInt(45000, 50000);
            getRandomIntervals(N , 0 , 1000);
            CASE();
        }
        /* not ready yet
        //tricky builder 1
        for (int i=0;i<4;i++){
            N = rnd.nextInt(45000, 50000);
            clearCase();
            getDuplicateIntervals(10000); //all same interval
            getSameStartIntervals(10000); //same startpoints 
            getSameEndIntervals(10000); //same endpoints
            getRandomIntervals(N - 30000);
            CASE(N, ST, ED);
        }

        //tricky builder 2: same like #1, but each subcases are separated
        for (int i=0;i<3;i++){
            N = rnd.nextInt(45000, 50000);
            clearCase();
            getDuplicateIntervals(10000, 0, 10000); //all same interval
            getSameStartIntervals(10000, 10000, 20000); //same startpoints 
            getSameEndIntervals(10000, 20000, 30000); //same endpoints
            getRandomIntervals(N - 30000 , 30000, 40000);
            CASE(N, ST, ED);
        }*/
    }

private:
    string toClock(int t){
        char ret[20];
        sprintf(ret, "%d:%d:%d", t  / 3600 , (t / 60) % 60 , t % 3600);
        return ret;
    }

    void clearCase(){
        ST.clear();
        ED.clear();
    }

    void getRandomIntervals(int amount, int minval, int maxval){
        for (int i=0;i<amount;i++){
            int st = rnd.nextInt(minval, maxval);
            int ed = rnd.nextInt(minval, maxval);
            if (st > ed) swap(st,ed);
            if (st == ed && ed < maxval) ed++;
            if (st == ed && st > minval) st--;

            ST.push_back(toClock(st));
            ED.push_back(toClock(ed));
        }
    }

    void getRandomIntervals(int amount) {
        getRandomIntervals(amount,0, 24*60*60 - 1);
    }
};

int main(int argc, char* argv[]) {
    Runner<Problem> runner(argc, argv);

    runner.setGenerator(new Generator());
    return runner.run();
}
