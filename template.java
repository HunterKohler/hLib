/*
ID: jhunter3
LANG: JAVA
PROB: NAME
*/

import java.io.*;
import java.util.*;
import static java.lang.Integer.parseInt;
import static java.lang.Math.*;

class NAME {
    static BufferedReader br;
    static StringTokenizer st;
    static BufferedWriter bw;

    public static void main(String[] args) throws IOException {
        long T_INIT = System.nanoTime();

        br = new BufferedReader(new FileReader("NAME.in"));

        bw = new BufferedWriter(new FileWriter("NAME.out"));

        System.out.println("time: " + ((System.nanoTime() - T_INIT) / pow(10, 9)));
    }

    StringTokenizer nextLine(){
        st = StringTokenizer(br.readLine());
        return st;
    }
}
