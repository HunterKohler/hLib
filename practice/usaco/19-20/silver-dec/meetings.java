import java.io.*;
import java.util.*;
import static java.lang.Integer.parseInt;
import static java.lang.Math.min;
import static java.lang.Math.max;
import static java.lang.Math.abs;

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
        int count = 0;
        while(wstopped * 2 < wsum) {
            int t = Integer.MAX_VALUE;
            for(int i = 0; i < n - 1; i) {
                int ii = order.get(i);
                int jj = order.get(i + 1);
                if(d[ii] != d[ij]) {
                    int diff = abs(x[ii] - x[jj]);
                    t = diff == 1 ? 1 : diff / 2
                }
            }
        }
    }
}
