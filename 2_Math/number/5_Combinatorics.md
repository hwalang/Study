- [Combinatorics( 조합론 )](#combinatorics-조합론-)
- [1. Permutation](#1-permutation)
  - [1.2. Basic Concepts](#12-basic-concepts)
    - [3개 중 2개를 늘어놓는다.](#3개-중-2개를-늘어놓는다)
    - [4개 중 3개를 늘어놓는다.](#4개-중-3개를-늘어놓는다)
- [2. Combination](#2-combination)
  - [2.1. Basic Concepts](#21-basic-concepts)
    - [3개 중 2개를 뽑는다.](#3개-중-2개를-뽑는다)
    - [4개 중 3개를 뽑는다.](#4개-중-3개를-뽑는다)
    - [수식 단순화](#수식-단순화)
  - [2.2. Pascal's Triangle 원리를 적용한 Combination](#22-pascals-triangle-원리를-적용한-combination)
  - [2.3. Counting Combinations](#23-counting-combinations)
    - [2.3.1. Recursion](#231-recursion)
    - [2.3.2. memoization](#232-memoization)
    - [2.3.3. DP](#233-dp)
  - [2.4. Generating Combinations](#24-generating-combinations)
    - [2.4.1. N Nested loops](#241-n-nested-loops)
- [3. Repeated Permutation](#3-repeated-permutation)
- [4. Repeated Combination](#4-repeated-combination)

<br>

**[ 순열 조합 공식 원리 철저히 이해하기 ](https://m.blog.naver.com/galaxyenergy/221565884833)**<br>

# Combinatorics( 조합론 )
순열과 조합에 대해 알아본다<br>

$$nCr = \binom{n}{r} = \frac{n!}{r!(n - r)!}$$

Combination의 수식을 나타낸다<br>

# 1. Permutation
`서로 다른 N개 중에 R개를 선택하는 경우의 수`를 의미한다<br>
순서 상관 있음<br>
N개 중 R개를 `늘어놓는다`는 개념<br>

$$nPr = \frac{n!}{(n - r)!}$$

## 1.2. Basic Concepts
2가지 예시로 개념을 이해한다<br>
### 3개 중 2개를 늘어놓는다.
```cpp
char arr[3] = {a, b, c};

ab, ac    // a - 2가지
ba, bc    // b - 2가지
ca, cb    // c - 2가지
```
a, b, c 3가지 문자 중 2개를 늘어놓는 방법은 6가지이다<br>
이때 앞의 문자만 본다면 3가지로 경우가 있으며, 각 문자가 2가지로 파생되기 때문에 3 * 2 = 6으로 계산한다<br>

### 4개 중 3개를 늘어놓는다.
```cpp
char arr[4] = {a, b, c, d};

a, b, c, d

ab ac ad
ba bc bd
ca cb cd
da db dc

abc abd acb acd adb adc
baO baO bcO bcO bdO bdO
caO caO cbO cbO cdO cdO
daO daO dbO dbO dcO dcO
```
첫 글자만 생각하면 4가지 방법이 존재<BR>
두 번째 글자까지 생각하면 4 * 3가지 방법이 존재, 4가지 경우가 3개씩 파생<BR>
세 번째 글자까지 생각하면 4 * 3 * 2가지 방법이 존재, 4 * 3가지 경우가 2개씩 파생<BR>

<br><br>

# 2. Combination
`서로 다른 N개 중에 R개를 선택하는 경우의 수`를 의미한다<br>
순서 상관 없음<br>
N개 중 R개를 `뽑는다`는 개념<br>

$$nCr = \frac{n!}{(n-r)!r!}$$

## 2.1. Basic Concepts
Combination은 Permutation을 이용한다<br>
$$nCr = \frac{nPr}{r!}$$

### 3개 중 2개를 뽑는다.
$$\text{3개 중에 2개를 뽑는 방법} = \frac{\text{3개 중에 2개를 늘어 놓는 방법}}{2!}$$
```cpp
char arr[3] = {a, b, c};

ab, cb, ac
```
순서에 상관 없이 3개 중 2개를 뽑는 방법이 궁금하기 때문에, permutation으로 나온 경우의 수는 중복된 경우의 수가 많다<br>
때문에 중복되는 경우의 수를 제거하기 위해 2!로 나눈다<br>

### 4개 중 3개를 뽑는다.
$$\text{4개 중에 3개를 뽑는 방법} = \frac{\text{4개 중에 3개를 늘어 놓는 방법}}{3!}$$
```cpp
char arr[4] = {a, b, c, d};

abc, abd, bcd, acd
```
permutation에서 abc, acb, bac, bca, cab, cba는 combination에선 abc 하나이다<br>
즉, 6가지의 중복이 생기므로 6!로 나누어 중복을 제거한다<br>

### 수식 단순화
$$nCr = \frac{nPr}{r!} = \frac{n!}{(n-r)!} \times \frac{1}{r!} = \frac{n!}{(n-r)!r!}$$

<br>

## 2.2. Pascal's Triangle 원리를 적용한 Combination
[ Pascal's Triangle ](https://ko.wikipedia.org/wiki/%ED%8C%8C%EC%8A%A4%EC%B9%BC%EC%9D%98_%EC%82%BC%EA%B0%81%ED%98%95)<br>
**[ Programmers - 구슬을 나누는 경우의 수 ](/1_Algorithm/Programmers/240913_구슬을나누는경우의수.md)**<br>

`Pascal's Triangle 기본 성질을 사용해서 경우의 수를 효율적으로 계산하는 방법`을 알아본다<br>

$$\binom{n}{r} = \binom{n - 1}{r - 1} + \binom{n - 1}{r}$$

`N개의 공에서 R개의 공을 선택하는 경우의 수를 두 가지 경우로 나눌 수 있다`는 의미이다<br>

1. 첫 번째 공을 선택하고 나머지 r - 1개를 n - 1개의 공에서 선택하는 경우
2. 첫 번째 공을 선택하지 않고, r개를 n - 1개의 공에서 선택하는 경우

이 `두 가지 경우의 수를 더하면, 전체 경우의 수`가 나온다<br>

<br>

## 2.3. Counting Combinations

### 2.3.1. Recursion
```cpp
// O(2^n)
using namespace std;

int combi(int n, int r){
    if(r == 0 || r == n) return 1;
    if(r > n) return 0;
    return combi(n-1, r) + combi(n-1, r-1);
}
```
`r == 0`은 $\binom{n}{0} = 1$를 의미하며, 0개를 선택하는 경우를 처리한다.<br>
`아무것도 선택하지 않는 경우는 항상 1가지 존재`한다<br>

`r > 0은 불가능하기 때문에 항상 0가지 존재`한다<br>


### 2.3.2. memoization
recursion 코드에서 중복 계산을 피하기 위한 방법   
```cpp
// O(n * r)
#include <vector>
using namespace std;

int combi(int n, int r, vector<vector<int>>& memo) {
  if (r == 0 || r == n) return 1;
  if (r > n) return 0;
  if (memo[n][r] != -1) return memo[n][r];
  memo[n][r] = combi(n - 1, r, memo) + combi(n - 1, r - 1, memo);
  return memo[n][r];
}
```
`vector<vector<int>> memo(n + 1, vector<int>(r + 1, -1))`   
memo[n][r]은 이미 계산된 combi(n, r) 값을 저장한다   
recursion 호출 전에 memo[n][r]을 확인하여 중복 계산을 방지한다   
시간 복잡도가 개선된다   

### 2.3.3. DP
```cpp
// O(n * r)
#include <vector>
using namespace std;

int combi(int n, int r) {
  vector<vector<int>> dp(n + 1, vector<int>(r + 1, 0));

  for (int i = 0; i <= n; ++i) {
    dp[i][0] = 1;     // nC0 = 1;
  }

  // iCj
  for (int i = 0; i <= n; ++i) {
    for (int j = 1; j <= min(i, r); ++j) {
      if (i == j) dp[i][j] = 1;   // nCn = 1
      else dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
    }
  }
  return dp[n][r];
}
```
dp[i][j]는 i개의 원소에서 j개를 선택하는 조합의 수를 저장한다   
`min(i, r)`은 선택한 원소의 수 j가 전체 원소의 수 i를 넘을 수 없기 때문이다   
pascal's triangle 원리를 이용한 조합 수식을 사용한다   

```cpp
// 공간: O(r) | 시간: O(n * r)
#include <vector>
using namespace std;

int combi(int n, int r) {
  vector<int> dp(r + 1, 0);
  dp[0] = 1;      // nC0 = 1

  for (int i = 1; i <= n; ++i) {          // iCj
    for (int j = min(i, r); j > 0; --j) {
      dp[j] = dp[j] + dp[j - 1];
    }
  }

  return dp[r];
}
```
공간 복잡도 O(n * r)에서 O(r)으로 줄여 공간 효율성을 높였다   
dp[j]는 현재 단계에서의 조합 수를 저장한다   
`dp[0] = 1` 조합의 기본 값인 C(n, 0) 즉, 아무것도 선택하지 않는 경우의 수는 항상 1이다   
j를 역순으로 순회하여 이전 단계의 값을 덮어쓰지 않는다   

`dp[j]`는 이전 단계까지 계산된 C(i - 1, j) 값이다   
`dp[j - 1]`은 C(i - 1, j - 1) 값이다   
즉, 이 식은 pascal's triangle 원리를 이용한 C(i, j) = C(i - 1, j) + C(i - 1, j - 1)이다   
두 조합값을 더한 dp[j]는 C(i, j)이다   

dp[r]은 C(n, r)값이 저장됐다   

<br>

## 2.4. Generating Combinations
주어진 Object, Number 등을 이용하여 서로 다른 N개의 조합을 만드는 방법을 알아본다   

### 2.4.1. N Nested loops
[Programmers - 소수 만들기](https://school.programmers.co.kr/learn/courses/30/lessons/12977)   
주어진 숫자 중 3개의 수를 더했을 때 소수가 되는 경우의 개수를 구하는 문제   
```cpp
// O(N^3)
#include <vector>

using namespace std;

int solution(vector<int> nums) {
    int count = 0;
    int n = nums.size();
    // Iterate over all combinations of three different numbers
    for (int i = 0; i < n - 2; ++i) {
        for (int j = i + 1; j < n - 1; ++j) {
            for (int k = j + 1; k < n; ++k) {
                int sum = nums[i] + nums[j] + nums[k]; // Sum of three numbers
                if (isPrime(sum)) count++;             // Increment count if sum is prime
            }
        }
    }
    return count; // Return the total count
}
```
`nums에는 최대 50개의 숫자가 존재`하며, 각 원소는 1이상 1000이하의 자연수이며, 중복된 숫자는 없다   
따라서 최대 조합의 수는 `C(50, 3) = 19600`이다   

`각 조합이 중복되지 않으려면 (i < j < k)` 조건을 충족해야 한다   

```cpp
// 예시
vector<int> nums = {1, 2, 3, 4};

i: 0 또는 1, (0 to n - 3)
j: (i + 1) to (n - 2)
k: (j + 1) to (n - 1)

// 1. i = 0 인 경우
j = 1, k = 2, 3
j = 2, k = 3

// 2. i = 1 인 경우
j = 2
k = 3

// Generated Combinations
| 1, 2, 3 | 1, 2, 4 | 1, 3, 4 | 2, 3, 4 |
```


<br><br>

# 3. Repeated Permutation
중복 가능한 N개 중에서 R개를 선택하는 경우의 수를 의미한다<br>
순서 상관 있음<br>

$$n\Pi r = n^r$$

<br>

# 4. Repeated Combination
중복 가능한 N개 중에서 R개를 선택하는 경우의 수를 의미한다<br>
순서 상관 없음<br>

$$n\Eta r = _{n+r-1}Cr$$