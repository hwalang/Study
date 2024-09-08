- [Lowest Common Multiple( LCM )](#lowest-common-multiple-lcm-)
    - [Common Multiple](#common-multiple)
- [1. GCD를 이용한 LCM 구하는 방법](#1-gcd를-이용한-lcm-구하는-방법)
- [1. Code Example](#1-code-example)

<br>

# Lowest Common Multiple( LCM )
Least Common Multiple라고도 불린다.<br>
`양의 공배수 가운데 가장 작은 하나`를 가리킨다<br>
$\text{lcm(a, b)}$

이때 a * m은 0이 아니다<br>

<br>

### Common Multiple
두 정수의 공배수란, 그들 `모두의 배수`가 되는 정수를 나타낸다<br>

<br><br>

# 1. GCD를 이용한 LCM 구하는 방법
$\text{lcm(a, b)} = \frac{a \times b}{\gcd{a, b}}$ <br>
LCM과 GCD의 관계를 나타낸 식이다<br>

<br><br>

# 1. Code Example
```cpp
int lcm(int a, int b) {
  return (a * b) / gcd(a, b);
}
```

```cpp
#include <numeric>

std::lcm(a, b);
```