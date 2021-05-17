// Formerly part of competition-library

package lib.utils.java;

import java.util.*;

public class Methods {
    // primitive zip is pzip as generics dont support prims
    public static int[]         pzip(int ...args)       { return args; }
    public static char[]        pzip(char ...args)      { return args; }
    public static short[]       pzip(short ...args)     { return args; }
    public static long[]        pzip(long ...args)      { return args; }
    public static boolean[]     pzip(boolean ...args)   { return args; }
    public static double[]      pzip(double ...args)    { return args; }
    public static float[]       pzip(float ...args)     { return args; }
    @SuppressWarnings("unchecked")
    public static <T> T[]       zip(T ...args)          { return args; }

    @SuppressWarnings("unchecked")
    public static <T> List<T>   list(T ...args)         { return new ArrayList<T>(Arrays.asList(args)); }


}
