#ifndef ONLINE_JUDGE
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"
#endif

#include <iostream>
#include <sstream>
#include <algorithm>

struct Seg {
  int start;
  int end;
};

bool compareByEnd(Seg &seg1, Seg &seg2) {
  return seg1.end < seg2.end;
}

int fun(std::istream &ins) {
  int n; ins >> n;
  Seg segs[n];
  for(int i=0; i < n; i++) {
    ins >> segs[i].start;
    ins >> segs[i].end;
  }

  std::sort(segs, segs+n, compareByEnd);

  int count=1, current=0;
  for(int i=0; i < n; i++) {
    if(segs[i].start >= segs[current].end) {
      count++;
      current = i;
    }
  }

  return count;
}
int fun(std::string input) {
  std::stringstream ins(input);
  return fun(ins);
}

#ifndef ONLINE_JUDGE
TEST_CASE("test solution") {
  CHECK(fun("3\n0 2\n2 4\n1 3") == 2);
}
#endif

#ifdef ONLINE_JUDGE
int main() {
  std::cout << fun(std::cin);
  return 0;
}
#endif
