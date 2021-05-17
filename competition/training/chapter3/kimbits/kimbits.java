/*
ID: jhunter3
LANG: JAVA
PROB: kimbits
*/

package competition.training.chapter3.kimbits;

import java.util.*;
import java.io.*;

class kimbits {
    public static void main(String[] args) throws IOException {
        long t = System.nanoTime();

        BufferedReader br = new BufferedReader(new FileReader("./kimbits.in"));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int N = Integer.parseInt(st.nextToken());
        int L = Integer.parseInt(st.nextToken());
        long I = Long.parseLong(st.nextToken());

        System.out.println(C(39,15));

        int len = 1;
        for(int l = 0; l < L; l++)
            while(C(len, l) < I){
                System.out.println(len);
                len++;
            }

        System.out.println(len);
        // System.out.println("ans: " + ans + ", time: " + ((System.nanoTime() - t)/Math.pow(10,9)));

    }

    static long[][] memC = new long[40][40];
    static long C(int n, int r) {
        if(memC[n][r] == 0) {
            if(n == 0 || n == r || r == 0)
                memC[n][r] =  1;
            else
                memC[n][r] =  C(n - 1, r - 1) + C(n - 1, r);
        }

        return memC[n][r];
    }
}
