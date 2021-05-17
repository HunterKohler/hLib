// Formerly part of competition-library

package lib.algorithms;

import java.util.*;
import lib.data_structures.DisjointSet;

public class Kruskals {
    static int[][] span(int n, int[][] edges) {
        int[][] adj = new int[n][n];

        PriorityQueue<int[]> pq = new PriorityQueue<int[]>((int[] u, int[] v) -> {
            return u[2] < v[2] ? -1 : 1;
        });

        for(int[] edge: edges)
            pq.add(edge);

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
        int n = 4;
        int[][] edges = new int[][]{{0, 1, 1}, {0, 2, 1}, {0,3,1}};
        int[][] spantree = span(n, edges);

        for(int j = 0; j < n;j++) {
            for(int i = 0; i < n;i++) {
                System.out.print(spantree[i][j] + ", ");
            }
            System.out.println();
        }
    }
}
