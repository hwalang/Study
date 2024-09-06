- [Irreducible Fraction( 기약 분수 )](#irreducible-fraction-기약-분수-)
  - [Example](#example)
    - [1. basic](#1-basic)
    - [2. 단위 분수( unit fraction )](#2-단위-분수-unit-fraction-)
  - [개념 살펴보기](#개념-살펴보기)
  - [1. Greatest Common Factor( GCF, GCD ) - 최대공약수](#1-greatest-common-factor-gcf-gcd----최대공약수)
    - [1.1. Euclidean Algorithm - 유클리드 호제법](#11-euclidean-algorithm---유클리드-호제법)
  - [2. Reduction of a Frction - 약분](#2-reduction-of-a-frction---약분)
    - [2.1. divisor - 약수](#21-divisor---약수)

<br>

# Irreducible Fraction( 기약 분수 )
[ wiki - 기약 분수 ](https://ko.wikipedia.org/wiki/%EA%B8%B0%EC%95%BD%EB%B6%84%EC%88%98)<br>

`분자와 분모의 공약수( Greatest Common Factor, GCF )가 1뿐이어서 더 이상 약분되지 않는 분수`이다<br>

<br>

## Example
### 1. basic
$\frac{120}{90} = \frac{12}{9} = \frac{4}{3}$ <br>

1. 분자와 분모를 10으로 약분
2. 분자와 분모를 3으로 약분
3. 1외에는 더 이상 약분할 수 없음

### 2. 단위 분수( unit fraction )
분자가 1인 분수를 뜻하며, 모든 단위 분수는 기약 분수가 된다<br>

<br><br>

## 개념 살펴보기
## 1. Greatest Common Factor( GCF, GCD ) - 최대공약수
`Greatest Common Divisor( GCD )`라고도 불린다<br>

$\gcd(12, 18) = 6$ <br>

공약수( common factor )는 모든 약수를 뜻한다.<br>
그 중에서 `최대공약수는 공약수 중에서 가장 큰 하나`다<br>

Greatest Common Divisor를 구하는 방법을 알아본다<br>

### 1.1. Euclidean Algorithm - 유클리드 호제법
`약분을 하기 위한 GCD는 유클리드 호제법` 등의 방법으로 찾을 수 있다<br>

192와 72의 최대공약수를 구해본다<br>
```cpp
// 1. 192를 72로 나눈 나머지를 구한다. ( 192 > 72 )
192 = 72 * 2 + 48;

// 2. 72를 48로 나눈 나머지를 구한다.
72 = 48 * 1 + 24;

// 3. 이 연산을 나머지가 0이 될 때까지 반복한다.
48 = 24 * 2 + 0;
```
나머지가 0이 되기 바로 직전의 연산에서의 나머지가 원래 두 수의 GCD가 된다<br>
즉, 24가 GCD이다<br>



<br>

## 2. Reduction of a Frction - 약분
`분자와 분모를 1 이외의 공통된 약수로 나누는 행위`이다<br>

### 2.1. divisor - 약수
0이 아닌 두 정수 n, m의 공약수란, n의 약수이자 m의 약수인 정수이다<br>