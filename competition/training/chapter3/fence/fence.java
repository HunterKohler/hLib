/*
ID: jhunter3
LANG: JAVA
PROB: fence
*/

package competition.training.chapter3.fence;

import java.io.*;
import java.util.*;

import static java.lang.Math.*;

public class fence {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("./fence.in"));

        E = Integer.parseInt(br.readLine());
        adj = new ArrayList[501];
        nodes = new HashSet<Integer>();
        for(int i = 0; i < E; i++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int v = Integer.parseInt(st.nextToken());
            int u = Integer.parseInt(st.nextToken());

            if(adj[v] == null)
                adj[v] = new ArrayList<Integer>();
            if(adj[u] == null)
                adj[u] = new ArrayList<Integer>();

            adj[v].add(u);
            adj[u].add(v);

            nodes.add(v);
            nodes.add(u);
        }

        int start = Integer.MAX_VALUE;
        for(int i: nodes)
            if(adj[i].size() % 2 != 0)
                start = Math.min(i, start);

        if(start == Integer.MAX_VALUE) {
            for(int i : nodes) {
                start = i;
                break;
            }
        }

        // System.out.println("start: " + start);

        path = new ArrayList<Integer>();
        findPath(start);

        BufferedWriter bw = new BufferedWriter(new FileWriter("./fence.out"));
        // System.out.println("ans:");
        for(int i = path.size() - 1; i >= 0; i--) {
            bw.write(path.get(i) + "\n");
            // System.out.println(path.get(i));
        }
        bw.close();
    }

    static int E;
    static List<Integer>[] adj;
    static Set<Integer> nodes;

    static List<Integer> path;
    static void findPath(int v) {
        while(adj[v].size() > 0) {
            int minU = Collections.min(adj[v]);
            adj[v].remove(Integer.valueOf(minU));
            adj[minU].remove(Integer.valueOf(v));
            findPath(minU);
        }

        path.add(v);
    }
}
