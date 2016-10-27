/* From Alex Li
   Basic matrix class with support for arithmetic operations
   as well as matrix multiplication and exponentiation. You
   can access/modify indices using m(r, c) or m[r][c]. You
   can also treat it as a 2d vector, since the cast operator
   to a reference to its internal 2d vector is defined. This
   makes it compatible with the 2d vector functions such as
   det() and lu_decompose() in later sections.
   */

#include <ostream>
#include <vector>
#define cmr const matrix &
#define fbo friend bool operator
#define fmo friend matrix operator

using namespace std;

template<class T> struct matrix {
    int r, c;
    vector<vector<T>> mat;

    matrix(int rows, int cols, T init = T()) {
        r = rows;
        c = cols;
        mat.resize(r, vector<T>(c, init));
    }

    matrix(const vector<vector<T>> & m) {
        r = m.size();
        c = m[0].size();
        mat = m;
        mat.resize(r, vector<T>(c));
    }

    template<size_t rows, size_t cols>
        matrix(T (&init)[rows][cols]) {
            r = rows;
            c = cols;
            mat.resize(r, vector<T>(c));
            for (int i = 0; i < r; i++)
                for (int j = 0; j < c; j++)
                    mat[i][j] = init[i][j];
        }

    operator vector<vector<T>>&() { return mat; }
    T & operator() (int r, int c) { return mat[r][c]; }
    vector<T> & operator[] (int r) { return mat[r]; }

    fbo <  (cmr a, cmr b) { return a.mat < b.mat; }
    fbo >  (cmr a, cmr b) { return a.mat > b.mat; }
    fbo <= (cmr a, cmr b) { return a.mat <= b.mat; }
    fbo >= (cmr a, cmr b) { return a.mat >= b.mat; }
    fbo == (cmr a, cmr b) { return a.mat == b.mat; }
    fbo != (cmr a, cmr b) { return a.mat != b.mat; }

    fmo + (cmr a, cmr b) {
        matrix res(a);
        for (int i = 0; i < res.r; i++)
            for (int j = 0; j < res.c; j++)
                res.mat[i][j] += b.mat[i][j];
        return res;
    }

    fmo - (cmr a, cmr b) {
        matrix res(a);
        for (int i = 0; i < a.r; i++)
            for (int j = 0; j < a.c; j++)
                res.mat[i][j] -= b.mat[i][j];
        return res;
    }

    fmo * (cmr a, cmr b) {
        matrix res(a.r, b.c, 0);
        for (int i = 0; i < a.r; i++)
            for (int j = 0; j < b.c; j++)
                for (int k = 0; k < a.c; k++)
                    res.mat[i][j] += a.mat[i][k] * b.mat[k][j];
        return res;
    }

    fmo + (cmr a, const T & v) {
        matrix res(a);
        for (int i = 0; i < a.r; i++)
            for (int j = 0; j < a.c; j++) res.mat[i][j] += v;
        return res;
    }

    fmo - (cmr a, const T & v) {
        matrix res(a);
        for (int i = 0; i < a.r; i++)
            for (int j = 0; j < a.c; j++) res.mat[i][j] -= v;
        return res;
    }

    fmo * (cmr a, const T & v) {
        matrix res(a);
        for (int i = 0; i < a.r; i++)
            for (int j = 0; j < a.c; j++) res.mat[i][j] *= v;
        return res;
    }

    fmo / (cmr a, const T & v) {
        matrix res(a);
        for (int i = 0; i < a.r; i++)
            for (int j = 0; j < a.c; j++)
                res.mat[i][j] /= v;
        return res;
    }

    friend ostream & operator << (ostream & out, cmr m) {
        out << "[";
        for (int i = 0; i < m.r; i++) {
            out << (i > 0 ? ",[" : "[");
            for (int j = 0; j < m.c; j++)
                out << (j > 0 ? "," : "") << m.mat[i][j];
            out << "]";
        }
        out << "]";
        return out;
    }
};

template <class T>
matrix<T> eye(int n) {
    matrix<T> res(n, n);
    for (int i = 0; i < n; i++) res[i][i] = 1;
    return res;
}

template <class T>
matrix<T> operator ^ (const matrix<T>& a, unsigned int n) {
    if (n == 0) return eye<T>(a.r);
    if (n % 2 == 0) return (a * a) ^ (n / 2);
    return a * (a ^ (n - 1));
}

//returns a^1 + a^2 + ... + a^n
template <class T>
matrix<T> powsum(const matrix<T>& a, unsigned int n) {
    if (n == 0) return matrix<T>(a.r, a.r);
    if (n % 2 == 0)
        return powsum(a, n / 2) * (eye<T>(a.r) + (a ^ (n / 2)));
    return a + a * powsum(a, n - 1);
}

/*** Example Usage ***/

#include <cassert>
#include <iostream>
using namespace std;

int main() {
    int a[2][2] = {{1,8}, {5,9}};
    matrix<int> m(5, 5, 10), m2(a);
    for (int i=0;i<m.r;++i)
        for(int j=0;j<m.c;++j)
            m[i][j] += 10;
    m[0][0] += 10;
    assert(m[0][0] == 30 && m[1][1] == 20);
    assert(powsum(m2, 3) == m2 + m2*m2 + (m2^3));
    return 0;
}
