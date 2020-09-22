/*
ID: jhunter3
LANG: JAVA
PROB: contact
*/

import java.io.*;
import java.util.*;
import java.util.regex.*;

class contact {
    static List<Tuple<String,Integer>> counts;
    static String bitstr;

    public static void main(String[] args) throws IOException {
        // long t = System.nanoTime();
        BufferedReader br = new BufferedReader(new FileReader("./contact.in"));

        String[] input = br.readLine().split(" ");
        int a = Integer.parseInt(input[0]);
        int b = Integer.parseInt(input[1]);
        int n = Integer.parseInt(input[2]);

        String line;
        bitstr = "";
        while((line = br.readLine()) != null)
            bitstr += line;

        counts = new ArrayList<Tuple<String,Integer>>();
        for(int l = a; l <= b; l++) {
            for(int i = 0; i < Math.pow(2, l); i++) {
                String istr = Integer.toBinaryString(i);
                while(istr.length() < l) {
                    istr = "0" + istr;
                }
                count(istr);
            }
        }

        Collections.sort(counts, (Tuple<String, Integer> p, Tuple<String, Integer> q) -> {
            if(p.v == q.v) {
                if(p.k.length() == q.k.length()) {
                    return Integer.parseInt(p.k,2) - Integer.parseInt(q.k,2);
                }

                return p.k.length() - q.k.length();
            }
            return q.v - p.v;
        });

        // System.out.println(Arrays.toString(counts.toArray()));

        BufferedWriter bw = new BufferedWriter(new FileWriter("./contact.out"));

        int i = 0;
        while(n > 0) {
            if(i >= counts.size())
                break;
            int num = counts.get(i).v;
            int online = 0;
            bw.write(num + "\n");
            line = "";
            while(i < counts.size() && counts.get(i).v == num) {
                if(online == 6) {
                    online = 0;
                    line += "\n";
                }

                line += counts.get(i).k + " ";
                online++;
                i++;
            }
            bw.write(line.substring(0,line.length() - 1) + "\n");
            n--;
        }
        bw.close();

        // System.out.println("time: " + ((System.nanoTime() - t) / Math.pow(10, 9)));
    }

    static void count(String str) {
        Pattern p = Pattern.compile(str);
        Matcher m = p.matcher(bitstr);

        int c = 0;
        int start = 0;
        while(m.find(start)) {
            c++;
            start = m.start() + 1;
        }
        if(c != 0)
            counts.add(new Tuple<String, Integer>(str, c));
    }

    static class Tuple<K,V> {
        K k;
        V v;
        Tuple(K k, V v) {
            this.k = k;
            this.v = v;
        }

        public String toString() {
            return "(" + this.k.toString() + "," + this.v.toString() + ")";
        }
    }
}
