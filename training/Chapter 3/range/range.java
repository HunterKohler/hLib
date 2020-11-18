/*
ID: jhunter3
LANG: JAVA
PROB: range
*/

import java.io.*;
import java.util.*;
import static java.lang.Integer.parseInt;
import static java.lang.Math.*;

class range {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("range.in"));
        PrintWriter pw = new PrintWriter(new FileWriter("range.out"));

        n = parseInt(br.readLine());
        field = new boolean[n][n];
        for(int i = 0; i < n; i++) {
            String line = br.readLine();
            for(int j = 0; j < n; j++)
                field[i][j] = line.charAt(j) == '1';
        }

        mem = new int[n][n];
        for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            mem[i][j] = -1;

        // for(int i = 0; i < n; i++)
        // for(int j = 0; j < n; j++) {
        //     System.out.println(i + " " + j + " " + biggest(i,j));
        // }
        //
        // for(int i = 0; i < n; i++) {
        //     System.out.println(Arrays.toString(mem[i]));
        // }

        int[] counts = new int[n + 1];
        for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
        for(int k = 0; k <= biggest(i,j); k++)
            counts[k]++;

        for(int s = 2; s <= n; s++) {
            if(counts[s] > 0)
                pw.println(s + " " + counts[s]);
        }

        pw.close();
    }

    static int n;
    static boolean[][] field;
    static int[][] mem;

    static int biggest(int i, int j) {
        if(i <= 0 || j <= 0) {
            mem[i][j] = (field[i][j]) ? 1 : 0;
        } else if(mem[i][j] == -1) {
            int k = 0;
            while(k <= min(i,j) && field[i-k][j] && field[i][j-k]) {
                k++;
            }
            mem[i][j] = min(k, biggest(i-1,j-1) + 1);
        }

        return mem[i][j];
    }

}
