#include "tester.h"

const string kDelimeter =
    "--- --- --- --- --- --- --- --- --- --- --- --- ---\n";

template <class Data, class Transformer>
Tester<Data, Transformer>::Tester(bool isVerbose, string prefix) {
  isVerbose_ = isVerbose;
  prefix_ = prefix;
  delimiter_ = kDelimeter;
}

template <class Data, class Transformer>
Tester<Data, Transformer>::Tester(bool isVerbose, string prefix,
                                  string delimiter)
    : Tester(isVerbose, prefix) {
  delimiter_ = delimiter;
}

template <class Data, class Transformer>
Data Tester<Data, Transformer>::Call(Data& data, Transformer transformer) {
  LogData(data);
  auto start_time = high_resolution_clock::now();
  Data result = transformer(data);
  auto end_time = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(end_time - start_time);
  LogData(result);
  cout << prefix_ << duration.count() << " ms." << endl;
  return result;
}

template <class Data, class Transformer>
void Tester<Data, Transformer>::Assert(Data& data1, Data& data2,
                                       string message) {
  if (data1 != data2) {
    cout << message << endl;
  }
}

template <class Data, class Transformer>
void Tester<Data, Transformer>::LogData(Data& data) {
  if (!isVerbose_) {
    return;
  }
  cout << delimiter_;
  cout << data << endl;
  cout << delimiter_;
}