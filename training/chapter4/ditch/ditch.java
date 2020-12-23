/*
ID: jhunter3
LANG: java
TASK: ditch
*/

import java.io.*;
import java.util.*;

class ditch {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("ditch.in"));
        BufferedWriter bw = new BufferedWriter(new FileWriter("ditch.out"));

        StringTokenizer st = new StringTokenizer(br.readLine());
        E = nextInt(st);
        N = nextInt(st);
        sink = N - 1;

        adj = new int[N][N];
        for(int i = 0; i < E; i++) {
            st = new StringTokenizer(br.readLine());
            adj[nextInt(st) - 1][nextInt(st) - 1] = nextInt(st);
        }

        while(true) {
            int[] parent = new int[N];
            for(int i = 0; i < N; i++)
                parent[i] = -1;

            Queue<Integer> q = new LinkedList<Integer>();
            q.add(source);

            while(!q.isEmpty()) {
                int u = q.poll();
                for(int v = 0; v < N; v++) {
                    if(parent[v] == -1 && v != source && adj[u][v] != 0) {
                        parent[v] = u;
                        q.add(v);
                    }
                }
            }

            if(parent[sink] == -1)
                break;
            else {
                int flow = INF;

                for(int v = sink, u = parent[sink]; u != -1; u = parent[v]) {
                    flow = Math.min(flow, adj[u][v]);
                    v = u;
                }

                for(int v = sink, u = parent[sink]; u != -1; u = parent[v]) {
                    adj[u][v] -= flow;
                    adj[v][u] += flow;
                    v = u;
                }

                total_flow += flow;
            }
        }

        bw.write(total_flow + "\n");
        bw.close();
    }

    static int nextInt(StringTokenizer st) { return Integer.parseInt(st.nextToken()); }

    static int E,N,sink,
        INF = Integer.MAX_VALUE / 10,
        total_flow = 0,
        source = 0;
    static int[][] adj;
}
