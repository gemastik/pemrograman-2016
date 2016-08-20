import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;

public class SolutionAshar {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));

        int T = Integer.parseInt(in.readLine());
        for (int tc = 0; tc < T; tc++) {
            int N = Integer.parseInt(in.readLine());
            long res = 0;
            for (int i = 0; i < N; i++) {
                int u = Integer.parseInt(in.readLine());
                res += u;
            }
            out.println(res);
        }
    }
}
