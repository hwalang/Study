- [Introduce](#introduce)
- [1. Prime Number( 소수 )](#1-prime-number-소수-)
  - [2.1. Prime Number in CPP](#21-prime-number-in-cpp)
- [2. Composite Number( 합성수 )](#2-composite-number-합성수-)
  - [2.1. Example](#21-example)
  - [2.2. Composite Number in CPP](#22-composite-number-in-cpp)

   

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
