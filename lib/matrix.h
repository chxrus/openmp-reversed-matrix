#ifndef MATRIX_H
#define MATRIX_H

#include <cfloat>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::fixed;
using std::isnan;
using std::istream;
using std::ostream;
using std::out_of_range;
using std::setprecision;
using std::showpos;
using std::string;

std::default_random_engine generator(
    std::chrono::high_resolution_clock::now().time_since_epoch().count());

class Matrix {
 private:
  int rows_;
  int columns_;
  double **matrix_;
  double **Allocate(int, int);

 public:
  // Methods
  Matrix(int, int);
  Matrix(const Matrix &);
  ~Matrix();

  int get_rows() const;
  int get_columns() const;
  int Size() const;

  // Helpers
  void PrintFmt(string) const;
  template <class T>
  void RandomFill(int, int);

  // Operators
  double *operator[](int) const;
  bool operator==(const Matrix &) const;
  bool operator!=(const Matrix &) const;
  friend istream &operator>>(istream &, Matrix &);
  friend ostream &operator<<(ostream &, const Matrix &);
};

#include "matrix.cc"

#endif
