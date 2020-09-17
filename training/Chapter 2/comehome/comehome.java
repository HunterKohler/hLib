/*
ID: jhunter3
LANG: JAVA
PROB: comehome
*/

import java.io.*;
import java.math.*;
import java.util.*;

class comehome {
    static int n = 52;
    static int e;
    static int[][] adj = new int[n][n];

    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(new File("./comehome.in"));

        int src = 'Z' - 'A';
        int[] dist = new int[n];
        ArrayList<Integer> unvisited = new ArrayList<Integer>();
        for(int i = 0; i < n;i++) {
            dist[i] = Integer.MAX_VALUE;
            unvisited.add(i);
            for(int j = 0; j < n; j++) {
                adj[i][j] = -1;
            }
        }

        e = sc.nextInt();
        sc.nextLine();
        for(int i = 0; i < e;i++) {
            String[] line = sc.nextLine().split(" ");
            // System.out.println(Arrays.toString(line));

            int a = translatedown(line[0].charAt(0));
            int b = translatedown(line[1].charAt(0));
            int w = Integer.parseInt(line[2]);

            if(a != b) {
                adj[a][b] = adj[a][b] == -1 ? w : Math.min(adj[a][b], w);
                adj[b][a] = adj[a][b];
            }
        }

        dist[src] = 0;
        boolean first = true;
        while(!unvisited.isEmpty()) {
            int v = unvisited.get(0);
            for(int u: unvisited) {
                v = dist[u] < dist[v] ? u : v;
            }
            unvisited.remove(Integer.valueOf(v));

            for(int u: unvisited) {
                if(adj[v][u] != -1) {
                    dist[u] = Math.min(dist[v] + adj[v][u], dist[u]);
                }
            }

            if(first) {
                first = false;
                // System.out.println(dist['d' - 'A'] + " " + ('d' - 'A'));
            }
        }

        int min = 0;
        for(int i = 0; i < 'Z' - 'A'; i++) {
            // System.out.println(i);
            min = dist[i] < dist[min] ? i : min;
        }
        // System.out.println(min);

        BufferedWriter bw = new BufferedWriter(new FileWriter("./comehome.out"));
        bw.write(String.format("%c %d\n", translateup(min), dist[min]));
        bw.close();
    }

    static int translatedown(int c) {
        if(c >= 'a') {
            return c - 'a' + 'Z' - 'A' + 1;
        } else {
            return c - 'A';
        }
    }

    static int translateup(int c) {
        if(c > 25) {
            return c + 'a' - 'Z' + 'A' - 1;
        } else {
            return c + 'A';
        }
    }
}
