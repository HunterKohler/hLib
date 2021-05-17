/*
ID: jhunter3
LANG: JAVA
PROB: kimbits
*/

import java.util.*;
import java.io.*;

class kimbits {
    public static void main(String[] args) throws IOException {
        long t = System.nanoTime();
        BufferedReader br = new BufferedReader(new FileReader("./kimbits.in"));
        StringTokenizer st = new StringTokenizer(br.readLine());
        long N = Long.parseLong(st.nextToken()); // length N
        long L = Long.parseLong(st.nextToken()); // <= L set bits
        long I = Long.parseLong(st.nextToken()); // Ith such

        String ans = "";
        for(long i = 0; i <= (1 << N) - 1; i++) {
            if(Long.bitCount(i) <= L){
                if(I == 1){
                    ans = Long.toString(i, 2);
                    break;
                } else{
                    // System.out.print(I + "th: " + Long.toString(i, 2));
                    I--;
                }
            }
        }

        for(long i = 0; ans.length() < N; i++) {
            ans = "0" + ans;
        }

        BufferedWriter bw = new BufferedWriter(new FileWriter("./kimbits.out"));
        bw.write(ans + "\n");
        bw.close();

        System.out.println("ans: " + ans + ", time: " + ((System.nanoTime() - t)/Math.pow(10,9)));
    }
}
