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
    static BufferedReader br;
    static StringTokenizer st;
    static BufferedWriter bw;

    static Pair[] knightMoves = new Pair[]{ new Pair( 1, 2), new Pair(-1, 2),
                                            new Pair( 1,-2), new Pair(-1,-2),
                                            new Pair( 2, 1), new Pair(-2, 1),
                                            new Pair( 2,-1), new Pair(-2,-1) };

    static List<Pair> gridList = new ArrayList<Pair>();


    public static void main(String[] args) throws IOException {
        long T_INIT = System.nanoTime();

        br = new BufferedReader(new FileReader("./camelot.in"));
        bw = new BufferedWriter(new FileWriter("./camelot.out"));
        st = new StringTokenizer(br.readLine());
        R = parseInt(st.nextToken());
        C = parseInt(st.nextToken());
        for(int c = 0; c < C; c++)
        for(int r = 0; r < R; r++)
            gridList.add(new Pair(c,r));


        st = new StringTokenizer(br.readLine());
        king = new Pair(st.nextToken().charAt(0) - 'A', parseInt(st.nextToken()) - 1);
        knights = new ArrayList<Pair>();
        String line;
        while((line = br.readLine()) != null) {
            st = new StringTokenizer(line);
            while(st.hasMoreTokens()){
                int c = (int) (st.nextToken().charAt(0) - 'A');
                int r = parseInt(st.nextToken()) - 1;
                knights.add(new Pair(c,r));
            }
        }

        Map<Pair,List<Pair>> adjList = new HashMap<Pair,List<Pair>>();
        for(Pair p: gridList)
            adjList.put(p, new ArrayList<Pair>());

        for(Pair p: gridList)
        for(Pair move: knightMoves) {
            Pair q = Pair.add(p,move);

            if(inGrid(q)) {
                adjList.get(p).add(q);
            }
        }

        // List: {p,q} -> minimum distance
        // FLOYD
        Map<List<Pair>,Integer> dist = new HashMap<List<Pair>,Integer>();
        Map<List<Pair>,Pair> first = new HashMap<List<Pair>,Pair>();
        for(Pair p: gridList)
        for(Pair q: gridList)
            dist.put(toList(p,q),(p.equals(q) ? 0 : Integer.MAX_VALUE));

        for(Pair p: gridList)
        for(Pair q: adjList.get(p)) {
            dist.put(toList(p,q),1);
            first.put(toList(p,q), q);
        }


        for(Pair k: gridList)
        for(Pair p: gridList)
        for(Pair q: gridList) {
            List<Pair> pq = toList(p,q);
            List<Pair> pk = toList(p,k);
            List<Pair> kq = toList(k,q);
            int dPKQ = dist.get(pk) + dist.get(kq);
            int dPQ = dist.get(pq);

            if(dist.get(pk) != Integer.MAX_VALUE &&
               dist.get(kq) != Integer.MAX_VALUE &&
               dPKQ < dPQ) {
                dist.put(pq, dPKQ);
                first.put(pq,first.get(pk).copy());
            }
        }
        // END FLOYD

        // START WITHOUT KING
        int minSum = Integer.MAX_VALUE;
        Pair fend = new Pair(0,0);
        for(Pair end: gridList) {
            int sum = 0;
            int minKingDist = kingDist(end);

            for(Pair knight: knights) {
                sum += dist.get(toList(knight,end));

                Pair p = knight.copy();

                // List<Pair> path = new ArrayList<Pair>();
                while(!p.equals(end)) {
                    // path.add(p);
                    minKingDist = min(minKingDist, kingDist(p));
                    p = first.get(toList(p,end)).copy();
                }
                // path.add(end);
                // System.out.println(Arrays.toString(path.toArray()));
            }

            sum += minKingDist;

            if(sum < minSum) {
                minSum = sum;
                fend = end;
            }
        }
        // System.out.println(fend);


        // ENUMERATE
        for(Pair knight: knights) {
            Pair p = knight.copy();

            List<Pair> path = new ArrayList<Pair>();
            while(!p.equals(fend)) {
                path.add(p);
                p = first.get(toList(p,fend)).copy();
            }
            path.add(fend);
            System.out.println(Arrays.toString(path.toArray()));
        }


        System.out.println("ans: " + minSum);
        System.out.println("time: " + ((System.nanoTime() - T_INIT) / pow(10, 9)));
    }

    static boolean inGrid(int r, int c) { return r >= 0 && c >= c && r < R && c < C; }
    static boolean inGrid(Pair p) { return inGrid(p.key(), p.val()); }

    static int kingDist(Pair p) { return max(abs(p.k - king.k), abs(p.v - king.v)); }

    static int R,C;
    static Pair king;
    static List<Pair> knights;

    static List<Pair> toList(Pair... pairs) {
        List<Pair> ret = new ArrayList<Pair>();
        for(Pair p: pairs)
            ret.add(p);
        return ret;
    }

    static class Pair {
        int k, v;

        Pair(int k, int v) {
            this.k = k;
            this.v = v;
        }

        Pair(char k, int v) {
            this.k = (int) (k - 'A');
            this.v = v - 1;
        }

        int key() { return this.k; }
        int key(int k) { return (this.k = k); }

        int val() { return this.v; }
        int val(int v) { return (this.v = v); }

        static Pair add(Pair p, Pair q) {
            return new Pair(p.k + q.k, p.v + q.v);
        }

        @Override
        public int hashCode() {
            return Objects.hash(this.k, this.v);
        }

        @Override
        public boolean equals(Object o) {
            if(this == o)
                return true;
            else if(o == null)
                return false;
            else if(this.getClass() != o.getClass())
                return false;

            Pair p = (Pair) o;
            return p.k == this.k && p.v == this.v;
        }

        @Override
        public String toString() {
            return String.format("(%c,%d)",this.k + 'A',this.v + 1);
        }

        Pair copy() {
            return new Pair(this.k,this.v);
        }
    }
}
