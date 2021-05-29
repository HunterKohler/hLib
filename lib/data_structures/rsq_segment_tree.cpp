#include <algorithm>

#include "./rsq_segment_tree.h"

// previously a member of competition-library


rsq_st::rsq_segment_tree(int a[], int _n): n{_n} { build(a); }

void rsq_st::build(int a[]) { build(a,1,0,n - 1); }
void rsq_st::build(int a[], int v, int l, int r) {
    if(l == r) {
        t[v] = a[l];
    } else {
        build(a,left(v),l,mid(l,r));
        build(a,left(v),mid(l,r) + 1, r);
        t[v] = t[left(v)] + t[right(v)];
    }
}

int rsq_st::sum(int i, int j) { return sum(1,0,n - 1,i,j); }
int rsq_st::sum(int v, int l, int r, int i, int j) {
    if(l > r) {
        return 0;
    } else if(l == i && r == j) {
        return t[v];
    } else {
        return sum(left(v), l, mid(l,r), i, std::min(r,mid(l,r)))
            + sum(right(v), mid(l,r) + 1, r, std::max(l,mid(l,r) + 1),j);
    }
}

void rsq_st::update(int i, int val) { update(1,0,n - 1,i,val); }
void rsq_st::update(int v, int l, int r, int i, int val) {
    if(l == r) {
        t[v] = val;
    } else {
        if(i <= mid(l,r)) {
            update(left(v),l,mid(l,r),i,val);
        } else {
            update(right(v),mid(l,r)+1, r, i, val);
        }

        t[v] = t[left(v)] + t[right(v)];
    }
}

inline int rsq_st::left(int i) { return i << 1; }
inline int rsq_st::right(int i) { return (i << 1) + 1; }
inline int rsq_st::mid(int i, int j) { return (i + j) / 2; }