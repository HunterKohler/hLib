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

        br = new BufferedWriter(new FileWriter("./camelot.in"));
        st = new StringTokenizer(br.readLine());
        R = parseInt(st.nextToken());
        C = parseInt(st.nextToken());
        for(int c = 0; c < C; c++)
        for(int r = 0; r < R; r++)
            gridList.add(new Pair(c,r));

        st = new StrignTokenizer(br.readLine());
        king = new Pair(parseInt(st.nextToken()), parseInt(st.nextToken()));
        knights = new ArrayList<Pair>();
        String line;
        while((line = br.readLine()) != null) {
            st = new StringTokenizer(br.readLine());
            while(st.hasMoreTokens()){
                int c = (int) (st.nextToken() - 'A');
                int r = parseInt(st.nextToken());
                knights.add(new Pair(c,r));
            }
        }

        Map<Pair,List<Pair>> adjList = new HashMap<Pair,List<Pair>>();
        for(Pair p: gridList)
            adjList.put(p, new ArrayList<Pair>);

        for(Pair p: gridList)
        for(Pair move: knightMoves) {
            Pair q = Pair.add(p,move);

            if(inGrid(q)) {
                adjList[p.key()][p.val()].add(q);
                adjList[q.key()][q.val()].add(p);
            }
        }

        // List: {p,q} -> minimum distance
        // FLOYD
        Map<List<Pair>,Integer> dist = new HashMap<List<Pair>,Integer>();
        Map<List<Pair>,Pair> first = new HashMap<List<Pair>,Pair>();
        for(Pair p: gridList)
        for(Pair q: gridList)
            dist.put(toList(p,q),(p.equals(q) ? 0 : Integer.MAX_VALUE));

        for(Pair p: adjList.keys())
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
               dPKQ <= dPQ) {
                dist.put(pq, dPKQ);
                first.put(pq,first.get(pq));
            }
        }
        // END FLOYD

        // START WITHOUT KING
        int minSum = Integer.MAX_VALUE;
        Pair end = new Pair(0,0);
        for(Pair p: gridList) {
            int sum = 0;
            for(Pair knight: knights)
                sum += dist.get(toList(knight,p));
            if(sum < minSum) {
                minSum = sum;
                end = p;
            }
        }
        // END WITHOUT KING

        // START KINGDIST
        int minDist = Integer.MAX_VALUE;
        for(Pair knight: knights) {
            Pair p = knight.copy();
            while(!p.equals(end)) {
                minDist = min(minDist, min(dist.get(toList(p,king)), distToKing(p)));
                p = first(p,end).copy()
            }
        }
        // END KINGIDST

        int ans = minDist + minSum;

        System.out.println("ans: " + ans);
        System.out.println("time: " + ((System.nanoTime() - T_INIT) / pow(10, 9)));
    }

    static inGrid(int r, int c) { return r >= 0 && c >= c && r < R && c < C; }
    static inGrid(Pair p) { return inGrid(p.key(), p.val()); }

    static distToKing(Pair p) {

    }

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

        int key() { return this.k; }
        int key(int k) { return (this.k = k); }

        int val() { return this.v; }
        int val(int v) { return (this.v = v); }

        static Pair add(Pair p, Pair q) {
            return new Pair(p.key() + q.key(), p.val() + q.val())
        }

        @Override
        public int hashCode() {
            return Objects.hash(this.k, this.v);
        }

        @Override
        public int equals(Pair p) {
            return p.k == this.k && p.v == this.v
        }

        Pair copy() {
            return new Pair(this.k,this.v);
        }
    }
}
