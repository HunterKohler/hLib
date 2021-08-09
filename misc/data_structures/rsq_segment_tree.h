#ifndef LIB_DATA_STRUCTURES_RSQ_SEGMENT_TREE_H_
#define LIB_DATA_STRUCTURES_RSQ_SEGMENT_TREE_H_

// previously a member of competition-library

class rsq_segment_tree {
  private:
    inline int left(int i);
    inline int right(int i);
    inline int mid(int i, int j);

    int n,t[];

    void build(int a[]);
    void build(int a[], int v, int l, int r);
    int sum(int v, int l, int r, int i, int j);
    void update(int v, int l, int r, int i, int val);

  public:
    rsq_segment_tree(int a[], int _n);

    int sum(int i, int j);
    void update(int i, int val);
};

typedef rsq_segment_tree rsq_st;

#endif
