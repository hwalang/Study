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
- [3. Repeated Permutation](#3-repeated-permutation)
- [4. Repeated Combination](#4-repeated-combination)

<br>

**[ 순열 조합 공식 원리 철저히 이해하기 ](https://m.blog.naver.com/galaxyenergy/221565884833)**<br>

# Combinatorics( 조합론 )
순열과 조합에 대해 알아본다<br>

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