import java.util.*;
import java.io.*;
import java.math.*;

public class SolusiAji{

	public static int grundy(int x){
		int res = 0;
		int p = (int) Math.floor(Math.sqrt(x));
		for (int i=2;i<=p;i++){
			while (x % i == 0){
				res++;
				x = x / i;
			}
		}
		if (x != 1) res++;
		return res;
	}

	public static void main(String arg[])  throws IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		int T = Integer.parseInt(in.readLine());
		while(T-- > 0){
			int N = Integer.parseInt(in.readLine());
			int res = 0;
			String inputs[] = in.readLine().split(" ");

			for (int i=0;i<N;i++){
				int x = Integer.parseInt(inputs[i]);
				res = res ^ grundy(x);
				//System.out.println(grundy(x));
			}
			if (res == 0)
				System.out.println("YA");
			else
				System.out.println("TIDAK");
		}
	}
}
