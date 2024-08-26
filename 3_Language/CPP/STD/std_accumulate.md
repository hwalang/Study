# std::accumulate
``` cpp
#include <numeric>

template<class InputIt, class T>
T accumulate(InputIt first, InputIt last, T init);

template<class InputIt, class T>
T accumulate(InputIt first, InputIt last, T init, BinaryOp op);
```
구간 [first, last)에 속한 elements의 합을 구한다. </br>
init으로 누적값을 초기화하고, 구간 내의 모든 elements를 차례대로 더해서 누적값을 반환한다. </br>

last iterator는 vector.end()처럼 마지막 element의 다음 위치를 가리키는 iterator이다. </br>

op는 적용할 binary operation 함수 객체이고, 아래와 같은 구조를 가진다.
``` cpp
Ret fun(const Type1 $a, const Type2 &b);
```
T는 Type1과 Type2 타입으로 implicitly 변환할 수 있어야 한다. </br>
Ret은 T 타입으로 변환할 수 있어야 한다.</br>

</br>

## Possible Implementation( 함수 구현 )
``` cpp
template<class InputIt, class T>
constexpr
T accumulate(InputIt first, InputIt last, T init)
{
  for (; first != last; ++first)
    init = std::move(init) + *first;

  return init;
}


template<class InputIt, class T>
constexpr
T accumulate(InputIt first, InputIt last, T init, BinaryOperation op)
{
  for (; first != last; ++first)
    init = op(std::move(init), *first);

  return init;
}
```

</br>

## 예시
``` cpp
#include <numeric>
#include <vector>

std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

int sum = std::accumulate(v.begin(), v.end(), 0);   // 55
int product = std::accumulate(v.begin(), v.end(), 1, std::multiplies<int>());  // 362880
```
product의 BinaryOp는 accumulate의 연산자를 +가 아니라 *로 변경한다. </br>
즉, 1부터 10까지의 모든 elements를 곱한 값을 리턴한다.


