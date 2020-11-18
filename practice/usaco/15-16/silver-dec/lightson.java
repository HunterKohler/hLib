import java.io.*;
import java.util.*;

class lightson {
    int n,m;
    List<Pair>[][] switches = new List<Pair>[n][n];
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new FileReader("lightson.in"));
        PrintWriter pw = new PrintWriter(new FileWriter("lightson.out"));
        StringTokenizer st = new StringTokenizer(br.readLine());
        n = Integer.parseInt(st.nextToken());
        m = Integer.parseInt(st.nextToken());
        switches = new List<Pair>[n][n];
        for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            switches[i][j] = new ArrayList<Pair>();
        for(int i = 0; i < n; i++) {
            st = new StringTokenizer(br.readLine());
            int x = Integer.parseInt(st.nextToken()) - 1;
            int y = Integer.parseInt(st.nextToken()) - 1;
            int a = Integer.parseInt(st.nextToken()) - 1;
            int b = Integer.parseInt(st.nextToken()) - 1;

            switches[x][y].add(new Pair(a,b))
        }

        boolean[][] visited = new boolean[n][n];
        boolean[][] lit = new boolean[n][n];
        Queue<Pair> q = new LinkedList<Pair>();
        q.add(new Pair(0,0));

        while(!q.isEmpty()) {
            Pair p = q.poll();
            if(!visited[p.x][p.y] && lit[p.x][p.y]) {
                for(Pair r)
            }
        }
    }

    static class Pair {
        int x,y;
        Pair(int x, int y) {
            this.x = x;
            this.y = y;
        }
        <T> val(T[][] arr){
            return arr[this.x][this.y];
        }
    }

    static boolean inGrid(Pair p) { return inGrid(p.x, p.y); }
    static boolean inGrid(int x, int y) { return 0 <= x && x < n && 0 <= y && y < n; }
}
