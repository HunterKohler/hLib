package graph;
import java.util.*;
import library.util.*;

class Graph {
    int[][] adj = null;
    boolean weighted = false;
    List<int[]>[] adjList = null; // [b,w]
    List<int[]> edgeList = null; // [a,b,w]
    int V, E;

    Graph(int V, int E) {
        this.V = V;
        this.E = E;
    }

    Graph(int V, int E, ArrayList<int[]>[] adjList) {
        this(V,E);
        this.adjList = adjList;
    }

    Graph(int V, int E, int[][] adj) {
        this(V,E);
        this.adj = adj;
    }

    int[][] getAdj() {
        if(adj != null){
            return adj;
        } else {
            adj = new int[V][V];
        }

        if(adjList != null){
            for(int v = 0; v < V;v++)
            for(int[] edge: adjList[v])
                adj[v][edge[0]] = adj[edge[0]][v] = edge[1];
        } else if(edgeList != null) {
            for(int[] edge: edgeList)
                adj[edge[0]][edge[1]] = adj[edge[1]][edge[0]] = edge[2];
        }

        return adj;
    }

    List<int[]>[] getAdjList() {
        if(adjList != null){
            return adjList;
        } else {
            adjList = new ArrayList[V];
            for(int v = 0; v < V;v++)
                adjList[v] = new ArrayList<int[]>();
        }

        if(adj != null) {
            for(int v = 0; v < V; v++)
            for(int u = 0; u < V; u++){
                adjList[v].add(zip(u,adj[v][u]));
                adjList[u].add(zip(v,adj[v][u]));
            }
        } else if(ad)

        return adjList;
    }
}
