/*
ID: jhunter3
LANG: JAVA
PROB: maze1
*/

import java.util.*;
import java.io.*;

class maze1 {
    static int w;
    static int h;
    static int[][] grid;
    public static void main(String[] args) throws IOException {
        long t0 = System.nanoTime();

        BufferedReader br = new BufferedReader(new FileReader("./maze1.in"));
        StringTokenizer st = new StringTokenizer(br.readLine());

        w = Integer.parseInt(st.nextToken()) * 2 + 1;
        h = Integer.parseInt(st.nextToken()) * 2 + 1;

        grid = new int[w][h];
        List<Integer> exits = new ArrayList<Integer>();
        List<Node> nodesList = new ArrayList<Node>();
        for(int y = 0; y < h;y++) {
            String[] line = br.readLine().split("");
            for(int x = 0; x < w;x++) {
                grid[x][y] = line[x].equals(" ") ? nodesList.size() : -1;
                if(grid[x][y] != -1){
                    if(x == 0 || y == 0 || x == w - 1 || y == h - 1) {
                        exits.add(nodesList.size());
                    }

                    nodesList.add(new Node(x,y,nodesList.size()));
                }
            }
        }
        int n = nodesList.size();

        Node[] nodes = nodesList.toArray(new Node[n]);
        for(int x = 0; x < w; x++) {
            for(int y = 0; y < h;y++) {
                if(!Node.isValid(x,y)) { continue; }

                for(int[] offset: new int[][]{{0,1},{1,0},{-1,0},{0,-1}}) {
                    offset[0] += x;
                    offset[1] += y;

                    if(Node.isValid(offset[0], offset[1])) {
                        int v = grid[x][y];
                        int u = grid[offset[0]][offset[1]];

                        nodes[v].adj.add(u);
                        nodes[u].adj.add(v);
                    }
                }
            }
        }

        Node[] arr2 = dijkstras(exits.get(1), Node.arrCopy(nodes));
        Node[] arr1 = dijkstras(exits.get(0), Node.arrCopy(nodes));
        int max = 0;
        for(int i = 0; i < n;i++) {
            max = Math.max(max, Math.min(arr1[i].dist, arr2[i].dist));
        }

        BufferedWriter bw = new BufferedWriter(new FileWriter("./maze1.out"));
        bw.write(((max + 1) / 2) + "\n");
        bw.close();
    }

    static class Node {
        int x,y,dist,i;
        Set<Integer> adj;

        Node(int x, int y) {
            this.x = x;
            this.y = y;
            this.adj = new HashSet<Integer>();
        }

        Node(int x, int y, int i) {
            this(x,y);
            this.i = i;
        }

        Node(int x, int y, int i, Set<Integer> adj){
            this(x,y,i);
            this.adj = adj;
        }

        boolean equals(Node u) { return this.x == u.x && this.y == u.y; }

        static boolean isValid(int x, int y) {
            return x >= 0 && y >= 0 && x < w && y < h && grid[x][y] != -1;
        }
        static boolean isValid(Node u) {
            return Node.isValid(u.x, u.y);
        }

        Node copy() { return new Node(this.x, this.y, this.i, this.adj); }

        static Node[] arrCopy(Node[] arr) {
            Node[] cp = new Node[arr.length];
            for(int i = 0 ; i < arr.length;i++) { cp[i] = arr[i].copy(); }
            return cp;
        }
    }

    static Node[] dijkstras(int src, Node[] nodes) {
        int n = nodes.length;

        List<Integer> unvisited = new ArrayList<Integer>();
        for(int i = 0; i < n; i++) {
            unvisited.add(i)    ;
            nodes[i].dist = Integer.MAX_VALUE;
        }
        nodes[src].dist = 0;

        while(!unvisited.isEmpty()) {
            int v = unvisited.get(0);
            int index = 0;
            for(int i = 0; i < unvisited.size();i++) {
                int u = unvisited.get(i);
                if(nodes[u].dist < nodes[v].dist) {
                    index = i;
                    v = u;
                }
            }
            if(nodes[v].dist == Integer.MAX_VALUE) { break; }
            unvisited.remove(index);

            for(int u: nodes[v].adj) {
                nodes[u].dist = Math.min(nodes[u].dist, nodes[v].dist + 1);
            }
        }

        return nodes;
    }
}
