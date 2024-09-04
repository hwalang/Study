- [std::for\_each](#stdfor_each)
    - [result](#result)
  - [1. stateful function object](#1-stateful-function-object)
  - [2. stateless function object](#2-stateless-function-object)
  - [3. stateful, stateless의 다양한 방법](#3-stateful-stateless의-다양한-방법)
- [Possible Implementation](#possible-implementation)
- [Example](#example)

<br>

# std::for_each
[ cppreference - for_each ](https://en.cppreference.com/w/cpp/algorithm/for_each)<br>
```cpp
#include <algorithm>

template <class InputIt, class UnaryFunc>
UnaryFunc for_each(InputIt first, InputIt last, UnaryFunc f);
```
`[first, last) 범위의 모든 iterator를 역참조( pointer가 가리키는 실제 값을 참조 )한 결과에 주어진 함수 객체 f를 적용`한다.<br>

### result
- 만약 InputIt TYPE의 `iterator가 mutable 하다면, f는 iterator로부터 역참조한 [first, last) 범위의 elements를 수정할 수 있다`
- for_each는 `function object를 수정한 후 그 객체를 반환`
  - stateful function object라면 [first, last)에 적용한 결과를 내부 상태로 저장하여 이를 객체로 반환할 수 있다

<br>

```cpp
void fun(const Type& a);    // const & 은 선택
```
f의 return value는 무시된다<br>

<br>

## 1. stateful function object
stateful function object란, `내부 상태를 가지고 있고 그 상태를 함수 호출 시마다 유지하거나 변경할 수 있는 함수 객체`다<br>

이는 functor( function object )가 호출될 때마다 내부 상태가 변화할 수 있으며, 그 상태가 이후에도 유지된다는 점에서 일반적인 function과 다르다<br>

`for_each의 f 인자는 stateful function object( 상태를 저장하는 함수 객체 )`이다<br>
```cpp
// stateful function object
struct Sum
{
  int sum {0};    // 상태를 저장하는 멤버 변수

  // 함수 호출 시 sum 값을 변경하는 stateful 함수 객체
  void operator() (int n) { sum += n; }
};
```
이러한 특징을 이용하면 위 코드처럼 내부 상태를 함수를 호출할 때마다 수정할 수 있다<br>

이외에도 상태 저장, 변경, 접근을 지원할 수 있다<br>

<br>

## 2. stateless function object
함수 객체가 내부 상태를 저장하지 않고, `호출될 때마다 독립적으로 동일한 동작을 수행`한다<br>
```cpp
Struct Print
{
  void operator() (int n) const { std::cout << n << " "; }
};
```
Print 객체는 상태를 저장하지 않고, 단순히 값을 출력한다<br>

## 3. stateful, stateless의 다양한 방법
```cpp
// 1. struct, class로 functor 정의

// 2. lambda expression
int value = 5;
std::for_each(v.begin(), v.end(), [&sum](int n) { sum += n; });
std::for_each(v.cbegin(), v.cend(), [=value](int& n) { n += value; });

// 3. Function Pointer
void add(int& n) { n += 2; }
std::for_each(v.begin(), v.end(), add);

// 4. std::function, std::bind
#include <functional>

void multiply(int &n, int factor) { n *= factor; }

// multiply 함수에 factor를 결합하여 2배로 만드는 함수 객체 생성
std::for_each(v.begin(), v.end(), std::bind(multiply, std::placeholders::_1, 2));
```
std::function과 std::bind를 사용해서 유연하게 함수 객체를 다룰 수 있다<br>

`std::function`은 callable object( 호출 가능한 객체, function, lambda, function pointer 등 )를 추상화했다<br>

`std::bind`는 특정 함수에 인자를 미리 결합하여 나중에 사용할 수 있다<br>

일반적으로 lambda expression을 이용해서 function object를 전달한다<br>

<br>
<br>

# Possible Implementation
```cpp
template <class InputIt, class UnaryFunc>
constexpr UnaryFunc for_each (InputIt first, InputIt last, UnaryFunc f)
{
  for (; first != last; ++first)
    f(*first);

  return f;
}
```

<br>
<br>

# Example
```cpp
#include <algorithm>

int main()
{
  std::vector<int> v{3, -4, 2, -8, 15, 267};
  auto print = [](const int& n) { std::cout << n << ' '; };

  // function object
  std::cout << "before: \t";
  std::for_each(v.cbegin(), v.cend(), print);
  std::cout << "\n";

  // increment elements in-place
  std::for_each(v.begin(), v.end(), [](int &n) { ++n; });

  std::cout << "after: \t";
  std::for_each(v.cbegin(), v.cend(), print);
  std::cout << "\n";

  struct Sum
  {
    void operator() (int n) { sum += n; }
    int sum {0};
  };

  // invoke Sum::operator() for each element
  Sum s = std::for_each(v.cbegin(), v.cend(), Sum());
}
```
[ invoke 의미 ](/5_CS/3_Invoke.md/#cpp)<br>

`Sum 구조체는 operator()를 overloading 했기 때문에 함수처럼 동작할 수 있는 Function Object`가 된다<br>
즉, 구조체를 함수처럼 사용할 수 있다<br>

std::for_each 함수가 [first, last) 범위의 각 elements에 대해 Sum 객체의 operator()를 호출한다<br>
`for_each가 끝난 후 for_each 연산 결과를 저장한 Sum 객체를 반환`한다<br>

```cpp
#include <algorithm>

string solution(vector<string> v, string ex) {
  string result;

  for_each(v.cbegin(), v.cend(), [ex, &result](string str) {
    if (str.find(ex) == string::npos) result += str;
  });

  return result;
}
```
[ Programmers - 꼬리 문자열 ](https://school.programmers.co.kr/learn/courses/30/lessons/181841)<BR>
이번엔 외부 변수에 저장했으며, 반환 값이 lambda expression( UnaryFunc )이기 때문에 void나 다름없다<br>