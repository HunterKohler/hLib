/*
ID: jhunter3
LANG: JAVA
PROG: butter
*/

import java.util.*;
import java.io.*;

class butter {
    public static void main(String[] args) throws IOException {
        // long t = System.nanoTime();

        BufferedReader br = new BufferedReader(new FileReader("./butter.in"));
        StringTokenizer st = new StringTokenizer(br.readLine());

        int n = Integer.parseInt(st.nextToken());
        int p = Integer.parseInt(st.nextToken());
        int c = Integer.parseInt(st.nextToken());

        int[] pos = new int[n];
        int[][] adj = new int[p][p];
        for(int i = 0; i < n;i++)
            pos[i] = Integer.parseInt(br.readLine()) - 1;

        for(int i = 0; i < p; i++)
        for(int j = 0; j < p; j++)
            if(i != j)
                adj[i][j] = Integer.MAX_VALUE;

        for(int i = 0; i < c; i++) {
            st = new StringTokenizer(br.readLine());
            int a = Integer.parseInt(st.nextToken()) - 1;
            int b = Integer.parseInt(st.nextToken()) - 1;
            int w = Integer.parseInt(st.nextToken());

            adj[a][b] = w;
            adj[b][a] = w;
        }

        adj = floyd(adj);

        int min = Integer.MAX_VALUE;
        for(int i = 0; i < p; i++) {
            int sum = 0;
            boolean reachable = true;
            for(int j: pos){
                if(adj[i][j] == Integer.MAX_VALUE){
                    reachable = false;
                    break;
                }
                sum += adj[i][j];
            }
            if(reachable)
                min = Math.min(min, sum);;
        }

        for(int i = 0; i < p;i++) {
            System.out.println(Arrays.toString(adj[i]));
        }

        BufferedWriter bw = new BufferedWriter(new FileWriter("./butter.out"));
        bw.write(min + "\n");
        bw.close();

        // System.out.println(min);
        // System.out.println("time: " + ((System.nanoTime() - t) / Math.pow(10,9)));
    }

    static int[][] floyd(int[][] adj) {
        int p = adj.length;

        for(int i = 0; i < p; i++)
        for(int j = 0; j < p; j++)
        for(int k = 0; k < p; k++)
            if(adj[i][k] != Integer.MAX_VALUE && adj[k][j] != Integer.MAX_VALUE)
                adj[i][j] = Math.min(adj[i][j], adj[i][k] + adj[k][j]);

        return adj;
    }
}
