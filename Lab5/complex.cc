#include "complex.h"
#include <math.h>
#include <iostream>

#define PI 3.14159265

using namespace std;





int Complex::geterror() const
{return(error);}

Complex::Complex()
{
  setComplex(0,0);
  error=0;
}

Complex::Complex(double Real)
{
  setComplex(Real,0);
  error=0;
}

void Complex::conjugate(){
    imag = imag * -1;
}

Complex::Complex(double Real, double Imag)
{
  setComplex(Real,Imag);
  error=0;
}

Complex::Complex(double Real, double, int e)
{
  setComplex(NAN,NAN);
  error=1;
}

double Complex::getreal() const
{
  return (real);
}

double Complex::getimag() const
{
  return (imag);
}

void Complex::setComplex(double Real, double Imag)
{
  real=Real;
  imag=Imag;
}

void Complex::displayPolar()
{
  double r=sqrt((getreal()*getreal())+(getimag()*getimag()));
  double theta= atan(getimag()/getreal());
  if(getreal()<0 && getimag()>0)
  {
    theta+= PI;
  }
  else if(getreal()<0 && getimag()<0)
  {
    theta-=PI;
  }
  if (error==1)
  {
    cout<<"NaN"<<"\n";
  }
  else{
    cout <<r << " < "<<theta<<"\n";
  }
}

Complex Complex::operator+(Complex RHS)
{
  double r= getreal()+RHS.getreal();
  double i= getimag()+RHS.getimag();
  Complex SUM(r,i);
  return (SUM);
}

Complex Complex::operator-(Complex RHS)
{
  double r=getreal()-RHS.getreal();
  double i=getimag()-RHS.getimag();
  Complex SUM(r,i);
  return (SUM);
}

Complex Complex::operator*(Complex RHS)
{
  double r=getreal()*RHS.getreal()-getimag()*RHS.getimag();
  double i=(getreal()+getimag())*(RHS.getreal()+RHS.getimag())-getreal()*RHS.getreal()-getimag()*RHS.getimag();
  Complex MULT(r,i);
  return (MULT);
}

Complex Complex::operator/(Complex RHS){
  if(RHS.getreal()*RHS.getreal()+RHS.getimag()*RHS.getimag()==0)
  {
    int e=1;
    double r=NAN;
    double i=NAN;
    Complex err(r,i,e);
    return(err);
  }
  double r=((getreal()*RHS.getreal()+getimag()*RHS.getimag())/(RHS.getreal()*RHS.getreal()+RHS.getimag()*RHS.getimag()));
  double i=((getimag()*RHS.getreal()-getreal()*RHS.getimag())/(RHS.getreal()*RHS.getreal()+RHS.getimag()*RHS.getimag()));
  Complex DIV(r,i);
  return(DIV);
}

void Complex::displayRect()
{
  if (geterror()==1)
  {
    cout<<"NaN"<<"\n";
  }
  else
  {
  cout<<getreal()<< " + " << getimag()<<"j"<<"\n";
  }
}

ostream & operator<<(ostream& output, const Complex& test)
{
  if(test.geterror()==1)
  {
    output<<"NaN";
  }
  else{
    output <<test.getreal()<< " + " << test.getimag()<<"j";
  }
  return (output);
}
