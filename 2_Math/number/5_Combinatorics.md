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
    - [2.2.1. code example : DP](#221-code-example--dp)
    - [2.2.2. code example : Recursion](#222-code-example--recursion)
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

### 2.2.1. code example : DP
```cpp
#include <vector>
#include <numeric>
using namespace std;

int solution(int n, int r) {
  vector<long long> dp(n - r + 1);
  dp[0] = 1;
  for (int i = 0; i < r; ++i) {
    for (int j = 1; j < dp.size(); ++j) {
      dp[j] += dp[j - 1];
    }
  }
  return accumulate(dp.begin(), dp.end(), 0ll);
}
```
dp에는 각 index의 의미는 뽑는 개수( r )이다<br>
즉, `dp[i]는 i개를 뽑는 경우의 수`를 나타낸다<br>

`가장 외부의 for문`에서 r의 개수가 현재 n에서 r개를 뽑는 행위를 의미한다<br>
만약 5개 중에 3개를 뽑는다면, 바깥 for문은 3번 반복한다<br>

`dp[j] += dp[j - 1]`는 pascal's triangle 원리를 적용했다<br>
- dp[j]는 두 가지 값을 저장
  - $\binom{n}{j}$ : dp[j]
  - $\binom{n - 1}{j}$ : dp[j] + dp[j - 1]에서의 dp[j]
  - 즉, 덧셈 전까지 dp[j]는 $\binom{n - 1}{j}$이며, 계산 후에 $\binom{n}{j}$를 나타낸다
- `dp[j - 1]`
  - j개를 뽑는 경우의 수가 아닌 `j - 1개를 뽑는 경우의 수`를 나타낸다
- 즉, dp[j] += dp[j - 1]은 $\binom{n}{j} = \binom{n - 1}{j - 1} + \binom{n - 1}{j}$를 반영하여 새로운 경우의 수를 누적하는 과정

예를 들면, $\binom{5}{3} = \binom{4}{3} + \binom{4}{2}$이다<br>

<br>

### 2.2.2. code example : Recursion
```cpp
using namespace std;

int combi(int n, int r){
    if(r == 0) return 1;
    if(r == n) return 1;
    if(r > n) return 0;
    return combi(n-1, r) + combi(n-1, r-1);
}

int solution(int balls, int share) {
    int answer = 0;
    answer = combi(balls, share);
    return answer;
}
```
`r == 0`은 $\binom{n}{0} = 1$를 의미하며, 0개를 선택하는 경우를 처리한다.<br>
`아무것도 선택하지 않는 경우는 항상 1가지 존재`한다<br>

`r > 0은 불가능하기 때문에 항상 0가지 존재`한다<br>


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