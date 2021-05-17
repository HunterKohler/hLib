// Formerly part of competition-library

package lib.data_structures;

import java.util.*;
import static lib.utils.java.Methods.*;

public class Graph {
    //  --- Info ---
    // Assumes that all have non-zero weights
    // For dijkstra have only positive weights

    int[][] adj = null;
    boolean weighted = false;
    List<int[]>[] adjList = null; // [v] = {[u,w], ...}
    List<int[]> edgeList = null; // {[v,u,w], [u,v,w], ...}
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

    public int[][] getAdj() {
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

    public List<int[]>[] getAdjList() {
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
                adjList[v].add(pzip(u,adj[v][u]));
                adjList[u].add(pzip(v,adj[v][u]));
            }
        } else if(edgeList != null) {
            for(int[] edge: edgeList) {
                adjList[edge[0]].add(pzip(edge[1], edge[2]));
                adjList[edge[1]].add(pzip(edge[0], edge[2]));
            }
        }

        return adjList;
    }

    public List<int[]> getEdgeList() {
        if(edgeList != null) {
            return edgeList;
        } else {
            edgeList = new ArrayList<int[]>();
        }

        if(adj != null) {
            for(int v = 0; v < V; v++)
            for(int u = 0; u < V; u++)
                if(adj[v][u] != 0) {
                    edgeList.add(pzip(v,u,adj[v][u]));
                    edgeList.add(pzip(u,v,adj[u][v]));
                }
        } else if (adjList != null) {
            for(int v = 0; v < V; v++)
            for(int[] edge: adjList[v]){
                edgeList.add(pzip(v, edge[0], edge[1]));
                edgeList.add(pzip(edge[0], v, edge[1]));
            }
        }

        return edgeList;
    }
}
