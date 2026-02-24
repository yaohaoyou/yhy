#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>

using namespace std;

const double EPS = 1e-9;
const double PI = acos(-1.0);

// 点结构体
struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    
    Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
    Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
    Point operator*(double k) const { return Point(x * k, y * k); }
    Point operator/(double k) const { return Point(x / k, y / k); }
    
    double dot(const Point& p) const { return x * p.x + y * p.y; }
    double cross(const Point& p) const { return x * p.y - y * p.x; }
    double length() const { return sqrt(x * x + y * y); }
    Point normalize() const { return *this / length(); }
    Point rotate(double angle) const {
        double c = cos(angle), s = sin(angle);
        return Point(x * c - y * s, x * s + y * c);
    }
};

// 直线结构体
struct Line {
    Point p1, p2;
    Line(Point p1 = Point(), Point p2 = Point()) : p1(p1), p2(p2) {}
};

// 多边形类
class Polygon {
private:
    vector<Point> vertices;
    int n;

public:
    Polygon(const vector<Point>& points) : vertices(points) {
        n = points.size();
    }
    
    // 获取边
    Line getEdge(int i) const {
        return Line(vertices[i], vertices[(i + 1) % n]);
    }
    
    // 获取顶点数
    int size() const { return n; }
    
    // 获取顶点
    Point getVertex(int i) const {
        return vertices[i % n];
    }
    
    // 判断点是否在多边形内（严格内部）
    bool isPointInside(const Point& p) const {
        // 使用射线法
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            Point a = vertices[i];
            Point b = vertices[(i + 1) % n];
            
            if (fabs((p - a).cross(b - a)) < EPS && 
                (p - a).dot(b - a) > -EPS && 
                (p - b).dot(a - b) > -EPS) {
                return true; // 在边界上
            }
            
            if (fabs(a.y - b.y) < EPS) continue;
            
            if (a.y > b.y) swap(a, b);
            if (p.y < a.y - EPS || p.y > b.y - EPS) continue;
            
            double t = (p.y - a.y) / (b.y - a.y);
            double x = a.x + t * (b.x - a.x);
            if (x > p.x + EPS) cnt++;
        }
        return cnt % 2 == 1;
    }
};

// 光线反射模拟器
class RayReflectionSimulator {
private:
    Polygon polygon;
    Point start;
    double angle; // 弧度
    
public:
    RayReflectionSimulator(const Polygon& poly, const Point& s, double alpha_degrees) 
        : polygon(poly), start(s) {
        angle = alpha_degrees * PI / 180.0; // 转换为弧度
    }
    
    // 计算两条直线的交点
    Point lineIntersection(const Line& l1, const Line& l2) const {
        Point a = l1.p1, b = l1.p2;
        Point c = l2.p1, d = l2.p2;
        
        double denom = (a.x - b.x) * (c.y - d.y) - (a.y - b.y) * (c.x - d.x);
        if (fabs(denom) < EPS) return Point(NAN, NAN); // 平行
        
        double x = ((a.x * b.y - a.y * b.x) * (c.x - d.x) - (a.x - b.x) * (c.x * d.y - c.y * d.x)) / denom;
        double y = ((a.x * b.y - a.y * b.x) * (c.y - d.y) - (a.y - b.y) * (c.x * d.y - c.y * d.x)) / denom;
        
        return Point(x, y);
    }
    
    // 计算点在线段上的投影
    Point projectPointToLine(const Point& p, const Line& l) const {
        Point v = l.p2 - l.p1;
        Point w = p - l.p1;
        double t = w.dot(v) / v.dot(v);
        return l.p1 + v * t;
    }
    
    // 计算反射方向
    Point reflectVector(const Point& incident, const Point& normal) const {
        Point n = normal.normalize();
        return incident - n * (2 * incident.dot(n));
    }
    
    // 模拟光线路径
    pair<bool, vector<Point>> simulateRayPath(int max_reflections = 1000) {
        vector<Point> path = {start};
        Point current_pos = start;
        Point current_dir = Point(cos(angle), sin(angle));
        set<int> visited_edges;
        
        for (int step = 0; step < max_reflections; step++) {
            // 找到下一个交点
            int hit_edge = -1;
            Point next_intersection;
            double min_dist = 1e18;
            
            for (int i = 0; i < polygon.size(); i++) {
                if (visited_edges.count(i)) continue;
                
                Line edge = polygon.getEdge(i);
                Line ray = Line(current_pos, current_pos + current_dir * 10000); // 长射线
                
                Point intersection = lineIntersection(ray, edge);
                if (isnan(intersection.x)) continue;
                
                // 检查交点是否在线段上
                Point v1 = intersection - edge.p1;
                Point v2 = edge.p2 - edge.p1;
                Point v3 = intersection - edge.p2;
                Point v4 = edge.p1 - edge.p2;
                
                if (v1.dot(v2) >= -EPS && v3.dot(v4) >= -EPS) {
                    // 检查方向是否正确
                    Point to_intersection = intersection - current_pos;
                    if (to_intersection.dot(current_dir) < EPS) continue;
                    
                    double dist = to_intersection.length();
                    if (dist < min_dist && dist > EPS) {
                        min_dist = dist;
                        next_intersection = intersection;
                        hit_edge = i;
                    }
                }
            }
            
            if (hit_edge == -1) {
                // 没有找到交点，光线射出多边形
                return {false, path};
            }
            
            // 记录访问的边
            visited_edges.insert(hit_edge);
            path.push_back(next_intersection);
            
            // 检查是否回到原点
            if ((next_intersection - Point(0, 0)).length() < EPS) {
                // 检查是否访问了所有边
                if (visited_edges.size() == polygon.size()) {
                    return {true, path};
                } else {
                    return {false, path};
                }
            }
            
            // 计算反射
            Line hit_edge_line = polygon.getEdge(hit_edge);
            Point edge_vector = hit_edge_line.p2 - hit_edge_line.p1;
            Point normal = Point(-edge_vector.y, edge_vector.x); // 法向量
            
            current_dir = reflectVector(current_dir, normal);
            current_pos = next_intersection;
            
            // 防止数值误差累积
            current_dir = current_dir.normalize();
        }
        
        return {false, path};
    }
};

// 测试函数
void testRayReflection() {
    // 创建一个正方形凸多边形
    vector<Point> square = {
        Point(-1, -1), Point(1, -1), Point(1, 1), Point(-1, 1)
    };
    Polygon poly(square);
    
    // 起点和角度
    Point start(0.5, 0.5);
    double angle = 45.0; // 度
    
    RayReflectionSimulator simulator(poly, start, angle);
    auto result = simulator.simulateRayPath();
    
    cout << "起点: (" << start.x << ", " << start.y << ")" << endl;
    cout << "角度: " << angle << "°" << endl;
    cout << "是否回到原点并访问所有边: " << (result.first ? "是" : "否") << endl;
    cout << "路径点:" << endl;
    
    for (int i = 0; i < result.second.size(); i++) {
        cout << "点" << i << ": (" << result.second[i].x << ", " << result.second[i].y << ")" << endl;
    }
}

int main() {
    int n;
    double start_x, start_y, angle;
    
    cout << "=== 凸多边形光线反射模拟 ===" << endl;
    
    // 输入多边形顶点数
    cout << "请输入凸多边形的顶点数: ";
    cin >> n;
    
    if (n < 3) {
        cout << "错误：多边形至少需要3个顶点！" << endl;
        return 1;
    }
    
    // 输入多边形顶点
    vector<Point> vertices;
    cout << "请按逆时针顺序输入多边形顶点坐标:" << endl;
    for (int i = 0; i < n; i++) {
        double x, y;
        cout << "顶点 " << i + 1 << " 的x坐标: ";
        cin >> x;
        cout << "顶点 " << i + 1 << " 的y坐标: ";
        cin >> y;
        vertices.push_back(Point(x, y));
    }
    
    // 输入起点坐标
    cout << "请输入起点坐标:" << endl;
    cout << "起点x坐标: ";
    cin >> start_x;
    cout << "起点y坐标: ";
    cin >> start_y;
    
    // 输入角度
    cout << "请输入射出角度(度, 逆时针方向): ";
    cin >> angle;
    
    // 创建多边形和模拟器
    Polygon poly(vertices);
    Point start(start_x, start_y);
    
    // 检查起点是否在多边形内
    if (!poly.isPointInside(start)) {
        cout << "警告：起点不在多边形内部！" << endl;
    }
    
    RayReflectionSimulator simulator(poly, start, angle);
    
    // 运行模拟
    cout << "\n开始模拟光线路径..." << endl;
    cout << "多边形顶点数: " << n << endl;
    cout << "起点: (" << start_x << ", " << start_y << ")" << endl;
    cout << "角度: " << angle << "°" << endl;
    
    auto result = simulator.simulateRayPath();
    
    cout << "\n=== 模拟结果 ===" << endl;
    if (result.first) {
        cout << "✓ 成功：光线回到原点并访问了所有边！" << endl;
    } else {
        cout << "✗ 失败：光线未能回到原点或未访问所有边" << endl;
    }
    
    // 显示路径详情
    cout << "\n光线路径详情:" << endl;
    cout << "总反射次数: " << result.second.size() - 1 << endl;
    for (int i = 0; i < result.second.size(); i++) {
        if (i == 0) {
            cout << "起点: ";
        } else {
            cout << "反射点" << i << ": ";
        }
        cout << "(" << result.second[i].x << ", " << result.second[i].y << ")" << endl;
    }
    while(true);
    return 0;
}