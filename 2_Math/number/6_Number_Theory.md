- [Introduce](#introduce)
- [1. Prime Number( 소수 )](#1-prime-number-소수-)
  - [1.1. prime factor와 prime number의 차이점](#11-prime-factor와-prime-number의-차이점)
  - [1.2. Prime Number in CPP](#12-prime-number-in-cpp)
    - [1.2.1. Prime Checking Function](#121-prime-checking-function)
    - [1.2.2. Prime Generating Function](#122-prime-generating-function)
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

## 1.1. prime factor와 prime number의 차이점
`Prime`은 Prime Number( 소수 )를 의미하며, 1과 자기 자신 외에는 약수를 가지지 않는 수   
`Factor`( 인수 )는 어떤 수를 곱해서 다른 수를 만들 수 있는 숫자   

예를 들면, 2, 3, 5, 7은 소수이고, 12의 factor는 1, 2, 3, 4, 6, 12이다   

따라서 `prime factor는` 어떤 수를 소수들의 곱으로 나누었을 때 나오는 그 소수들, 즉 `소인수`를 의미한다   
prime factor는 `그 자체로 소수이면서 동시에 소인수 역할을 수행`한다   
예를 들면, 18의 prime factor는 2와 3이다. 왜냐하면 18은 $2 \times 3^2$로 소인수 분해( Prime Factorizaion )할 수 있기 때문이다   
이 경우, 2와 3은 prime number이며, 18을 소수들로 나눈 결과가 prime factor이다   

## 1.2. Prime Number in CPP
참고로 1은 소수가 아니다   
### 1.2.1. Prime Checking Function
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
위 코드를 통해 composite number를 판단하는 함수를 떠올릴 수 있다   

```cpp
bool is_prime(int num) {
    if (num <= 1) return false;         // 1 or less is not prime
    if (num == 2) return true;          // 2 is prime
    if (num % 2 == 0) return false;     // Even numbers greater than 2 are not prime
    
    for (int i = 3; i * i <= num; i += 2) { // Check odd divisors only
        if (num % i == 0) return false;
    }
    return true;
}
```
오직 소수를 판단하는 기능을 최적화한 방법이다   

### 1.2.2. Prime Generating Function
N까지의 자연수 중 무엇이 prime number인지 저장하는 list를 생성한다   
```cpp
// Function to generate all primes up to 'max_num' using Sieve of Eratosthenes
vector<bool> generate_primes(int max_num) {
  vector<bool> is_prime(max_num + 1, true);
  is_prime[0] = is_prime[1] = false;
  for (int i = 2; i * i <= max_num; ++i) {
    if (is_prime[i]) {
      for (int j = i * i; j <= max_num; j += i) {
        is_prime[j] = false;
      }
    }
  }
  return is_prime;
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

bool is_composite(int num) {
  if (num <= 3) return false;

  for (int i = 2; i * i <= num; ++i) {
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

num이 3이하인 경우에는 소수로 판단하지만, i가 2부터 시작하는 이유는 합성수를 판단하는 로직 때문이다   
loop 시작을 4로 하면, num = 9일 때, 약수인 3을 검사하지 않기 때문에 잘못된 결과를 얻게 된다   
따라서 2부터 시작하여 num의 약수인지 판단해야 한다   

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

모든 composite number는 `sqrt(n) 이하의 prime factor를 적어도 하나는 가진다`   
```cpp
// 왜 sqrt(n)까지 순회하나?
// composite number: n
n의 인수 i에 대해 n = i * (n / i)가 성립

i와 (n / i)가 sqrt(n)보다 크다면, i * (n / i) = n 임을 부정하는 것이다
때문에 i와 (n / i) 중 최소 하나는 반드시 sqrt(n)이하이다
```
또한 `i * i <= n`까지 순회하는 이유는 n의 인수인 i에 대해 `n == i * (n / i)`가 성립한다   
이러한 성질을 이용하여 1 또는 하나의 소수가 남을 때까지 number를 소수로 나눈다   

`n /= i를 모든 i에 대해 반복적으로 수행하여 n을 prime factor i( n의 인수 )와 중복된 경우를 제거`한다

#### 남은 prime factor 처리
`마지막으로 남은 수가 2보다 크면, num 자체가 소수`이다   
