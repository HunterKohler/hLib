import java.io.*;
import java.util.*;

class cv {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();

        List<Integer>[] adjList = new List[n];
        for(int i = 0; i < n; i++) {
            adjList[i] = new ArrayList<Integer>();
        }

        for(int i = 0; i < n - 1; i++) {
            sc.nextLine();
            int a = sc.nextInt() - 1;
            int b = sc.nextInt() - 1;

            adjList[a].add(b);
            adjList[b].add(a);
        }

        Queue<Integer> q = new LinkedList<Integer>();
        q.add(0);

        int count = 0;
        boolean[] visited = new boolean[n];
        while(!q.isEmpty()) {
            int a = q.poll();

            if(!visited[a]) {
                visited[a] = true;

                count += (int) Math.ceil(log2(adjList[a].size() + 1));

                for(Integer b: adjList[a]) {
                    q.add(b);
                }
            }
        }

        System.out.println(count);
    }

    static double log2(double x) {
        return Math.log(x) / Math.log(2);
    }
}
