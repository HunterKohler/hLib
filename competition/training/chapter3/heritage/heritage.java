/*
ID: jhunter3
LANG: JAVA
PROB: heritage
*/

package competition.training.chapter3.heritage;

import java.io.*;
import java.util.*;

class heritage {
    static BufferedReader br;
    static BufferedWriter bw;

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new FileReader("heritage.in"));
        bw = new BufferedWriter(new FileWriter("heritage.out"));
        String in = br.readLine();
        String pre = br.readLine();

        tree(in, pre);
        bw.write("\n");
        bw.close();
    }

    static void tree(String in, String pre) throws IOException {
        if(in.length() == 1) {
            bw.write(in);
            return;
        }

        if(in.length() == 0) {
            return;
        }

        // System.out.printf("tree(%s,%s)\n",in,pre);

        String root = pre.substring(0,1);
        String[] in_arr = in.split(root);
        String in_left = in_arr[0];
        String in_right = (in_arr.length == 2) ? in_arr[1] : "";
        String pre_left = pre.substring(1,in_left.length() + 1);
        String pre_right = pre.substring(in_left.length() + 1);

        // System.out.println("root: " +root);
        // System.out.println("in_left: " +in_left);
        // System.out.println("in_right: " +in_right);
        // System.out.println("pre_left: " +pre_left);
        // System.out.println("pre_right: " +pre_right);

        tree(in_left, pre_left);
        tree(in_right, pre_right);
        bw.write(root);
    }
}
