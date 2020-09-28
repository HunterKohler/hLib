/*
ID: jhunter3
LANG: JAVA
PROB: camelot
*/

import java.io.*;
import java.util.*;
import static java.lang.Math.*;
import static java.lang.Integer.parseInt;

class camelot {
    public static void main(String[] args) throws IOException {
        long t = System.nanoTime();

        BufferedReader br = new BufferedReader(new FileReader());
        StringTokenizer st = new StringTokenizer(br.readLine());
        int R = parseInt(st.nextToken());
        int C = parseInt(st.nextToken());
        List<Peice> peices = new ArrayList<Peice>();
        boolean first = true;
        String line;
        while((line = br.readLine()) != null) {
            st = new StingTokenizer(line);
            if(first)
                peices.add(new Peice(
                    st.nextToken().charAt(0) - 'A',
                    parseInt(st.nextToken()) - 1, 'k'));
            while(st.hasMoreTokens()) {
                peices.add(new Peice(
                    st.nextToken().charAt(0) - 'A',
                    parseInt(st.nextToken()) - 1, 'h'));
            }
        }

        Set<State> visited = new HashSet<State>();
        Queue<State> q = new LinkedList<State>();
        q.add(new List<Integer>());

        int minSoFar = Integer.MAX_VALUE;
        while(q.size() > 0) {
            State current = q.poll();
            if(visited.contains(current)){
                visited.add(current);
            } else if(current.moves.size() < minSoFar) {
                if(peices.size() == 1) {
                    minSoFar = peices.moves.size();
                } else {
                    q.addAll(current.next());
                }
            }
        }

        System.out.println("ans: " + minSoFar + " time: " + ((System.nanoTime() - t) / pow(10,9)));
    }

    static boolean onGrid(int r, int c) {
        return r >= 0 && c >= 0 && r < R && c < C;
    }

    static class State {
        List<Integer> moves;
        List<Peice> peices;

        State(List<Peice> peices, List<Integer> moves) {
            this.peices = peices;
            this.moves = moves;
        }

        State(List<Peice> peices) {
            this(peices, new List<Integer>());
        }

        @Override
        public int hashCode() {
            return this.moves.hashCode();
        }

        @Override
        public boolean equals(State s) {
            return s.hashCode() == this.hashCode();
        }

        List<Integer> next() {
            for(Peice p: peices) {
                if()
            }
        }
    }

    static class Peice {
        int r,c;
        char type; // 'h' or 'k'

        Peice(int r, int c, char type) {
            this.r = r;
            this.c = c;
            this.type = type;
        }
    }
}
