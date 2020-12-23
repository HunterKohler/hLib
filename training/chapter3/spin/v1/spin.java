/*
ID: jhunter3
LANG: JAVA
PROB: spin
*/

import java.util.*;
import java.io.*;

class spin {
    static final int TWOPI = 360;

    static boolean nonblocking(Wheel[] wheels, int t) {
        for(int i = 0; i < TWOPI; i++) {
            for(int j = 0; j < TWOPI; i++) {
                boolean open = wheels[0].getOpen(i,j,t);
                for(Wheel w: wheels)
                    if(open != w.getOpen(i,j,t))
                        return false;
            }
        }
        return true;
    }

    static int hash(Wheel[] wheels, int t) {
        return Objects.hash( wheels[0].pos(t),
                             wheels[1].pos(t),
                             wheels[2].pos(t),
                             wheels[3].pos(t),
                             wheels[4].pos(t) ) ;
    }

    static boolean blocking(Wheel[] wheels, int t) {
        return !nonblocking(wheels, t);
    }

    public static void main(String[] args) throws IOException {
        long t0 = System.nanoTime();

        BufferedReader br = new BufferedReader(new FileReader("./spin.in"));

        int n = 5;
        Wheel[] wheels = new Wheel[5];
        for(int i = 0; i < n; i++)
            wheels[i] = new Wheel(br.readLine());

        System.out.println(hash(wheels,0));
        System.out.println(hash(wheels,1));

        int t = 0;
        boolean none = false;
        Set<Integer> visited = new HashSet<Integer>();
        while(blocking(wheels, t)) {
            if(visited.contains(hash(wheels,t))) {
                none = true;
                break;
            }
            t++;
            visited.add(hash(wheels,t));
        }

        // System.out.println((none ? "none" : t));
        BufferedWriter bw = new BufferedWriter(new FileWriter("./spin.out"));
        bw.write((none ? "none" : t) + "\n");
        bw.close();

        System.out.println(visited);

        System.out.println("runtime: " + ((System.nanoTime() - t0) / Math.pow(10,9)));
    }

    static class Wheel {
        int s;
        boolean[][] open = new boolean[TWOPI][TWOPI];
        int[][] wedges; // [start, end]
        int w;

        Wheel(String str) {
            StringTokenizer st = new StringTokenizer(str);
            this.s = Integer.parseInt(st.nextToken());
            this.w = Integer.parseInt(st.nextToken());
            this.wedges = new int[this.w][2];
            for(int i = 0; i < this.w;i++) {
                int start = Integer.parseInt(st.nextToken());
                int end = start + Integer.parseInt(st.nextToken());
                this.wedges[i] = new int[]{start, end};
                for(int a = start; a <= end; a++)
                    for(int b = start; b <= end; b++)
                        this.setOpen(a,b,true);
            }
        }

        void setOpen(int i, int j, boolean val) {
            this.open[Math.floorMod(i, TWOPI)][Math.floorMod(j, TWOPI)] = val;
        }

        boolean getOpen(int i, int j, int t) {
            i = Math.floorMod((i - (this.s * t)), TWOPI);
            j = Math.floorMod((j - (this.s * t)), TWOPI);
            return this.open[i][j];
        }

        int pos(int t) {
            return this.s * t;
        }
    }

}
