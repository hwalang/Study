[leetcode](https://leetcode.com/problems/remove-element/description/)   

two pointer를 이용한 방법이 STL 뿐만 아니라 다른 자료 구조에도 활용할 수 있다고 판단해서 메모한다.   

# 풀이
## ME
```cpp
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
      for (auto it = nums.begin(); it != nums.end();) {
        if (*it == val) {
          it = nums.erase(it);
        }
        else {
          ++it;
        }
      }

      return nums.size();
    }
};
```

## Two-Pointer
```cpp
class Solution {
public:
  int removeElement(vector<int>& nums, int val) {
    int index = 0;
    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] != val) {
        nums[index] = nums[i];
        ++index;
      }
    }
    return index;
  }
};
```
index pointer는 `val과 같지 않은 element를 가리킨다`. 또한 `val 원소들을 제거한 nums 배열 원소의 수`를 나타낸다.   
i는 nums 배열을 순회하면서 모든 elements를 가리킨다.   