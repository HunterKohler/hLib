/*
ID: jhunter3
LANG: JAVA
PROB: humble
*/

package competition.training.chapter3.humble;

import java.io.*;
import java.util.*;

class humble {
    public static void main(String[] args) throws IOException {
        // long t = System.nanoTime();
        BufferedReader br = new BufferedReader(new FileReader("./humble.in"));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int k = Integer.parseInt(st.nextToken());
        int n = Integer.parseInt(st.nextToken());
        long[] s = new long[k];

        st = new StringTokenizer(br.readLine());
        for(int i = 0; i < k;i++){
            s[i] = Long.parseLong(st.nextToken());
        }

        // System.out.println("k = " + k);
        // System.out.println("n = " + n);
        // System.out.println("s = " + Arrays.toString(s));

        List<Long> multiples = new ArrayList<Long>();
        int[] next = new int[k];
        multiples.add((long) 1);
        for(int i = 0; i < n; i++) {
            int index = 0;
            for(int j = 1; j < k;j++) {
                long jval = s[j] * multiples.get(next[j]);
                long indexval = s[index] * multiples.get(next[index]);

                if(jval == indexval) {
                    next[j]++;
                } else if(jval < indexval) {
                    index = j;
                }
            }

            multiples.add(s[index] * multiples.get(next[index]));
            next[index]++;
        }

        BufferedWriter bw = new BufferedWriter(new FileWriter("./humble.out"));
        bw.write(multiples.get(multiples.size() - 1) + "\n");
        bw.close();

        // System.out.println("time: " + ((System.nanoTime() - t) / Math.pow(10,9)));
    }
}
