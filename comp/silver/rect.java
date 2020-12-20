import java.util.*;

class rect {
    public static void main(String[] args) {

        // List<Integer> l = new ArrayList<Integer>();
        // l.add(1);
        // l.add(3);
        // l.add(5);
        // l.add(6);
        //
        // Collections.sort(l);
        // System.out.println(-(Collections.binarySearch(l,2) + 1));

        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();

        int[] x = new int[n];
        int[] y = new int[n];

        List<Integer> xsort = new ArrayList<Integer>();
        List<Integer> ysort = new ArrayList<Integer>();

        for(int i = 0; i < n; i++) {
            x[i] = sc.nextInt();
            y[i] = sc.nextInt();
            xsort.add(i);
            ysort.add(i);
        }

        Collections.sort(xsort, (i,j) -> x[i] - x[j]);
        Collections.sort(ysort, (i,j) -> y[i] - y[j]);

        System.out.println(Arrays.toString(xsort.toArray()));
        System.out.println(Arrays.toString(ysort.toArray()));

        int count = 0;
        // overcounting if behind
        for(int xleft = 0; xleft < n; xleft++)
        for(int yleft = 0; yleft < n; yleft++) {
            int xright = where(xsort, x[ysort.get(yleft)], (a,b) -> {
                try{
                    return x[a] - x[b];
                } finally {
                    return a - b;
                }
            });
            int yright = where(ysort, y[xsort.get(xleft)], (a,b) -> {
                try {
                    return y[a] - y[b];
                } finally {
                    return a - b;
                }
            });

            if(xright >= xleft && yright >= yleft) {
                count++;
            }
        }

        System.out.println(count);
    }

    static <T> int where(List<? extends T> list,  T key, Comparator<? super T> c) {
        int ind = Collections.binarySearch(list,key,c);
        return ind < 0 ? -(ind + 1) : ind;
    }
}
