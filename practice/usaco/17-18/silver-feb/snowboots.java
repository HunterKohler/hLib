import java.io.*;
import java.util.*;
// import static java.lang.Math.*;

class snowboots {
    static int INF = Integer.MAX_VALUE / 2;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("snowboots.in"));
        PrintWriter pw = new PrintWriter(new FileWriter("snowboots.out"));
        StringTokenizer st = new StringTokenizer(br.readLine());
        n = Integer.parseInt(st.nextToken());
        b = Integer.parseInt(st.nextToken());
        f = new int[n];
        st = new StringTokenizer(br.readLine());
        for(int i = 0; i < n; i++) {
            f[i] = Integer.parseInt(st.nextToken());
        }
        s = new int[b];
        d = new int[b];
        for(int i = 0; i < b; i++) {
            st = new StringTokenizer(br.readLine());
            s[i] = Integer.parseInt(st.nextToken());
            d[i] = Integer.parseInt(st.nextToken());
        }

        mem = new int[n][b];
        for(int i = 0; i < n; i++)
        for(int j = 0; j < b; j++) {
            mem[i][j] = (i == n - 1) ? 0 : -1;
        }

        // System.out.println(minboots(0,0));
        pw.println(minboots(0,0));
        pw.close();
    }

    static int n,b;
    static int[] f,d,s;

    static int[][] mem;
    static int minboots(int x, int i) { // x position, i displaced
        if(x >= n || i >= b) {
            return INF;
        }

        if(mem[x][i] == -1) {
            mem[x][i] = INF;
            for(int xn = x + 1; xn <= x + d[i] && xn < n; xn++) {
                if(f[xn] <= s[i]){
                    mem[x][i] = Math.min(mem[x][i], minboots(xn,i));
                }
            }
            for(int in = i + 1; in < b; in++) {
                if(f[x] <= s[in]) {
                    mem[x][i] = Math.min(mem[x][i],(in - i) + minboots(x,in));
                }
            }
        }

        // System.out.println(x + " " + i + ": " + mem[x][i]);
        return mem[x][i];
    }
}
