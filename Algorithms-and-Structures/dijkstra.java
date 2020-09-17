import java.util.*;
import java.io.*;
import java.math.*;

class Dijkstra {
    static int n, e, src;
    static int[] dist;
    static int[][] adj;
    static ArrayList<Integer> unvisited;

    public static void main(String[] args) throws IOException { // implemented at O(V^3)
        Scanner sc = new Scanner(new File("./dijkstra.in"));

        n = sc.nextInt();
        e = sc.nextInt();
        src = sc.nextInt();

        dist = new int[n];
        unvisited = new ArrayList<Integer>();
        adj = new int[n][n];

        for(int i = 0; i < n; i++) {
            dist[i] = Integer.MAX_VALUE;
            unvisited.add(i);

            for(int j = 0; j < n;j++) {
                adj[i][j] = -1;
            }
        }

        for(int i = 0; i < e; i++) {
            int a = sc.nextInt();
            int b = sc.nextInt();
            int w = sc.nextInt();

            adj[a][b] = w;
            adj[b][a] = w;
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
                if(adj[a][b] != -1) {
                    System.out.printf("%d %d\n", a,b);
                    dist[b] = Math.min(dist[b], dist[a] + adj[a][b]);
                }
            }

            unvisited.remove(Integer.valueOf(a));
        }

        System.out.println(Arrays.toString(dist));
    }
}
