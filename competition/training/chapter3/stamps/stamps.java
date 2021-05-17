/*
ID: jhunter3
LANG: JAVA
PROB: stamps
*/

package competition.training.chapter3.stamps;

import java.util.*;
import java.io.*;

class stamps {
    static int[] stamps;
    static int k, n;
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("./stamps.in"));
        StringTokenizer st = new StringTokenizer(br.readLine());
        k = Integer.parseInt(st.nextToken());
        n = Integer.parseInt(st.nextToken());
        String line;
        stamps = new int[n];
        int i = 0;
        while((line = br.readLine()) != null) {
            st = new StringTokenizer(line);
            while(st.hasMoreTokens()){
                stamps[i] = Integer.parseInt(st.nextToken());
                i++;
            }
        }
        int j = 1;
        while(minstamps(j) <= k)
            j++;
        j--;
        BufferedWriter bw = new BufferedWriter(new FileWriter("./stamps.out"));
        bw.write(j + "\n");
        bw.close();
    }
    static short[] mem = new short[10000 * 200 + 1];
    static {
        Arrays.fill(mem, (short) -1);
        mem[0] = 0;
    }
    static short minstamps(int j) {
        if(mem[j] == -1){
            mem[j] = Short.MAX_VALUE;
            for(int stamp: stamps) {
                if(j - stamp < 0)
                    continue;

                short call = minstamps(j - stamp);
                if(call != -1) {
                    mem[j] = (short) Math.min(mem[j], call + 1);
                }
            }
        }
        return mem[j];
    }
}
