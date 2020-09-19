import java.util.*;
import java.io.*;

class stamps {
    static final int MAX_VALUE = 200 * 10000;

    static int k, n;
    static int[] bases;
    static Set<List> mem;
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("./stamps.in"));
        StringTokenizer st = new StringTokenizer(br.readLine());
        k = Integer.parseInt(st.nextToken());
        n = Integer.parseInt(st.nextToken());
        bases = new int[n];
        mem = new HashSet<List>();

        String line;
        while((line = br.readLine()) != null) {
            st = new StringTokenizer(line);
            for(int i = 0 ; st.hasMoreTokens(); i++) {
                bases[i] = Integer.parseInt(st.nextToken());
                reached(bases[i], 1);
            }
        }
        reached(0, k);

        int c = 1;
        while(reachable(c, k))
            c++;

        for(List l: mem) {
            System.out.printf("[%d,%d]\n", l.get(0), l.get(1));
        }

        System.out.println(c - 1);
    }

    static boolean reachable(int val, int num) {
        if(hasBeenReached(val,num)) {
            return true;
        } else {
            for(int i: bases) {
                if(val - i >= 0 && reachable(val - i, num - 1)) {
                    return true;
                }
            }
        }

        return false;
    }

    static void reached(int val, int num) {
        while(num <= k) {
            mem.add(zip(val, num));
            num++;
        }
    }

    static boolean hasBeenReached(int val, int num) {
        return mem.contains(zip(val, num));
    }

    static List zip(int a, int b) {
        return Arrays.asList(new Integer[]{a,b});
    }
}
