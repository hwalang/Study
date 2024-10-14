- [Terminating Decimal( 유한 소수 )](#terminating-decimal-유한-소수-)
  - [Terminating Decimal 조건](#terminating-decimal-조건)
    - [1. 분수](#1-분수)
      - [Code Example 1](#code-example-1)
      - [Code Example 2](#code-example-2)

<br><br>

# Terminating Decimal( 유한 소수 )
소수 부분이 유한하게 끝나는 숫자를 의미   

## Terminating Decimal 조건
### 1. 분수
[기약 분수( Irreducible Fraction )](2_Irreducible_Fraction.md)   
Terminating Decimal이 되기 위한 Fraction의 조건은 다음과 같다   
`분수를 기약 분수로 나타내었을 때, 분모의 소인수가 오직 2 또는 5로 구성`되면 Terminating Decimal이다     

10진법에서 분모에 2 또는 5 이외의 소인수( [prime factor](6_Number_Theory.md/#1-prime-number-소수-prime-factor-) )가 존재하면, 소수점 아래의 자리수가 무한히 반복되는 순환 소수( Repeating Decimal )가 된다   

#### Code Example 1
```cpp
#include <numeric>

using namespace std;

int solution(int a, int b) {    // b가 분모라 가정
  b /= std::gcd(a, b);

  while (b % 2 == 0) {
    b /= 2;
  }
  while (b % 5 == 0) {
    b /= 5;
  }
  return b == 1 ? 1 : 2;
}
```
분모를 분자의 최대 공약수로 나눠서 Simplified Fraction으로 만든다   
이후 분모를 2와 5로 나눠서 더 이상 2와 5의 multiple( 배수 )이 아니게 만든다   
분모가 1이면 Terminating Decimal로 나타낼 수 있으며, 그렇지 않으면 Repeating Decimal이다   

#### Code Example 2
```cpp
#include <numeric>

using namespace std;

bool is_prime_factor_2_5(int num) {
    while (num % 2 == 0) {
        num /= 2;
    }
    
    for (int i = 3; i * i <= num; i += 2) {
        if (num % i == 0 && i != 5) {
            return false;
        }
        while (num % i == 0) {
            num /= i;
        }
    }
    
    if (num > 2 && num != 5) return false;
    return true;
}

int solution(int a, int b) {
    b /= gcd(a, b);
    if (is_prime_factor_2_5(b)) return 1;
    return 2;
}
```
분자와 분모의 GCD를 구하여 이를 분모에서 나누면 Simplified Fraction( 기약 분수 )가 된다   
Prime Factorization 함수를 사용해서 분모가 오직 2와 5로만 나눌 수 있는지 확인한다   