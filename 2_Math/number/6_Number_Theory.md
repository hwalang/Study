- [Introduce](#introduce)
- [1. Prime Number( 소수 )](#1-prime-number-소수-)
  - [2.1. Prime Number in CPP](#21-prime-number-in-cpp)
- [2. Composite Number( 합성수 )](#2-composite-number-합성수-)
  - [2.1. Example](#21-example)
  - [2.2. Composite Number in CPP](#22-composite-number-in-cpp)
- [3. Prime Factorization( 소인수 분해, Prime Decomposition )](#3-prime-factorization-소인수-분해-prime-decomposition-)
  - [3.1. Prime Factorization in CPP](#31-prime-factorization-in-cpp)
    - [3.1.1. How does this work?](#311-how-does-this-work)
      - [2의 인수 제거](#2의-인수-제거)
      - [홀수 인수 검사 및 제거](#홀수-인수-검사-및-제거)
      - [남은 prime factor 처리](#남은-prime-factor-처리)

   

# Introduce
Number Theory( 정수론 )는 정수의 성질과 그들 사이의 관계를 연구하는 수학의 분야   


# 1. Prime Number( 소수 )
`1과 자기 자신만을 약수로 가지는 1보다 큰 자연수`   

## 2.1. Prime Number in CPP
```cpp
#include <iostream>
#include <cmath>

bool is_prime(int num) {
  if (num <= 1) return false;

  for (int i = 2; i <= std::sqrt(num); ++i) {
    if (num % i == 0) return false;   // composite number
  }

  return true;
}
```


<br><br>


# 2. Composite Number( 합성수 )
`1과 자기 자신 이외의 다른 약수를 가지는 1보다 큰 자연수`를 말한다   
즉, 소수( prime number )가 아닌 1보다 큰 자연수이다   

## 2.1. Example
```
4의 약수: 1, 2, 4
6의 약수: 1, 2, 3, 6
```
4와 6이 composite number인지 판단해보자   
4는 1과 4가 아닌 약수가 1개 이상 존재해야 한다. 여기서 2가 있기 때문에 4는 composite number다   
6은 1과 6이 아닌 약수가 1개 이상 존재하기 때문에 composite number다   

## 2.2. Composite Number in CPP
```cpp
#include <iostream>
#include <cmath>

bool is_composite(int num) {
  if (num <= 1) return false;

  for (int i = 2; i <= std::sqrt(num); ++i) {
    if (num % i == 0) return true;
  }

  // prime number
  return false;
}
```
1이하는 prime number, composite number도 아니다   
2부터 num의 제곱근까지 검사한다   
제곱근까지 검사하는 이유는 약수의 대칭성 때문이다. 12의 약수는 (2, 6), (3, 4)와 같이 곱셈의 순서가 바뀐 쌍으로 나타나기 때문에 제곱근 이상을 검사할 필요가 없다   
약수를 찾지 못하면 약수가 1과 자기 자신만 존재하기 때문에 prime number다   


<br><br>


# 3. Prime Factorization( 소인수 분해, Prime Decomposition )
`어떤 composite number를 소수들의 곱으로 표현하는 것`이다   
예를 들면, 12를 소인수 분해하면 2 * 2 * 3이다.   

## 3.1. Prime Factorization in CPP
**[ Effcient Program to print all prime factors of a given number ](https://www.geeksforgeeks.org/print-all-prime-factors-of-a-given-number/)**   
```cpp
// C++ program to print all prime factors 
#include <bits/stdc++.h>
using namespace std;
 
// A function to print all prime 
// factors of a given number n 
void primeFactors(int n) 
{ 
    // Print the number of 2s that divide n 
    while (n % 2 == 0) 
    { 
        cout << 2 << " "; 
        n = n/2; 
    } 
 
    // n must be odd at this point. So we can skip 
    // one element (Note i = i +2) 
    for (int i = 3; i <= sqrt(n); i = i + 2)    // (i * i <= n) efficient code
    { 
        // While i divides n, print i and divide n 
        while (n % i == 0) 
        { 
            cout << i << " "; 
            n = n/i; 
        } 
    } 
 
    // This condition is to handle the case when n 
    // is a prime number greater than 2 
    if (n > 2) 
        cout << n << " "; 
} 
 
/* Driver code */
int main() 
{ 
    int n = 315; 
    primeFactors(n);    // 3 3 5 7
    return 0; 
} 
```
중복을 허용한 소인수 분해 예시다   
최악의 경우 O(sqrt(N))가 걸리고, 가장 좋은 경우엔 O(logN)이다   

참고로 `sqrt(n)을 연산하는 것보다 i * i가 더 효율적`이다   
부동소수점 연산보다 정수 연산이 상대적으로 훨씬 빠르기 때문이다   

### 3.1.1. How does this work?
#### 2의 인수 제거
주어진 composite num을 prime number인 2로 나눌 수 없을 때까지 나눈다   
`더 이상 2로 나눌 수 없는 양의 정수는 홀수`임이 명백하다   

#### 홀수 인수 검사 및 제거
step 1 이후, `i가 3부터 시작하여 2씩 증가하면서 sqrt(num)까지 순회`한다.   
모든 composite number는 자신과 같거나 작은 prime factor를 최소 하나를 가진다.   
```cpp
// 왜 sqrt(n)까지 순회하나?
// composite number: n
n의 인수 i에 대해 n = i * (n / i)가 성립

i와 (n / i)가 sqrt(n)보다 크다면, i * (n / i) = n 임을 부정하는 것이다
때문에 i와 (n / i) 중 최소 하나는 반드시 sqrt(n)이하이다
```
이러한 성질을 이용하여 for문을 수행한다   
1. i + 2를 통해 n의 소인수인 1 또는 prime factor를 찾는다
2. `n /= i를 모든 i에 대해 반복적으로 수행하여 n을 prime factor i( n의 인수 )와 중복된 경우를 제거`한다

#### 남은 prime factor 처리
`마지막으로 남은 수가 2보다 크면, num 자체가 소수`이다   
