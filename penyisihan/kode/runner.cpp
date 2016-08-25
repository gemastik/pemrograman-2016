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
        setTimeLimit(10000);
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
        SAMPLE_CASE({"3",
                    "00:00:00 00:00:01",
                    "00:00:01 00:00:10",
                    "00:00:02 00:00:10"});
    }

    // random, dengan interval paling panjang 100 atau 1000. 0.0001% interval TIDAK mengikuti aturan tsb.
    void TestGroup1() {
        assignToSubtasks({-1});
        //full random testcases
        for (int i=0;i<5;i++){
            CASE(N = rnd.nextInt(45000, 50000), clearCase(), getRandomIntervals(N , MODE_RANDOM,  100 , 0.0001));
            CASE(N = rnd.nextInt(45000, 50000), clearCase(), getRandomIntervals(N , MODE_RANDOM,  1000 , 0.0001));
        }
    }

     // mirip TC1. parameter lebih di-tweak.
    void TestGroup2(){
        assignToSubtasks({-1});
        for (int i=0;i<2;i++){
            CASE(N = rnd.nextInt(45000, 50000), clearCase() , getRandomIntervals(N ,MODE_RANDOM, 1 , 0.001));
            CASE(N = rnd.nextInt(45000, 50000), clearCase() , getRandomIntervals(N ,MODE_RANDOM, 5 , 0.001));
            CASE(N = rnd.nextInt(45000, 50000), clearCase() , getRandomIntervals(N ,MODE_RANDOM, 10 , 0.001));
            CASE(N = rnd.nextInt(45000, 50000), clearCase() , getRandomIntervals(N ,MODE_RANDOM, 100 , 0.001));
            CASE(N = rnd.nextInt(45000, 50000), clearCase() , getRandomIntervals(N ,MODE_RANDOM, 200 , 0.001));
        }

    }

    // BANYAK interval duplikat. Jawaban mayoritas -1
    void TestGroup3(){
        assignToSubtasks({-1});
        for (int i=0;i<4;i++){
            CASE(N = rnd.nextInt(45000, 50000),
            clearCase(),
            getRandomIntervals(10000 , SAME_BOTH, 100 , 0.00001), //all same interval
            getRandomIntervals(10000 , SAME_START , 100 , 0.00001), //same startpoints
            getRandomIntervals(10000 , SAME_END, 100 , 0.00001), //same endpoints
            getRandomIntervals(N - 30000 , MODE_RANDOM, 100 , 0.00001));
        }
        //tricky builder 2: same like #1, but each chunk are disjoint
        for (int i=0;i<6;i++){
            CASE(N = rnd.nextInt(45000, 50000),
            clearCase(),
            getRandomIntervals(10000, 0, 10000 , SAME_BOTH, 100 , 0.00001), //all same interval
            getRandomIntervals(10000, 10000, 20000 , SAME_START, 100 , 0.00001), //same startpoints
            getRandomIntervals(10000, 20000, 30000 , SAME_END,100 , 0.00001), //same endpoints
            getRandomIntervals(N - 30000 , 30000, 80000 , MODE_RANDOM, 100 , 0.00001));
        }
    }

    // TC-TC khusus. Jawaban kebanyakan '2'
    void TestGroup4(){
        assignToSubtasks({-1});

        CASE(N = 50000 , allDisjoint(1));
        CASE(N = 50000 , allDisjoint(5));
        CASE(N = 50000 , allDisjoint(10));
        CASE(N = 49999 , allDisjoint(1), N++, getRandomIntervals(1 , 0, 50000));
        CASE(N = 49999 , allDisjoint(5), N++, getRandomIntervals(1 , 0, 50000));


        //tricky builder 3:
        for (int i=0;i<3;i++){
            CASE(trickyBuilder());
        }
        //edge case 1
        CASE(N = 50000, clearCase(), getRandomIntervals(N , MODE_RANDOM));
        //edge case 2
        CASE(N = 3, ST = {"00:00:00" , "00:00:00" , "23:59:58"} , ED = {"00:00:01" , "23:59:59" , "23:59:59"});
    }

private:
    void allDisjoint(int shift){
        clearCase();
        for (int i=0;i<N;i++){
            ST.push_back(toClock(i));
            ED.push_back(toClock(i + shift));
        }
    }

    void trickyBuilder(){
        clearCase();
        N = rnd.nextInt(450, 500) * 10;
        int st = 0;
        for (int i=1;i<N;i+=10){
            getRandomIntervals(10 , st , st + 100);
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

    void getRandomIntervals(int amount, int minval, int maxval, int mode, int maxGap){
        int st;
        int ed;

        for (int i=0;i<amount;i++){
            //batch shuffle
            if (i % 10 == 0) {
                st = rnd.nextInt(minval, maxval);
                ed = rnd.nextInt(st, min(maxval, st + maxGap));
            }
            if (mode == SAME_END || mode == MODE_RANDOM) {
                st = rnd.nextInt(minval, maxval);
            }
            if (mode == SAME_START || mode == MODE_RANDOM) {
                ed = rnd.nextInt(st, min(maxval, st + maxGap));
            }
            if (st == ed && ed < maxval) ed++;
            if (st == ed && st > minval) st--;

            ST.push_back(toClock(st));
            ED.push_back(toClock(ed));
        }
    }
    void getRandomIntervals(int amount, int minval, int maxval, int mode, int maxGap, float mutationRate){
        int mutated = amount * mutationRate;
        int normal = amount - mutated;
        
        getRandomIntervals(normal,minval, maxval, mode, maxGap);
        getRandomIntervals(mutated,minval, maxval, mode , 100000);
    }

    void getRandomIntervals(int amount, int mode, int maxGap, float mutationRate){
        int mutated = amount * mutationRate;
        int normal = amount - mutated;

        getRandomIntervals(normal, 0, 24*60*60 - 1, mode, maxGap);
        getRandomIntervals(mutated, 0, 24*60*60 - 1, mode, 100000);

    }

    void getRandomIntervals(int amount, int minval, int maxval){
         getRandomIntervals(amount,minval, maxval, MODE_RANDOM,100000);
    }

    void getRandomIntervals(int amount, int mode) {
        getRandomIntervals(amount,0, 24*60*60 - 1, mode, 100000);
    }
    
};

int main(int argc, char* argv[]) {
    Runner<Problem> runner(argc, argv);

    runner.setGenerator(new Generator());
    return runner.run();
}
