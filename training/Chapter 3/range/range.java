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
        long t = System.nanoTime();

        BufferedReader br = new BufferedReader(new FileReader("./range.in"));
        n = parseInt(br.readLine());
        grid = new boolean[n][n];
        for(int i = 0; i < n; i++) {
            String line = br.readLine();
            for(int j = 0; j < n; j++) {
                grid[i][j] = line.charAt(j) == '1';
            }
        }

        mem = new boolean[n][n][n];
        count = new int[n + 1];

        for(int i = 2; i <= n; i++)
            if(count[i] != 0)
                System.out.println(count[i]);

        System.out.println("time: " + ((System.nanoTime() - t) / pow(10,9)));
    }

    static int n;
    static boolean[][] grid;
    static boolean[][][] mem;
    static boolean[][][] visited;
    static int[] count;

    static boolean count(int x, int y, int s) {
        if(!visited[x][y][s]) {
            visited[x][y][s] = true;

            if(s == 1) {
                mem[x][y][s];
            } else {

            }
        }

        return mem[x][y][s];
    }

    static iZip(int ...args) { return args };
}
