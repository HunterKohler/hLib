import java.io.*;
import java.util.*;

import static java.lang.Math.*;

class range {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("./range.in"));

        int n = Integer.parseInt(br.readLine());

        boolean[][] open = new boolean[n][n];
        for(int y = 0; y < n; y++) {
            char[] line = br.readLine().toCharArray();
            for(int x = 0; x < n; x++) {
                open[x][y] = line[x] == 1 ? true : false ;
            }
        }

        for( )

        BufferedWriter bw = new BufferedWriter(new FileWriter("./range.out"));
        for(int size = 2; size <= n; size++) {
            int count = 0;
            for(int start = 0; start + size <= n; start++) {
                boolean valid = true;
                for(int i = start; i < start + size; i++) {
                    for(int j = start; j < start + size; j++) {
                        if(!open[i][j]){
                            valid = false;
                            break;
                        }
                    }
                    if(!valid)
                        break;
                }
                if(valid)
                    count++;
            }
            if(count != 0)
                bw.write(size + " " + count);
        }
        bw.close();
    }
}
