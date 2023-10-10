#include "mat_f.h"
#include <assert.h>
#include <iostream>

using namespace std;

//default ctor
MatF::MatF():
  rows(0),
  cols(0),
  dimension(0),
  v(nullptr){}

// ctor with dim
MatF::MatF(int rows_, int cols_):
  rows(rows_),
  cols(cols_),
  dimension(rows*cols),
  v(new float[dimension]){}

// copy ctor
MatF::MatF(const MatF& other):
  MatF(other.rows, other.cols){
  for (int i=0; i<dimension; ++i)
    v[i]=other.v[i];
}

//dtor
MatF::~MatF() {
  if (dimension)
    delete [] v;
}

void MatF::fill(float f) {
  for (int i=0; i<dimension; ++i)
    v[i]=f;
}

void MatF::randFill() {
  for (int i=0; i<dimension; ++i)
    v[i]=drand48();
}

// read/write access to element at pos
float& MatF::at(int pos) {
  return v[pos];
}
  
// read access to element at pos
// const after () means that the method does not modify the invoking object
const float& MatF::at(int pos) const {
  return v[pos];
}

// read/write access to element at pos
float& MatF::at(int r, int c) {
  return v[r*cols+c];
}
  
// read access to element at pos
// const after () means that the method does not modify the invoking object
const float& MatF::at(int r, int c) const {
  return v[r*cols+c];
}

//op =, deep copy
MatF& MatF::operator =(const MatF& other) {
  // TODO: fillme
  //DONE
  rows = other.rows;
  cols = other.cols;
  dimension = other.dimension;
  if(v!=nullptr)
    free(v);
  v = new float[dimension];
  for (int i=0; i<dimension; ++i)
    v[i]=other.at(i);
  return *this;
}

//returns the sum this + other
MatF MatF::operator + (const MatF& other) const {
  assert (other.cols==cols && other.rows==rows && "dim mismatch");
  MatF returned (*this);
  // TODO: fillme
  //DONE
  for (int i=0; i<dimension; ++i)
    returned.at(i)+=other.at(i);  //this could not be possible if i didn't have two implementations of the 'at' method
  return returned;
}

//returns the difference this - other
MatF MatF::operator - (const MatF& other) const {
assert (other.cols==cols && other.rows==rows && "dim mismatch");
  MatF returned (*this);
  // TODO: fillme
  //DONE
  for (int i=0; i<dimension; ++i)
    returned.at(i)-=other.at(i);  //same as for the '+' operator
  return returned;
}  


// returns this*f
MatF  MatF::operator* (float f) const {
  MatF returned (*this);
  // TODO: fillme
  //DONE
  for (int i=0; i<dimension; ++i)
    returned.at(i)*=f;
}

// returns this* other where the other is a vector
VecF  MatF::operator* (const VecF& other) const {
  assert(other.dim==cols && "dim mismatch");
  VecF returned (rows);
  // TODO: fillme
  //DONE
  for (int r=0; r<rows; ++r) {
    returned.at(r)=0;
    for (int c=0; c<cols; ++c)
      returned.at(r)+=at(r,c)*other.at(c);
  }

  //prof solution
  // for (int i=0; i<rows; ++i) {
  //   float acc = 0.0f;
  //   for (int c=0; c<cols; ++c)
  //     acc+=at(i,c)*other.at(c);
  // returned.at(i)=acc;
  //}
  return returned;
}

  // returns this* other where the other is a matrix
MatF  MatF::operator* (const MatF& other) const {
  assert(cols==other.rows && "dimension mismatch");
  MatF returned(rows, other.cols);
  //TODO: fillme
  //DONE
  for (int r=0; r<rows; ++r)
    for (int c=0; c<other.cols; ++c) {
      returned.at(r,c)=0;
      for (int i=0; i<cols; ++i)
        returned.at(r,c)+=at(r,i)*other.at(i,c);
    }
  
  //prof solution
 //see solutions 
  return returned;
}

MatF MatF::transpose() const {
  MatF returned(cols, rows);
  for (int r=0; r<rows; ++r)
    for (int c=0; c<cols; ++c)
      returned.at(c,r)=at(r,c);
  return returned;
}


std::ostream& operator << (std::ostream& os, const MatF& m) {
  os << "{ ptr: " << &m <<", rows: " << m.rows << ",  cols: " << m.cols << endl;
  os << "  values:[ " << endl;
  for (int r=0; r<m.rows; ++r) {
    os << "\t";
    for (int c=0; c<m.cols; ++c) {
      os << m.at(r,c) <<  " ";
    }
    os << endl;
  }
  os << " ]" << endl << "}";
  return os;
      
}