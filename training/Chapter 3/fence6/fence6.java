/*
ID: jhunter3
LANG: JAVA
PROB: fence6
*/

import java.io.*;
import java.util.*;
import static java.lang.Integer.parseInt;

class fence6 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("fence6.in"));
        BufferedWriter bw = new BufferedWriter(new FileWriter("fence6.out"));

        n = parseInt(br.readLine());
        edgeList = new Edge[n];

        for(int i = 0; i < n; i++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int s = parseInt(st.nextToken()) - 1;
            edgeList[s] = new Edge(s, parseInt(st.nextToken()),
                parseInt(st.nextToken()), parseInt(st.nextToken()));

            st = new StringTokenizer(br.readLine());
            for(int j = 0; j < edgeList[s].n1_len; j++) {
                edgeList[s].n1.add(parseInt(st.nextToken()) - 1);
            }

            st = new StringTokenizer(br.readLine());
            for(int j = 0; j < edgeList[s].n2_len; j++) {
                edgeList[s].n2.add(parseInt(st.nextToken()) - 1);
            }
        }

        // for(int i = 0; i < n; i++) {
        //     System.out.println(edgeList[i]);
        // }

        int min = INF;
        for(int i = 0; i < n; i++) {
            min = Math.min(min, dfs(0,i,-1,i,new boolean[n]));
        }

        // System.out.println(min);
        bw.write(min + "\n");
        bw.close();
    }

    static int INF = Integer.MAX_VALUE / 1000;
    static Edge[] edgeList;
    static int n;

    // copy array
    static int dfs(int sum, int current, int last, int start, boolean[] visited) {
        if(visited[current]) {
            if(current == start) {
                return sum;
            } else {
                return INF;
            }
        } else {
            visited[current] = true;
            int min = INF;
            for(int s: edgeList[current].n1.contains(last)
                ? edgeList[current].n2
                : edgeList[current].n1) {
                min = Math.min(
                    min,
                    dfs(
                        sum + edgeList[current].l, // sum
                        s, // current
                        current, // last
                        start, // start
                        Arrays.copyOf(visited, visited.length) // visited
                    )
                );
            }

            return min;
        }
    }

}

class Edge {
    int s,l,n1_len,n2_len;
    Set<Integer> n1, n2;

    Edge(int s, int l, int n1_len, int n2_len) {
        this.s = s;
        this.l = l;
        this.n1_len = n1_len;
        this.n2_len = n2_len;
        this.n1 = new HashSet<Integer>();
        this.n2 = new HashSet<Integer>();
    }

    public String toString() {
        return String.format(
            "Edge: {\n"
                + "\ts: %d\n"
                + "\tl: %d\n"
                + "\tn1: %s\n"
                + "\tn2: %s\n"
            + "}",
            this.s,
            this.l,
            this.n1,
            this.n2
        );
    }
}
