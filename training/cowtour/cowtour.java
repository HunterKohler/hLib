import java.util.*;
import java.io.*;
import java.math.*;

class cowtour {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("./cowtour.in"));

        int n = Integer.parseInt(br.readLine());
        double[][] loc = double[n][2];
        double[][] planeDist = double[n][n];
        boolean[][] adj = new boolean[n][n];
        List<List<Integer>> parts = new ArrayList<List<Integer>>();

        for(int i = 0; i < n; i++) {
            String[] line = br.readLine().split(" ");
            loc[0] = Integer.parseInt(line[0]);
            loc[1] = Integer.parseInt(line[1]);
        }

        for(int j = 0; j < n;j++) {
            String[] line = br.readLine().split("");
            for(int i = 0; i < n;i++) {
                adj[i][j] = line[i].equals("1");
                planedist[i][j] = distance(loc[i], loc[j]);
            }
        }

        List<List> parts = partition(adj);
        double[][] graphDist = floyd(adj, planeDist);

        List<Integer> diameters = new ArrayList<Integer>();
        for(List part: parts) {
            int max = 0;

            for(int i: part) {
                for(int j: part){
                    max = Math.max(max, graphDist[i][j])
                }
            }

            diameters.add(max);
        }

    }

    static List<List> partition(boolean[][]) {
        boolean[] visited = new boolean[];
        List<List> parts = new List<List>();
        for(int i = 0; i < n; i++) {
            if(visited[i]) { continue; }
            List<Integer> part = new ArrayList<Integer>();
            Queue<Integer> q = new Queue<Integer>();


            while(!q.isEmpty()) {
                int head = q.pop();
                if(visited[head]) { continue; }
                visited[head] = true;

                for(int j = 0; j < n;j++) {
                    if(adj[head][j]) {
                        queue.add(j);
                    }
                }
            }
        }
    }

    static double distance(double[] p, double[] q) {
        return Math.sqrt(Math.pow(p[0] - q[0], 2) + Math.pow(p[1] - p[0], 2));
    }

    static double[][] floyd(boolean[][] adj, double[][] planeDist) {
        int n = adj.length;
        double[][] graphDist = new double[][];

        for(int i = 0; i < n;i++) {
            for(int j = 0; j < n;j++) {
                if(i == j) {
                    graphDist[i][j] = 0;
                } else if(adj[i][j]) {
                    graphDist[i][j] = planeDist[i][j]
                } else {
                    graphDist[i][j] = Integer.MAX_VALUE;
                }
            }
        }

        for(int i =0 ; i < n;i++) {
            for(int j =0 ; j < n;j++) {
                for(int k = 0; k < n;k++) {
                    if( graphDist[i][k] != Integer.MAX_VALUE && graphDist[k][j] != Integer.MAX_VALUE ) {
                        graphDist[i][j] = Math.max(graphDist[i][j], graphDist[i][k] + graphDist[k][j]);
                    }
                }
            }
        }

        return graphDist;
    }
}
