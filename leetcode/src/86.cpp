#define LOCAL_TEST
#ifdef LOCAL_TEST
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../doctest.h"
#include "ListNode.h"
#endif

class Solution {
public:
  ListNode *partition(ListNode *head, int x) {
    ListNode *smallerHead = new ListNode(-1);
    ListNode *smallerTail = smallerHead;
    ListNode *biggerHead = new ListNode(-1);
    ListNode *biggerTail = biggerHead;

    ListNode *cur = head;
    for(cur = head; cur!=nullptr; cur=cur->next) {
      if(cur->val < x) {
        smallerTail->next = cur;
        smallerTail = cur;
      } else {
        biggerTail->next = cur;
        biggerTail = cur;
      }
    }
    smallerTail->next = biggerHead->next;
    biggerTail->next = nullptr;

    return smallerHead->next;
  }
};

#ifdef LOCAL_TEST
TEST_CASE("testing the solution") {
  Solution sol;
  CHECK(nullptr == sol.partition(nullptr, 0));

  CHECK(eq(sol.partition(buildList("2,1"), 2), buildList("1,2")));

  ListNode *input = buildList("1,4,3,2,5,2");
  CHECK(eq(sol.partition(input, 3), buildList("1,2,2,4,3,5")));
}
#endif
