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

Point origin = Point(0, 0);

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
    return dis(origin, a);
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

Point get_tangent (double a, double b, Point center, double r) {
    double offset_x = center.x, offset_y = center.y;
    double x1 = b, y1 = - a, x2 = b + b, y2 = - a - a;
    x1 -= offset_x;
    y1 -= offset_y;
    x2 -= offset_x;
    y2 -= offset_y;
    double dx = x2 - x1, dy = y2 - y1;
    double sqr_dr = sqr(dx) + sqr(dy);
    double D = x1 * y2 - x2 * y1;
    double x = D * dy / sqr_dr;
    double y = - D * dx / sqr_dr;
    x += offset_x;
    y += offset_y;
    return Point(x, y);
}

Point print_point(Point a) {
    printf("%.3lf %.3lf\n", a.x, a.y);
}

int equal(Point a, Point b) {
    return fcmp(a.x, b.x) == 0 && fcmp(a.y, b.y) == 0;
}

double area_triangle (Point a, Point b, Point c) {
    return 0.5 * fabs(cross(c.x - a.x, c.y - a.y, c.x - b.x, c.y - b.y));
}

int point_in_triangle(Point p, Point a, Point b, Point c) {
    if(equal(a, b) || equal(a, c) || equal(b, c)) {
        return 0;
    }
    return fcmp(area_triangle(a, b, c), area_triangle(p, a, b) + area_triangle(p, b, c) + area_triangle(p, a, c)) == 0;
}

double calc(double cx, double cy, double r, double hx, double hy) {
    Point center = Point(cx, cy);
    Point house = Point(hx, hy);

    double norm_h = norm(house);
    
    /* Calculate the coefficients a, b in the equation ax + by = 0 for the
     * two tangent lines of the circle through origin */

    double a1, b1, a2, b2;
    if (fcmp(fabs(cy), r) == 0) {
        a1 = 0;
        b1 = 1;
        a2 = 2 * cx * cy;
        b2 = sqr(r) - sqr(cx);
        if (b2 > 0) {
            a2 = -a2;
            b2 = -b2;
        }
        //cout << a1 << " " << b1 << " " << a2 << " " << b2 << endl;
    } else {
        a1 = 1;
        a2 = -1;
        b1 = (- cx * cy - r * safe_sqrt(sqr(cy) + sqr(cx) - sqr(r))) / (sqr(cy) - sqr(r));
        b2 = -(- cx * cy + r * safe_sqrt(sqr(cy) + sqr(cx) - sqr(r))) / (sqr(cy) - sqr(r));
    }

    
    /* Get tangent points */

    Point t1 = get_tangent(a1, b1, center, r);
    Point t2 = get_tangent(a2, b2, center, r);

    if (point_in_triangle(house, origin, t1, t2)) {
        return 0;
    }

    //cout << "Triangle test passed" << endl;

    //print_point(t1);
    //print_point(t2);

    double vx1 = b1, vy1 = -a1, vx2 = b2, vy2 = -a2;

    //vx1=-vx1, vy1=-vy1, vx2=-vx2, vy2=-vy2;

    //printf("%.3lf %.3lf %.3lf %.3lf\n", a1, b1, a2, b2);

    //print_normal(vx1, vy1);
    //print_normal(vx2, vy2);
    //print_normal(hx, hy);

    

    //printf("%.3lf %.3lf\n", cross(vx1,vy1,hx,hy), cross(vx2,vy2,hx,hy));
    
    /* Angle test */
    
    if (fsig(cross(vx1, vy1, hx, hy) * cross(vx2, vy2, hx, hy)) != fsig(cross(vx1, vy1, cx, cy) * cross(vx2, vy2, cx, cy))) {
        return 0;
    }

    double minx = cx - r, maxx = cx + r, miny = cy - r, maxy = cy + r;

    if (fsig(hx) < fsig(minx) || fsig(hx) > fsig(maxx) || fsig(hy) < fsig(miny) || fsig(hy) > fsig(maxy)) {
        return 0;
    }

    //cout << "Quadrant test passed" << endl;

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
