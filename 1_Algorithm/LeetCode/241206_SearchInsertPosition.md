[leetcode](https://leetcode.com/problems/search-insert-position/description/)   

binary search 기능을 구현하여 nums array에 target이 있으면 해당 index를 반환하고, 없으면 target이 순서에 맞춰 존재할 수 있는 index를 반환한다.   

참고로 nums는 중복된 elements가 없으며, ascending order로 정렬됐다.   
그리고 O(logN)으로 기능을 구현해야 한다.   

# Solution
```cpp
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
      int low = 0;
      int high = nums.size();
      int mid;

      if (target > nums[high - 1]) {
        return high;
      }

      while (low <= high) {
        mid = (low + high) / 2;
        if (nums[mid] == target) {
          return mid;
        }

        if (target < nums[mid]) {
          high = mid - 1;
        }
        else {
          low = mid + 1;
        }
      }

      return low;
    }
};
```
binary search 기능을 구현하기 위해서 low, mid, high index를 구분했다.   
만약 nums[high - 1]보다 target이 크다면, high를 반환한다.   

low가 high보다 작거나 같을 때까지 loop를 반복한다.   
loop가 반복될 때마다 mid index를 초기화한다.   
nums[mid]가 target과 같으면 mid를 반환한다. target이 nums[mid]보다 작으면 high를 mid - 1로 지정하고, 반대인 경우는 low를 mid + 1로 세팅한다.   
loop가 종료하면 low를 반환한다.   