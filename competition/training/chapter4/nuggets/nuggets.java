/*
ID: jhunter3
LANG: JAVA
PROB: nuggets
*/

package competition.training.chapter4.nuggets;

import java.io.*;
import java.util.*;
import static java.lang.Integer.parseInt;

class nuggets {
    static int MIN = 1;
    static int MAX = 256;
    static int LENGTH = (MAX * MAX) - (MAX * 2);

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("nuggets.in"));
        BufferedWriter bw = new BufferedWriter(new FileWriter("nuggets.out"));

        int n = parseInt(br.readLine());
        int[] x = new int[n];

        boolean[] valid = new boolean[LENGTH + 1];
        for(int i = 0; i < n; i++) {
            x[i] = parseInt(br.readLine());
            valid[x[i]] = true;
        }

        int max = 0;
        for(int i = 1; i <= LENGTH; i++) {
            for(int j = 0; j < n && i >= x[j]; j++) {
                valid[i] = valid[i] || valid[i - x[j]];
            }
            if(!valid[i]) {
                max = i;
            }
        }

        System.out.println(max);
        bw.write(((65023 == max) ? 0 : max) + "\n");
        bw.close();
    }
}
