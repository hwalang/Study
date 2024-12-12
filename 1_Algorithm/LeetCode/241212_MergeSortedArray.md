[leetcode](https://leetcode.com/problems/merge-sorted-array/description/?envType=study-plan-v2&envId=top-interview-150)   

두 배열이 주어졌을 때, nums1은 m + n 크기를 가지고 nums2는 n 크기를 가진다. 두 정렬은 오름차순으로 정렬됐다.   
nums1은 m개의 원소를 가지며, 나머지 n개는 merge 이후의 배열 크기를 포함한 것이다. 때문에 n개의 원소들은 0으로 초기화되어 있다.   
이러한 두 배열을 merge하고, 오름차순으로 정렬하는 방법을 알아본다. 참고로 STL은 사용하지 않고 순수 구현으로 문제를 풀이한다.   

# 풀이
## Other
```cpp
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
      int i = m - 1;
      int j = n - 1;
      int k = m + n - 1;
      while (j >= 0) {
        if (i >= 0 && nums1[i] > nums2[j]) {
          nums1[k] = nums1[i];
          --i;
        }
        else {
          nums1[k] = nums2[j];
          --j;
        }
        --k;
      }
    }
};
```
merge sorted array의 마지막 index에 들어가는 원소를 두 배열의 마지막 원소를 기준으로 비교를 통해 선택한다.   
때문에 `k`는 loop가 수행될 때마다 줄어들며, `i, j`는 `k` 위치에 들어가는 경우에만 줄어든다.   