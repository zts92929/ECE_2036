

#include "matrix.h"
#include <stdio.h>
#include <iomanip>
#include <iostream>

Matrix::Matrix(int rows, int columns)
{
    row = rows;
    column = columns;
    matrixPtr = new Complex[row*column];
}

Matrix::~Matrix()
{
    delete[] matrixPtr;
}

Matrix::Matrix(const Matrix& m){
    matrixPtr = new Complex[m.getRow() * m.getColumn()];
    Matrix temp(m.getRow(), m.getColumn());
    for (int i = 1; i <= m.getRow(); i++){
        for(int t = 1; t <= m.getColumn(); t++){
            temp(i,t) = m(i,t);
        }
    }
    (*this) = temp;
}

void Matrix::matrixErr()
{
    matrixPtr= NULL;
    cout<<"Matrix Mismatch Error!"<<endl;
    cout<<"This matrix has zero elements"<<endl;
}

int Matrix::getRow() const
{
    return(row);
}

int Matrix::getColumn() const
{
    return(column);
}

Complex& Matrix::operator()(int spotR, int spotC) const
{
    int spot = (spotR-1)*column + spotC-1;
    return(matrixPtr[spot]);
}

ostream & operator<<(ostream& output, const Matrix& matrix)
{
    for (int r = 1; (r <= matrix.getRow()); r++)
    {
        for (int c = 1; (c <= matrix.getColumn()); c++)
        {
            if (matrix(r,c).getimag()==0)
            {
            output << matrix(r,c).getreal() << setw(5) << " " ;
            }
            else
            {output << matrix(r,c) << setw(5) << " " ;}
        }
        output << "\n";
    }
    return output;
}

void Matrix::transpose()
{
  Matrix transmatrix(column, row);
  int rowcounter = 1;
  int test = 0;
  for(int i = 1; rowcounter <= row; test++)
  {
      if (i <= column){
          transmatrix(i, rowcounter) = (*this)(rowcounter,i);
          i++;

      }
      else
      {
          rowcounter++;
          i = 1;
      }
  }
  (*this) = transmatrix;
}
void Matrix::printMatrix()
{
    for (int r = 1; (r <= row); r++)
    {
        for (int c = 1; (c <= column); c++)
        {
          Complex temp= (*this)(r,c);

          if (temp.getimag()==0)
          {
            cout << temp.getreal()<< setw(5)<< " ";
          }

          else{

            cout << temp<< setw(5)<< " ";}
        }
        cout << "\n";
    }
}

Matrix& Matrix::operator=(const Matrix & m)
{
    delete[] matrixPtr;
    row = m.getRow();
    column =m.getColumn();
    matrixPtr = new Complex[row * column];
    for (int r = 1; (r<=row); r++)
    {
        for (int c = 1; (c<=column); c++)
        {
            (*this)(r,c) = m(r,c);
        }
    }
    return(*this);
}

Matrix Matrix::operator+(Matrix & m)
{
    Matrix AMatrix(row, column);
    if(row == m.getRow() and column == m.getColumn()){
        Matrix AMatrix(row, column);
        if ((row != m.getRow()) or (column != m.getColumn()))
        {
            matrixErr();
        }
        else
        {
            for (int r = 1; (r<=row); r++)
            {
                for (int c = 1; (c<=column); c++)
                {
                    AMatrix(r,c) = (*this)(r,c) + m(r,c);
                }
            }
        }
        return(AMatrix);
    }
    else{
        matrixErr();
        Matrix nullit(0,0);
        return nullit;
    }
}

Matrix Matrix::operator-(Matrix & m)
{
    if ((row != m.getRow()) or (column != m.getColumn()))
    {
        matrixErr();
        Matrix nullit(0,0);
        return nullit;
    }
    else
    {
        Matrix SMatrix(row, column);
        for (int r = 1; (r<=row); r++)
        {
            for (int c = 1; (c<=column); c++)
            {
                SMatrix(r,c) = (*this)(r,c) - m(r,c);
            }
        }
        return(SMatrix);
    }
}


Matrix Matrix::operator*(Matrix & m)
{
    if ((column != m.getRow()))
    {
        matrixErr();
        Matrix nullit(0,0);
        return nullit;
    }
    else
    {
        Matrix Mmatrix(row, m.getColumn());
        for(int i = 1; i <= row; i++){
            for(int t = 1; t <= m.getColumn(); t++){
                Complex Cnum(0,0);
                for(int j = 1; j <= m.getColumn(); j++){
                    Cnum = Cnum + (*this)(i,j)*m(j,t);\
                }
                Mmatrix(i,t) = Cnum;
            }
        }
        return Mmatrix;
        }
    }

Matrix Matrix::operator~(){
  Matrix transmatrix(column, row);
  int rowcounter = 1;
  int test = 0;
  for(int i = 1; rowcounter <= row; test++)
  {
      if (i <= column){
          transmatrix(i, rowcounter) = (*this)(rowcounter,i);
          i++;

      }
      else
      {
          rowcounter++;
          i = 1;
      }
  }
  return(transmatrix);
}

Matrix Matrix::operator!(){
    Matrix InvMatrix(row, column);
    for(int i = 1; i <= row; i++){
        for(int t = 1; t <= row; t++){
            (*this)(i,t).conjugate();
            InvMatrix(i,t) = (*this)(i,t);
        }
    }
    InvMatrix.transpose();
    return InvMatrix;
}

Matrix operator*(Complex num, Matrix & holder){
    Matrix doublehold(holder.getRow(),holder.getColumn());
    for(int i = 1; i <= holder.getRow(); i++){
        for(int t = 1; t <= holder.getColumn(); t++){
            doublehold(i,t) = holder(i,t)*num;
        }
    }
    return doublehold;
}

Matrix operator*(Matrix& holder, Complex num){
    Matrix doublehold(holder.getRow(),holder.getColumn());
    for(int i = 1; i <= holder.getRow(); i++){
        for(int t = 1; t <= holder.getColumn(); t++){
            doublehold(i,t) = holder(i,t)*num;
        }
    }
    return doublehold;
}
