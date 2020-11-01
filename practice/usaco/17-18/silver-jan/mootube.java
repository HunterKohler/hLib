import java.io.*;
import java.util.*;

public class mootube {
	public static void main(String[] args) throws IOException{
		BufferedReader br = new BufferedReader(new FileReader("mootube.in"));
		PrintWriter pw = new PrintWriter(new FileWriter("mootube.out"));
		StringTokenizer st = new StringTokenizer(br.readLine());
		int n = Integer.parseInt(st.nextToken());
		int q = Integer.parseInt(st.nextToken());

		List<int[]>[] adj = new List[n];
		for(int i = 0; i < n; i++){
			adj[i] = new ArrayList<int[]>();
		}

		for(int i = 0; i < n - 1; i++){
			st = new StringTokenizer(br.readLine());
			int a = Integer.parseInt(st.nextToken()) - 1;
			int b = Integer.parseInt(st.nextToken()) - 1;
			int r = Integer.parseInt(st.nextToken());

			adj[a].add(new int[]{b,r});
			adj[b].add(new int[]{a,r});
		}

		for(int i = 0; i < q; i++){
			st = new StringTokenizer(br.readLine());
			int k = Integer.parseInt(st.nextToken());
			int v = Integer.parseInt(st.nextToken()) - 1;

			boolean[] visited = new boolean[n];

			Queue<Integer> queue = new LinkedList<Integer>();
			queue.add(v);
			int count = -1;
			while(!queue.isEmpty()) {
				count++;
				int u = queue.poll();
				visited[u] = true;
				for(int[] e : adj[u]) {
					if (e[1] >= k && !visited[e[0]]) {
						queue.add(e[0]);
					}
				}
			}
			pw.print(count + "\n");
		}

		pw.close();
	}

}
