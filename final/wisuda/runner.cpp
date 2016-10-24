#include "tcframe/runner.hpp"
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

class Problem : public BaseProblem {
protected:
    int T;
    int N;
    vector<string> types;
    vector<int> K;
    vector<vector<string>> names;
    int res;

    void Config() {
        setSlug("wisuda");
        setTimeLimit(2);
        setMemoryLimit(64);
        setMultipleTestCasesCount(T);
    }

    void InputFormat() {
        LINE(N);
        LINES(types, K, names) % SIZE(N);
    }

    void OutputFormat() {
        LINE(res);
    }

    void Constraints() {
        CONS(1 <= N && N <= 100);
        CONS(eachElementBetween(K, 1, 10));
        CONS(validNames());
        CONS(namesAndKMatch());
        CONS(uniqueNamesInAPhoto());
    }

    void MultipleTestCasesConstraints() {
        CONS(1 <= T && T <= 20);
    }

private:
    bool eachElementBetween(const vector<int>& A, int lo, int hi) {
        return all_of(A.begin(), A.end(), [lo, hi](int a) {return lo <= a && a <= hi;});
    }

    bool validNames() {
        for (vector<string>& v : names) {
            for (string s : v) {
                if (s.size() < 1 || s.size() > 8) {
                    return false;
                }
                for (char c : s) {
                    if (c < 'a' || c > 'z') {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    bool namesAndKMatch() {
        for (int i = 0; i < N; i++) {
            if (K[i] != names[i].size()) {
                return false;
            }
        }
        return true;
    }

    bool uniqueNamesInAPhoto() {
        for (vector<string>& v : names) {
            set<string> s(v.begin(), v.end());
            if (s.size() != v.size()) {
                return false;
            }
        }
        return true;
    }
};

class Generator : public BaseGenerator<Problem> {
protected:
    void SampleTestCases() {
        SAMPLE_CASE({
            "2",
            "selfie 2 ani budi",
            "selfie 1 candra"
        });
        SAMPLE_CASE({
            "3",
            "dibantu 3 ani budi candra",
            "dibantu 1 budi",
            "selfie 3 ani candra budi"
        });
    }

    void TestCases() {
        CASE(
            N = 1,
            types = {"selfie"},
            K = {1},
            names = {{"dengklek"}}
        );
        CASE(
            N = 2,
            types = {"selfie", "selfie"},
            K = {1, 1},
            names = {{"dengklek"}, {"dengklek"}}
        );
        CASE(
            N = 2,
            types = {"selfie", "selfie"},
            K = {1, 1},
            names = {{"dengklek"}, {"ganesh"}}
        );
        CASE(
            N = 1,
            types = {"dibantu"},
            K = {1},
            names = {{"dengklek"}}
        );
        CASE(
            N = 2,
            types = {"dibantu", "dibantu"},
            K = {1, 1},
            names = {{"dengklek"}, {"dengklek"}}
        );
        CASE(
            N = 2,
            types = {"dibantu", "dibantu"},
            K = {1, 1},
            names = {{"dengklek"}, {"ganesh"}}
        );
        CASE( // agak tricky
            N = 3,
            types = {"dibantu", "dibantu", "selfie"},
            K = {1, 1, 2},
            names = {{"kwak"}, {"kwok"}, {"kwok", "kwak"}}
        );
        CASE( // tricky parah
            N = 2,
            types = {"dibantu", "selfie"},
            K = {1, 2},
            names = {{"kwak"}, {"kwok", "kwak"}}
        );
        CASE( // tricky parah juga
            N = 3,
            types = {"dibantu", "selfie", "selfie"},
            K = {3, 2, 1},
            names = {{"kwak", "kwek", "kwok"}, {"kwek", "kwak"}, {"kwok"}}
        );

        CASE(N = 20, random(0, 10));
        CASE(N = 20, random(100, 10));
        CASE(N = 50, random(50, 50));
        CASE(N = 60, random(25, 10));
        CASE(N = 60, random(90, 60));
        CASE(N = 70, random(10, 70));
        CASE(N = 100, random(0, 100));
        CASE(N = 100, random(100, 10));
        CASE(N = 100, random(50, 100));
        CASE(N = 100, random(0, 10));
        CASE(N = 100, random(33, 33));
    }
private:
    void random(int selfieProb, int namesPoolSize) {

        vector<string> pool;
        set<string> st;
        for (int i = 0; i < namesPoolSize; i++) {
            string name;
            while (true) {
                name = "";
                int len = rnd.nextInt(8) + 1;
                for (int j = 0; j < len; j++) {
                    char c = 'a' + rnd.nextInt(26);
                    name += c;
                }
                if (!st.count(name)) {
                    break;
                }
            }
            pool.push_back(name);
            st.insert(name);
        }

        types.clear();
        K.clear();
        names.clear();
        for (int i = 0; i < N; i++) {
            types.push_back(rnd.nextInt(100) < selfieProb ? "selfie" : "dibantu");
            int k = rnd.nextInt(10) + 1;
            K.push_back(k);

            rnd.shuffle(pool.begin(), pool.end());
            vector<string> photo;
            for (int j = 0; j < k; j++) {
                photo.push_back(pool[j]);
            }
            names.push_back(photo);
        }

        if (namesPoolSize == 10) {
            int idx = rnd.nextInt(N);
            K[idx] = 10;
            names[idx] = pool;
        }
    }
};

int main(int argc, char* argv[]) {
    Runner<Problem> runner(argc, argv);

    runner.setGenerator(new Generator());
    return runner.run();
}
