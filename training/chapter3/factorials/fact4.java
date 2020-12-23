/*
ID: jhunter3
LANG: JAVA
PROB: fact4
*/

import java.util.*;
import java.io.*;

class fact4 {
    public static void main(String[] args) throws IOException {
        // long t = System.nanoTime();
        int n = (new Scanner(new File("./fact4.in"))).nextInt();
        PrintWriter pw = new PrintWriter(new File("./fact4.out"));
        pw.println(solve(n));
        pw.close();
        // System.out.println("time: " + ((System.nanoTime() - t) / Math.pow(10,9)));
    }

    static int solve(int n) {
        int u = 1;
        for(int i = 1; i <= n; i++) {
            u *= i;
            while(u % 10 == 0)
                u /= 10;
            u = shorten(u,5);
        }
        return shorten(u,1);
    }

    static int shorten(int i, int l) {
        return i - ((i / pow(10,l)) * pow(10,l));
    }

    static int pow(int a, int b) {
        return (int) Math.pow(a,b);
    }
}
