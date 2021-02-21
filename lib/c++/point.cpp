#include "point.hpp"

point::point(): point(0,0) { }
point::point(int _x, int _y): x { _x }, y { _y } { }

int& point::operator[](int i) {
    if (i == 0) return x;
    if (i == 1) return y;
    throw std::out_of_range("point subscript out of range 0 <= i <= 1");
}

size_t point::cantor() const { return cantor(*this); }
size_t point::cantor(const point& p) { return cantor(p.x,p.y); }
size_t point::cantor(int x, int y) {
    x = point::hash_sign(x);
    y = point::hash_sign(y);
    return (x + y + 1) * (x + y) / 2 + y;
}

size_t point::szudzik() const { return szudzik(*this); }
size_t point::szudzik(const point&p) { return szudzik(p.x,p.y); }
size_t point::szudzik(int x, int y) {
    x = point::hash_sign(x);
    y = point::hash_sign(y);
    return x < y ? y * y + x : x * x + x + y;
}

template <class T1, class T2>
std::pair<T1,T2> point::to_pair() { return {x,y}; }
std::pair<int,int> point::to_pair() { return {x,y}; }

double point::length() { return hypot(x,y); }
double point::length(point& p) { return hypot(p.x,p.y); }
double point::length(int x, int y) { return hypot(x,y); }

int point::hash_sign(int x) { return x > 0 ? 2 * x : -2 * x + 1; }

point& point::operator+=(const point& p) { x += p.x; y += p.y; return *this; }
point& point::operator-=(const point& p) { x -= p.x; y -= p.y; return *this; }
point& point::operator*=(int m) { x *= m; y *= m; return *this; }
point& point::operator/=(int m) { x /= m; y /= m; return *this; }

point operator+(const point& p) { return p; };
point operator-(const point& p) { return {-p.x, -p.y}; };
point operator+(const point& p, const point& q) { return {p.x + q.x, p.y + q.y}; }
point operator-(const point& p, const point& q) { return {p.x - q.x, p.y - q.y}; }
int operator*(const point& p, const point& q) { return p.x * q.x + p.y * q.y; }
point operator*(int m, const point& p) { return {m * p.x, m * p.y}; }
point operator*(const point& p, int m) { return {m * p.x, m * p.y}; }
point operator/(const point& p, int d) { return {p.x / d, p.y / d}; }
point operator^(const point& p, const point& q) { return {p.x * q.x, p.y * q.y}; }

bool operator==(const point&p, const point& q) { return p.x == q.x && p.y == q.y; }
bool operator<(const point& p, const point& q) { return p.x < q.x && p.y < q.y; }
bool operator>(const point& p, const point& q) { return p.x > q.x && p.y > q.y; }
bool operator<=(const point& p, const point& q) { return p.x <= q.x && p.y <= q.y; }
bool operator>=(const point& p, const point& q) { return p.x >= q.x && p.y >= q.y; }

std::ostream& operator<<(std::ostream& os, const point& p) { return os << "(" << p.x << "," << p.y << ")"; }
std::istream& operator>>(std::istream& is, point& p) { return is >> p.x >> p.y; }

size_t std::hash<point>::operator()(const point& p) const { return p.szudzik(); }

int main() { }
