#define LOCAL_TEST
#ifdef LOCAL_TEST
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../doctest.h"
#include "ListNode.h"
#endif

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

#ifdef LOCAL_TEST
TEST_CASE("testing the solution") {
  Solution sol;
  CHECK(nullptr == sol.mergeTwoLists(nullptr, nullptr));

  ListNode *list1 = buildList("1");
  ListNode *list2 = buildList("2");
  CHECK(!eq(buildList("1"), buildList("2")));

  CHECK(eq(list1, sol.mergeTwoLists(list1, nullptr)));
  CHECK(eq(list2, sol.mergeTwoLists(nullptr, list2)));

  ListNode *list12 = buildList("1,2");
  CHECK(eq(list12, sol.mergeTwoLists(list1, list2)));

  list1 = buildList("1");
  list2 = buildList("2");
  CHECK(eq(list12, sol.mergeTwoLists(list2, list1)));

  ListNode *list13 = buildList("1,3");
  ListNode *list24 = buildList("2,4");
  ListNode *list1234 = buildList("1,2,3,4");
  ListNode *result = sol.mergeTwoLists(list13, list24);
  CHECK(eq(list1234, result));

}
#endif
