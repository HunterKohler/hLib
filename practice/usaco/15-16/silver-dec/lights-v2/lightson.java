import java.io.*;
import java.util.*;
import static java.lang.Math.pow;

class lightson {
    static int m,n;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("lightson.in"));
        PrintWriter pw = new PrintWriter(new FileWriter("lightson.out"));
        StringTokenizer st = new StringTokenizer(br.readLine());
        n = Integer.parseInt(st.nextToken());
        m = Integer.parseInt(st.nextToken());

        Map<Vect,List<Vect>> switches = new HashMap<Vect,List<Vect>>();
        for(int i = 0; i < m; i++) {
            st = new StringTokenizer(br.readLine());
            Vect v = new Vect(Integer.parseInt(st.nextToken()),
                              Integer.parseInt(st.nextToken()));
            if(!switches.containsKey(v)) {
                switches.put(v,new ArrayList<Vect>());
            }
            switches.get(v).add(new Vect(Integer.parseInt(st.nextToken()),
                                         Integer.parseInt(st.nextToken())));
        }

        // for(Vect v: switches.get(new Vect(1,1))) {
        //     System.out.println(v);
        // };

        Set<Vect> lit = new HashSet<Vect>();
        lit.add(new Vect(1,1));

        boolean cont = true;
        int count = 1;
        while(cont) {
            cont = false;

            Set<Vect> visited = new HashSet<Vect>();
            Queue<Vect> q = new LinkedList<Vect>();
            q.add(new Vect(1,1));

            while(!q.isEmpty()) {
                Vect v = q.poll();
                if(lit.contains(v) && !visited.contains(v)) {
                    visited.add(v);
                    if(switches.containsKey(v)) {
                        for(Vect u: switches.get(v)) {
                            if(!lit.contains(u)) {
                                count++;
                            }

                        }
                        switches.remove(v);
                        cont = true;
                    }

                    for(Vect u: v.adj()) {
                        q.add(u);
                    }
                }
            }
        }

        // System.out.println(lit);
        // System.out.println(count);
        // System.out.println(lit.size());
        // pw.println(lit.size());
        System.out.println(count);
        pw.println(count);
        pw.close();
    }

    static class Vect {
        int x,y;
        Vect(int x, int y) {
            this.x = x;
            this.y = y;
        }

        public int hashCode() { return Objects.hash(this.x, this.y); }
        public boolean equals(Object o) { return this.x == ((Vect) o).x && this.y == ((Vect) o).y; }
        public boolean inGrid() { return 0 < this.x && this.x <= n && 0 < this.y && this.y <= n; }
        public List<Vect> adj() {
            List<Vect> adjList = new ArrayList<Vect>();
            for(Vect v: new Vect[]{ new Vect(x + 1,y),
                                    new Vect(x,y + 1),
                                    new Vect(x - 1,y),
                                    new Vect(x,y - 1) }) {
                if(v.inGrid()) {
                    adjList.add(v);
                }
            }
            return adjList;
        }
        public String toString() { return "(" + this.x  +"," + this.y + ")"; }
    }
}

// import java.io.*;
// import java.util.*;
// import static java.lang.Math.pow;
//
// class lightson {
//     static int m,n;
//
//     public static void main(String[] args) throws IOException {
//         BufferedReader br = new BufferedReader(new FileReader("lightson.in"));
//         PrintWriter pw = new PrintWriter(new FileWriter("lightson.out"));
//         StringTokenizer st = new StringTokenizer(br.readLine());
//         n = Integer.parseInt(st.nextToken());
//         m = Integer.parseInt(st.nextToken());
//
//         Map<Vect,List<Vect>> switches = new HashMap<Vect,List<Vect>>();
//         for(int i = 0; i < m; i++) {
//             st = new StringTokenizer(br.readLine());
//             Vect v = new Vect(Integer.parseInt(st.nextToken()),
//                               Integer.parseInt(st.nextToken()));
//             if(!switches.containsKey(v)) {
//                 switches.put(v,new ArrayList<Vect>());
//             }
//             switches.get(v).add(new Vect(Integer.parseInt(st.nextToken()),
//                                          Integer.parseInt(st.nextToken())));
//         }
//
//         Set<Vect> lit = new HashSet<Vect>();
//         Set<Vect> visited = new HashSet<Vect>();
//         Queue<Vect> q = new LinkedList<Vect>();
//         lit.add(new Vect(1,1));
//         q.add(new Vect(1,1));
//         while(!q.isEmpty()) {
//             Vect v = q.poll();
//             if(lit.contains(v) && !visited.contains(v)) {
//                 visited.add(v);
//
//                 if(switches.containsKey(v)) {
//                     lit.addAll(switches.get(v));
//                     for(Vect u: switches.get(v))
//                     for(Vect adj_u: u.adj()) {
//                         if(visited.contains(adj_u)) {
//                             q.add(u);
//                             break;
//                         }
//                     }
//                 }
//
//                 for(Vect u: v.adj()) {
//                     q.add(u);
//                 }
//             }
//         }
//
//         // System.out.println(lit.size());
//         pw.println(lit.size());
//         pw.close();
//     }
//
//     static class Vect {
//         int x,y;
//         Vect(int x, int y) {
//             this.x = x;
//             this.y = y;
//         }
//
//         public int hashCode() { return Objects.hash(this.x, this.y); }
//         public boolean equals(Object o) { return this.hashCode() == o.hashCode(); }
//         public boolean inGrid() { return 0 < this.x && this.x <= n && 0 < this.y && this.y <= n; }
//         public List<Vect> adj() {
//             List<Vect> adjList = new ArrayList<Vect>();
//             for(Vect v: new Vect[]{ new Vect(x + 1,y),
//                                     new Vect(x,y + 1),
//                                     new Vect(x - 1,y),
//                                     new Vect(x,y - 1) }) {
//                 if(v.inGrid()) {
//                     adjList.add(v);
//                 }
//             }
//             return adjList;
//         }
//     }
// }
