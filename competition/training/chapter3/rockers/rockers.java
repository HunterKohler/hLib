/*
ID: jhunter3
LANG: JAVA
PROB: rockers
*/

package competition.training.chapter3.rockers;

import java.io.*;
import java.util.*;
import static java.lang.Math.*;


class rockers {
    static int inf = Integer.MAX_VALUE / 100;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("rockers.in"));
        StringTokenizer st = new StringTokenizer(br.readLine());
        N = Integer.parseInt(st.nextToken());
        T = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        songs = new int[N];
        st = new StringTokenizer(br.readLine());
        for(int i = 0; i < N; i++) {
            songs[i] = Integer.parseInt(st.nextToken());
        }

        pack_mem = new int[N][M][T];
        for(int n = 0; n < N; n++)
        for(int m = 0; m < M; m++)
        for(int t = 0; t < T; t++) {
            pack_mem[n][m][t] = -1;
        }

        // System.out.println(pack(0,0,0));
        PrintWriter pw = new PrintWriter(new FileWriter("rockers.out"));
        pw.println(pack(0,0,0));
        pw.close();
    }

    static int N,M,T;
    static int[] songs;
    static int[][][] pack_mem;
    static int pack(int n, int m, int t) {
        if(n == N || m == M || t > T) {
            return 0;
        }

        if(t == T) {
            return pack(n,m + 1,0);
        }

        if(pack_mem[n][m][t] == -1) {
            int ret = max(
                pack(n,m + 1,0),
                pack(n + 1,m,t)
            );

            if(songs[n] + t <= T) {
                ret = max(ret, pack(n + 1, m, t + songs[n]) + 1);
            }

            pack_mem[n][m][t] = ret;
        }

        return pack_mem[n][m][t];
    }
}
