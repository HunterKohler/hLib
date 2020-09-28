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
        for(int i = 0; i < n; i++) {
            String line = br.readLine();
            for(int j = 0; j < n; j++) {
                open[i][j] = line.substring(j,j+1).equals("1");
            }
        }

        mem = new int[n][n][n];
        for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
        for(int s = 0; s < n; s++)
            mem[i][j][s] = -1;

        BufferedWriter bw = new BufferedWriter(new FileWriter("./range.out"));
        for(int s = 2; s < n; s++) {
            int c = 0;
            for(int i = 0; i + s <= n; i++)
            for(int j = 0; j + s <= n; j++) {
                if(isOpen(i,j,s))
                    c++;
            }
            if(c != 0)
                bw.write(s + " " + c + "\n");
        }
        bw.close();
        System.out.println("time: " + ((System.nanoTime() - t) / pow(10,9)));
    }

    static int[][][] mem;
    static int n;
    static boolean[][] open;
    static boolean isOpen(int i,int j,int s) {
        if(mem[i][j][s] != -1)
            return mem[i][j][s] == 1;

        if(s == 1) {
            return open[i][j];
        } else {

            for(int k = 0; k < s; k++) {
                if( (!isOpen(i + k, j, 1)) ||
                    (!isOpen(i, j + k, 1)) ) {
                    mem[i][j][s] = 0;
                    return false;
                }
            }

            if(!isOpen(i + 1, j + 1, s - 1)) {
                mem[i][j][s] = 0;
                return false;
            }

            mem[i][j][s] = 1;
            return true;
        }
    }
}
