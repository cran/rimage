/** 
 **  Copyright (c) 2003 Nikon Digital Technologies Co., Ltd.
 **  For complete license terms see file LICENSE
 **/

#include <assert.h>
#include "matrix.h"

Matrix::Matrix() {

  m = NULL;
  x=-1; y=-1; 
  //cerr << "*** constructed matrix object " << (int)this << " ***" << endl;

};


Matrix::Matrix(int i, int j) {

  //cout << " Matrix(int,int): " << i << "/" << j << endl;
//   m.resize(i);
//   //cout << "hier\n";
//   for(int n=0;n<i;n++)
//     {
//       m[n].resize(j);
//       //cerr << "n=" <<n << endl;
//       //getchar();
//     }
  x = i;
  y = j;
  m = new vector< vector<double> >();
  (*m).resize(i);
      for ( int ii=0; ii<i; ii++ )
 	(*m)[ii].resize(j);

  // (i,j)
  //cerr << "*** constructed matrix object " << (int)this << " ***" << endl;
  //cerr << "leaving..." << endl;
  //init();
}


Matrix::Matrix( Matrix &ma ) {

  //cerr << "*** entered Matrix::Matrix( Matrix& ma ) ***" << endl;
  //cerr << "address of ma = " << (int)&ma << endl;
  //cerr << "ma.getX() = " << ma.getX() << ", ma.getY() = " << ma.getY() << endl;
  //resize(ma.getX(),ma.getY());
  m = new vector< vector<double> >();
  //(ma.getX(),ma.getY())
  (*m).resize(ma.getX());
  for ( int i=0; i<ma.getX(); i++ )
    (*m)[i].resize(ma.getY());
  x = ma.getX();
  y = ma.getY();
  for( int i=0 ; i<ma.getX() ; i++ )
    for( int j=0 ; j<ma.getY() ; j++ )
      (*m)[i][j] = ma[i][j];
  //cerr << "*** constructed matrix object " << (int)this << " ***" << endl;

}


Matrix::~Matrix() {

  //cerr << "in Matrix::~Matrix()" << endl;
  //cerr << "*** deconstructing matrix object " << (int)this << " ***" << endl;
  delete(m);

}


vector<double>& Matrix::operator[](int i) {

  if( i>x || i<0 )
    {
      fprintf(stderr, "Matrix: illegal access on array of size %d / %d -- current cell accessed is: %d\n",x,y,i);
      abort();
    }
  assert(m);
  //assert((*m)[i]);
  return (*m)[i];
}


void Matrix::operator=(Matrix& ma) {

  //cerr << "***** entering Matrix::Operator=() *****" << endl;
  if( x!=ma.getX() || y!=ma.getY() )
    resize( ma.getX(), ma.getY() );
  for( int i=0 ; i<ma.getX() ; i++ )
    for( int j=0 ; j<ma.getY() ; j++ )
      (*m)[i][j] = ma[i][j];
  //cerr << "***** leaving Matrix::operator=() *****" << endl;

}



void Matrix::removeRow( int row ) {

  // m[i].remove(row)...
  //info();
  for( int i=0; i<(*m).size(); i++ )
    {
      vector<double>::iterator it = ((*m)[i]).begin();
      it += row;
      (*m)[i].erase(it);
    }
  y--;

}


void Matrix::removeColumn( int column ) {

  //info();
  vector< vector<double> >::iterator it = (*m).begin();
  it += column;
  (*m).erase(it);
  x--;

}



void Matrix::resize( int nx, int ny ) {

  //cerr << "***** entering Matrix::resize() *****" << endl;
  if( m==NULL ) {
    m = new vector< vector<double> >();
  // (nx,ny)
    (*m).resize(nx);
    for ( int i=0; i<nx; i++ )
 	(*m)[i].resize(ny);
  }
  else
    {
      (*m).resize(nx);
      for ( int i=0; i<nx; i++ )
	(*m)[i].resize(ny);
    }
  x = nx;
  y = ny;
  //cerr << "***** leaving Matrix::resize() *****" << endl;

}

void Matrix::set( double d ) {

  for( int i=0; i<x; i++ )
    for( int j=0; j<y; j++ )
      (*m)[i][j] = d;

}

void Matrix::deb(void) {

  string s("Short hello from Matrix...");
  fprintf(stderr,"%s\n", s.c_str());

};




Matrix& mapRtoC( double *img, int x, int y ) {

    Matrix& m = *(new Matrix(x,y));
    for( int i=0; i<x; i++ )
      for( int j=0; j<y; j++ )
	m[i][j] = img[ i*y + j ];
    return m;

}

void mapCtoR( Matrix & m, double *res ) {

  int x = m.getX();
  int y = m.getY();
  for( int i=0; i<x; i++ )
    for( int j=0; j<y; j++ )
      res[ i*y + j ] = m[i][j];

}




void Matrix::print(void) {

  cout << "\n ** Matrix is" << endl;
  for( int i=0; i<x; i++ )
    {
      for( int j=0; j<y; j++ )
	  cout << (*m)[i][j] << " ";
      cout << endl;
    }
  cout << "*********\n" << endl;

}

/*
Matrix::~Matrix() {

  info();
  //cout << "compared to this: m.size()="<<m.size()<<endl;
  //cout << "compared to this: m.size()="<<m.size()<<endl;
  vector< vector<double> >::iterator it = m.begin();
  cout << " m[0].size()=" << m[0].size() << endl;
  for( int i=0; i<m.size(); i++ )
    {
      //cout << " i=" << i << endl;
      //cout << " m[i].size()=" << m[i].size() << endl;
      //m.erase(it);
      m[i].clear();
      //cout << " m[i].size()=" << m[i].size() << endl;
      it--;
    }
  cout << "compared to this: m.size()="<<m.size()<<endl;

  m.clear();

}
*/
