#include "tcframe/runner.hpp"
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class Problem : public BaseProblem {
protected:
    int T;
    int N;
    vector<int> S;
    string RES;

    void Config() {
        setSlug("jenius");
        setTimeLimit(2);
        setMemoryLimit(64);
        setMultipleTestCasesCount(T);
    }

    void InputFormat() {
        LINE(N);
        LINE(S % SIZE(N));
    }

    void OutputFormat() {
        LINE(RES);
    }

    void Constraints() {
        CONS(1 <= N && N <= 10000);
        CONS(eachElementBetween(S, 1, 1000000000));
    }

    void MultipleTestCasesConstraints() {
        CONS(1 <= T && T <= 20);
    }

private:
    bool eachElementBetween(const vector<int>& A, int lo, int hi) {
        return all_of(A.begin(), A.end(), [lo, hi](int a) {return lo <= a && a <= hi;});
    }
};

class Generator : public BaseGenerator<Problem> {
private:
    const int MANY_PRIME_FACTORS =
            2 * 2 * 2 * 3 * 5 * 7 * 11 * 13 * 17 * 19 * 23;

    const int LARGE_PRIMES[200] = {
            999991469, 999991507, 999991547, 999991571, 999991591, 999991627, 999991661, 999991669, 999991819, 999991829,
            999991843, 999991847, 999991873, 999991919, 999991921, 999991973, 999992023, 999992029, 999992039, 999992057,
            999992087, 999992099, 999992101, 999992107, 999992111, 999992129, 999992131, 999992153, 999992177, 999992209,
            999992221, 999992263, 999992267, 999992281, 999992293, 999992339, 999992347, 999992359, 999992387, 999992407,
            999992423, 999992447, 999992509, 999992527, 999992537, 999992573, 999992579, 999992639, 999992641, 999992647,
            999992677, 999992723, 999992731, 999992737, 999992753, 999992759, 999992783, 999992837, 999992867, 999992891,
            999992899, 999992927, 999992977, 999992999, 999993031, 999993041, 999993061, 999993067, 999993083, 999993119,
            999993143, 999993179, 999993221, 999993229, 999993289, 999993311, 999993367, 999993377, 999993439, 999993461,
            999993469, 999993481, 999993571, 999993581, 999993583, 999993623, 999993637, 999993641, 999993653, 999993671,
            999993697, 999993707, 999993719, 999993721, 999993733, 999993739, 999993763, 999993791, 999993811, 999993817,
            999993821, 999993823, 999993833, 999993851, 999993887, 999993899, 999993901, 999993913, 999993947, 999993971,
            999994003, 999994007, 999994081, 999994091, 999994097, 999994123, 999994129, 999994157, 999994159, 999994189,
            999994201, 999994241, 999994267, 999994273, 999994277, 999994297, 999994309, 999994313, 999994321, 999994337,
            999994343, 999994357, 999994379, 999994381, 999994397, 999994423, 999994427, 999994433, 999994439, 999994487,
            999994507, 999994531, 999994537, 999994549, 999994603, 999994609, 999994613, 999994649, 999994651, 999994691,
            999994693, 999994703, 999994741, 999994747, 999994753, 999994763, 999994771, 999994781, 999994813, 999994823,
            999994837, 999994843, 999994861, 999994867, 999994883, 999994903, 999994913, 999994951, 999994973, 999994979,
            999994987, 999995093, 999995107, 999995111, 999995141, 999995239, 999995257, 999995261, 999995273, 999995291,
            999995341, 999995377, 999995393, 999995413, 999995419, 999995431, 999995531, 999995561, 999995567, 999995599,
            999995611, 999995621, 999995627, 999995629, 999995651, 999995663, 999995677, 999995681, 999995701, 999995713
    };
    vector<int> compositeNumbers;

protected:
    void SampleTestCases() {
        SAMPLE_CASE({
            "4",
            "2 1 2 2"
        });
        SAMPLE_CASE({
            "1",
            "7"
        });
        SAMPLE_CASE({
            "2",
            "6 4"
        });
    }

    void TestCases() {
        CASE(N = 1, S = {1});
        CASE(N = 2, S = {1, 1});
        CASE(N = 200, S = vector<int>(LARGE_PRIMES, LARGE_PRIMES+200));
        CASE(N = 199, S = vector<int>(LARGE_PRIMES, LARGE_PRIMES+199));
        CASE(N = 100, randomS(false));
        CASE(N = 100, randomS(true));
        CASE(N = 1000, composites(false));
        CASE(N = 1000, composites(true));
        CASE(N = 10000, randomS(false));
        CASE(N = 10000, randomS(true));
        CASE(N = 10000, composites(true));
        CASE(N = 10000, composites(false));
        CASE(N = 10000, composites(true));
        CASE(N = 10000, composites(false));
        CASE(N = 10000, composites(true));
        CASE(N = 10000, composites(false));
        CASE(N = 10000, composites(true));
        CASE(N = 10000, composites(false));
        CASE(N = 10000, composites(true));
        CASE(N = 10000, composites(false));
    }

private:
    static int compute_grundy(int x) {
        int res = 0;
        for (int i = 2; i*i <= x; i++) {
            while (x % i == 0) {
                res++;
                x /= i;
            }
        }
        if (x > 1) {
            res++;
        }
        return res;
    }

    void randomS(bool forceZeroXor) {
        S.clear();
        int grundy = 0;
        for (int i = 0; i < N; i++) {
            int x = rnd.nextInt(1000000000) + 1;
            if (i) {
                grundy ^= compute_grundy(x);
            }
            S.push_back(x);
        }
        if (grundy && forceZeroXor) {
            S[0] = 1<<grundy;
        }
    }

    void composites(bool forceZeroXor) {
        S.clear();
        int grundy = 0;
        for (int i = 0; i < N; i++) {
            int x = compositeNumbers[rnd.nextInt(20000)];
            if (i) {
                grundy ^= compute_grundy(x);
            }
            S.push_back(x);
        }
        if (grundy && forceZeroXor) {
            S[0] = 1<<grundy;
        }
    }

    class AlmostHighlyCompositeNumbers {
    public:
        vector<int> generate() {
            go(1ll, 0);
            sort(res.begin(), res.end());
            reverse(res.begin(), res.end());
            vector<int> ans;
            for (pair<int, ll> p : res) {
                ans.push_back((int)p.second);
            }
            return ans;
        }

    private:
        const int MAX = 1000000000;

        int primes[8] = {2, 3, 5, 7, 11, 13, 17, 19};
        int limits[8] = {6, 5, 4, 3, 2, 2, 2, 2};

        vector<pair<int, ll>> res;
        int pows[8] = {};

        void go(ll n, int idx) {
            if (n > MAX) {
                return;
            }

            int factors = 1;
            for (int i = 0; i < 8; i++) {
                factors *= pows[i]+1;
            }

            res.push_back(make_pair(factors, n));

            if (idx == 8) {
                return;
            }

            ll mult = 1;
            int oldp = pows[idx];
            for (int i = 0; i <= limits[idx]; i++) {
                pows[idx]++;
                go(n * mult, idx+1);
                mult *= primes[idx];
            }
            pows[idx] = oldp;
        }
    };

public:
    Generator() {
        compositeNumbers = AlmostHighlyCompositeNumbers().generate();
    }
};

int main(int argc, char* argv[]) {
    Runner<Problem> runner(argc, argv);

    runner.setGenerator(new Generator());
    return runner.run();
}
