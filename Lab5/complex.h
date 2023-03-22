#ifndef COMPLEX_H_
#define COMPLEX_H_



#include <iostream>

using namespace std;
class Complex{

public:
  Complex();
  Complex(double, double);
  Complex(double);
  Complex(double,double, int);
  double getreal() const;
  void setComplex(double, double);
  double getimag() const;
  void displayPolar();
  void displayRect();
  void conjugate();
  int geterror() const;
  Complex operator+(Complex);
  Complex operator-(Complex);
  Complex operator*(Complex);
  Complex operator/(Complex);
  friend std::ostream& operator<< (std::ostream&, const Complex&);
private:
  double real;
  double imag;
  int error;

};

#endif
