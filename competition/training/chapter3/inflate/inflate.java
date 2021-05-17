/*
ID: jhunter3
LANG: JAVA
PROB: inflate
*/

package competition.training.chapter3.inflate;

import java.io.*;
import java.util.*;
import java.math.*;

class inflate {
    static int m, n;
    static Problem[] problems;
    public static void main(String[] args) throws IOException {
        long t = System.nanoTime();

        Scanner sc = new Scanner(new File("./inflate.in"));
        m = sc.nextInt();
        n = sc.nextInt();
        problems = new Problem[n];
        for(int i = 0; i < n; i++) {
            problems[i] = new Problem(sc.nextInt(), sc.nextInt());
        }

        // System.out.println("m: " + m);
        // System.out.println("n: " + n);
        // System.out.println("problems: " + Arrays.toString(problems));

        int ans =  solve(m,n,problems);

        // System.out.println("ans: " + ans);
        BufferedWriter bw = new BufferedWriter(new FileWriter("./inflate.out"));
        bw.write(ans + "\n");
        bw.close();
        System.out.println("time: " + ((System.nanoTime() - t) / Math.pow(10,9)));
    }

    static Map<List<Integer>, Integer> mem;
    static int solve(int m, int n, Problem[] problems) {
        mem = new HashMap<List<Integer>,Integer>();
        return maximize(m, 0);
    }

    static int maximize(int time, int sum) {
        if(mem.containsKey(zip(time,sum))) {
            return mem.get(zip(time, sum));
        }
        if(time < 0) {
            return 0;
        } else if(time == 0) {
            return sum;
        }

        int max = 0;
        for(Problem p: problems){
            int newtime = time - p.len;
            int newsum = sum + p.val;

            max = Math.max(max, max + maximize(newtime, newsum));
        }

        mem.put(zip(time, sum), max);
        return max;
    }

    static List<Integer> zip(int a, int b) {
        return Arrays.asList(new Integer[]{a,b});
    }

    static class Problem {
        int val,len;
        Problem(int val, int len) {
            this.val = val;
            this.len = len;
        }

        Problem(String val, String len) {
            this(Integer.parseInt(val), Integer.parseInt(len));
        }

        public String toString() {
            return("{val: " + this.val + ", len: " + this.len + "}");
        }
    }
}
