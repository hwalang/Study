- [std::gcd](#stdgcd)
    - [return value](#return-value)
  - [사용하는 경우](#사용하는-경우)
    - [1. Irreducible Fraction - 기약 분수](#1-irreducible-fraction---기약-분수)
    - [2. Coprime - 서로소](#2-coprime---서로소)
- [std::lcm](#stdlcm)
  - [return value](#return-value-1)
  - [사용하는 경우](#사용하는-경우-1)
    - [1. 주기](#1-주기)
    - [2. 배수 관계](#2-배수-관계)
    - [3. 분수의 덧셈 및 뺄셈](#3-분수의-덧셈-및-뺄셈)
- [Example](#example)

<br>

[ standard library를 안 쓰고 GCD와 LCM을 구하는 방법 ](/2_Math/number/README.md)<br>

# std::gcd
[ Greatest Commond Divisor ](/2_Math/number/3_GCD.md)<br>
[ cppreference - gcd ](https://en.cppreference.com/w/cpp/numeric/gcd)<br>
```cpp
#include <numeric>

template <class M, class N>
constexpr std::common_type_t<M, N> gcd(M m, N n);
```
`M과 N 둘 중 하나라도 Integer가 아니거나 bool인 경우, 잘못된 문법`이기 때문에 runtime-error가 발생한다<br>

### return value
둘 중 하나라도 0이 존재하면, 0을 반환<br>
그렇지 않다면, $|M|$과 $|N|$의 gcd를 반환<BR> 

<br>

## 사용하는 경우
### 1. Irreducible Fraction - 기약 분수
[ Irreducible Fraction ](/2_Math/number/2_IrreducibleFraction.md)<br>
`분수를 약분할 때 사용`한다.<br>
분자와 분모를 GCD로 나누어 분수를 가장 간단한 형태로 만들 수 있다<br>

<br>

### 2. Coprime - 서로소
`두 수의 GCD가 1이면, 두 수는 서로소`이다<br>



<br><br>

# std::lcm
[ Least Common Multiple ](/2_Math/number/4_LCM.md)<br>
[ cppreference - lcm ](https://en.cppreference.com/w/cpp/numeric/lcm)<br>
```cpp
#include <numeric>

template <class M, class N>
constexpr std::common_type_t<M, N> lcm(M m, N n);
```
`M과 N 둘 중 하나라도 Integer가 아니거나 bool인 경우, 잘못된 문법`이기 때문에 runtime-error가 발생한다<br>

## return value
둘 중 하나라도 0이 존재하면, 0을 반환<br>
그렇지 않다면, $|M|$과 $|N|$의 lcm을 반환<BR> 

<br>

## 사용하는 경우
### 1. 주기
`두 개 이상의 사건이 일정한 간격으로 발생할 때, 이들이 동시에 일어나는 시간`을 계산할 때 LCM을 사용한다<br>
예를 들어, 6일마다 일어나는 사건1과 10일마다 일어나는 사건2가 처음으로 동시에 일어나는 시점을 계산하려면 LCM(6, 10)을 구해 30일 후 임을 알 수 있다.<br>

<br>

### 2. 배수 관계
`어떤 수들을 모두 포함할 수 있는 최소한의 공통 배수를 찾을 때` 사용한다<br>

<br>

### 3. 분수의 덧셈 및 뺄셈
`분모의 공통 배수를 찾을 때` 사용한다.<br>

<br><br>

# Example
[ Programmers - 피자 나눠 먹기 2 ](https://school.programmers.co.kr/learn/courses/30/lessons/120815)<br>
```cpp
// library를 사용하지 않은 경우
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int solution(int n) {
    int lcm_num = lcm(n, 6);
    return lcm_num / 6;
}
```
```cpp
// library를 사용한 경우
#include <numeric>

int solution(int n) {
  return std::lcm(n, 6) / 6;
}
```
피자 한 판에 6조각으로 잘라주는 가게가 있다<br>
피자를 나눠 먹을 사람이 n명일 때, n명이 주문한 피자를 남기지 않고 모두 같은 수의 피자 조각을 먹어야 한다.<br>
최소 몇 판을 시켜야 하나?

눈대중으로 최소공배수를 사용해야 함을 알았다<br>
예를 들면, 피자 6조각을 5명이서 모두 같은 수의 피자를 먹으려면 30조각이 필요하다.<br>
때문에 피자는 총 5판이 필요하며, 이는 최소공배수를 이용해서 풀었음을 알았다<br>