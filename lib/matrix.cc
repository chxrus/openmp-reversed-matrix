#include "matrix.h"

double **Matrix::Allocate(int n, int m) {
  double **matrix_ = new double *[n];
  for (int i = 0; i < n; i++) {
    matrix_[i] = new double[m]();
  }
  return matrix_;
}

Matrix::Matrix(int rows, int columns) : rows_(rows), columns_(columns) {
  matrix_ = Allocate(rows, columns);
}

Matrix::Matrix(const Matrix &origin) {
  rows_ = origin.get_rows();
  columns_ = origin.get_columns();
  matrix_ = Allocate(rows_, columns_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < columns_; j++) {
      matrix_[i][j] = origin[i][j];
    }
  }
}

Matrix::~Matrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

double *Matrix::operator[](int index) const {
  if (index < 0 || index >= rows_ * columns_) {
    throw out_of_range("Index out of range");
  }
  return matrix_[index];
}

bool Matrix::operator==(const Matrix &other) const {
  if (rows_ != other.get_rows() || columns_ != other.get_columns()) {
    return false;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < columns_; j++) {
      if ((matrix_[i][j] - other.matrix_[i][j]) > DBL_EPSILON) {
        return false;
      }
    }
  }
  return true;
}

bool Matrix::operator!=(const Matrix &other) const {
  if (rows_ != other.get_rows() || columns_ != other.get_columns()) {
    return true;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < columns_; j++) {
      if ((matrix_[i][j] - other.matrix_[i][j]) > DBL_EPSILON) {
        return true;
      }
    }
  }
  return false;
}

istream &operator>>(istream &is, Matrix &matrix) {
  for (int i = 0; i < matrix.get_rows(); i++) {
    for (int j = 0; j < matrix.get_columns(); j++) {
      cout << "matrix[" << i << "][" << j << "]: ";
      is >> matrix[i][j];
    }
  }
  return is;
}

ostream &operator<<(ostream &os, const Matrix &matrix) {
  for (int i = 0; i < matrix.get_rows(); i++) {
    for (int j = 0; j < matrix.get_columns(); j++) {
      os << matrix[i][j] << " ";
    }
    if (i != matrix.get_rows() - 1) {
      puts("\n");
    }
  }
  return os;
}

int Matrix::get_rows() const { return rows_; }

int Matrix::get_columns() const { return columns_; }

int Matrix::Size() const { return columns_ * rows_; }

void Matrix::PrintFmt(string title) const {
  // Save flags/precision.
  std::ios_base::fmtflags old_flags = std::cout.flags();
  std::streamsize old_precision = std::cout.precision();
  cout << title << endl;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < columns_; j++) {
      cout << fixed << setprecision(3) << showpos << matrix_[i][j] << "\t";
    }
    cout << "\n";
  }
  // Restore flags/precision.
  std::cout.flags(old_flags);
  std::cout.precision(old_precision);
}

template <class T>
void Matrix::RandomFill(int min, int max) {
  std::uniform_real_distribution<double> dist(min, max);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < columns_; j++) {
      T rand_num = (T)dist(generator);
      matrix_[i][j] = rand_num;
    }
  }
}