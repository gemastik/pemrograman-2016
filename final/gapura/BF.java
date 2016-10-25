import java.util.*;
import java.io.*;


public class BF{
	public static long best = 0;
	public static long sum = 0;

	public static void bf(int p_tiang[],int pos,long kanan,long tengah, long kiri){
		if (pos == p_tiang.length){
			if (kanan == kiri && kanan * tengah < best){
				best = kanan * tengah;
			}
			return;
		}
		//impossible
		long kurang = Math.abs(kanan - kiri);
		if (sum - kanan - kiri - tengah < kurang)
			return;

		bf(p_tiang,pos + 1, kanan + p_tiang[pos], tengah , kiri);
		bf(p_tiang,pos + 1, kanan, tengah + p_tiang[pos], kiri);
		bf(p_tiang,pos + 1, kanan, tengah, kiri + p_tiang[pos]);
	}

	public static void main(String args[]) throws Exception{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int T = Integer.parseInt(br.readLine());
		while (T-- > 0){
			best = 0;
			sum = 0;
			int N = Integer.parseInt(br.readLine());
			String tiang[] = br.readLine().split(" ");
			N = tiang.length;
			int p_tiang[] = new int[N];
			for (int i=0;i<N;i++){
				p_tiang[i] = Integer.parseInt(tiang[i]);
				sum = sum + p_tiang[i];
			}
			bf(p_tiang,0,0,0,0);
			System.out.println(best);
		}
	}
}