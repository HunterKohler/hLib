/*
ID: jhunter3
LANG: JAVA
PROB: msquare
*/

import java.io.*;
import java.util.*;

class msquare {
    public static void main(String[] args) throws IOException {
        // long t = System.nanoTime();

        State end = new State((new BufferedReader(new FileReader("./msquare.in"))).readLine().split(" "));
        Set<Integer> hset = new HashSet<Integer>();

        Queue<State> q = new LinkedList<State>();
        q.add(new State());
        StringBuilder sb = new StringBuilder();
        while(q.size() != 0) {
            State s = q.poll();
            if(!hset.contains(s.hashCode())) {
                if(s.hashCode() == end.hashCode()) {
                    sb = new StringBuilder(s.transform);
                }

                q.add(s.copy().A());
                q.add(s.copy().B());
                q.add(s.copy().C());
                hset.add(s.hashCode());
            }
        }

        int i = 60;
        int tlength = sb.length();
        while(i < sb.length()) {
            sb.insert(i, "\n");
            i += 61;
        }

        BufferedWriter bw = new BufferedWriter(new FileWriter("./msquare.out"));
        bw.write(tlength + "\n" + sb.toString() + "\n");
        bw.close();
        // System.out.println("time: " + ((System.nanoTime() - t) / Math.pow(10,9)));
    }

    static class State {
        int[] pos = new int[8];
        String transform = "";

        State() {
            for(int i = 0; i < 8; i++)
                this.pos[i] = i;
        }

        State(int[] pos) {
            this.pos = pos;
        }

        State(String[] pos) {
            for(int i = 0; i < 8; i++)
                this.pos[i] = Integer.parseInt(pos[i]) - 1;
        }

        State(int[] pos, String transform) {
            this.pos = pos;
            this.transform = transform;
        }

        State copy() {
            return new State(this.pos, this.transform);
        }

        public int hashCode() {
            return Objects.hash(
                pos[0],
                pos[1],
                pos[2],
                pos[3],
                pos[4],
                pos[5],
                pos[6],
                pos[7]);
        }

        public boolean equals(State s) {
            return this.hashCode() == s.hashCode();
        }

        State A() {
            this.pos = new int[]{
                this.pos[7],
                this.pos[6],
                this.pos[5],
                this.pos[4],
                this.pos[3],
                this.pos[2],
                this.pos[1],
                this.pos[0]};
            this.transform += "A";
            return this;
        }

        State B() {
            this.pos = new int[]{
                this.pos[3],
                this.pos[0],
                this.pos[1],
                this.pos[2],
                this.pos[5],
                this.pos[6],
                this.pos[7],
                this.pos[4]};
            this.transform += "B";
            return this;
        }

        State C() {
            this.pos = new int[]{
                this.pos[0],
                this.pos[6],
                this.pos[1],
                this.pos[3],
                this.pos[4],
                this.pos[2],
                this.pos[5],
                this.pos[7]};
            this.transform += "C";
            return this;
        }
    }
}
