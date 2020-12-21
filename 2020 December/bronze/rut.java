import java.util.*;

class rut {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        char[] dir = new char[n];
        int[] x = new int[n];
        int[] y = new int[n];

        List<Integer> north = new ArrayList<Integer>();
        List<Integer> east = new ArrayList<Integer>();
        for(int i = 0; i < n; i++) {
            dir[i] = sc.next().charAt(0);
            x[i] = sc.nextInt();
            y[i] = sc.nextInt();

            if(dir[i] == 'E')
                east.add(i);
            else
                north.add(i);
        }

        Collections.sort(north, (i,j) -> x[i] - x[j]);
        Collections.sort(east, (i,j) -> y[i] - y[j]);

        // System.out.println(Arrays.toString(east.toArray()));
        // System.out.println(Arrays.toString(north.toArray()));

        int[] moved = new int[n];
        for(int i: east) // east
        for(int j: north) { // north
            if(moved[j] == 0) {
                int ti = x[j] - x[i];
                int tj = y[i] - y[j];

                // System.out.println(i + " " + j + " " + ti + " " + tj);

                if(ti >= 0 && tj >= 0) {
                    if(ti < tj) { // y gets stopped
                        moved[j] = tj;
                    } else if(tj < ti) { // x gets stopped
                        moved[i] = ti;
                        break;
                    } // else none stopped
                }
            }
        }

        for(int i: moved) {
            System.out.println(i == 0 ? "Infinity" : i);
        }
    }
}
