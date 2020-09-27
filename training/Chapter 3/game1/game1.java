import java.io.*;
import java.util.*;
import static java.lang.Math.*;
import static java.lang.Integer.parseInt;

class game1 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("./game1.in"));
        int n = parseInt(br.readLine());
        int[] board = new int[n];
        String line;
        int index = 0;
        while((line = br.readLine()) != null) {
            StringTokenizer st = new StringTokenizer(line);
            while(st.hasMoreTokens()) {
                board[index] = parseInt( st.nextToken() );
                index++;
            }
        }

        int[][][] mem = new int[n][n][2];
        Set<List<Integer>> visited = new HashSet<List<Integer>>();
        Queue<List<Integer>> q = new LinkedList<List<Integer>>();
        for(int i = 0; i < n;i++) {
            mem[i][i][n % 2] = 0;
            mem[i][i][(n + 1) % 2] = board[i];
            List<Integer> list = new ArrayList<Integer>(); // {i,j,p} -> {left, right, player}
            list.add(i + 1);
            list.add(i);
            list.add(n % 2);
            q.add(list);

            List<Integer> list2 = new ArrayList<Integer>(); // {i,j,p} -> {left, right, player}
            list2.add(i);
            list2.add(i + 1);
            list2.add(n % 2);
            q.add(list2);
        }

        while(!q.isEmpty()) {
            List<Integer> current = q.poll();
            int i = current.get(0);
            int j = current.get(1);
            int p = current.get(2);
            if(!visited.contains(current) && i < n && j < n) {
                if(i == 0) {
                    mem[i][j] = mem[i][j - 1];
                    mem[i][j][p] += board[j - 1];
                } else if (j ==0 ) {
                    mem[i][j] = mem[i - 1][j];
                    mem[i][j][p] += board[i - 1];
                } else if(mem[i][j - 1][p] > mem[i - 1][j][p]) {
                    mem[i][j] = mem[i][j - 1];
                    mem[i][j][p] += board[j - 1];
                } else {
                    mem[i][j] = mem[i - 1][j];
                    mem[i][j][p] += board[i - 1];
                }

                visited.add(current);

                List<Integer> list = new ArrayList<Integer>(); // {i,j,p} -> {left, right, player}
                list.add(i + 1);
                list.add(j);
                list.add((p + 1) % 2);
                q.add(list);

                List<Integer> list2 = new ArrayList<Integer>(); // {i,j,p} -> {left, right, player}
                list2.add(i);
                list2.add(j + 1);
                list2.add((p + 1) % 2);
                q.add(list2);
            }
        }

        System.out.println(Arrays.toString(mem[0][n - 1]));
        BufferedWriter bw = new BufferedWriter(new FileWriter("./game1.out"));
        bw.write(mem[0][n - 1][0] + " " + mem[0][n - 1][1]);
        bw.close();
    }
}
