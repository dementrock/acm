#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

class Point {
public:
    double x, y;
    Point() {
        x = y = 0;
    }
    Point (double tx, double ty) {
        x = tx;
        y = ty;
    }
};

int fsig(double x) {
    if (fabs(x) < 1e-6) {
        return 0;
    } else if (x > 0) {
        return 1;
    } else {
        return -1;
    }
}

int fcmp (double x, double y) {
    return fsig(x - y);
}

double sqr(double x) {
    return x * x;
}

double safe_sqrt(double x) {
    if (fsig(x) == 0) {
        return 0;
    } else {
        return sqrt(x);
    }
}

double dis (Point a, Point b) {
    return safe_sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

double dis(double x1, double y1, double x2, double y2) {
    return safe_sqrt(sqr(x1 - x2) + sqr(y1 - y2));    
}

double norm(Point a) {
    return dis(Point(0, 0), a);
}

double norm(double x, double y) {
    return dis(0, 0, x, y);
}

double cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

double cross(double x1, double y1, double x2, double y2) {
    return x1 * y2 - x2 * y1;
}

double dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

double dot(double x1, double y1, double x2, double y2) {
    return x1 * x2 + y1 * y2;
}

/* Distance from (x, y) to the line ax + by + c = 0 */
double dis_ptl(Point p, double a, double b, double c) {
    return (a * p.x + b * p.y + c) / sqrt(sqr(a) + sqr(b));
}

double dis_ptl(double x, double y, double a, double b, double c) {
    return fabs(a * x + b * y + c) / sqrt(sqr(a) + sqr(b));
}

void print_normal(double x, double y) {
    double n = norm(x, y);
    printf("%.3lf %.3lf\n", x/n, y/n);
}

double calc(double cx, double cy, double r, double hx, double hy) {
    Point center = Point(cx, cy);
    Point house = Point(hx, hy);
    //double norm_h = norm(house);
    /* test the distance from origin */
    /*if (fcmp(norm_h, norm(cx, cy)) <= 0) {
        return 0;
    }

    printf("origin passed.\n");*/
    /* Calculate the coefficients a, b in the equation ax + by = 0 for the
     * two tangent lines of the circle through origin */

    double a1, b1, a2, b2;
    //if (fcmp(fabs(cy), r) < 0) { // which should not happen
     //   return 0;
    if (fcmp(fabs(cy), r) == 0) {
        a1 = 0;
        b1 = 1;
        a2 = 2 * cx * cy;
        b2 = sqr(r) - sqr(cx);
    } else {
        a1 = a2 = 1;
        //cout << cx * cy << endl;
        //cout << sqr(cy) + sqr(cx) - sqr(r) << endl;
        //cout << r * safe_sqrt(sqr(cy) + sqr(cx) - sqr(r)) << endl;
        b1 = (- cx * cy - r * safe_sqrt(sqr(cy) + sqr(cx) - sqr(r))) / (sqr(cy) - sqr(r));
        b2 = (- cx * cy + r * safe_sqrt(sqr(cy) + sqr(cx) - sqr(r))) / (sqr(cy) - sqr(r));
        //printf("%.3lf %.3lf %.3lf %.3lf\n", a1, b1, a2, b2);
    }

    //double va1 = a1, vb1 = -b1, va2 = a2, vb2 = -b2;
    double vx1 = b1, vy1 = -a1, vx2 = b2, vy2 = -a2;

    //vx1=-vx1, vy1=-vy1, vx2=-vx2, vy2=-vy2;

    //printf("%.3lf %.3lf %.3lf %.3lf\n", a1, b1, a2, b2);

    print_normal(vx1, vy1);
    print_normal(vx2, vy2);
    print_normal(hx, hy);

    //printf("%.3lf %.3lf\n", cross(vx1,vy1,hx,hy), cross(vx2,vy2,hx,hy));
    
    /* Angle test */
    
    if (fsig(cross(vx1, vy1, hx, hy) * cross(vx2, vy2, hx, hy)) != fsig(cross(vx1, vy1, cx, cy) * cross(vx2, vy2, cx, cy))) {
        return 0;
    }

    //printf("angle1 passed.\n");

    double minx = cx - r, maxx = cx + r, miny = cy - r, maxy = cy + r;

    if (fsig(hx) != fsig(minx) && fsig(hx) != fsig(maxx) || fsig(hy) != fsig(miny) && fsig(hy) != fsig(maxy)) {
        return 0;
    }

    /*double norm_v1 = norm(vx1, vy1), norm_v2 = norm(vx2, vy2);
    double cosa = dot(vx1, vy1, hx, hy) / (norm_v1 * norm_h);
    double cosb = dot(vx2, vy2, hx, hy) / (norm_v2 * norm_h);
    double sina = safe_sqrt(1 - sqr(cosa)), sinb = safe_sqrt(1 - sqr(cosb));
    double sinab = sina * cosb + sinb * cosa;
    if (fsig(sinab) < 0) {
        return 0;
    }*/

    /* All tests pass. Then calculate the minimum among the distance of house
     * from two tangent lines, and the distance from the circle */

    double ans = dis(cx, cy, hx, hy) - r;
    ans = min(ans, dis_ptl(hx, hy, a1, b1, 0));
    //cout << a1 << " " << b1 << endl;
    //printf("%.3lf\n", ans);
    ans = min(ans, dis_ptl(hx, hy, a2, b2, 0));
    //printf("%.3lf\n", ans);

    return ans;
}

int main() {
    int times;
    scanf("%d", &times);
    while (times--) {
        double cx, cy, r, hx, hy;
        scanf("%lf%lf%lf%lf%lf", &cx, &cy, &r, &hx, &hy);
        printf("%.3lf\n", calc(cx, cy, r, hx, hy));
    }
    return 0;
}
