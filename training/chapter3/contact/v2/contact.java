/*
ID: jhunter3
LANG: JAVA
PROB: contact
*/

import java.util.*;
import java.io.*;

class contact {
    public static void main(String[] args) throws IOException {
        long t = System.nanoTime();

        BufferedReader br = new BufferedReader(new FileReader("./contact.in"));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int a = Integer.parseInt(st.nextToken());
        int b = Integer.parseInt(st.nextToken());
        int n = Integer.parseInt(st.nextToken());

        String read;
        String bitstr = "";
        while((read = br.readLine()) != null)
            bitstr += read;

        Map<String,Integer> count = new HashMap<String,Integer>();

        for(int i = 0; i < bitstr.length(); i++) {
            for(int j = a; j <= b && i + j <= bitstr.length(); j++) {
                String substr = bitstr.substring(i, i + j);
                count.put(substr, (count.get(substr) == null ? 0 : count.get(substr)) + 1);
            }
        }

        List<Tuple> list = new ArrayList<Tuple>();
        for(String key: count.keySet())
            list.add(new Tuple(key, count.get(key)));

        Collections.sort(list, (Tuple p, Tuple q) -> {
            if(p.v == q.v) {
                if(p.k.length() == q.k.length()) {
                    return Integer.parseInt(p.k, 2) - Integer.parseInt(q.k, 2);
                }

                return p.k.length() - q.k.length();
            }

            return q.v - p.v;
        });

        BufferedWriter bw = new BufferedWriter(new FileWriter("./contact.out"));
        int i = 0;
        while(n > 0 && i < list.size()) {
            bw.write(list.get(i).v + "\n");
            int j = i;
            String line = "";
            while(j < list.size() && list.get(j).v == list.get(i).v) {
                line += list.get(j).k + " ";
                j++;
            }
            i = j;
            n--;
            bw.write(line.substring(0,line.length() - 1) + "\n");
        }
        bw.close();

        System.out.println("time: " + ((System.nanoTime() - t) / Math.pow(10,9)));
    }

    static class Tuple{
        String k;
        int v;
        Tuple(String k, int v) {
            this.k = k;
            this.v = v;
        }
    }
}
