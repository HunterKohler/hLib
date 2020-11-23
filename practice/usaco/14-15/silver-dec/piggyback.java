import java.io.*;
import java.util.*;

class piggyback {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("piggyback.in"));
        BufferedWriter bw = new BufferedWriter(new FileWriter("piggyback.out"));

        StringTokenizer st = new StringTokenizer(br.readLine());
        B = Integer.parseInt(st.nextToken());
        E = Integer.parseInt(st.nextToken());
        P = Integer.parseInt(st.nextToken());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());

        adj = new List<Integer>[N];
        for(int i = 0; i < N; i++)  {
            adj[i] = new ArrayList<Integer>();
        }

        for(int i = 0; i < M; i++) {
            st = new StringTokenizer(br.readLine());
            int v = Integer.parseInt(st.nextToken());
            int u = Integer.parseInt(st.nextToken());
            adj[v].add(u);
            adj[u].add(v);
        }

        int[]

    }

    static int B,E,P,N,M;
    static List<Integer>[] adj;

    static int[] dijkstras(int src) {
        PriorityQueue<Integer> pq = new PriorityQueue<Integer>();
        pq.add(src);
        boolean[] visited = new boolean[N];
        int[] dist = new int[N][N];
        for(int i = 0; i < n; i++)
            dist[i] = Integer.MAX_VALUE / 1000;
        dist[src] = 0;

        while(!pq.isEmpty()) {
            int v = pq.poll();
            if(!visited[v]) {
                visited[v] = true;
                for(int u: adj.get(v)) {
                    if(dist[u] + dist[u][v] < dist[src][u]) {
                        dist[v] = dist[src][u] + dist[u][v];
                        pq.add(u)
                    }
                }
            }
        }

        return dist;
    }
}
