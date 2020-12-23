import java.util.*;
import java.io.*;
import java.math.BigInteger;
import static java.lang.Math.abs;
import static java.lang.Integer.parseInt;

class rect {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int n = parseInt(br.readLine());

        Point[] points = new Point[n];

        Integer[] y_sort = new Integer[n];
        for(int i = 0; i < n; i++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            points[i] = new Point(parseInt(st.nextToken()), parseInt(st.nextToken()),i);

            y_sort[i] = i;
        }

        Arrays.sort(y_sort, (i,j) -> points[i].y - points[j].y);

        for(int i = 0; i < n; i++) {
            points[y_sort[i]].y_sort = i;
        }

        Arrays.sort(points, (i,j) -> i.x - j.x);

        BigInteger two = new BigInteger("2");
        BigInteger total = two.pow(n);

        for(int i = 0; i < n; i++) {
            boolean down = false;
            boolean up = false;
            for(int j = i + 1; j < n; j++) {
                int diff = points[i].y_sort - points[j].y_sort;
                if((diff < 0 && down) || (diff > 0 && up) || (down && up)) {
                    int val = n - abs(diff) - 1;

                    // System.out.println(points[i]);
                    // System.out.println(points[j]);
                    // System.out.println(String.format("\t 2^%d = %s", val, two.pow(val).toString()));

                    total = total.subtract(two.pow(val));
                }

                if(diff < 0) {
                    down = true;
                } else if (diff > 0) {
                    up = true;
                } else {
                    down = true;
                    up = true;
                }
            }
        }

        System.out.println(total);

    }

    static class Point {
        int x,y,index,y_sort;
        Point(int x, int y, int index) {
            this.x = x;
            this.y = y;
            this.index = index;
        }

        public String toString() {
            return String.format("Point: (%d,%d) index=%d, y_sort=%d",this.x, this.y, this.index, this.y_sort);
        }
    }
}
