/*
ID: jhunter3
LANG: JAVA
PROB: game1
*/

import java.io.*;
import java.util.*;
import static java.lang.Math.*;
import static java.lang.Integer.parseInt;

class game1 {
    public static void main(String[] args) throws IOException {
        // long t = System.nanoTime();

        BufferedReader br = new BufferedReader(new FileReader("./game1.in"));

        n = parseInt(br.readLine());
        board = new int[n];
        mem = new int[n][n][2];

        int index = 0;
        String line;
        while((line = br.readLine()) != null) {
            StringTokenizer st = new StringTokenizer(line);
            while(st.hasMoreTokens()) {
                board[index] = parseInt(st.nextToken());
                index++;
            }
        }

        int[] opt = optimize();

        BufferedWriter bw = new BufferedWriter(new FileWriter("game1.out"));
        bw.write(opt[0] + " " + opt[1] + "\n");
        bw.close();

        // System.out.println(Arrays.toString(optimize()));
        // System.out.println("time: " + ((System.nanoTime() - t) / pow(10,9)));
        // printMem("Final");
    }

    static int n;
    static int[] board;
    static int[][][] mem;

    static int[] optimize() {
        for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
        for(int k = 0; k < 2; k++)
            mem[i][j][k] = -1;

        // printMem("Init");

        return optimize(0, n - 1, 0);
    }

    static int[] optimize(int l, int r, int p) {
        if(l < 0 || r >= n)
            return new int[]{-1, -1};

        if(mem[l][r][0] == -1) {
            if(l == r) {
                mem[l][r][p] = board[l];
                mem[l][r][flip(p)] = 0;
            } else {
                int[] leftOpt = optimize(l + 1, r, flip(p)).clone();
                int[] rightOpt = optimize(l, r - 1, flip(p)).clone();
                leftOpt[p] += board[l];
                rightOpt[p] += board[r];

                if(leftOpt[p] == rightOpt[p]) {
                    mem[l][r] = leftOpt[flip(p)] < rightOpt[flip(p)]
                        ? leftOpt.clone() : rightOpt.clone() ;
                } else {
                    mem[l][r] = leftOpt[p] > rightOpt[p]
                        ? leftOpt.clone() : rightOpt.clone() ;
                }
            }
        }
        return mem[l][r];
    }

    static int mod2(int x) {
        return floorMod(x,2);
    }

    static int flip(int x) {
        return mod2(x + 1);
    }

    // static void printMem(String title) {
    //     System.out.println("\t\t" + title);
    //     for(int[][] row: mem) {
    //         System.out.print("\t| ");
    //         for(int[] arr: row) {
    //             System.out.print(Arrays.toString(arr) + " ");
    //         }
    //         System.out.println("| ");
    //     }
    // }
}
