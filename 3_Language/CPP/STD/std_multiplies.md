- [std::multiplies](#stdmultiplies)
- [std::multiplies::operator()](#stdmultipliesoperator)
- [예시](#예시)
  - [1. 기본 사용법](#1-기본-사용법)
  - [2. STL과 함께 사용](#2-stl과-함께-사용)
    - [2.1. accumulate](#21-accumulate)

<br>

# std::multiplies
accumulate()의 BinaryOp 인자를 찾던 중 발견한 함수 객체이다<br>
`Binary Operation( 이항 연산 ) 함수 객체`이다<br>

[ cppreference - std::multiplies ](https://en.cppreference.com/w/cpp/utility/functional/multiplies)<br>
```cpp
#include <functional>

template <class T>
struct multiplies;
```
`곱셈을 수행하기 위한 함수 객체`이다<br>
효과적으로 Type T인 두 피연산자( 인자 )에 대해 operator*을 호출한다<br>

<br>
<br>

# std::multiplies::operator()
multiplies가 가진 member function을 알아야 이후 등장할 예시를 이해할 수 있다<br>
```cpp
T operator()(const T& lhs, const T& rhs) const
{
  return lhs * rhs;
}
```
`lhs * rhs를 반환`한다<br>

<br>
<br>

# 예시

## 1. 기본 사용법
```cpp
#include <functional>

int main()
{
	std::multiplies<int> multiply;
	int result = multiply(10, 20);
	std::cout << "10 * 20 = " << result << std::endl;
}
```
Template Class이기 떄문에 다양한 TYPE에 대해 곱셈을 수행할 수 있다<br>

## 2. STL과 함께 사용
### 2.1. accumulate
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
[std::accumulate](std_accumulate.md) <br>
accumulate의 4번째 인자에 BinaryOp를 전달하는데 위 예시는 multiplies를 전달하여 모든 원소의 곱을 반환한다<br>