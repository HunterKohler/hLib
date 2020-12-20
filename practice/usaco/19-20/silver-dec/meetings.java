import java.io.*;
import java.util.*;
import static java.lang.Integer.parseInt;

class meetings {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("meetings.in"));
        BufferedWriter bw = new BufferedWriter(new FileWriter("meetings.out"));

        StringTokenizer st = new StringTokenizer(br.readLine());
        int n = parseInt(st.nextToken());
        int l = parseInt(st.nextToken());

        int wsum = 0;
        int[] w = new int[n];
        int[] x = new int[n];
        int[] d = new int[n];

        List<Integer> order = new ArrayList<Integer>();

        for(int i = 0; i < n; i++) {
            order.add(i);

            st = new StringTokenizer(br.readLine());
            w[i] = parseInt(st.nextToken());
            x[i] = parseInt(st.nextToken());
            d[i] = parseInt(st.nextToken());

            wsum += w[i];
        }

        Collections.sort(order, (a,b) -> x[a] - x[b]);
        System.out.println(Arrays.toString(order.toArray()));

        int wstopped = 0;
        while(wstopped * 2 < wsum) {
            for(int i = 0; i < n; i++) {
                
            }
        }
    }
}
