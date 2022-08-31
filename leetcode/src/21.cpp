#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../doctest.h"
#include <iostream>

// using namespace std;

/**
 * Definition for singly-linked list.
 */
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

bool eq(ListNode *one, ListNode *other) {
  if(one!=nullptr && other!=nullptr) {
    return (one->val == other->val) && eq(one->next, other->next);
  } else if(one==nullptr && other==nullptr) return true;
  else return false;
}

std::string output(ListNode *list) {
  std::string result;
  ListNode *n = list;
  while(n!=nullptr) {
    result += std::to_string(n->val) + ",";
    n = n->next;
  }
  result += "\n";
  return result;
}


class Solution {
public:
  ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
    if(list1==nullptr) return list2;
    else if(list2==nullptr) return list1;
    else {
      ListNode * smaller = list1->val < list2->val ? list1 : list2;
      ListNode * bigger = list1->val < list2->val ? list2 : list1;
      smaller->next = mergeTwoLists(smaller->next, bigger);
      return smaller;
    }
  }
};

TEST_CASE("testing the solution") {
  Solution sol;
  CHECK(nullptr == sol.mergeTwoLists(nullptr, nullptr));

  ListNode *list1 = new ListNode(1);
  ListNode *list2 = new ListNode(2);
  CHECK(!eq(list1, list2));

  CHECK(eq(list1, sol.mergeTwoLists(list1, nullptr)));
  CHECK(eq(list2, sol.mergeTwoLists(nullptr, list2)));

  ListNode *list12 = new ListNode(1, new ListNode(2));
  CHECK(eq(list12, sol.mergeTwoLists(list1, list2)));

  list1 = new ListNode(1);
  list2 = new ListNode(2);
  CHECK(eq(list12, sol.mergeTwoLists(list2, list1)));

  ListNode *list13 = new ListNode(1, new ListNode(3));
  ListNode *list24 = new ListNode(2, new ListNode(4));
  ListNode *list1234 = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4))));
  ListNode *result = sol.mergeTwoLists(list13, list24);
  CHECK(eq(list1234, result));

}
