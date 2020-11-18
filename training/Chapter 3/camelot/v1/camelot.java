/*
ID: jhunter3
LANG: JAVA
PROB: range
*/

import java.io.*;
import java.util.*;
import static java.lang.Math.*;
import static java.lang.Integer.parseInt;

class camelot {
    static int inf = Integer.MAX_VALUE / 10;

    static P[] Dk = { new P(1,2), new P(-1,2), new P(1,-2), new P(-1,-2),
                      new P(2,1), new P(-2,1), new P(2,-1), new P(-2,-1) };

    static int R,C;
    static P king;
    static List<P> knights = new ArrayList<P>();
    static Map<List<P>,Integer> dist = new HashMap<List<P>,Integer>();
    static Map<List<P>,Integer> distking = new HashMap<List<P>,Integer>();

    static List<P> grid = new ArrayList<P>();

    public static void main(String[] args) throws IOException {
        long t0 = System.nanoTime();

        BufferedReader br = new BufferedReader(new FileReader("camelot.in"));
        BufferedWriter bw = new BufferedWriter(new FileWriter("camelot.out"));

        StringTokenizer st = new StringTokenizer(br.readLine());
        R = parseInt(st.nextToken());
        C = parseInt(st.nextToken());

        st = new StringTokenizer(br.readLine());
        king = new P(st.nextToken().charAt(0) - 'A', parseInt(st.nextToken()));

        String line;
        while((line = br.readLine()) != null) {
            st = new StringTokenizer(line);
            while(st.hasMoreTokens()) {
                int c = st.nextToken().charAt(0) - 'A';
                int r = parseInt(st.nextToken());
                knights.add(new P(c,r));
            }
        }

        for(int c = 0; c < C; c++)
        for(int r = 0; r < R; r++)
            grid.add(new P(c,r));

        for(P i: grid) {
            dist.put(list(i,i),0);
        }

        for(P i: grid)
        for(P dk: Dk) {
            if(inGrid(i.add(dk))) {
                dist.put(list(i,i.add(dk)), 1);
            }
        }

        for(P k: grid)
        for(P i: grid)
        for(P j: grid) {
            Integer ij = dist.get(list(i,j)); if(ij == null) ij = inf;
            Integer ik = dist.get(list(i,k)); if(ik == null) ik = inf;
            Integer kj = dist.get(list(k,j)); if(kj == null) kj = inf;
            Integer ikj = ik + kj;
            dist.put(list(i,j), min(ij,ikj));
        }

        System.out.println((System.nanoTime() - t0) / 1e9);
    }

    static boolean inGrid(int c,int r) { return 0 <= c && c < C && 0 <= r && r < R; }
    static boolean inGrid(P p) { return inGrid(p.c,p.r); }
    static <T> List<T> list(T ...arr) { return Arrays.asList(arr); }

    static class P {
        int c,r;
        P(int c,int r) {
            this.c = c;
            this.r = r;
        }
        public int hashCode() { return Objects.hash(this.c,this.r); }
        public boolean equals(Object obj) {
            return ((P) obj).c == this.c && ((P) obj).r == this.r;
        }
        public P clone() { return new P(this.c, this.r); }
        public P add(int dc, int dr) { return new P(this.c+dc,this.r+dr); }
        public P add(P dk) { return this.add(dk.c,dk.r); }
        public String toString() { return "("+this.c+","+this.r+")"; }
    }
}
