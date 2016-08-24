import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class SolutionAshar {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

        int[][][] dp = new int[1001][1001][2];

        int T = Integer.parseInt(in.readLine());
        for (int tc = 0; tc < T; tc++) {
            String[] line = in.readLine().split(" ");
            int N = Integer.parseInt(line[0]);
            int S = Integer.parseInt(line[1]);
            int P = Integer.parseInt(line[2]);

            int[] K = new int[N];
            int[] V = new int[N];
            for (int i = 0; i+1 < N; i++) {
                line = in.readLine().split(" ");
                K[i] = Integer.parseInt(line[0]);
                V[i] = Integer.parseInt(line[1]);
            }

            for (int i = N-1; i >= 0; i--) {
                for (int j = 0; j <= S; j++) {
                    if (i == N-1) {
                        dp[i][j][0] = dp[i][j][1] = 0;
                        continue;
                    }
                    dp[i][j][0] = -1;
                    // kereta
                    if (j >= K[i] && dp[i+1][j-K[i]][0] != -1) {
                        dp[i][j][0] = Math.max(dp[i][j][0], V[i] + dp[i+1][j-K[i]][0]);
                    }
                    // pesawat
                    if (j >= P) {
                        dp[i][j][0] = Math.max(dp[i][j][0], dp[i+1][j-P][1]);
                    }

                    dp[i][j][1] = -1;
                    // kereta
                    if (j >= K[i] && dp[i+1][j-K[i]][0] != -1) {
                        dp[i][j][1] = Math.max(dp[i][j][1], V[i] + dp[i+1][j-K[i]][0]);
                    }
                    // pesawat
                    dp[i][j][1] = Math.max(dp[i][j][1], dp[i+1][j][1]);
                }
            }
            System.out.println(dp[0][S][0]);
        }
    }
}
