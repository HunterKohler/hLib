/*
ID: jhunter3
LANG: JAVA
PROB: butter
*/

import java.io.*;
import java.util.*;

class butter {
    public static void main(String[] args) throws IOException {
        // long t = System.nanoTime();

        BufferedReader br = new BufferedReader(new FileReader("./butter.in"));
        StringTokenizer st = new StringTokenizer(br.readLine());

        int n = Integer.parseInt(st.nextToken()); // num of cows
        int p = Integer.parseInt(st.nextToken()); // num of nodes
        int c = Integer.parseInt(st.nextToken()); // num of edges

        int[] cows = new int[n];
        for(int i = 0; i < n;i++)
            cows[i] = Integer.parseInt(br.readLine()) - 1;

        List<int[]>[] edgeList = new List[p];
        for(int j = 0; j < p;j++)
            edgeList[j] = new ArrayList<int[]>();

        for(int i = 0; i < c;i++) {
            st = new StringTokenizer(br.readLine());
            int v = Integer.parseInt(st.nextToken()) - 1;
            int u = Integer.parseInt(st.nextToken()) - 1;
            int w = Integer.parseInt(st.nextToken());

            edgeList[v].add(new int[]{u,w});
            edgeList[u].add(new int[]{v,w});
        }

        int[] distsum = new int[p];
        boolean[] reachable = new boolean[p];
        Arrays.fill(reachable, true);
        for(int v: cows){
            int[] dist = dijkstra(p, edgeList, v);
            for(int i = 0; i < p ;i++) {
                if(dist[i] == Integer.MAX_VALUE)
                    reachable[i] = false;
                distsum[i] += dist[i];
            }
        }

        int min = Integer.MAX_VALUE;
        for(int i = 0; i < p;i++)
            if(reachable[i])
                min = Math.min(min, distsum[i]);

        BufferedWriter bw = new BufferedWriter(new FileWriter("./butter.out"));
        bw.write(min + "\n");
        bw.close();

        // System.out.printf("min: %d, time: %f s\n", min, (System.nanoTime() - t) / Math.pow(10,9));
    }

    static int[] dijkstra(int n, List<int[]>[] edgeList, int src) {
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

    static int[] sum(int[] a, int[] b) {
        for(int i = 0; i < a.length; i++)
            a[i] += b[i];
        return a;
    }
}
