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

        String bitstr = br.readLine();
        Map<String,Integer> count = new HashMap<String,Integer>();

        for(int i = 0; i < bitstr.length(); i++) {
            for(int j = a; j <= b && i + j <= bitstr.length(); j++) {
                String substr = bitstr.substring(i, i + j);
                count.put(substr, (count.get(substr) == null ? 0 : count.get(substr)) + 1);
            }
        }

        List<Tuple> list = new ArrayList<Tuple>();
        for(String key: count.keySet())
            list.add(new Tuple<String,Integer>(key, count.get(key));

        Collections.sort(list, (Tuple a, Tuple b) -> {
            if(a.v == b.v) {
                if(a.k.size() == b.k.size()) {
                    return Integer.parseInt(a.k, 2) - Integer.parseInt(b.k, 2);
                }

                return a.k.size() - b.k.size();
            }

            return b.v - a.v;
        })

        int i = 0;
        while(n > 0) {
            int i = 0;
            while()
        }

        System.out.println(count);
        System.out.println("time: " + ((System.nanoTime() - t) / Math.pow(10,9)));
    }

    class Tuple<K,V> {
        this.k;
        this.v;
        Tuple(K k, V v) {
            this.k = k;
            this.v = v;
        }
    }
}
