#include <vector>
#include <cmath>

class segment_tree {
  private:
    inline int left(int i) { return i << 1; }
    inline int right(int i) { return (i << 1) + 1; }
    inline int mid(int i, int j) { return (i + j) / 2; }

    int n;
    vector<int> t;

    void build(const vector<int>& a) {
        build(a,1,0,n - 1);
    }

    void build(const vector<int>& a, int v, int l, int r) {
        if(l == r) {
            t[v] = a[l];
        } else {
            build(a,left(v),l,mid(l,r))
            build(a,left(v),mid(l,r) + 1, r);
            t[v] = t[left(v)] + t[right(v)];
        }
    }

    int sum(int v, int l, int r, int i, int j) {
        if(l > r) {
            return 0;
        } else if(l == i && r == j) {
            return t[v];
        } else {
            return sum(left(v), l, mid(l,r), i, min(r,mid(l,r)))
                + sum(right(v), mid(l,r) + 1, max(l,mid(l,r) + 1),j);
        }
    }

    void update(int v, int l, int r, int i, int val) {
        if(l == r) {
            t[v] = val;
        } else {
            if(i <= mid(l,r)) {
                update(left(v),l,mid(l,r),i,val);
            } else {
                update(right(v),mid(l,r)+1, i, val);
            }

            t[v] = t[left(v)] + t[right(v)];
        }
    }

  public:
    segment_tree(const vector<int>& a):
        n{(int) a.size()}, t(n << 2)
    {
        build(a);
    }

    int sum(int i, int j) {
        return sum(1,0,n - 1,i,j);
    }

    void update(int i, int val) {
        update(1,0,n - 1,i,val);
    }
};

int main() {}
