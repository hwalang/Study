[leetcode](https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/description/)   

std::string::find, two-pointer, KMP algorithm을 사용하여 특정 문자열에 원하는 부분 문자열의 첫 위치를 구한다.   

# 풀이
## ME
```cpp
int strStr(string haystack, string needle) {
  return haystack.find(needle);
}
```

## two-pointer 1
```cpp
int strStr(string haystack, string needle) {
  int m = haystack.size(), n = needle.size();
  for (int i = 0; i <= m - n; ++i) {
    int j = 0;
    for (; j < n; ++j) {
      if (haystack[i + j] != needle[j]) {
        break;
      }
    }

    if (j == n) {
      return i;
    }
  }
  return -1;
}
```

## two-pointer 2
```cpp
int strStr(string haystack, string needle) {
  int m = haystack.size(), n = needle.size();
  int p = 0;
  while (p + n - 1 < m) {
    if (haystack.substr(p, n) == needle) {
      return p;
    }
    while (++p + n - 1 < m && haystack[p] != needle[0]);
  }
  return -1;
}
```
`p + n - 1 < m` 조건은 현재 위치 p에서 needle의 길이 n을 더한 위치가 haystack 길이 m 보다 작은지 확인한다.   

`while (p++ + n - 1 < m && haystack[p] != needle[0]);`코드는 `++p;`로 대체할 수도 있지만, 효율성을 위해 추가됐다.   
p를 증가시키기만 하면 haystack의 index를 1씩 증가하면서 `p + n - 1`만큼 `substr()`을 계속 비교한다.   
반면에 while문은 needle의 첫 문자와 `haystack[p]`를 비교하여 같은 경우에만 p부터 n까지의 `substr()`을 `needle`과 비교한다.   
즉, **needle의 첫 문자와 일치하지 않는 haystack의 위치를 건너뛰어, 비교 가능한 위치로 빠르게 이동**한다.   

## KMP Algorithm
[KMP.md](/1_Algorithm/11_KMP.md)   
```cpp
class Solution {
public:
  int strStr(string haystack, string needle) {
    int n = haystack.length();
    int m = needle.length();

    std::vector<int> table = FailureFunction(needle);

    for (int i = 0, j = 0; i < n; ++i) {
      while (j > 0 && haystack[i] != needle[j]) {
        j = table[j - 1];
      }

      if (haystack[i] == needle[j]) {
        ++j;
      }

      if (j == m) {
        return i - j + 1;
      }
    }
    
    return -1;
  }

private:
  std::vector<int> FailureFunction(const string& pattern) {
    int m = pattern.length();
    std::vector<int> table(m, 0);

    int j = 0;
    for (int i = 1; i < m; ++i) {
      while (j > 0 && pattern[i] != pattern[j]) {
        j = table[j - 1];
      }

      if (pattern[i] == pattern[j]) {
        table[i] = ++j;
      }
      else {
        table[i] = 0;
      }
    }
    return table;
  }
};
```