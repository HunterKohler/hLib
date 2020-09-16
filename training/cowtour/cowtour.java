import java.util.*;
import java.io.*;
import java.math.*;

class cowtour {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("./cowtour.in"));

        int n = Integer.parseInt(br.readLine());
        double[][] adj = new double[n][n];
        double[][] locations = new double[n][2];

        for(int i = 0; i < n;i++) {
            String[] line = br.readLine().split(" ");
            locations[i][0] = Double.parseDouble(line[0]);
            locations[i][1] = Double.parseDouble(line[1]);
        }

        for(int j = 0; j < n; j++) {
            String[] line = br.readLine().split("");
            for(int i = 0; i < n;i++) {
                adj[i][j] = Double.parseDouble(line[i]);
            }
        }

        double[][] dist = floyd(adj);
        
    }

    static double pointDist(double x0, double y0, double x1, double y1) {
        return Math.sqrt(Math.pow(x0-x1, 2) + Math.pow(y0-y1, 2));
    }

    static double pointDist(double[] p, double q[]) {
        return pointDist(p[0], p[1], q[0], q[1]);
    }

    static double[][] floyd(double[][] adj) {
        int n = adj.length;
        double[][] dist = new double[n][n];
        for(int j = 0; j < n; j++) {
            for(int i = 0; i < n;i++) {
                if(i == j) {
                    dist[i][j] = 0;
                } else {
                    dist[i][j] = adj[i][j] == 1
                        ? pointDist(locations[i], locations[j])
                        : Integer.MAX_VALUE;
                }
            }
        }

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                for(int k = 0; k < n;k++) {
                    if(dist[i][k] != Integer.MAX_VALUE && dist[k][j] != Integer.MAX_VALUE ) {
                        dist[i][j] = Math.min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }

        return dist;
    }
}
