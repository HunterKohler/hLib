/*
ID: jhunter3
LANG: JAVA
PROB: inflate
*/

import java.io.*;
import java.util.*;
import java.math.*;

class inflate {
    public static void main(String[] args) throws IOException {
        long t = System.nanoTime();

        StringTokenizer st;
        BufferedReader br;
        BufferedWriter bw;

        br = new BufferedReader(new FileReader("./inflate.in"));
        st = new StringTokenizer(br.readLine());

        int m = Integer.parseInt(st.nextToken());
        int n = Integer.parseInt(st.nextToken());
        PriorityQueue<Problem> pq =
            new PriorityQueue<Problem>((Problem p, Problem q) -> {
                return p.density > q.density ? -1 : 1;
            });

        for(int i = 0; i < n; i++) {
            st = new StringTokenizer(br.readLine());
            pq.add(new Problem(st.nextToken(), st.nextToken(), i + 1));
        }

        // System.out.println(pq);

        int max = 0;
        while(!pq.isEmpty()) {
            Problem head = pq.peek();
            if(m >= head.minutes) {
                m -= head.minutes;
                max += head.points;
                System.out.println(head.i);
            } else {
                pq.poll();
            }
        }
        //
        System.out.println("max: " + max);
        System.out.println("time: " + ((System.nanoTime() - t) / Math.pow(10,9)));

        bw = new BufferedWriter(new FileWriter("./inflate.out"));
        bw.write(max + "\n");
        bw.close();
    }

    static class Problem {
        int points, minutes, i;
        double density;
        Problem(int points, int minutes, int i) {
            this.points = points;
            this.minutes = minutes;
            this.density = ((double) this.points) / ((double) this.minutes);
            this.i = i;
        }

        Problem(String points, String minutes, int i){
            this(Integer.parseInt(points), Integer.parseInt(minutes), i);
        }

        public String toString() {
            return String.format("%.2f", this.density);
        }
    }
}
