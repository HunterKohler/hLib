import java.util.*;
import static java.lang.Integer.parseInt;
import static java.lang.Math.ceil;
import static java.lang.Math.max;
import static java.lang.Math.log;

class cow {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();

        List<List<Integer>> adj = new ArrayList<List<Integer>>();
        for(int i = 0; i < n; i++)
            adj.add(new ArrayList<Integer>());

        for(int i = 0; i < n - 1; i++) {
            int a = sc.nextInt() - 1;
            int b = sc.nextInt() - 1;

            adj.get(a).add(b);
            adj.get(b).add(a);
        }

        // System.out.println("n " + n);
        // System.out.println("adjList");
        // for(List<Integer> l: adj) {
            // System.out.println("\t" + Arrays.toString(l.toArray()));
        // }

        Queue<Integer> q = new LinkedList<Integer>();
        for(int a: adj.get(0))
            q.add(a);


        // System.out.println("0: " + minpow(adj[0].size()));
        int count = minpow(adj.get(0).size() + 1);
        boolean[] visited = new boolean[n];
        visited[0] = true;
        while(!q.isEmpty()) {
            int a = q.poll();

            if(!visited[a]) {
                count++;
                visited[a] = true;
                count += minpow(adj.get(a).size());

                // System.out.println(a + ": " + 1 + " + " + minpow(adj[a].size()));
                for(int b: adj.get(a)) {
                    q.add(b);
                }
            }
        }

        System.out.println(count);
    }

    static int minpow(int x) {
        return (int) ceil( log(x) / log(2) );
    }
}
