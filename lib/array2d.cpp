template <class T>
class array2d {
  private:
    T* mem;
    int n,m;
  public:
    typedef T value_type;
    array2d(int,int);
    ~array2d();
    T* operator[](int i);

    int width() const;
    int length() const;
};

template <class T> array2d<T>::array2d(int _n, int _m): n{_n},m{_m},mem{new T[m*n]} {}
template <class T> array2d<T>::~array2d() {delete[] mem;}
template <class T> T* array2d<T>::operator[](int i) { return mem[n*i]; }
