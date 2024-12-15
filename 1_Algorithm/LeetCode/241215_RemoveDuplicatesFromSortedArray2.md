[leetcode](https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/description/?envType=study-plan-v2&envId=top-interview-150)   

최종 nums에는 최대 2번 중복을 허용하는 elements가 ascending order로 저장되어야 한다.   
해당 조건을 만족하는 원소의 수 `k`를 반환한다.   
다른 memory를 사용하지 않고 기존 nums만 이용한다.   

# 풀이
## ME
```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int cnt = 0;
        int k = 1;
        for (int i = 1; i < nums.size(); ++i) {
          if (nums[i - 1] != nums[i]) {
            cnt = 0;
            nums[k++] = nums[i];
          }
          else {
            ++cnt;
            if (cnt <= 1) { // 같은 원소가 2개만 존재
              nums[k++] = nums[i];
            }
          }
        }
        
        return k;
    }
};
```
중복 원소를 최대 2개까지 허용한다는 점을 착각해서 `cnt`의 최대값을 `2`로 설정해서 시간을 많이 소모했다.   

`nums`의 탐색을 위한 `i` index가 존재한다.   
`k`는 조건을 만족하는 `nums` elements의 수를 저장하고, `nums`를 탐색하면서 조건을 만족하는 elements를 앞으로 땡겨오기 위한 index이다.   
첫 번째 원소는 무조건 저장되기 때문에 `i`와 `k`를 1부터 시작한다.   

## Other
```cpp
int removeDuplicates(vector<int>& nums) {
    int i = 0;
    for (int n : nums)
        if (i < 2 || n > nums[i-2])
            nums[i++] = n;
    return i;
}
```
여기선 `i`가 내가 작성한 풀이의 `k`에 해당한다.   

처음에 2개의 `nums` elements를 `[0], [1]`에 순서대로 저장하고 시작한다.   
ascending order라서 `nums[i - 2]`가 `n`보다 큰 경우, `nums[i]`에 `n`을 저장한다. 이는 중복되지 않은 경우를 말한다.   
그 외의 경우는 아무런 기능이 없으므로 내가 작성한 풀이보다 효율적이다.   