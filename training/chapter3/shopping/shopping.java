/*
ID: jhunter3
LANG: JAVA
PROB: shopping
*/
import java.io.*;
import java.util.*;
import static java.lang.Math.*;
import static java.lang.Integer.parseInt;
class shopping  {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("./shopping.in"));
        int s = parseInt(br.readLine());
        options = new ArrayList<Option>();
        for(int i = 0; i < s; i++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int n = parseInt(st.nextToken());
            int[] c = new int[n];
            int[] k = new int[n];
            for(int j = 0; j < n; j++) {
                c[j] = parseInt(st.nextToken());
                k[j] = parseInt(st.nextToken());
            }
            int p = parseInt(st.nextToken());
            options.add(new Option(n,c,k,p));
        }
        int b = parseInt(br.readLine());
        imap = new HashMap<Integer,Integer>();
        cmap = new HashMap<Integer,Integer>();
        int[] req = new int[5];
        for(int i = 0; i < b; i++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int c = parseInt(st.nextToken());
            int k = parseInt(st.nextToken());
            int p = parseInt(st.nextToken());
            req[i] = k;
            options.add(new Option(c,p));
            cmap.put(c,i);
            imap.put(i,c);
        }
        // for(Option opt: options) {
        //     System.out.println(opt);
        // }
        mem = new int[6][6][6][6][6];
        for(int e0 = 0; e0 < 6; e0++)
        for(int e1 = 0; e1 < 6; e1++)
        for(int e2 = 0; e2 < 6; e2++)
        for(int e3 = 0; e3 < 6; e3++)
        for(int e4 = 0; e4 < 6; e4++)
            mem[e0][e1][e2][e3][e4] = -1;
        mem[0][0][0][0][0] = 0;
        int m = minCost(req.clone());
        // System.out.println("minCost: " + m + " time: " + ((System.nanoTime() - t) / pow(10,9)));
        BufferedWriter bw = new BufferedWriter(new FileWriter("./shopping.out"));
        bw.write(m + "\n");
        bw.close();
    }
    static int s,b;
    static List<Option> options;
    static Map<Integer,Integer> imap; //i -> c;
    static Map<Integer,Integer> cmap; //c -> i;
    static int[][][][][] mem;
    static int minCost(int[] req) {
        // System.out.println(Arrays.toString(req));
        if(mem[req[0]][req[1]][req[2]][req[3]][req[4]] != -1)
            return mem[req[0]][req[1]][req[2]][req[3]][req[4]];
        int thisMin = Integer.MAX_VALUE;
        for(Option opt: options) {
            boolean valid = true;
            int[] clone = req.clone();
            for(int i = 0 ; i < opt.n; i++) {
                if(clone[cmap.get(opt.c[i])] < opt.k[i]) {
                    valid = false;
                    break;
                } else {
                    clone[cmap.get(opt.c[i])] -= opt.k[i];
                }
            }
            if(valid)
                thisMin = min(thisMin, minCost(clone) + opt.p);
        }
        mem[req[0]][req[1]][req[2]][req[3]][req[4]] = thisMin;
        return thisMin;
    }
}
class Option {
    int n,p;
    int[] c,k;
    Option(int n, int[] c, int[] k, int p) {
        this.n = n;
        this.c = c;
        this.k = k;
        this.p = p;
    }
    Option(int c, int p) {
        this(1, new int[]{c}, new int[]{1}, p);
    }
    @Override
    public String toString() {
        return String.format( "{n=%d,c=%s,k=%s,p=%d}",
                              this.n,
                              Arrays.toString(this.c),
                              Arrays.toString(this.k),
                              this.p );
    }
}
