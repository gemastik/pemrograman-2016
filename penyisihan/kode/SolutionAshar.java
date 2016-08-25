import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;


class Event  implements Comparable<Event>{
    public int id;
    public int x;
    public int type;
    public Event(int id, int x, int type){
        this.id = id;
        this.x = x;
        this.type = type;
    }

    private long make_tuple(int a,int b,int c,int d){
        return (long)a * 10 * 1000000 * 10000000 + (long)b * 1000000 * 10000000 + (long)c * 1000000 + d;
    }

    @Override
    public int compareTo(Event o) {
        long tmp =  make_tuple(x, type, -SolutionAshar.E[id], -SolutionAshar.S[id]) - make_tuple(o.x, o.type, -SolutionAshar.E[o.id], -SolutionAshar.S[o.id]);
        if (tmp < 0)
            return -1;
        if (tmp > 0)
            return 1;
        return 0;
    }
}

public class SolutionAshar {
    static int START = 1;
    static int END = 0;
    static int S[];
    static int E[];
    // jenius fake pair<int,int>
    public static long make_pair(int a, int b) {
        return (long)a * 1000000 + b;
    }

    public static int pair_first(long pair){
        return (int)(pair / 1000000);
    }

    public static int pair_second(long pair){
        return (int)(pair % 1000000);
    }


    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

        int T = Integer.parseInt(in.readLine());
        HashMap<Long,Integer> dup = new HashMap<Long,Integer>();

        for (int tc = 0; tc < T; tc++){
            int N = Integer.parseInt(in.readLine());
            
            Event M[] = new Event[2*N];
            S = new int[N];
            E = new int[N];
            int ans[] = new int[N];

            for (int i = 0; i < N; i++) {
                String line[] = in.readLine().split(" |\\:");
                S[i] = Integer.parseInt(line[0]) * 60 * 60 + Integer.parseInt(line[1]) * 60 + Integer.parseInt(line[2]);
                E[i] = Integer.parseInt(line[3]) * 60 * 60 + Integer.parseInt(line[4]) * 60 + Integer.parseInt(line[5]);

                M[2*i] = new Event(i, S[i], START);
                M[2*i + 1] = new Event(i, E[i], END);
                ans[i] = 2;

                //handle duplication
                int v = 0;
                long k = make_pair(S[i],E[i]);
                if (dup.get(k) != null)
                    v = dup.get(k);
                dup.put(k, v + 1);
            }
            Arrays.sort(M);

            int last = -1;
            SortedSet<Long> active = new TreeSet<Long>();

            for (int i = 0; i < 2*N; i++) {
                if (M[i].x != last && active.size() == 1) {
                    ans[pair_second( active.last() ) ] = 1;
                }

                if (M[i].type == START) {
                    if (active.size() > 0 && pair_first( active.last() ) >= E[M[i].id]) {
                        ans[M[i].id] = -1;
                    }
                    active.add(make_pair(E[M[i].id], M[i].id));
                    //System.out.println("Adding " + E[M[i].id] + " : " + M[i].id + " ==> "+make_pair(E[M[i].id], M[i].id));
                } else {
                   // System.out.println("remove "+E[M[i].id]);
                    active.remove(make_pair(E[M[i].id], M[i].id));
                }
                last = M[i].x;
            }

            // dupe check
            for (int i = 0; i < N; i++) {
                if (dup.get(make_pair(S[i], E[i])) > 1) {
                    ans[i] = -1;
                }
            }

            for (int i = 0; i < N; i++) {
                System.out.println(ans[i]);
            }

        }
    }
}