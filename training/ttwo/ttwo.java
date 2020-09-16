/*
ID: jhunter3
LANG: JAVA
PROB: ttwo
*/

import java.util.*;
import java.io.*;
import java.math.*;

class ttwo {
    static int n;
    static State[][] grid;
    static Moveable farmer, cow;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("./ttwo.in"));

        n = 12;
        grid = new State[n][n];
        for(int j = 0; j < 10 ;j++) {
            String line = br.readLine();

            for(int i = 0; i < 10; i++) {
                State state = State.from(line.charAt(i));
                if(state == State.COW) {
                    cow = new Moveable(i + 1, j + 1, state);
                    state = State.EMPTY;
                } else if(state == State.FARMER) {
                    farmer = new Moveable(i + 1, j + 1, state);
                    state = State.EMPTY;
                }
                grid[i + 1][j + 1] = state;
            }
        }

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n;j++) {
                if(i == 0 || j== 0 || i == n - 1 || j == n - 1) {
                    grid[i][j] = State.WALL;
                }
            }
        }

        int time = 0;
        for(int t = 1; t <= Math.pow(10 * 10 * 4, 2); t++) {
            cow.move();
            farmer.move();

            if(cow.x == farmer.x && cow.y == farmer.y) {
                time = t;
                break;
            }
        }

        BufferedWriter bw = new BufferedWriter(new FileWriter("./ttwo.out"));
        bw.write(time + "\n");
        bw.close();
    }

    static class Moveable {
        int x,y;
        State state;
        Direction dir;

        Moveable(int x, int y, State state) {
            this.x = x;
            this.y = y;
            this.state = state;
            this.dir = Direction.NORTH;
        }

        void move() {
            int px = this.x + this.dir.x;
            int py = this.y + this.dir.y;

            switch(grid[px][py]) {
                case EMPTY:
                    this.x = px;
                    this.y = py;
                    break;
                case WALL:
                    this.dir = this.dir.rotate();
                    break;
            }
        }

        void move(int t) { for(int i = 0; i < t; i++) this.move(); }
    }

    static void printgrid() {
        for(int j =0 ; j < n;j++) {
            for(int i = 0; i < n;i++) {
                if(cow.x == i && cow.y == j) {
                    System.out.print(cow.state);
                } else if(farmer.x == i && farmer.y == j) {
                    System.out.print(farmer.state);
                } else {
                    System.out.print(grid[i][j]);
                }

            }
            System.out.println();
        }
    }

    enum Direction {
        NORTH(0, -1, 0),
        SOUTH(0, 1, 1),
        EAST(1, 0, 2),
        WEST(-1, 0, 3);

        public final int x, y, hash;
        private Direction(int x, int y, int hash) {
            this.x = x;
            this.y = y;
            this.hash = hash;
        }

        public Direction rotate() {
            Direction dir = null;
            switch(this) {
                case NORTH: dir = Direction.EAST; break;
                case EAST: dir = Direction.SOUTH; break;
                case SOUTH: dir = Direction.WEST; break;
                case WEST: dir = Direction.NORTH; break;
            }
            return dir;
        }
    }

    enum State {
        EMPTY('.'),
        WALL('*'),
        COW('C'),
        FARMER('F');

        public final char label;
        private State(char label) {
            this.label = label;
        }

        static State from(char c){
            State state = null;
            switch(c) {
                case '.': state = State.EMPTY; break;
                case '*': state = State.WALL; break;
                case 'C': state = State.COW; break;
                case 'F': state = State.FARMER; break;
            }
            return state;
        }

        @Override
        public String toString() {
            return Character.toString(this.label);
        }
    }
}
