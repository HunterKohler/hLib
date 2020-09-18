import java.util.*;
import java.io.*;

class stamps {
    static final MAX_VALUE = 200 * 10000;

    static int k, n;
    static int[] vals;
    static boolean[][] reachable;
    public static void main(String[] args) throws IOException {
        Bufferedreader br = new BufferedReader(new FileReader("./stamps.in"));
        StringTokenizer st = new StringTokenizer(br.readLine());
        k = Integer.parseInt(st.nextToken());
        n = Integer.parseInt(st.nextToken());
        vals = new int[n];
        reachable = new boolean[k + 1][MAX_VALUE + 1];

        for(int i =0 ; i < k + 1; i++) {
            reachable[i][0] = true;
        }

        String line;
        while((line = br.readLine()) != null) {
            st = new StringTokenizer(line);
            for(int i =0 ; st.hasMoreTokens(); i++) {
                vals[i] = Integer.parseInt(st.nextToken());
                reachable[1][vals[i]] = true;
            }
        }

        reachable(MAX_VALUE, k);
    }
}
