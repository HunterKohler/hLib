/*
ID: jhunter3
LANG: JAVA
PROB: agrinet
*/
import java.io.*;
import java.util.*;

class agrinet {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("./agrinet.in"));

        int n = Integer.parseInt(br.readLine());
        String line, matrix = "";
        while((line = br.readLine()) != null) {
            matrix += line + " ";
        }

        int[][] adj = new int[n][n];
        StringTokenizer st = new StringTokenizer(matrix);
        for(int i = 0; st.hasMoreTokens(); i++) {
            adj[i % n][i / n] = Integer.parseInt(st.nextToken());
        }

        for(int j =0 ; j < n;j++) {
            for(int i = 0; i < n;i++) {
                System.out.print(adj[i][j] + " ");
            }
            System.out.println();
        }

        List<int[]> edges = new ArrayList<int[]>();
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n;j++) {
                if(adj[i][j] != 0) {
                    edges.add(new int[]{i,j,adj[i][j]});
                }
            }
        }

        for(int[] edge: edges) {
            System.out.println(Arrays.toString(edge));
        }

        adj = kruskals(n, edges);

        for(int j =0 ; j < n;j++) {
            for(int i = 0; i < n;i++) {
                System.out.print(adj[i][j] + " ");
            }
            System.out.println();
        }

        int count = 0;
        for(int i = 0; i < n;i++) {
            for(int j = i + 1; j < n; j++) {
                count += adj[i][j];
            }
        }

        BufferedWriter bw = new BufferedWriter(new FileWriter("./agrinet.out"));
        bw.write(count + "\n");
        bw.close();
    }

    static int[][] kruskals(int n, List<int[]> edges) {
        int[][] adj = new int[n][n];
        DisjointedSet dset = new DisjointedSet(n);
        PriorityQueue<int[]> pq = new PriorityQueue<int[]>((int[] a, int[] b) -> {
            return a[2] < b[2] ? -1 : 1;
        });
        for(int[] edge: edges) pq.add(edge);

        while(!pq.isEmpty()) {
            int a = pq.peek()[0];
            int b = pq.peek()[1];
            int w = pq.poll()[2];

            if(dset.root(a) != dset.root(b)) {
                adj[a][b] = w;
                adj[b][a] = w;
                dset.union(a,b);
            }
        }

        return adj;
    }

    static class DisjointedSet {
        int[] p, r;
        int n;

        DisjointedSet(int n) {
            this.n = n;
            this.p = new int[n];
            this.r = new int[n];
            for(int i = 0; i < n;i++) {
                this.p[i] = i;
                this.r[i] = 1;
            }
        }

        void union(int i, int j) {
            i = root(i);
            j = root(j);
            if(i == j) {return;}

            if(this.r[i] < this.r[j]) {
                this.r[i] += this.r[j];
                this.p[j] = i;
            } else {
                this.r[j] += this.r[i];
                this.p[i] = j;
            }

            System.out.println("u: (" + i + "," + j + ") " + Arrays.toString(p));
        }

        int root(int i) {
            while(i != p[i]){
                p[i] = p[p[i]];
                i = p[i];
            }
            return i;
        }
    }
}
