/*
ID: jhunter3
LANG: JAVA
PROB: camelot
*/

import java.io.*;
import java.util.*;
import static java.lang.Integer.parseInt;
import static java.lang.Math.*;

class camelot {
    static BufferedReader br;
    static StringTokenizer st;
    static BufferedWriter bw;

    static int R,C;

    public static void main(String[] args) throws IOException {
        long T_INIT = System.nanoTime();

        List<Peice> peices = new ArrayList<Peice>();

        br = new BufferedReader(new FileReader("camelot.in"));
        st = new StringTokenizer(br.readLine());
        R = parseInt(st.nextToken());
        C = parseInt(st.nextToken());
        st = new StringTokenizer(br.readLine());
        Peice king = new Peice(st.nextToken().charAt(0) - 'A', parseInt(st.nextToken()) - 1);
        String line;
        while((line = br.readLine()) != null) {
            st = new StringTokenizer(br.readLine());

            while(st.hasMoreTokens()) {
                peices.add()
            }
        }



        bw = new BufferedWriter(new FileWriter("camelot.out"));
        System.out.println("time: " + ((System.nanoTime() - T_INIT) / pow(10, 9)));
    }
}

class Peice {
    int r,c;

    Peice(int c, int r) {
        this.c = c;
        this.r = r;
    }
}
