import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class SolutionAshar {
    static int T;

    static double[][] comb = new double[53][53];
    static int[] val = new int[256];
    static boolean[][] have = new boolean[256][13];

    static double solve(int lo, int hi, int x, int wow) {
        if (x == 3) {
            return 1;
        }

        double res = 0;
        for (int l = 0; l <= lo; l++) {
            for (int h = 0; h <= hi; h++) {
                if (l > 0 || h == 0) {
                    res += comb[lo][l] * comb[hi][h] * comb[wow][13-l-h] * solve(lo-l, hi-h, x+1, wow - (13-l-h));
                }
            }
        }
        return res;
    }

    static void solve(int lo, int hi) {
        double num = solve(lo, hi, 0, 39 - lo - hi);
        double denom = comb[39][13] * comb[26][13] * comb[13][13];

        double res = num * 100 / denom;
        System.out.printf("%.5f%%", res);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

        for (int i = 0; i <= 52; i++) {
            comb[i][0] = 1;
            for (int j = 1; j <= i; j++) {
                comb[i][j] = comb[i-1][j] + comb[i-1][j-1];
            }
        }

        for (char c = '2'; c <= '9'; c++) {
            val[c] = c - '2';
        }
        val['T'] = 8;
        val['J'] = 9;
        val['Q'] = 10;
        val['K'] = 11;
        val['A'] = 12;

        T = Integer.parseInt(in.readLine());
        for (int tc = 0; tc < T; tc++) {
            String[] card = in.readLine().split(" ");

            if (tc > 0) {
                System.out.println();
            }
            for (int i = 0; i < 256; i++) {
                for (int j = 0; j < 13; j++) {
                    have[i][j] = false;
                }
            }
            for (int i = 0; i < 13; i++) {
                int v = val[card[i].charAt(0)];
                int s = card[i].charAt(1);
                have[s][v] = true;
            }

            for (int i = 0; i < 13; i++) {
                int hi = 0, lo = 0;

                int v = val[card[i].charAt(0)];
                int s = card[i].charAt(1);

                for (int j = 0; j < v; j++) {
                    if (!have[s][j]) lo++;
                }
                for (int j = v+1; j < 13; j++) {
                    if (!have[s][j]) hi++;
                }

                System.out.print(card[i] + ": ");
                solve(lo, hi);
                System.out.println();
            }
        }
    }
}
