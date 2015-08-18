/* 
 * File:   MatrixGSL.h
 * Author: fordem
 *
 * Created on June 5, 2015, 6:00 PM
 */

#ifndef MATRIXGSL_H
#define	MATRIXGSL_H
#include <gsl/gsl_matrix.h>
#include <iostream>
#include <math.h>

class MatrixGSL {
public:
    MatrixGSL(u_int32_t, u_int32_t);
    MatrixGSL(double**, u_int32_t, u_int32_t);
    virtual ~MatrixGSL();
    void setElement(u_int32_t, u_int32_t, double);
    u_int32_t getLineSize();
    u_int32_t getColumnSize();
    double getElement(u_int32_t, u_int32_t);
    gsl_matrix * data();
    MatrixGSL & operator=(MatrixGSL&);
    MatrixGSL & operator=(gsl_matrix&);
    bool operator==(MatrixGSL&);
    bool operator!=(MatrixGSL&);
    void print();
    void transpose();
private:
    u_int32_t L, C;
    gsl_matrix * M;
};

inline void MatrixGSL::transpose() {
    gsl_matrix * T = gsl_matrix_alloc(C, L);
    u_int32_t temp = C;
    C = L;
    L = temp;
    gsl_matrix_transpose_memcpy(T, M);
    gsl_matrix_free(M);
    M = T;
}

inline bool MatrixGSL::operator==(MatrixGSL& op1) {
    if (this->data() != op1.data()) {
        if ((getColumnSize() == op1.getColumnSize())&&(getLineSize() == op1.getLineSize())) {
            for (u_int32_t i = 0; i < L; i++) {
                for (u_int32_t j = 0; j < C; j++) {
                    if (getElement(i, j) != op1.getElement(i, j)) {
                        return false;
                    }
                }
            }
            return true;
        }
        return false;
    } else {
        return true;
    }
}

inline bool MatrixGSL::operator!=(MatrixGSL& op1) {
    return !(*this == op1);
}

inline MatrixGSL& operator+(MatrixGSL & A, MatrixGSL & B) {
    if ((A.getColumnSize() == B.getColumnSize())&&(A.getLineSize() == B.getLineSize())) {
        gsl_matrix_add(A.data(), B.data());
    }
    return A;
}

inline MatrixGSL& operator-(MatrixGSL & A, MatrixGSL & B) {
    if ((A.getColumnSize() == B.getColumnSize())&&(A.getLineSize() == B.getLineSize())) {
        gsl_matrix_sub(A.data(), B.data());
    }
    return A;
}

inline MatrixGSL& operator*(MatrixGSL & A, double c) {
    gsl_matrix_scale(A.data(), c);
    return A;
}

inline MatrixGSL& operator*(MatrixGSL & A, MatrixGSL & B) {
    //2x3*3x2
    u_int64_t l1 = A.getLineSize();
    u_int64_t l2 = B.getLineSize();
    u_int64_t c1 = A.getColumnSize();
    u_int64_t c2 = B.getColumnSize();
    if (l2 == c1) {
        MatrixGSL * retorno = new MatrixGSL(l1, c2);
        for (u_int64_t i = 0; i < l1; i++) {
            for (u_int64_t j = 0; j < c2; j++) {
                for (u_int64_t k = 0; k < l2; k++) {
                    retorno->setElement(i, j, A.getElement(i, k) * B.getElement(k, j));
                }
            }
        }
        A = *retorno;
        delete retorno;
    }
    return A;
}

inline void MatrixGSL::print() {
    for (u_int32_t i = 0; i < L; i++) {
        for (u_int32_t j = 0; j < C; j++) {
            std::cout << getElement(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

inline MatrixGSL::MatrixGSL(double** data, u_int32_t Line, u_int32_t Column) {
    L = Line;
    C = Column;
    M = gsl_matrix_alloc(L, C);
    for (u_int32_t i = 0; i < L; i++) {
        for (u_int32_t j = 0; j < C; j++) {
            setElement(i, j, data[i][j]);
        }
    }
}
inline MatrixGSL & MatrixGSL::operator=(gsl_matrix& rhs){
    L=rhs.size1;
    C=rhs.size2;
    gsl_matrix * temp = gsl_matrix_alloc(L,C);
    for (u_int32_t i = 0; i < L; i++) {
        for (u_int32_t j = 0; j < C; j++) {
            gsl_matrix_set(temp,i, j, gsl_matrix_get(&rhs,i,j));
        }
    }
    gsl_matrix_free(M);
    M=temp;
    return *this;
}

inline MatrixGSL & MatrixGSL::operator=(MatrixGSL& rhs) {
    if (*this != rhs) {
        L = rhs.getLineSize();
        C = rhs.getColumnSize();
        gsl_matrix_free(M);
        M = gsl_matrix_alloc(L, C);
        for (u_int32_t i = 0; i < L; i++) {
            for (u_int32_t j = 0; j < C; j++) {
                setElement(i, j, rhs.getElement(i, j));
            }
        }
    }
    return *this;
}

inline gsl_matrix * MatrixGSL::data() {
    return M;
}

inline MatrixGSL::MatrixGSL(u_int32_t Line, u_int32_t Column) {
    L = Line;
    C = Column;
    M = gsl_matrix_alloc(L, C);
}

inline void MatrixGSL::setElement(u_int32_t Line, u_int32_t Column, double element) {
    if (Line < L && Column < C) {
        gsl_matrix_set(M, Line, Column, element);
    } else {
        std::cerr << "Indexes out of range, element: " << element << " not added" << std::endl;
    }
}

inline double MatrixGSL::getElement(u_int32_t Line, u_int32_t Column) {
    if (Line < L && Column < C) {
        return gsl_matrix_get(M, Line, Column);
    } else {
        std::cerr << "Indexes out of range, no element found." << std::endl;
        return NAN;
    }
}

inline u_int32_t MatrixGSL::getLineSize() {
    return L;
}

inline u_int32_t MatrixGSL::getColumnSize() {
    return C;
}

inline MatrixGSL::~MatrixGSL() {
    gsl_matrix_free(M);
}


#endif	/* MATRIXGSL_H */

