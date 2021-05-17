/*
ID: jhunter3
LANG: JAVA
PROB: ratios
*/

package competition.training.chapter3.ratios;

import java.io.*;
import java.util.*;
import java.math.*;

class ratios {
    static int gcd(int a, int b) {
        if(b > a)
            return gcd(b, a);
        else if(b == 0)
            return a;
        else
            return gcd(b, a % b);
    }

    static int lcm(int a, int b) {
        return (a * b) / gcd(a,b);
    }

    static int[] parse(String[] arr) {
        int[] ret = new int[arr.length];
        for(int i = 0; i < arr.length;i++)
            ret[i] = Integer.parseInt(arr[i]);
        return ret;
    }

    static public void main(String[] args) throws IOException {
        long t = System.nanoTime();

        BufferedReader br = new BufferedReader(new FileReader("./ratios.in"));
        int[] goal = parse(br.readLine().split(" "));

        int[] a = parse(br.readLine().split(" "));
        int[] b = parse(br.readLine().split(" "));
        int[] c = parse(br.readLine().split(" "));

        int min = Integer.MAX_VALUE;
        int[] state = new int[]{1,1,1};
        for(int i = 0; i < 100; i++)
        for(int j = 0; j < 100; j++)
        for(int k = 0; k < 100; k++) {
            int[] sum = new int[]{ (a[0] * i) + (b[0] * j) + (c[0] * k),
                                   (a[1] * i) + (b[1] * j) + (c[1] * k),
                                   (a[2] * i) + (b[2] * j) + (c[2] * k) };
            int m = -1;
            boolean valid = true;
            for(int x = 0; x < 3; x++) {
                if(goal[x] == 0) {
                    valid = valid && sum[x] == 0;
                } else if (sum[x] == 0){
                    valid = false;
                } else {
                    int rem = sum[x] % goal[x];
                    int div = sum[x] / goal[x];

                    valid = valid && rem == 0;
                    if(m == -1)
                        m = sum[x] / goal[x];
                    else
                        valid = valid && m == div;
                }
            }

            if(valid && m < min) {
                min = m;
                state = new int[]{i,j,k};
            }
        }

        if(min == -1)
            min = 0;

        String str;
        if(min == Integer.MAX_VALUE)
            str = "NONE";
        else
            str = String.format("%d %d %d %d", state[0], state[1], state[2], min);

        BufferedWriter bw = new BufferedWriter(new FileWriter("./ratios.out"));
        bw.write(str + "\n");
        bw.close();

        System.out.println("time: " + ((System.nanoTime() - t) / Math.pow(10,9)));
    }
}
