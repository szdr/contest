static const int COUNTER_CLOCKWISE = 1;
static const int CLOCKWISE = -1;
static const int ONLINE_BACK = 2;    // p2 -> p0 -> p1
static const int ONLINE_FRONT = -2;  // p0 -> p1 -> p2
static const int ON_SEGMENT = 0;     // p0 -> p2 -> p1
class Point {
    public:
        double x, y;
        Point(double x = 0, double y = 0): x(x), y(y) {}
        Point operator + (Point p) { return Point(x + p.x, y + p.y); }
        Point operator - (Point p) { return Point(x - p.x, y - p.y); }
        Point operator * (double a) { return Point(a * x, a * y); }
        Point operator / (double a) { return Point(x / a, y / a); }

        double abs() { return sqrt(norm()); }
        double norm() { return x * x + y * y; }

        bool operator < (const Point &p) const {
            return x != p.x ? x < p.x : y < p.y;    
        }

        bool operator == (const Point &p) const {
            return fabs(x - p.x) < EPS && fabs(y - p.y) < EPS;
        }

};

typedef Point Vector;

struct Segment {
    Point p1, p2;
};

typedef Segment Line;

class Circle {
    public:
        Point c;
        double r;
        Circle(Point c = Point(), double r = 0.0): c(c), r(r) {}
};

typedef vector<Point> Polygon;

double dot (Vector a, Vector b) { return a.x * b.x + a.y * b.y; }
double cross (Vector a, Vector b) { return a.x * b.y - a.y * b.x; }
bool is_orthogonal (Vector a, Vector b) { return dot(a, b) < EPS; }
bool is_orthogonal (Point a_1, Point a_2, Point b_1, Point b_2) { return is_orthogonal(a_1 - a_2, b_1 - b_2); }
bool is_orthogonal (Segment s1, Segment s2) { return dot(s1.p2 - s1.p1, s2.p2 - s2.p1) < EPS; }
bool is_parallel(Vector a, Vector b) { return cross(a, b) < EPS; }
bool is_parallel(Point a_1, Point a_2, Point b_1, Point b_2) { return is_parallel(a_1 - a_2, b_1 - b_2); }
bool is_parallel(Segment s1, Segment s2) { return cross(s1.p2 - s1.p1, s2.p2 - s2.p1) < EPS; }
Point project(Segment s, Point p) {
    Vector base = s.p2 - s.p1;
    double r = dot(p - s.p1, base) / base.norm();
    return s.p1 + base * r;
}
Point reflect(Segment s, Point p) {
    return p + (project(s, p) - p) * 2.0;
}
double get_distance(Point a, Point b) { return (a - b).abs(); }
double get_distance_lp(Line l, Point p) { return fabs(cross(l.p2 - l.p1, p - l.p1) / (l.p2 - l.p1).abs()); }
double get_distance_sp(Segment s, Point p) { 
    if ( dot(s.p2 - s.p1, p - s.p1) < EPS ) return (p - s.p1).abs();
    if ( dot(s.p1 - s.p2, p - s.p2) < EPS ) return (p - s.p2).abs();
    return get_distance_lp(s, p);
}
int ccw (Point p_0, Point p_1, Point p_2) {
    Vector a = p_1 - p_0;
    Vector b = p_2 - p_0;
    if ( cross(a, b) > EPS ) return COUNTER_CLOCKWISE;
    if ( cross(a, b) < -EPS ) return CLOCKWISE;
    if ( dot(a, b) < -EPS ) return ONLINE_BACK;
    if ( a.norm() < b.norm() ) return ONLINE_FRONT;
    return ON_SEGMENT;
}
bool intersect (Point p_1, Point p_2, Point p_3, Point p_4) {
    return ( ccw(p_1, p_2, p_3) * ccw(p_1, p_2, p_4) <= 0 &&
            ccw(p_3, p_4, p_1) * ccw(p_3, p_4, p_2) <= 0 );
}
bool intersect (Segment s_1, Segment s_2) {
    return intersect(s_1.p1, s_1.p2, s_2.p1, s_2.p2);
}
Point get_cross_point (Segment s_1, Segment s_2) {
    Vector base = s_2.p2 - s_2.p1;
    double d1 = fabs(cross(base, s_1.p1 - s_2.p1));
    double d2 = fabs(cross(base, s_1.p2 - s_2.p1));
    double t = d1 / (d1 + d2);
    return s_1.p1 + (s_1.p2 - s_1.p1) * t;
}
pair<Point, Point> get_cross_points (Circle c, Line l) {
    // if intersection check need, please input here
    Vector pr = project(l, c.c);
    Vector e = (l.p2 - l.p1) / (l.p2 - l.p1).abs();
    double base = sqrt(c.r * c.r - (pr - c.c).norm());
    return make_pair(pr + e * base, pr - e * base);
}
double arg (Vector p) { return atan2(p.y, p.x); }
Vector polar (double a, double r) { return Point(cos(r) * a, sin(r) * a); }
pair<Point, Point> get_cross_points (Circle c_1, Circle c_2) {
    // if intersection check need, please input here
    double d = (c_1.c - c_2.c).abs();
    double a = acos((c_1.r * c_1.r + d * d - c_2.r * c_2.r) / (2 * c_1.r * d));
    double t = arg(c_2.c - c_1.c);
    return make_pair(c_1.c + polar(c_1.r, t + a), c_1.c + polar(c_1.r, t - a));
}
int contains (Polygon g, Point p) {
    // IN 2, ON 1, OUT 0
    int n = g.size();
    bool x = false;
    for (int i = 0; i < n; i++) {
        Point a = g[i] - p, b = g[(i + 1) % n] - p;
        if (fabs(cross(a, b)) < EPS && dot(a, b) < EPS) return 1;
        if (a.y > b.y) swap(a, b);
        if (a.y < EPS && EPS < b.y && cross(a, b) > EPS) x = !x;
    }
    return (x ? 2 : 0);
}
Polygon andrew_scan (Polygon s) {
    // if point on convex is ok, <!= CLOCKWISE> -> <== COUNTER_CLOCKWISE>
    Polygon u, l;
    if (s.size() < 3) return s;
    sort(s.begin(), s.end());
    u.push_back(s[0]);
    u.push_back(s[1]);
    l.push_back(s[s.size() - 1]);
    l.push_back(s[s.size() - 2]);
    // upper side
    for (int i = 2; i < s.size(); i++) {
        for (int n = u.size(); n >= 2 && ccw(u[n-2], u[n-1], s[i]) != CLOCKWISE; n--) {
            u.pop_back();
        }
        u.push_back(s[i]);
    }
    // lower side
    for (int i = s.size() - 3; i >= 0; i--) {
        for (int n = l.size(); n >= 2 && ccw(l[n-2], l[n-1], s[i]) != CLOCKWISE; n--) {
            l.pop_back();
        }
        l.push_back(s[i]);
    }
    reverse(l.begin(), l.end());
    for (int i = u.size() - 2; i >= 1; i--) l.push_back(u[i]);
    return l;
}
