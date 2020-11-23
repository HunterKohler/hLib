/*
ID: jhunter3
LANG: JAVA
PROB: nuggets
*/

import java.io.*;
import java.util.*;
import static java.lang.Math.*;

class nuggets {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("nuggets.in"));
        BufferedWriter bw = new BufferedWriter(new FileWriter("nuggets.out"));

        int n = Integer.parseInt(br.readLine());
        List<Integer> nums = new ArrayList<Integer>(); //  each num in (0,256]
        for(int i = 0; i < n; i++) {
            nums.add(Integer.parseInt(br.readLine()));
        }

        Collections.sort(nums);

        // printList(nums);

        int a = 0;
        while(a < nums.size()) {
            int b = a + 1;
            while(b < nums.size()) {
                if(nums.get(b) % nums.get(a) == 0) {
                    nums.remove(b);
                } else {
                    b++;
                }
            }
            a++;
        }

        // printList(nums);

        // System.out.println("gcd: " + gcd(nums));

        if(gcd(nums) != 1) {
            // System.out.println(0);
            bw.write(0);
            bw.close();
        } else {
            int last = 0;
            int index = 0;
            boolean[] range = new boolean[(int) 1e6];
            range[0] = true;
            while(abs(last - index) <= nums.get(nums.size() - 1) && index < range.length) {
                // System.out.println("last: " + last);
                // System.out.println("index: " + index);
                if(range[index]) {
                    for(int num: nums) {
                        range[index + num] = true;
                    }
                } else {
                    last = index;
                }
                index++;
            }

            // System.out.println(last);
            bw.write(last);
            bw.close();
        }
    }

    // static void printList(List l) {
    //     System.out.println(Arrays.toString(l.toArray()));
    // }

    static int gcd(List<Integer> A) {
        int ret = A.get(0);
        for(int a: A) {
            ret = gcd(ret, a);
        }
        return ret;
    }

    static int gcd(int a, int b) {
        int temp;
        if(a < b){
            temp = b;
            b = a;
            a = temp;
        }

        while(b > 0) {
            temp = a;
            a = b;
            b = temp % b;
        }

        return a;
    }
}
