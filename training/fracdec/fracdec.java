import java.io.*;
import java.util.*;
import java.math.*;

class fracdec {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(new File('./fracdec.in'));
        double n = sc.nextInt();
        double d = sc.nextInt();

        System.out.println(n / d);
    }


}
