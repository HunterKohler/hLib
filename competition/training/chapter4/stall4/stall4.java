/*
ID: jhunter3
LANG: JAVA
TASK: stall4
*/

package competition.training.chapter4.stall4;

import java.io.*;
import java.util.*;

class stall4 {
    static final int INF = Integer.MAX_VALUE / 1000;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("stall4.in"));
        BufferedWriter bw = new BufferedWriter(new FileWriter("stall4.out"));
        StringTokenizer st = new StringTokenizer(br.readLine());

        int N = Integer.parseInt(st.nextToken());
        int M = Integer.parseInt(st.nextToken());
        int V = N + M + 2;

        List<List<Integer>> adj = new ArrayList<List<Integer>>();
        for(int i = 0; i < V; i++)
            adj.add(new ArrayList<Integer>());
        int[][] capacity = new int[V][V];
        int s = V - 2;
        int t = V - 1;

        for(int u = 0; u < N;u++) {
            capacity[s][u] = 1;
            adj.get(s).add(u);
            adj.get(u).add(s);
        }

        for(int u = N; u < N + M; u++) {
            capacity[u][t] = 1;
            adj.get(u).add(t);
            adj.get(t).add(u);
        }

        for(int u = 0; u < N; u++) {
            st = new StringTokenizer(br.readLine());
            st.nextToken();
            while(st.hasMoreTokens()){
                int v = Integer.parseInt(st.nextToken()) + N - 1;
                capacity[u][v] = 1;
                adj.get(u).add(v);
                adj.get(v).add(u);
            }
        }

        int flow, totalFlow = 0;
        int[] parent = new int[V];
        while((flow = bfs(parent,adj,capacity,s,t)) != 0) {
            totalFlow += flow;
            System.out.println(Arrays.toString(parent));
            for(int u = t; u != s; u = parent[u]) {
                capacity[u][parent[u]] += flow;
                capacity[parent[u]][u] -= flow;
            }
        }

        bw.write(totalFlow + "\n");
        bw.close();
    }

    static int bfs(int[] parent,List<List<Integer>> adj, int[][] capacity, int s, int t) {
        Arrays.fill(parent, -1);

        Queue<int[]> q = new LinkedList<int[]>();
        q.add(new int[]{s,INF});

        while(!q.isEmpty()) {
            int u = q.peek()[0];
            int flow = q.poll()[1];

            for(int v: adj.get(u)) {
                if(capacity[u][v] > 0 && v != s && parent[v] == -1) {
                    parent[v] = u;
                    int newFlow = Math.min(flow, capacity[u][v]);
                    if(v == t) {
                        return newFlow;
                    } else {
                        q.add(new int[]{v,newFlow});
                    }
                }
            }
        }

        return 0;
    }
}
