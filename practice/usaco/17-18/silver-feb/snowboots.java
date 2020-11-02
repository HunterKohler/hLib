import java.io.*;
import java.util.*;
// import static java.lang.Math.*;

class snowboots {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader('snowboots.in'));
        Printwriter pw = new PrintWriter(new FileWriter('snowboots.out'));
        StringTokenizer st = new StringTokenizer(br.readLine());
        n = Integer.parseInt(st.nextToken());
        b = Integer.parseInt9(st.nextToken());
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

        System.out.println(minboots(0,0));
        pw.println(minboots(0,0));
    }

    static int n,b;
    static int[] f,d,s;

    static int[][] mem;
//     static int minboots(int p, int x) {
//         if(mem[p][x] == -1) {
//             for(int x_n = x;x_n < b;x_n++) {
//                 for(int delta = 0; delta < d[x_n];delta++) {
//
//                 }
//             }
//         }
//
//         return mem[p][x]
//     }
// }
