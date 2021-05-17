/*
ID: jhunter3
LANG: JAVA
PROB: fence9
*/

import java.io.*;
import java.util.*;
import static java.lang.Math.*;

class fence9 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("fence9.in"));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int n = Integer.parseInt(st.nextToken());
        int m = Integer.parseInt(st.nextToken());
        int p = Integer.parseInt(st.nextToken());


        int f;
        int dy_1 = m;
        int dx_1 = n;
        while((f = gcd(dy_1,dx_1)) != 1) {
            dy_1 /= f;
            dx_1 /= f;
        }

        int dy_2 = m;
        int dx_2 = abs(p - n);
        while((f = gcd(dy_2,dx_2)) != 1) {
            dy_2 /= f;
            dx_2 /= f;
        }

        int A = m * p / 2;
        int P = ((dx_1 == 0) ? m : (n / dx_1)) + p + ((dx_2 == 0) ? m : (abs(p - n) / dx_2));
        int I = A + 1 - (P / 2);

        // System.out.println(A);
        // System.out.println(P);
        // System.out.println(I);

        PrintWriter pw = new PrintWriter(new FileWriter("fence9.out"));
        pw.println(I);
        pw.close();
    }

    static int gcd(int a, int b) {
        if (a < b)
            return gcd(b,a);

        while(b!=0) {
            int a_next = b;
            int b_next = a % b;
            a = a_next;
            b = b_next;
        }

        return a;
    }
}
