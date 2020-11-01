/*
ID: jhunter3
LANG: JAVA
PROB: camelot
*/

import java.io.*;
import java.util.*;
import static java.lang.Integer.parseInt;
import static java.lang.Math.*;

class camelot {
    static int INF = Integer.MAX_VALUE;

    static BufferedReader br;
    static StringTokenizer st;
    static BufferedWriter bw;

    static int R, C;
    static Pair king;
    static List<Pair> knights;

    static List<Pair> BOARD_LIST;
    static int[][] MOVES = new int[][]{ { 2, 3 },   { 3, 2 },
                                        { -2, 3 },  { -3, 2 },
                                        { 2, -3 },  { 3, -2 },
                                        { -2, -3 }, { -3, -2 } };

    public static void main(String[] args) throws IOException {
        long T_INIT = System.nanoTime();

        br = new BufferedReader(new FileReader("camelot.in"));

        R = parseInt(st.nextToken());
        C = parseInt(st.nextToken());

        st = nextLine(br);

        int kingc = st.nextToken().charAt(0) - 'A';
        int kingr = parseInt(st.nextToken());
        king = pair(kingr, kingc);

        knights  = new ArrayList<int[]>();
        String line;
        while((line = br.readLine()) != null) {
            st = nextLine(line);
            c = st.nextToken().charAt(0) - 'A';
            r = parseInt(st.nextToken());
            while(st.hasMoreTokens())
                knights.add(pair(r,c));
        }

        BOARD_LIST = new AdjList<Pair>();
        for(int r = 0; r < R; r++)
        for(int c = 0; c < C; c++)
            BOARD_LIST.add(pair(r,c));

        Map<List<Pair>, Boolean> adj = new HashMap<List<Pair>, Boolean>();
        for(Pair p: BOARD_LIST) {
            adj.put(list(p,p), 0);
            for(int[] move: MOVES) {
                Pair np = p.add(move);
                if(np.inGrid())
                    adj.put(list(p, np), 1);
            }
        }

        Map<List<Pair>, Integer> dist = new HashMap<List<Pair>, Integer>();
        Map<Pair, Pair> next = new HashMap<Pair, Pair>();
        for(Pair p: BOARD_LIST)
        for(Pair q: BOARD_LIST) {
            List<Pair> pq = list(p,q);
            int val;
            if((val = adj(pq)) != null) {
                dist.put(pq, val);
                next.put(p, q);
            }
        }

        for(Pair k : BOARD_LIST)
        for(Pair i : BOARD_LIST)
        for(Pair j : BOARD_LIST) {
            ik = dist.get(i,k);
            kj = dist.get(k,j);
            ij = dist.get(i,j);
            ikj = ik + kj;
            if(ik != null && kj != null) {
                if(ikj < ij) {
                    next.put(i, k);
                    dist.put(list(i,j), ikj);
                }
            }
        }

        bw = new BufferedWriter(new FileWriter("camelot.out"));

        end = pair('B', 5);
        for(Pair k: knights) {
            n = k.copy();
            while(n != end) {
                bw.write(k + " ");
                n = next.get(n);
            }
            bw.write(end + "\n");
        }

        bw.close();

        System.out.println("time: " + ((System.nanoTime() - T_INIT) / pow(10, 9)));
    }

    static StringTokenizer nextLine(BufferedReader br){
        return new StringTokenizer(br.readLine());
    }

    static StringTokenzer nextLine(String s) {
        return new StringTokenizer(s);
    }

    static Pair pair(int r, int c) {
        return new Pair(r,c);
    }

    static <T> List<T> list(T p, T q) {
        List<T> ret = new ArrayList<T>();
        ret.add(p);
        ret.add(q);
        return ret;
    }

    static boolean inGrid(int r, int c) {
        return r >= 0 && c >= 0 && r < R && c < C;
    }

    class Pair {
        int r, c;

        Pair(int r, int c) {
            this.r = r;
            this.c = c;
        }

        boolean inGrid() {
            return inGrid(this.r,this.c);
        }

        Pair add(int dr, int dc) {
            return pair(this.r + dr, this.c + dc);
        }

        Pair add(int[] d) {
            return pair(this.r + d[0], this.c + d[1]);
        }

        @override
        public int hashCode(){
            return Object.hash(this.r, this.c);
        }

        @override
        public boolean equals(Object o) {
            return (o instanceof Pair) && this.r == r && this.c == c;
        }

        @override
        public String toString() {
            return ((char) ('A' + this.r)) + " " + this.c;
        }

        Pair copy() {
            return pair(this.r, this.c);
        }
    }
}
