/*
ID: jhunter3
LANG: JAVA
TASK: ditch
*/

import java.io.*;
import java.util.*;

class ditch {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("ditch.in"));
        BufferedWriter bw = new BufferedWriter(new FileWriter("ditch.out"));
        StringTokenizer st = new StringTokenizer(br.readLine());

        E = Integer.parseInt(st.nextToken());
        N = Integer.parseInt(st.nextToken());
        t = N - 1;

        capacity = new int[N][N];
        for(int i = 0; i < N; i++)
            adj.add(new ArrayList<Integer>());

        for(int i = 0; i < E; i++) {
            st = new StringTokenizer(br.readLine());
            int u = Integer.parseInt(st.nextToken()) - 1;
            int v = Integer.parseInt(st.nextToken()) - 1;
            capacity[u][v] += Integer.parseInt(st.nextToken());
            adj.get(u).add(v);
            adj.get(v).add(u);
        }

        int totalFlow = 0, flow;
        int[] parent = new int[N];
        while((flow = bfs(parent)) != 0) {
            for(int u = t; u != s; u = parent[u]) {
                capacity[parent[u]][u] -= flow;
                capacity[u][parent[u]] += flow;
            }
            totalFlow += flow;
        }

        System.out.println(totalFlow);
        bw.write(totalFlow + "\n");
        bw.close();
    }

    static int E, N, INF = Integer.MAX_VALUE / 100, s = 0, t;
    static int[][] capacity;
    static List<List<Integer>> adj = new ArrayList<List<Integer>>();

    static int bfs(int[] parent) {
        Arrays.fill(parent,-1);
        Queue<int[]> q = new LinkedList<int[]>();
        q.add(new int[]{0,INF});

        while(!q.isEmpty()) {
            int u = q.peek()[0];
            int flow = q.poll()[1];

            for(int v: adj.get(u)) {
                if(parent[v] == -1 && v != s && capacity[u][v] > 0) {
                    int newFlow = Math.min(flow,capacity[u][v]);
                    parent[v] = u;
                    if(v == t) {
                        return newFlow;
                    }
                    q.add(new int[]{v, newFlow});
                }
            }
        }
        return 0;
    }
}
