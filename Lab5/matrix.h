

#ifndef matrix_h
#define matrix_h

#include "complex.h"
#include <iostream>

using namespace std;

class Matrix;
Matrix operator*(Complex, Matrix &);

class Matrix
{
friend std::ostream& operator<< (std::ostream&, const Matrix&);
friend Matrix operator*(Complex, Matrix &);
friend Matrix operator*(Matrix&, Complex);
private:
    int row;
    int column;
    Complex * matrixPtr;
public:
    Matrix(int, int);
    ~Matrix();
    Matrix(const Matrix & m);
    void matrixErr();
    int getRow() const;
    int getColumn() const;
    void transpose();
    void printMatrix();
    Matrix & operator=(const Matrix & m);
    Complex& operator()(int spotR, int spotC) const;
    Matrix operator+(Matrix &);
    Matrix operator-(Matrix &);
    Matrix operator*(Matrix &);
    Matrix operator~();
    Matrix operator!();
};

#endif /* matrix_h */
