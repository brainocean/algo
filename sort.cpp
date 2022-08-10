#include <cmath>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <random>
#include <climits>

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

inline bool bubbleMaxToRight(int data[], int len) {
  bool swapped = false;
  for(int i = 0; i < len-1; i++) {
    if(data[i]>data[i+1]) {
      swap(data[i], data[i+1]);
      swapped = true;
    }
  }
  return swapped;
}

void bubbleSort(int data[], int len) {
  bool swapped = false;
  for(int i = 0; i < len-1; i++) {
    swapped = bubbleMaxToRight(data, len-i);
    if(!swapped) return;
  }
}

// selection sort

inline int findMax(int data[], int len) {
  int idx = 0;
  int max = INT_MIN;
  for(int i = 0; i < len; i++) {
    if(data[i]>max) {
      idx = i;
      max = data[i];
    }
  }
  return idx;
}

inline void swapMaxToRight(int data[], int len) {
  int maxIdx = findMax(data, len);
  if (maxIdx != len - 1) {
    swap(data[maxIdx], data[len - 1]);
  }
}

void selectionSort(int data[], int len) {
  for(int i = 0; i < len; i++) {
    swapMaxToRight(data, len-i);
  }
}

void test() {

  const int COUNT = 7;
  int data[] = {1,2,3,4,5,6,7};
  int expected[] = {1,2,3,4,5,6,7};

  shuffle(data, data+COUNT, default_random_engine(0));
  bubbleSort(data, COUNT);
  assertArrayEq(data, expected, COUNT);

  shuffle(data, data+COUNT, default_random_engine(0));
  selectionSort(data, COUNT);
  assertArrayEq(data, expected, COUNT);

  cout << "All pass" << endl;
}

int main() {

  test();
  return 0;
}
