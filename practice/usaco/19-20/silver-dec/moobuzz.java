import java.io.*;
import java.util.*;

class moobuzz {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("moobuzz.in"));
        BufferedWriter bw = new BufferedWriter(new FileWriter("moobuzz.out"));

        int n = Integer.parseInt(br.readLine()) - 1;
        int[] arr = new int[]{1,2,4,7,8,11,13,14};
        n = (n / 8) * 15 + (arr[n % 8]);

        bw.write(n + "\n");
        bw.close();
    }
}
