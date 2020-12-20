import java.io.*;
import java.util.*;

class rut {
    static int n;
    static int[] x,y;
    static char[] dir;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();

        x = new int[n];
        y = new int[n];
        dir = new char[n];
        int[] count = new int[n];

        List<Integer> east = new ArrayList<Integer>(); // sorted by y, then x;
        List<Integer> north = new ArrayList<Integer>(); // sorted by x, then y;
        for(int i = 0; i < n; i++) {
            dir[i] = sc.next().charAt(0);
            x[i] = sc.nextInt();
            y[i] = sc.nextInt();

            if(dir[i] == 'E')
                east.add(i);
            else
                north.add(i);
        }

        Collections.sort(east, (i,j) -> y[i] - y[j]);
        Collections.sort(north, (i,j) -> x[i] - x[j]);

        boolean[] stopped = new boolean[n];
        for(int i = 0; i < east.size(); i++)
        for(int j = 0; j < north.size(); j++) {
            if(!stopped[north.get(j)]) {
                int f = first(east.get(i),north.get(j));
                if (f < 0) {
                    stopped[north.get(j)] = true;
                    count[east.get(i)] += count[north.get(j)] + 1;
                } else if (f > 0) {
                    stopped[east.get(i)] = true;
                    count[north.get(j)] += count[east.get(i)] + 1;
                    break;
                }
            }
        }

        for(int i: count) {
            System.out.println(i);
        }
    }

    static int[] position(int i, int t) {
        return dir[i] == 'E'
            ? new int[]{ x[i] + t, y[i] }
            : new int[]{ x[i], y[i] + t };
    }

    static int first(int i, int j) { // i moving east, j moving west (-1 for i first, 0 both, 1 for j first)
        int ti = x[j] - x[i];
        int tj = y[i] - y[j];

        if(ti < 0 || tj < 0)
            return 0;
        else
            return ti - tj;
    }
}
