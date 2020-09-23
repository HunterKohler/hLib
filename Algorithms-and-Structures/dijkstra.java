import java.util.*;
import java.io.*;
import java.math.*;

class Dijkstra {
    int[] dijkstraSquare(int n, int e, int[][] adj, int src) { // n^2 implementation
        int[] dist = new int[n];
        ArrayList<Integer> unvisited = new ArrayList<Integer>();

        for(int i = 0; i < n; i++) {
            dist[i] = Integer.MAX_VALUE;
            unvisited.add(i);
        }

        dist[src] = 0;

        while(!unvisited.isEmpty()) {
            int a = unvisited.get(0);
            for(int b: unvisited) {
                if(dist[b] < dist[a]) {
                    a = b;
                }
            }

            for(int b: unvisited) {
                if(adj[a][b] != 0) {
                    dist[b] = Math.min(dist[b], dist[a] + adj[a][b]);
                }
            }

            unvisited.remove(Integer.valueOf(a));
        }

        return dist;
    }

    int[] dijkstraHeap(int n, int e, List<int[]>[] edgeList, int src) {
        int[] dist = new int[n];
        for(int i = 0; i < n; i++)
            dist[i] = Integer.MAX_VALUE;

        dist[src] = 0;
        PriorityQueue<Integer> pq = new PriorityQueue<Integer>((Integer v, Integer u) -> dist[v] - dist[u]);
        pq.add(src);
        while(!pq.isEmpty()) {
            int v = pq.poll();

            for(int[] edge: edgeList[v]) {
                int u = edge[0];
                int w = edge[1];

                if(dist[u] > dist[v] + w) {
                    dist[u] = dist[v] + w;
                    pq.add(u);
                }
            }
        }

        return dist;
    }
}
