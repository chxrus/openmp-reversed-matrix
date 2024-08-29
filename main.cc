#include <io.h>

#include <chrono>
#include <fstream>
#include <iostream>

#include "lib/matrix_math.h"
#include "lib/matrix_math_parallel.h"
#include "lib/tester.h"

using std::cin;
using std::cout;
using std::endl;
using std::left;
using std::ofstream;
using std::right;
using std::setw;
using std::string;
using namespace std::chrono;

using M = Matrix;
using MM = MatrixMath;
using MMP = MatrixMathParallel;

struct SizesData {
  size_t length_;
  size_t *sizes_;
};

void Run(bool, bool);
M *FillHandler(bool, size_t);
SizesData SizeHandler(bool);

const string kMatrixesNotEqualMsg = "The matrices 1 and 2 are not equal";
const int kMinRandomValue = 10;
const int kMaxRandomValue = 10000;
auto sequenceTester = Tester<M, MM (*)(const M &)>(true, "Sequential: ");
auto parallelTester = Tester<M, MMP (*)(const M &)>(false, "Parallel: ");
auto assert = Tester<M, void (*)()>::Assert;

int main() {
  int choice;
  cout << "1. Single run" << endl;
  cout << "2. Multiple run" << endl;
  cout << "3. Single run with user input" << endl;
  cout << "4. Multiple run with user input" << endl;
  cout << "5. File run. Test with user input for size of matrixes sizes and "
          "run times"
       << endl;
  cin >> choice;
  if (choice == 1) Run(false, false);
  if (choice == 2) Run(true, false);
  if (choice == 3) Run(false, true);
  if (choice == 4) Run(true, true);
  return 0;
}

void Run(bool isMultiple, bool userFills) {
  SizesData sizes = SizeHandler(isMultiple);
  system("cls");
  for (size_t i = 0; i < sizes.length_; i++) {
    size_t n = sizes.sizes_[i];
    M *matrix = FillHandler(userFills, n);
    cout << "Matrix #" << i << " size: " << n << endl;
    M matrix1 = sequenceTester.Call(*matrix, MM::Reversal);
    M matrix2 = parallelTester.Call(*matrix, MMP::Reversal);
    assert(matrix1, matrix2, kMatrixesNotEqualMsg);
    delete matrix;
  }
}

M *FillHandler(bool userFills, size_t size) {
  M *matrix = new M(size, size);
  if (userFills) {
    cin >> *matrix;
  } else {
    (*matrix).RandomFill<int>(kMinRandomValue, kMaxRandomValue);
  }
  return matrix;
}

SizesData SizeHandler(bool isMultiple) {
  SizesData sizes;
  if (isMultiple) {
    puts("Enter size length: ");
    cin >> sizes.length_;
  } else {
    sizes.length_ = 1;
  }
  sizes.sizes_ = new size_t[sizes.length_];
  for (size_t i = 0; i < sizes.length_; i++) {
    cout << "Enter size #" << i + 1 << ": ";
    cin >> sizes.sizes_[i];
  }
  return sizes;
}

void FileTest() {
  string fname1, fname2;
  cout << "Enter sequence algorithm filename: ";
  cin >> fname1;
  cout << "Enter parallel algorithm filename: ";
  cin >> fname2;

  cout << "Size for matrixes: " << endl;
  SizesData sizes = SizeHandler(true);
  cout << "Size for multiple times running: " << endl;
  SizesData times = SizeHandler(true);

  ofstream file1(fname1);
  ofstream file2(fname2);
  for (size_t i = 0; i < sizes.length_; i++) {
    size_t n = sizes.sizes_[i];
    M *matrix = FillHandler(false, n);
    double measure1 = 0, measure2 = 0;
    for (size_t j = 0; j < times.sizes_[i]; j++) {
      auto start = high_resolution_clock::now();
      M matrix1 = sequenceTester.Call(*matrix, MM::Reversal);
      auto end = high_resolution_clock::now();
      auto duration =
          duration_cast<std::chrono::nanoseconds>(end - start).count();
      measure1 += duration;

      start = high_resolution_clock::now();
      M matrix2 = parallelTester.Call(*matrix, MMP::Reversal);
      end = high_resolution_clock::now();
      duration = duration_cast<std::chrono::nanoseconds>(end - start).count();
      measure2 += duration;
    }
    file1 << n << ";" << measure1 / 1e9 / times.sizes_[i] << endl;
    file2 << n << ";" << measure2 / 1e9 / times.sizes_[i] << endl;
    cout << "Size " << n << " has successfully written to file" << endl;
    delete matrix;
  }
  file1.close();
  file2.close();
}