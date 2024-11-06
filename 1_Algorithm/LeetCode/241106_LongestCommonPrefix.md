# Longest Common Prefix
[leetcode](https://leetcode.com/problems/longest-common-prefix/description/)   

문자열 리스트의 각 elements의 가장 긴 공통 접두사를 찾는 로직을 구할 때, sort를 이용한 방법을 기록한다.   

# 풀이
## ME
```cpp
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
      // 1. strs.size()가 1이면, 첫 번째 원소를 반환한다.
      // 2. strs의 longest common prefix를 구한다.
      //    2.1. lcp에는 strs[0]을 저장한다.
      //    2.2. lcp와 strs[i]의 lcp를 구한다.
      //    2.3. 위 과정을 lcp의 크기가 0 또는 i가 strs.size()일 때, 종료한다.
      // 3. lcp를 반환한다.

      if (strs.size() == 1) return strs[0];
      string lcp = strs[0];
      for (int i = 1; i < strs.size(); ++i) {
        int j = 0;
        while (j < lcp.size() && j < strs[i].size()) {
          if (lcp[j] != strs[i][j]) {
            break;
          }
          ++j;
        }
        lcp = lcp.substr(0, j);
        if (lcp.size() == 0) break;
      }

      return lcp;
    }
};
```

## Other
```cpp
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
      string lcp = "";
      int size = strs.size();

      sort(strs.begin(), strs.end());

      string first = strs[0]; string last = strs[size - 1];
      for (int i = 0; i < min(first.size(), last.size()); ++i) {
        if (first[i] != last[i]) return lcp;
        lcp += first[i];
      }

      return lcp;
    }
};
```
arguments로 받은 strs를 sort한다.   
사전식으로 정렬된 리스트에서 첫 번째와 마지막 문자열의 공통 접두사를 찾으면, 전체 리스트의 모든 문자열이 공유하는 공통 접두사를 쉽게 파악할 수 있다.   