import java.util.*;

class daisy {
    static int n;
    static int[] p;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        n = sc.nextInt();
        p = new int[n];
        for(int i = 0; i < n; i++) {
            p[i] = sc.nextInt();
        }

        int count = 0;
        for(int i = 0; i < n; i++)
        for(int j = i; j < n; j++) {
            boolean[] seen = new boolean[1001];
            int sum = 0;
            for(int k = i; k <= j; k++) {
                sum += p[k];
                seen[p[k]] = true;
            }

            if(sum % (j - i + 1) == 0 && seen[sum / (j - i + 1)]) {
                count++;
            }
        }

        System.out.println(count);
    }
}
