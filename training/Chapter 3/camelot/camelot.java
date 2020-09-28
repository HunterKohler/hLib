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
    static int R;
    static int C;

    public static void main(String[] args) throws IOException {
        long t = System.nanoTime();

        BufferedReader br = new BufferedReader(new FileReader("./camelot.in"));
        StringTokenizer st = new StringTokenizer(br.readLine());
        R = parseInt(st.nextToken());
        C = parseInt(st.nextToken());
        List<Peice> peices = new ArrayList<Peice>();
        boolean first = true;
        String line;
        while((line = br.readLine()) != null) {
            st = new StringTokenizer(line);
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
        q.add(new State(peices));

        int minSoFar = Integer.MAX_VALUE;
        while(q.size() > 0) {
            State current = q.poll();
            if(visited.contains(current)){
                visited.add(current);
            } else if(current.moves.size() < minSoFar) {
                if(peices.size() == 1) {
                    minSoFar = current.moves.size();
                } else {
                    q.addAll(current.next());
                }
            }
        }

        BufferedWriter bw = new BufferedWriter(new FileWriter("./camelot.out"));
        bw.write(minSoFar);
        bw.close();

        System.out.println("ans: " + minSoFar + " time: " + ((System.nanoTime() - t) / pow(10,9)));
    }

    static boolean onGrid(int r, int c) {
        return r >= 0 && c >= 0 && r < R && c < C;
    }

    static boolean onGrid(Point p) {
        return onGrid(p.r,p.c);
    }

    static class State {
        List<Point> moves;
        Map<Point,Peice> board;

        State(List<Peice> peices) {
            this.moves = new ArrayList<Point>();
            this.board = new HashMap<Point, Peice>();
            for(Peice peice: peices) {
                this.board.put(peice.p, peice);
            }
        }

        State(List<Point> moves, Map<Point,Peice> board) {
            this.moves = moves;
            this.board = board;
        }

        @Override
        public int hashCode() {
            return this.moves.hashCode();
        }

        public boolean equals(State s) {
            return s.hashCode() == this.hashCode();
        }

        List<State> next() {
            List<State> states = new ArrayList<State>();
            for(Map.Entry<Point,Peice> entry: this.board.entrySet()) {
                states.addAll(this.move(entry.getValue()));
            }
            return states;
        }

        List<State> move(Peice peice) {
            List<State> states = new ArrayList<State>();
            for(Point p: peice.moveSet()) {
                if(onGrid(p)) {
                    State s = this.copy();

                    if(s.board.keySet().contains(p) && peice.type != 'k') {
                        s.board.remove(peice.p);
                    } else {
                        s.board.remove(peice.p);
                        if(s.board.get(p).type != 'k') {
                            s.board.put(p, peice.copy(p));
                        };
                        s.moves.add(peice.p);
                        s.moves.add(p);
                        states.add(s);
                    }
                }
            }

            return states;
        }

        State copy() {
            return new State(this.moves, this.board);
        }
    }

    static class Peice {
        Point p;
        char type; // 'h' or 'k'

        Peice(int r, int c, char type) {
            this.p = new Point(r,c);
            this.type = type;
        }

        List<Point> moveSet() {
            List<Point> ret = new ArrayList<Point>();
            switch(this.type) {
                case 'h':
                    ret.add(this.p.moveCopy(1,2));
                    ret.add(this.p.moveCopy(-1,2));
                    ret.add(this.p.moveCopy(1,-2));
                    ret.add(this.p.moveCopy(-1,-2));
                    ret.add(this.p.moveCopy(2,1));
                    ret.add(this.p.moveCopy(-2,1));
                    ret.add(this.p.moveCopy(2,-1));
                    ret.add(this.p.moveCopy(-2,-1));
                    break;
                case 'k':
                    ret.add(this.p.moveCopy(1,0));
                    ret.add(this.p.moveCopy(-1,0));
                    ret.add(this.p.moveCopy(0,1));
                    ret.add(this.p.moveCopy(0,-1));
                    ret.add(this.p.moveCopy(1,1));
                    ret.add(this.p.moveCopy(-1,1));
                    ret.add(this.p.moveCopy(1,-1));
                    ret.add(this.p.moveCopy(-1,-1));
                    break;
            }

            return ret;
        }

        Peice copy(Point p) {
            return new Peice(p.r, p.c, this.type);
        }
        Peice copy() {
            return new Peice(this.p.r, this.p.c, this.type);
        }
    }

    static class Point {
        int r,c;

        Point(int r, int c) {
            this.r = r;
            this.c = c;
        }

        Point moveCopy(int addr,int addc) {
            return new Point(this.r + addr, this.c + addc);
        }
    }
}
