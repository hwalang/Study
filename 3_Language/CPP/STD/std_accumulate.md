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

### BinaryOp
op는 적용할 binary operation( 이항 연산 ) 함수 객체이고, 아래와 같은 구조를 가진다.<br>
이름 그대로 `2개의 피연산자를 입력`으로 받아 `하나의 결과를 산출하는 연산`을 의미한다<br>
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

## 예시 1
``` cpp
#include <numeric>
#include <vector>

std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

int sum = std::accumulate(v.begin(), v.end(), 0);   // 55
int product = std::accumulate(v.begin(), v.end(), 1, std::multiplies<int>());  // 362880
```
product의 BinaryOp는 accumulate의 연산자를 +가 아니라 *로 변경한다. </br>
즉, 1부터 10까지의 모든 elements를 곱한 값을 리턴한다.

<br>

## 잘못된 예시 2 : 무조건 모든 index를 순회한다
```cpp
#include <numeric>

int solution(vector<int> nums. int n) 
{
  return std::accumulate(nums.begin(), nums.end(), 0, [idx = 0, threshold = n](int sum, int value) {
    sum += value;
    if (sum > threshold) return sum;
    ++idx;
  });
}
```
accumulate()는 중간에 순회를 멈추는 기능이 없다<br>
아무리 lambda 식으로 sum이 threshold보다 높을 때 중단하고 싶어도 accumulate()가 허락하지 않는다<br>
따라서 위 코드를 수행하면 threshold와 관계없이 무조건 nums의 총합이 반환된다<br>

<br>

## 예시 2 : BinaryOp
```cpp
#include <functional>
#include <numeric>

int main()
{
	std::vector<int> numbers = { 1, 2, 3, 4, 5 };
	int product = std::accumulate(numbers.begin(), numbers.end(), 1, std::multiplies<int>());
	std::cout << product << std::endl;
}
```
[std::multiplies](std_multiplies.md) <br>
