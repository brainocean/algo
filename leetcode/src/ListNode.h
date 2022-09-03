#ifndef LISTNODE_H_
#define LISTNODE_H_

#include <iostream>
#include <vector>
#include <sstream>

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

std::vector<int> parseString(const std::string& str) {
  char delim = ',';
    std::stringstream ss(str);
    std::string item;
    std::vector<int> elems;
    while (std::getline(ss, item, delim)) {
        if (!item.empty()) {
            elems.push_back(stoi(item));
        }
    }
    return elems;
}

ListNode * buildList(std::string s) {
  ListNode *cur = new ListNode(-1);
  ListNode *head = cur;
  std::vector<int> items = parseString(s);
  for(std::vector<int>::iterator itr=items.begin(); itr!=items.end(); itr++) {
    cur->next = new ListNode(*itr);
    cur = cur->next;
  }
  ListNode *ret = head->next;
  delete head;
  return ret;
}


#endif // LISTNODE_H_
