#include "tcframe/runner.hpp"
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

class Problem : public BaseProblem {
protected:
    int T;
    int N;
    vector<string> ST,ED;
    vector<int> RES;

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
        LINES(RES) % SIZE(N);
    }

    void Constraints() {

        CONS(0 < N && N <= 50000);
        CONS(eachElementValidClock(ST));
        CONS(eachElementValidClock(ED));
    }

    void MultipleTestCasesConstraints() {
        CONS(T <= 10);
    }


private:
    int parseClock(const string& st){
        int h,m,s;
        if (sscanf(st.c_str(),"%d:%d:%d",&h,&m,&s) != 3) {
            return -1;
        }
        if (h < 0 || m < 0 || s < 0 || h > 23 || m > 59 || s > 59)
            return -1;
        return h * 60 * 60 + m * 60 + s;
    }

    bool eachElementValidClock(const vector<string>& V) {
        int N = V.size();
        for (int i=0;i<N;i++){
            if (parseClock(V[i]) == -1)
                return 0;
        }
        return 1;
    }

    bool eachIntervalValid(const vector<string>& a, const vector<string>& b) {
        for (int i = 0; i < a.size(); i++) {
            if (parseClock(a[i]) >= parseClock(b[i])) {
                return 0;
            }
        }
        return 1;
    }
};

class Generator : public BaseGenerator<Problem> {
private:
    const int MODE_RANDOM = 0;
    const int SAME_END = 1;
    const int SAME_START = 2;
    const int SAME_BOTH = 3;

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

    void TestGroup1() {
        assignToSubtasks({-1});
        //full random testcases
        for (int i=0;i<10;i++){
            CASE(N = rnd.nextInt(5000, 50000), clearCase(), getRandomIntervals(N , MODE_RANDOM));
        }
    }

    void TestGroup2(){
        assignToSubtasks({-1});

        for (int i=0;i<10;i++){
            CASE(N = rnd.nextInt(45000, 50000), clearCase() , getRandomIntervals(N , 0 , 1000 , MODE_RANDOM));
        }
    }

    void TestGroup3(){
        assignToSubtasks({-1});
        for (int i=0;i<4;i++){
            CASE(N = rnd.nextInt(45000, 50000),
            clearCase(),
            getRandomIntervals(10000 , SAME_BOTH), //all same interval
            getRandomIntervals(10000 , SAME_START), //same startpoints
            getRandomIntervals(10000 , SAME_END), //same endpoints
            getRandomIntervals(N - 30000 , MODE_RANDOM));
        }

        //tricky builder 2: same like #1, but each subcases are separated
        for (int i=0;i<6;i++){
            CASE(N = rnd.nextInt(45000, 50000),
            clearCase(),
            getRandomIntervals(10000, 0, 10000 , SAME_BOTH), //all same interval
            getRandomIntervals(10000, 10000, 20000 , SAME_START), //same startpoints
            getRandomIntervals(10000, 20000, 30000 , SAME_END), //same endpoints
            getRandomIntervals(N - 30000 , 30000, 80000 , MODE_RANDOM));
        }
    }

    void TestGroup4(){
        assignToSubtasks({-1});

        CASE(allDisjoint());
        CASE(allDisjoint());

        //tricky builder 3:
        for (int i=0;i<6;i++){
            CASE(trickyBuilder());
        }
        //edge case 1
        CASE(N = 50000, clearCase(), getRandomIntervals(N , MODE_RANDOM));
        //edge case 2
        CASE(N = 3, ST = {"00:00:00" , "00:00:00" , "23:59:58"} , ED = {"00:00:01" , "23:59:59" , "23:59:59"});

    }

private:
    void allDisjoint(){
        clearCase();
        N = 50000;
        for (int i=0;i<N;i++){
            getRandomIntervals(1,i,i+1, MODE_RANDOM);
        }
    }

    void trickyBuilder(){
        clearCase();
        N = rnd.nextInt(450, 500) * 10;
        int st = 0;
        for (int i=1;i<N;i+=10){
            getRandomIntervals(10 , st , st + 100, MODE_RANDOM);
            st += 100;
        }
    }

    string toClock(int t){
        char ret[20];
        sprintf(ret, "%02d:%02d:%02d", t  / 3600 , (t / 60) % 60 , t % 60);

        return ret;
    }

    void clearCase(){
        ST.clear();
        ED.clear();
    }

    void getRandomIntervals(int amount, int minval, int maxval, int mode){
        int st;
        int ed;

        for (int i=0;i<amount;i++){
            //batch shuffle
            if (i % 100 == 0) {
                st = rnd.nextInt(minval, maxval);
                ed = rnd.nextInt(minval, maxval);
            }
            if (mode == SAME_END || mode == MODE_RANDOM) {
                st = rnd.nextInt(minval, maxval);
            }
            if (mode == SAME_START || mode == MODE_RANDOM) {
                ed = rnd.nextInt(minval, maxval);
            }
            if (st > ed) swap(st,ed);
            if (st == ed && ed < maxval) ed++;
            if (st == ed && st > minval) st--;

            ST.push_back(toClock(st));
            ED.push_back(toClock(ed));
        }
    }

    void getRandomIntervals(int amount, int mode) {
        getRandomIntervals(amount,0, 24*60*60 - 1, mode);
    }
};

int main(int argc, char* argv[]) {
    Runner<Problem> runner(argc, argv);

    runner.setGenerator(new Generator());
    return runner.run();
}
