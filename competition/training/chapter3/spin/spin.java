/*
ID: jhunter3
LANG: JAVA
PROB: spin
*/

package competition.training.chapter3.spin;

import java.util.*;
import java.io.*;
import java.math.*;

class spin {
    static int TWOPI = 360;
    static int cMod(int i) { return Math.floorMod(i,TWOPI); }

    public static void main(String[] args) throws IOException {
        long t0 = System.nanoTime();

        BufferedReader br = new BufferedReader(new FileReader("./spin.in"));

        Wheel[] wheels = new Wheel[5];
        for(int i = 0; i < 5; i++)
            wheels[i] = new Wheel(i, br.readLine());

        int t = 0;
        boolean none = false;
        Set<Integer> visited = new HashSet<Integer>();
        while(true) {
            int h = hash(wheels, t);
            if(visited.contains(h)) {
                none = true;
                break;
            }

            boolean breaker = false;
            for(int i: wheels[0].open) {
                int iadj = cMod(wheels[0].pos(t) + i);
                boolean pass = true;
                for(Wheel v: wheels)
                    if(!v.isOpen(iadj, t)){
                        pass = false;
                        break;
                    }
                if(pass){
                    breaker = true;
                    break;
                }
            }

            if(breaker)
                break;

            visited.add(h);
            t++;
        }

        BufferedWriter bw = new BufferedWriter(new FileWriter("./spin.out"));
        bw.write((none ? "none" : t) + "\n");
        bw.close();

        // System.out.println("t: " + (none ? "none " + t: t));
        // System.out.println("time: " + ((System.nanoTime() - t0) / Math.pow(10,9)));
    }

    static int hash(Wheel[] wheels, int t) {
        return Objects.hash( wheels[0].pos(t),
                             wheels[1].pos(t),
                             wheels[2].pos(t),
                             wheels[3].pos(t),
                             wheels[4].pos(t) );
    }

    static class Wheel {
        int index, w, s;
        int[][] wedges; // [start, length];
        Set<Integer> open = new HashSet<Integer>();

        Wheel(int index, String args) {
            StringTokenizer st = new StringTokenizer(args);
            this.index = index;
            this.s = Integer.parseInt(st.nextToken());
            this.w = Integer.parseInt(st.nextToken());
            this.wedges = new int[w][2];

            for(int i = 0; i < w; i++){
                int a = Integer.parseInt(st.nextToken());
                int d = Integer.parseInt(st.nextToken());

                this.wedges[i] = new int[]{a,d};
                for(int j = a; j <= a + d; j++)
                    this.open.add(cMod(j));
            }
        }

        int pos(int t) {
            return cMod(this.s * t);
        }

        boolean isOpen(int a, int t) {
            a = cMod(a - this.pos(t));
            return open.contains(a);
        }

        int[] wedgeRange(int i, int t) {
            return new int[] {
                cMod(this.wedges[i][0] + this.pos(t)),
                cMod(this.wedges[i][0] + this.wedges[i][1] + this.pos(t))
            };
        }
    }
}
