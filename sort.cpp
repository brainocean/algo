#include <iostream>
#include <cassert>
#include <algorithm>
#include <random>
#include <type_traits>

using namespace std;

void assertArrayEq(int data[], int expected[], int len) {
  for(int i = 0; i < len; i++) {
    assert(data[i]==expected[i]);
  }
}

void outputArray(int data[], int len) {
  for(int i=0; i < len; i++)
    cout << data[i] << ",";
  cout << endl;
}

// bubble sort

bool bubbleMax(int data[], int len) {
  bool swapped = false;
  for(int i = 0; i < len-1; i++) {
    if(data[i]>data[i+1]) {
      swap(data[i], data[i+1]);
      swapped = true;
    }
  }
  return swapped;
}

void bubbleSort(int data[], int len ) {
  bool swapped = false;
  for(int i = 0; i < len-1; i++) {
    swapped = bubbleMax(data, len-i);
    if(!swapped) return;
  }
}

#define testSort(algo, data, expected, len) {\
  shuffle(data, data+len,  default_random_engine(0)); \
  algo(data, len); \
  assertArrayEq(data, expected, len);}

void test() {

  const int COUNT = 7;
  int data[] = {1,2,3,4,5,6,7};
  int expected[] = {1,2,3,4,5,6,7};

  testSort(bubbleSort, data, expected, COUNT);

  cout << "All pass" << endl;
}

int main() {

  test();
  return 0;
}
