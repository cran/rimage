/** 
 **  Copyright (c) 2003 Nikon Digital Technologies Co., Ltd.
 **  For complete license terms see file LICENSE
 **/


#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

/*** memory style: first columns, then rows.
     so the 1st vector indicates columns, the 2nd rows ***/
class Matrix {

 private:
  vector< vector<double> >* m;
  int x,y;
 public:
  Matrix();
  Matrix( Matrix &ma );
  Matrix(int i, int j);
  ~Matrix();
  vector<double>& operator[](int i);
  void operator=(Matrix& ma);
  
  int getX() {return x;};
  int getY() {return y;};
  void removeColumn( int column );
  void removeRow( int row );
  void resize(int nx, int ny);
  void deb(void);
  void info(void) { cout << "rows=" << x << ", columns=" << y << endl; };
  void print();
  void init() { set(0.0); };
  void set(double d) ;
  //print()

};


Matrix& mapRtoC( double *img, int x, int y );
void mapCtoR( Matrix & m, double *res );


