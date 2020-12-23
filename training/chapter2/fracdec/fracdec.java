/*
ID: jhunter3
LANG: JAVA
PROB: fracdec
*/

import java.io.*;
import java.util.*;
import java.math.*;

class fracdec {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(new File("./fracdec.in"));
        int n = sc.nextInt();
        int d = sc.nextInt();

        String[] str = ( n > d
            ? stringify(n,d).split("\\.")[0] + "." + stringify(n % d, d).split("\\.")[1]
            : stringify(n,d) )
                .split("(?<=\\G.{76})");
        PrintWriter pw = new PrintWriter(new File("./fracdec.out"));
        for(String line: str) {
            pw.println(line);
        }
        pw.close();
    }

    static String stringify(int n, int d) {
        Map<Integer,Integer> map = new HashMap<Integer,Integer>();
        int num = n;
        StringBuilder sb = new StringBuilder();
        boolean looping = false;
        while(true) {
            if(num == 0) { break; }
            boolean first = true;
            while(num < d) {
                num = num * 10;
                if(!first) { sb.append(0); }
                first = false;
            }
            if(map.keySet().contains(num)) {
                sb.insert((int) map.get(num),'(');
                sb.append(')');
                looping = true;
                break;
            }
            int q = num / d;
            int r = num % d;
            map.put(num, sb.length());
            sb.append(q);
            num = r;
        }

        String calc = String.format("%.1f", ((double) n) / ((double) d));
        int shift = calc.indexOf(".") - (calc.charAt(0) == '0' ? 1 : 0);
        sb.insert(shift, '.');
        if(sb.charAt(0) == '.') {
            sb.insert(0,0);
        }
        if(sb.charAt(sb.length() - 1) == '.') {
            sb.append(0);
        }
        if(looping) {
            int base = sb.indexOf("(");
            int i = 1;
            while(sb.charAt(base - i) == sb.charAt(sb.length() - 1 -i)) { i++; }
            if(i != 1){
                int length = i - 1;
                sb.deleteCharAt(base);
                sb.insert(base - length, '(');
                sb.delete(sb.length() - length - 1, sb.length() - 1);
            }
        }
        return sb.toString();
    }
}
