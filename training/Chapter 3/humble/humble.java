import java.io.*;
import java.util.*;

class humble {
    static int k,n;
    static int[] s;
    public static void main(String[] args) throws IOException {
        BufferedReader br;
        BufferedWriter bw;
        StringTokenizer st;

        br = new BufferedReader(new FileReader("./humble.in"));
        st = new StringTokenizer(br.readLine());
        k = Integer.parseInt(st.nextToken());
        n = Integer.parseInt(st.nextToken());

        s = new int[k];
        st = new StringTokenizer(br.readLine());
        for(int i = 0;i < k;i++)
            s[i] = Integer.parseInt(st.nextToken());

        
    }
}
