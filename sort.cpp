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

// insertion sort

inline void insertWithOrder(int value, int data[], int len) {
  int i = len-1;
  while(i >= 0 && data[i] > value) {
    data[i+1] = data[i];
    i--;
  }
  data[i+1] = value;
}

void insertionSort(int data[], int len) {
  for(int i = 0; i < len; i++) {
    insertWithOrder(data[i], data, i);
  }
}

// merge sort

void merge(int a[], int low, int mid, int high) {
  int temp[high-low+1];
  // subarray1 = a[low..mid], subarray2 = a[mid+1..high], both sorted
  int N = high-low+1;
  int b[N];
  int left = low, right = mid+1, bIdx = 0;
  while (left <= mid && right <= high) // 归并
    b[bIdx++] = (a[left] <= a[right]) ? a[left++] : a[right++];
  while (left <= mid) b[bIdx++] = a[left++]; // left-mid的剩余元素
  while (right <= high) b[bIdx++] = a[right++]; // right-high的剩余元素
  for (int k = 0; k < N; k++) a[low+k] = b[k]; // copy back
}

void mergeSort(int data[], int low, int high) {
  // 要排序的数组是 a[low..high]
  if (low < high) { // 基础情况: low >= high (0或1项)
    int mid = (low+high) / 2;
    mergeSort(data, low, mid ); // 分成两半
    mergeSort(data, mid+1, high); // 递归地将它们排序
    merge(data, low, mid, high); // 解决步骤: 归并子程序
  }
}

void mergeSort(int data[], int len) {
  mergeSort(data, 0, len-1);
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

  shuffle(data, data+COUNT, default_random_engine(0));
  insertionSort(data, COUNT);
  assertArrayEq(data, expected, COUNT);

  shuffle(data, data+COUNT, default_random_engine(0));
  mergeSort(data, COUNT);
  assertArrayEq(data, expected, COUNT);

  cout << "All pass" << endl;
}

int main() {

  test();
  return 0;
}
