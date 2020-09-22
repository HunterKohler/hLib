/*
ID: jhunter3
LANG: JAVA
TASK: contact
*/

import java.io.*;
import java.util.*;

class contact {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("./contact.in"));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int a = Integer.parseInt(st.nextToken());
        int b = Integer.parseInt(st.nextToken());
        int n = Integer.parseInt(st.nextToken());

        String line;
        String bitstr = "";
        while((line = br.readLine()) != null)
            bitstr += line;

        Map<String,Integer> map = new HashMap<String,Integer>();
        for(int l = a; l <= b;l++) {
            for(int i = 0; i <= bitstr.length() - l; i++) {
                String s = bitstr.substring(i, i + l);
                if(map.keySet().contains(s))
                    map.put(s, map.get(s) + 1);
                else
                    map.put(s, 1);
            }
        }

        List<Pair> list = new ArrayList<Pair>();
        for(String s: map.keySet())
            list.add(new Pair(s, map.get(s)));


        Collections.sort(list, (Pair p, Pair q) -> {
            if(p.count == q.count) {
                // if(p.str.length() == p.str.length()){
                //     return p.num() - q.num();
                // }

                return p.str.length() - q.str.length();
            }

            return q.count - p.count;
        });
        // System.out.println(Arrays.toString(list.toArray()));

        BufferedWriter bw = new BufferedWriter(new FileWriter("./contact.out"));
        int i = 0;
        while(n > 0 && i < list.size()) {
            bw.write(list.get(i).count + "\n");
            int j = i;
            int online = 0;
            while(j < list.size() && list.get(j).count == list.get(i).count) {
                if(online == 6) {
                    bw.write("\n" + list.get(j).str);
                } else if(online == 0) {
                    bw.write(list.get(j).str);
                } else {
                    bw.write(" " + list.get(j).str);
                }
                online++;
                j++;
            }
            bw.write("\n");
            n--;
            i = j;
        }

        bw.close();

    }

    static class Pair {
        String str;
        int count;

        Pair(String str, int count) {
            this.str = str;
            this.count = count;
        }

        public String toString() {
            return String.format("[str=%s,count=%d]", this.str, this.count);
        }

        public int num() {
            return Integer.parseInt(this.str, 2);
        }
    }
}
