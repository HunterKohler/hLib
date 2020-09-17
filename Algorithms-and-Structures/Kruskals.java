import java.util.*;
import java.io.*;


public class Kruskals {
    static int[][] span(int n, int[][] edges) {
        int[][] adj = new int[n][n];

        PriorityQueue<int[]> pq = new PriorityQueue<int[]>((int[] u, int[] v) -> {
            return u[2] < v[2] ? -1 : 1;
        });

        DisjointSet dset = new DisjointSet(n);
        while(!pq.isEmpty()) {
            int a = pq.peek()[0];
            int b = pq.peek()[1];
            int w = pq.poll()[2];

            if(dset.root(a) != dset.root(b)) {
                dset.union(a,b);
                adj[a][b] = w;
                adj[b][a] = w;
            }
        }

        return adj;
    }

    public static void main(String[] args) {
        int n = 3;
        int[][] edges = new int[][]{{0,1,1}, {1,2,1}, {1,2,3}};
        int[][] spantree = span(n, edges);

        for(int j = 0; j < n;j++) {
            for(int i = 0; i < n;i++) {
                System.out.print(spantree[i][j] + ", ");
            }
            System.out.println();
        }
    }
}
