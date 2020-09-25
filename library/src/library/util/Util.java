package library.util;
import java.util.*;

public class Util {
    public static int[] zip(int ...args) { return args; }
    // public static Character[] zip(char ...args) { return args; }
    // public static Short[] zip(short ...args) { return args; }
    // public static Long[] zip(long ...args) { return args; }
    // public static Boolean[] zip(boolean ...args) { return args; }
    // public static Double[] zip(double ...args) { return args; }
    // public static Float[] zip(float ...args) { return args; }
    @SuppressWarnings("unchecked")
    public static <T> T[] zip(T ...args) { return args; }
    // public static <T> List<T> list(T ...args) { return Arrays.asList(args); }
}
