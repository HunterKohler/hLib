import java.util.*;

class abc {
    static int n;
    static int[] arr;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        n = 7;
        arr = new int[]{
            sc.nextInt(),
            sc.nextInt(),
            sc.nextInt(),
            sc.nextInt(),
            sc.nextInt(),
            sc.nextInt(),
            sc.nextInt()
        };

        Arrays.sort(arr);

        for(int i = 0; i < n; i++)
        for(int j = i + 1; j < n; j++)
        for(int k = j + 1; k < n; k++) {
            int a = arr[i];
            int b = arr[j];
            int c = arr[k];

            int[] temp = new int[] {
                arr[i],
                arr[j],
                arr[k],
                arr[i] + arr[j],
                arr[i] + arr[k],
                arr[j] + arr[k],
                arr[i] + arr[j] + arr[k]
            };

            Arrays.sort(temp);

            if(arrequal(temp)){
                System.out.println(a + " " + b + " " + c);
                return;
            }
        }
    }

    static boolean arrequal(int[] temp) {
        for(int i = 0; i < n; i++) {
            if(temp[i] != arr[i]) {
                return false;
            }
        }

        return true;
    }
}
