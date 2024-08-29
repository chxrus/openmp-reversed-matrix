#include "matrix_math.h"

MatrixMath::MatrixMath(int rows, int columns) : Matrix(rows, columns) {}

void MatrixMath::DecomposeLU(const Matrix &a, Matrix &l, Matrix &u) {
  int n = (int)sqrt(a.Size());

  for (int i = 0; i < n; i++) {
    l[i][i] = 1;

    for (int j = i; j < n; j++) {
      u[i][j] = a[i][j];
      for (int k = 0; k < i; k++) {
        u[i][j] -= l[i][k] * u[k][j];
      }
    }

    for (int j = i + 1; j < n; j++) {
      l[j][i] = a[j][i];
      for (int k = 0; k < i; k++) {
        l[j][i] -= l[j][k] * u[k][i];
      }
      l[j][i] /= u[i][i];
    }
  }
}

MatrixMath MatrixMath::SolveLU(Matrix &l, Matrix &u, Matrix &e) {
  int n = (int)sqrt(l.Size());
  MatrixMath x = MatrixMath(n, n);

  for (int i = 0; i < n; i++) {
    MatrixMath y = MatrixMath(1, n);

    for (int j = 0; j < n; j++) {
      y[j / n][j % n] = e[j][i];
      for (int k = 0; k < j; k++) {
        y[j / n][j % n] -= l[j][k] * y[k / n][k % n];
      }
    }

    for (int j = n - 1; j >= 0; j--) {
      x[j][i] = y[j / n][j % n];
      for (int k = j + 1; k < n; k++) {
        x[j][i] -= u[j][k] * x[k][i];
      }
      x[j][i] /= u[j][j];
    }
  }

  return x;
}

MatrixMath MatrixMath::Reversal(const Matrix &origin) {
  int n = origin.get_rows();

  MatrixMath u = MatrixMath(n, n);
  MatrixMath l = MatrixMath(n, n);
  MatrixMath e = MatrixMath::Identity(n);

  MatrixMath::DecomposeLU(origin, l, u);

  MatrixMath reversal = MatrixMath::SolveLU(l, u, e);

  return reversal;
}

MatrixMath MatrixMath::Identity(int n) {
  MatrixMath a(n, n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      a[i][j] = (i == j) ? 1 : 0;
    }
  }
  return a;
}