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
        long t = System.nanoTime();

        BufferedReader br = new BufferedReader(new FileReader("./range.in"));
        n = parseInt(br.readLine());
        open = new boolean[n][n];
        for(int j = 0; j < n; j++) {
            String line = br.readLine();
            for(int i = 0; i < n; i++)
                open[i][j] = line.substring(i,i+1).equals(1);
        }

        mem = new int[n][n][n];
        for(int i = 0; i < n;i++)
        for(int j = 0; j < n;j++)
        for(int s = 0; s < n;s++)
            mem[i][j][s] = -1;

        for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++) {
            if(i + 1 == n || j + 1 == n)
                mem[i][j][2] = 0;
            else
                mem[i][j][2] = open[i][j] &&
                               open[i + 1][j] &&
                               open[i][j + 1] &&
                               open[i + 1][j + 1] ? 1 : 0;
            for(int s = 3; s < n; s++)
                if(s + i == n || s + j == n)
                    mem[i][j][s] = 0;
        }

        // BufferedWriter bw = new BufferedWriter(new FileWriter("./range.out"));
        System.out.println("ans: ");
        for(int s = 2; s < n ; s++) {
            int tcount = 0;
            for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                tcount += count(i,j,s);
            if(tcount > 0)
                System.out.println(s + " " + tcount);
        }

        System.out.println("time: " + ((System.nanoTime() - t) / pow(10,9)));
    }

    static int n;
    static boolean[][] open;
    static int[][][] mem;

    static int count(int i, int j ,int s) {
        System.out.printf("count(%d %d %d)\n",i,j,s);
        if(i + s >= n || j + s >= n)
            return 0;

        if(mem[i][j][s] != -1)
            return mem[i][j][s];

        int tcount = 0;
        for(int x = i; x < i + s; x++)
        for(int y = j; y < j + s; y++)
            tcount += count(x,y,s);

        mem[i][j][s] = tcount;
        return tcount;
    }
}
