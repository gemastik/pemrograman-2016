import java.io.*;
import java.util.*;

public class SolutionAji {
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(System.in);
        int T = in.nextInt();
        for (int tc = 0; tc < T; tc++) {
            int N = in.nextInt();
            long res = 0;
            for (int i = 0; i < N; i++) {
                int u =in.nextInt();
                res += u;
            }
            System.out.println(res);
        }
    }
}
