import java.util.*;
import static java.lang.Integer.parseInt;
import static java.lang.Math.min;
import static java.lang.Math.max;

class rut {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();

        int[] d = new int[n];
        int[] x = new int[n];
        int[] y = new int[n];

        List<Integer> east = new ArrayList<Integer>(); // sorted by y <---------
        List<Integer> north = new ArrayList<Integer>(); // sorted by x <---------

        for(int i = 0; i < n; i++) {
            d[i] = sc.next().charAt(0);
            x[i] = sc.nextInt();
            y[i] = sc.nextInt();

            if(d[i] == 'N')
                north.add(i);
            else
                east.add(i);
        }

        Collections.sort(east, (i,j) -> y[i] - y[j]);
        Collections.sort(north, (i,j) -> x[i] - x[j]);

        int[] count = new int[n];
        boolean[] stopped = new boolean[n];
        for(int i: east) {
            for(int j: north) {
                if(!stopped[j]) {
                    int ti = x[j] - x[i];
                    int tj = y[i] - y[j];
                    int t = tj - ti;

                    if(ti > 0 && tj > 0) {
                        if(t > 0) {
                            count[i] += count[j] + 1;
                            stopped[j] = true;
                        } else if(t < 0) {
                            count[j] += count[i] + 1;
                            stopped[i] = true;
                            break;
                        }
                    }
                }
            }
        }

        for(int i: count) {
            System.out.println(i);
        }
    }
}
