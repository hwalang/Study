# Sigma

## Arithmetic Series( 산술 급수 )
$$\sum^n_{i = 1}{i} = \frac{n \times (n + 1)}{2}$$
1부터 n까지의 정수의 합   

### 1. 예시 : 두 정수 사이의 합
[Programmers( level1 ) - 두 정수 사이의 합](/1_Algorithm/Programmers_level_1/241012_두정수사이의합.md)   
```cpp
#include <algorithm>

using namespace std;

long long solution(int a, int b) {
    if (a > b) swap(a, b);
    return (static_cast<long long>(b) * (b + 1) / 2) - (static_cast<long long>(a) * (a - 1) / 2);
}
```
$$\text{Sum from a to b =} \sum^{b}_{i = a}{i}$$
두 정수 a, b 사이의 모든 정수의 합을 계산하는 함수다   
이때 a는 b보다 작거나 같다   

$\frac{b \times (b + 1)}{2}$는 1 ~ b까지의 합을 구한다   
$\frac{(a - 1) \times a}{2}$는 1 ~ (a - 1)까지의 합을 구한다   
두 합을 서로 뺀 값은 a ~ b 사이의 정수 합을 뜻한다   