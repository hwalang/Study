# Remove Duplicates from Sorted Array
[leetcode](https://leetcode.com/problems/remove-duplicates-from-sorted-array/solutions/3676877/best-method-100-c-java-python-beginner-friendly/)   

std::unique가 아닌 two-point를 이용해서 풀이한 방법을 기록한다.   

# 풀이
## ME
```CPP
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        // std::unique를 이용하여 nums에 중복 elements를 제거한다.
        // nums.size()를 반환한다.
        auto last = unique(nums.begin(), nums.end());
        nums.erase(last, nums.end());
        return nums.size();
    }
};
```

## Two-Point
```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
      int j = 1;
      for (int i = 1; i < nums.size(); ++i) {
        if (nums[i] != nums[i - 1]) {
          nums[j] = nums[i];
          ++j;
        }
      }
      return j;
    }
};
```
### Approach
j는 unique elements를 추적하는 index이다.   
nums[0]은 항상 unique하기 때문에 loop를 j와 loop의 index를 1부터 시작한다.   

loop 내부에서 nums[i]와 num[i - 1]이 같지 않으면 nums[i]가 unique하기 때문에 nums[j]에 nums[i]를 저장하고, j를 증가시킨다.   

j는 unique elements의 개수도 의미하기 때문에 j를 반환한다.   