/*
ID: jhunter3
LANG: JAVA
PROB: range
*/

import java.io.*;
import java.util.*;
import static java.lang.Math.*;
import static java.lang.Integer.parseInt;

class range {
    public static void main(String[] args) throws IOException {
        // long t = System.nanoTime();

        BufferedReader br = new BufferedReader(new FileReader("./range.in"));
        n = parseInt(br.readLine());
        grid = new boolean[n][n];
        for(int j = 0; j < n; j++) {
            String line = br.readLine();
            for(int i = 0; i < n; i++) {
                grid[i][j] = line.charAt(i) == '1';
            }
        }

        BufferedWriter bw = new BufferedWriter(new FileWriter("./range.out"));
        for(int l = 2; l <= n; l++) { // s = start
            int count = 0;
            for(int si = 0; si + l <= n; si++)
            for(int sj = 0; sj + l <= n; sj++)
                if(valid(l,si,sj))
                    count++;
            if(count > 0)
                bw.write(l + " " + count + "\n");
        }
        bw.close();

        // System.out.println("time: " + ((System.nanoTime() - t) / Math.pow(10,9)));
    }

    static int n;
    static boolean[][] grid;

    static boolean valid(int l, int si, int sj) {
        for(int i = si; i < si + l; i++)
        for(int j = sj; j < sj + l; j++)
            if(!grid[i][j])
                return false;

        return true;
    }
}
