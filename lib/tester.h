#ifndef TESTER_H
#define TESTER_H

#include <chrono>
#include <iostream>

using std::cout;
using std::string;
using namespace std::chrono;

template <class Data, class Transformer>
class Tester {
 public:
  // Methods
  Tester(bool, string);
  Tester(bool, string, string);
  Data Call(Data&, Transformer);

  // Static
  static void Assert(Data&, Data&, string);

 private:
  // Fields
  bool isVerbose_;
  string prefix_;
  string delimiter_;

  // Methods
  void LogData(Data&);
};

#include "tester.cc"

#endif
