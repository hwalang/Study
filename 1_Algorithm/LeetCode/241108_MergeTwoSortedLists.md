# Merge Two Sorted Lists
[leetcode](https://leetcode.com/problems/merge-two-sorted-lists/description/)   

struct pointer를 다루는 방법을 기록한다.   

# 풀이
## ME
```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* start_pos = new ListNode();    // Merge List의 첫 위치를 기억
        ListNode* cur = start_pos;
        while (list1 && list2) {
          if (list1->val <= list2->val) {
            cur->next = list1;
            list1 = list1->next;
          }
          else {
            cur->next = list2;
            list2 = list2->next;
          }
          cur = cur->next;
        }

        cur->next = list1 ? list1 : list2;   // nullptr이 아닌 나머지 list를 추가한다.

        return start_pos->next;   // 첫 위치 다음 node를 반환한다.
    }
};
```
### 1. Returned ListNode 초기화
ListNode의 첫 위치를 기억하여 반환하기 때문에 이를 기억하는 `start_pos`를 초기화한다.   
현재 노드를 탐색하면서 로직을 수행하기 때문에 현재 노드를 추적하는 `cur`을 선언하고, start_pos를 가리킨다.   
`주의`할 점은 ListNode의 기본 생성자는 val 값이 있다.   

### 2. Loop Logic
list1과 list2가 nullptr이 아닌 경우 loop를 수행한다.   
현재 list1과 list2의 val 값을 비교하여 작은 val을 가진 list를 `cur->next`에 저장한다.   
그 후 cur->next로 저장된 list는 다음 Node를 가리킨다.   

### 3. After Loop
loop가 끝나면 list1과 list2 둘 중 하나는 element가 남아 있기 때문에 남은 Nodes를 cur->next에 저장한다.   
list의 head를 저장하기 때문에 남은 node를 모두 저장할 수 있다.   

### 4. Return
첫 위치( start_pos )는 val = 0을 가지는 head이다.   
때문에 그 다음 위치인 `start_pos->next`를 반환한다.   