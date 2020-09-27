import java.io.*;
import java.util.*;

import static java.lang.Math.*;
import static java.lang.Integer.parseInt;

class game1 {
    public static void main(String[] args) throws IOException {
        long t = System.nanoTime();
        BufferedReader br = new BufferedReader(new FileReader("game1.in"));

        n = parseInt(br.readLine());
        board = new int[n];

        int i = 0;
        String line;
        while((line = br.readLine()) != null) {
            StringTokenizer st = new StringTokenizer(line);
            while(st.hasMoreTokens()) {
                board[i] = parseInt(st.nextToken());
                i++;
            }
        }

        System.out.println("n: " + n + "\nboard: " + Arrays.toString(board));

        int[] ans = optimal();
        BufferedWriter bw = new BufferedWriter(new FileWriter("game1.out"));
        bw.write(ans[0] + " " + ans[1] + "\n");
        bw.close();

        System.out.println("final: ");
        printMem();
        System.out.println("time: " + ((System.nanoTime() - t) / pow(10,9)));
    }

    static int n;
    static int[] board;
    static int[][][] mem; // left, right, player
    static int[] optimal() {
        mem = new int[n][n][2];
        for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++) {
            if(i == j){
                mem[i][j][n % 2] = 0;
                mem[i][j][flip(n % 2)] = board[i];
            } else {
                mem[i][j] = new int[] {-1,-1};
            }
        }

        System.out.println("init: ");
        printMem();

        return optimal(0, n - 1, 0);
    }

    static int[] optimal(int left, int right, int player) { // player in {0,1}
        System.out.printf("optimal(%d, %d, %d)\n", left, right,player);
        printMem();

        if(mem[left][right][player] == -1) {
            int[] lOptimal = optimal(left + 1, right, flip(player));
            lOptimal[player] += board[left];
            int[] rOptimal = optimal(left, right - 1, flip(player));
            rOptimal[player] += board[right];

            mem[left][right] = lOptimal[player] > rOptimal[player] ? lOptimal : rOptimal;
        }

        if(mem[0][0][0] == 7) {
            System.out.println("&&&&&&&&&&&&&&&&&&&&&&&&&&");
            System.out.printf("optimal(%d, %d, %d)\n", left, right,player);

            printMem();
            throw new Error("Whata");
        }

        return mem[left][right];
    }

    static int flip(int i) {
        return (i + 1) % 2;
    }

    static void printMem() {
        for(int[][] row: mem) {
            System.out.print("    | ");
            for(int[] arr: row) {
                System.out.print(Arrays.toString(arr) + " ");
            }
            System.out.println("|");
        }
    }
}
