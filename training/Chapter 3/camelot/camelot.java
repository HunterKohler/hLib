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
    static int inf = Integer.MAX_VALUE / 1000;

    static int[] di = new int[] {1,1,-1,-1,2,2,-2,-2};
    static int[] dj = new int[] {2,-2,2,-2,1,-1,1,-1};

    static int[] king;
    static int I,J;

    public static void main(String[] args) throws IOException {
        long t0 = System.nanoTime();

        BufferedReader br = new BufferedReader(new FileReader("camelot.in"));
        BufferedWriter bw = new BufferedWriter(new FileWriter("camelot.out"));

        StringTokenizer st = new StringTokenizer(br.readLine());
        J = parseInt(st.nextToken()); // R
        I = parseInt(st.nextToken()); // C

        st = new StringTokenizer(br.readLine());
        king = parsePiece(st.nextToken(), st.nextToken());

        int[][] dsum = new int[I][J];
        int[][] mindelta = new int[I][J];
        int[][] minind = new int[I][J];

        for(int i = 0; i < I; i++)
        for(int j = 0; j < J; j++) {
            dsum[i][j] = inf;
            for(int k = 0; k < I*J;k++)
                mindelta[i][j] = inf;
        }

        int z = 0;
        int ind = 0;
        String line;
        while((line = br.readLine()) != null) {
            st = new StringTokenizer(line);
            while(st.hasMoreTokens()) {
                int[] k = parsePiece(st.nextToken(), st.nextToken());
                int[][][] dist = new int[I][J][2];
                for(int i = 0; i < I; i++)
                for(int j = 0; j < J; j++) {
                    dist[i][j] = new int[]{inf,inf};
                }

                // bfs
                Queue<int[]> q = new LinkedList<int[]>();
                q.add(new int[]{k[0], k[1], 0, 0});
                // {i,j, haspickedup, dist}

                boolean[][][] visited = new boolean[I][J][2];
                while(!q.isEmpty()) {
                    int i = q.peek()[0];
                    int j = q.peek()[1];
                    int p = q.peek()[2];
                    int d = q.poll()[3];

                    // System.out.println(i + " " + j + " " + p);
                    if(d < dist[i][j][p]) {
                        dist[i][j][p] = d;

                        if(p == 0) {
                            dist[i][j][p] = d;
                            if(dsum[i][j] == inf) {
                                dsum[i][j] = d;
                            } else {
                                dsum[i][j] += d;
                            }
                        } else {
                            int delta = d - dist[i][j][p];

                            if(delta < mindelta[i][j]) {
                                mindelta[i][j] = delta;
                                minind[i][j] = ind;
                            }
                        }

                        for(int n = 0; n < 8 ;n++) {
                            if(p == 0) {
                                q.add(new int[]{i,j,1,d+kdist(i,j)});
                            }

                            if(inGrid(i+di[n],j+dj[n])) {
                                q.add(new int[]{i+di[n],j+dj[n],p,d+1});
                            }
                        }
                    }
                }
                ind++;
            }
        }

        int tmin = inf;
        int[] end = new int[2];
        for(int i = 0; i < I; i++)
        for(int j = 0; j < J; j++) {
            mindelta[i][j] = min(mindelta[i][j], kdist(i,j));
            if(dsum[i][j] + mindelta[i][j] < tmin) {
                end = new int[]{i,j};
            }

            tmin = min(tmin, dsum[i][j] + mindelta[i][j]);
        }

        // System.out.println(Arrays.toString(end));
        // System.out.println(tmin);
        bw.write(tmin + "\n");
        bw.close();

        // System.out.println("time: " + (System.nanoTime() - t0) / 10e9);
    }

    static boolean inGrid(int i, int j) {
        return 0 <= i && i < I && 0 <= j && j < J;
    }

    static int[] parsePiece(String i, String j) {
        return new int[]{i.charAt(0) - 'A', parseInt(j) - 1};
    }

    static String toPiece(int i, int j) {
        return ((char) i) + " " + (j + 1);
    }

    static int kdist(int i, int j) {
        return max(abs(i - king[0]), abs(j - king[1]));
    }
}
