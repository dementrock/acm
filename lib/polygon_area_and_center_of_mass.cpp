/* Assume that the points are already sorted. Shall first use convex hull
 * algorithm to sort the points. */

class Point {
public:
    coord_t x, y;
    Point () {
        x = 0;
        y = 0;
    }
    Point (coord_t tx, coord_t ty) {
        x = tx;
        y = ty;
    }
    bool operator <(const Point &p) const {
        return x < p.x || x == p.x && y < p.y;
    }
};

Point calc_center (vector<Point> P) {
    double area = calc_area(P);
    double factor = 1.0 / (6 * area);
    double cx = 0, cy = 0;
    int s = P.size();
    for (int i = 0; i < s; ++i) {
        Point cur = P[i], next = P[(i + 1) % s];
        cx += (cur.x + next.x) * (cur.x * next.y - cur.y * next.x);
        cy += (cur.y + next.y) * (cur.x * next.y - cur.y * next.x);
    }
    cx *= factor;
    cy *= factor;
    return Point(cx, cy);
}
