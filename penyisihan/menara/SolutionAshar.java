import java.io.*;
import java.util.Arrays;

public class SolutionAshar {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

        int T = Integer.parseInt(in.readLine());
        for (int tc = 0; tc < T; tc++) {
            int N = Integer.parseInt(in.readLine());
            int L = 0;
            int H = 0;
            for (int i = 0; i < N; i++) {
                String[] line = in.readLine().split(" ");
                int[] dim = new int[3];
                dim[0] = Integer.parseInt(line[0]);
                dim[1] = Integer.parseInt(line[1]);
                dim[2] = Integer.parseInt(line[2]);
                Arrays.sort(dim);
                L += dim[0];
                H += dim[2];
            }
            System.out.println(L + " " + H);
        }
    }
}
