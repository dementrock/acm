import java.util.*;
import java.io.*;
import java.math.*;

class Point {
  int x, y;

  Point (int x, int y) {
    this.x = x;
    this.y = y;
  }

  public Point minus(Point b) {
    return new Point(x - b.x, y - b.y);
  }

  public int cross(Point b) {
    return x * b.y - y * b.x;
  }

  public int mult(Point b) {
    return x * b.x + y * b.y;
  }

  public static bool conPoint(Point p[], int n) {
    for (int i = 1; i < n; ++i) {
      if (!p[i].equals(p[0])) {
        return false;
      }
    }
    return true;
  }

  
}

class Main {
    public static Scanner cin = new Scanner (new BufferedInputStream(System.in));
    public static void main(String[] args) {
      int n = cin.nextInt();
      Point [] p = new Point[n+1];
      for (int i = 1; i <= n; ++i) {
        p[i].x = cin.nextInt();
        p[i].y = cin.nextInt();
      }
      System.out.println(n);
    }
}

