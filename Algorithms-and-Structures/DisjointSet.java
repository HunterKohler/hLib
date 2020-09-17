import java.util.*;

public class DisjointSet {
    int n;
    int[] p; // parents
    int[] r; // ranks

    DisjointSet(int n) { // avg complexity O(Lg*(n)) approx. O(n)
        this.n = n;
        this.p = new int[n];
        for(int i = 0; i < n; i++){
            this.p[i] = i;
            this.r[i] = 1;
        }

    }

    void union(int i, int j) { // implemented at O(Log(n))
        if(r[i] > r[j]) {
            p[j] = i;
            r[i] += r[j];
        } else {
            p[i] = j;
            r[j] += r[i];
        }
    }

    int root(int i) { // implemented at O(Log(n))
        while(p[i] != i) {
            p[i] = p[p[i]];
            i = p[i];
        }

        return i;
    }
}
