#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <cstddef>
#include <functional>

class point {
public:
    int x,y;

    point();
    point(int _x, int _y);

    int& operator[](int i);

    size_t cantor() const;
    static size_t cantor(const point& p);
    static size_t cantor(int x, int y);

    size_t szudzik() const;
    static size_t szudzik(const point& p);
    static size_t szudzik(int x, int y);

    template <class T1, class T2>
    pair<T1,T2> to_pair();
    pair<int,int> to_pair();

    double length();
    static double length(point& p);
    static double length(int x, int y);

    point unit();
    static point unit(point& p);
    static point unit(int x, int y);

    point& operator+=(const point& p);
    point& operator-=(const point& p);
    point& operator*=(int m);
    point& operator/=(int m);
};

point operator+(const point& p);
point operator-(const point& p);
point operator+(const point& p, const point& q);
point operator-(const point& p, const point& q);
int operator*(const point& p, const point& q);
point operator*(int m, const point& p);
point operator*(const point& p, int m);
point operator/(const point& p, int d);
point operator^(const point& p, const point& q);
point operator%(const point& p, int m);

bool operator==(const point&p, const point& q);
bool operator<(const point& p, const point& q);
bool operator>(const point& p, const point& q);
bool operator<=(const point& p, const point& q);
bool operator>=(const point& p, const point& q);

ostream& operator<<(ostream& os, const point& p);
istream& operator>>(istream& is, point& p);


const point
    i_hat {1,0},
    j_hat {0,1},
    zero {0,0};

namespace std {
    template <>
    struct hash<point> {
        size_t operator()(const point& p) const;
    };
}

#endif
