- [std::transform](#stdtransform)
  - [return](#return)
- [Possible Implementation](#possible-implementation)
- [예시](#예시)
  - [1. cppreference](#1-cppreference)
    - [cbegin(), cend()](#cbegin-cend)
  - [2. programmers](#2-programmers)
    - [예시 1 : lambda](#예시-1--lambda)
    - [예시 2](#예시-2)

<br>

# std::transform
```cpp
#include <algorithm>

// 1. Unary Operation : 단항 연산자
templace <class InputIt, class OutputIt, class UnaryOp>
OutputIt transform(InputIt first1, InputIt last1, OutputIt d_first, UnaryOp unary_op);

// 2
template <class ExecutionPolicy, class ForwardIt1, class ForwardIt2, class UnaryOp>
ForwardIt2 transform(ExecutionPolicy&& policy, ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 d_first, UnaryOp unary_op);

// 3. Binary Operation : 이항 연산자
template <class InputIt1, class InputIt2, class OutputIt, class BinaryOp>
OutputIt transform(InputIt1 first1, InputIt1 last1, InputIt2 first2, OutputIt d_first, BinaryOp binary_op);

// 4.
template <class ExecutionPolicy, 
          class ForwardIt1, class ForwardIt2, 
          class ForwardIt3, class BinaryOp>
ForwardIt3 transform(ExecutionPolicy&& policy, ForwardIt1 first1, ForwardIt1 last1, 
                     ForwardIt2 first2, ForwardIt3 d_first, BinaryOp binary_op);

```
`[first1, last1) 내의 범위에 주어진 elements에게 주어진 function을 적용`시킨다<br>
`d_first 첫 시작 주소를 가져와서 위 결과를 저장`한다<br>

1. UnaryOp를 [first1, last1) 범위에 있는 elements에 적용한다.
3. [first1, last1) 범위와 같은 크기를 가진 first2에 binary operation을 적용해서 d_first로 출력한다
   - first2의 범위는 암묵적으로 [first1, last1)과 같다
   - distance(first1, last1)이 n이라면, first2 + n 범위를 가진다
2.4. 1, 3번과 같지만, policy에 영향을 받는다

<br>

## return
[first1, last1)에 operation을 적용한 후 그 결과를 OutputIt에 저장한다.<br>
`반환되는 iterator는 OutputIt의 마지막 요소 다음을 가리키는 반복자( OutputIt.end() )`이다<br>

d_first의 크기는 first2처럼 [first1, last1)의 범위이다<br>

<br>
<br>

# Possible Implementation
```cpp
// 1. UnaryOp
template<class InputIt, class OutputIt, class UnaryOp>
constexpr
OutputIt transform(InputIt first1, InputIt last1, OutputIt d_first, UnaryOp unary_op)
{
  for (; first1 != last1; ++d_first, ++first1)
    *d_first = unary_op(*first1);

  return d_first;   // d_first는 for문에서 위치가 ++이 되고, 마지막엔 last 위치이다
}

// 2. BinaryOp
template<class InputIt1, class InputIt2, class OutputIt, class BinaryOp>
constexpr
OutputIt transform(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                   OutputIt d_first, BinaryOp binary_op)
{
  for (; first1 != last1; ++d_first, ++first1, ++first2)
    *d_first = binary_op(*first1, *first2);

  return d_first;
}
```

<br>
<br>

# 예시
## 1. cppreference
```cpp
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>

char to_uppercase(unsgined char c)
{
  return std::toupper(c);
}

void unary_transform_example(std::string& hello, std::string world)
{
  std::trasnform(hello.cbegin(), hello.cend(), hello.begin(), to_uppercase);
  std::cout << "hello = " << std::quoted(hello) << "\n";
}

void binary_transform_example(std::vector<unsigned> ordinals)
{
  std::transform(ordinals.cbegin(), ordinals.cend(), ordinals.cbegin(), ordinals.begin(), std::plus<>{});
}

int main()
{
  std::string hello("Hello");
  unary_transform_example(hello, "world");

  std::vector<unsigned> ordinals;
  std::copy(hello.cbegin(), hello.cend(), std::back_inserter(ordinals));
  binary_transform_example(std::move(ordinals));
}
```

### cbegin(), cend()
const_begin(), const_end()라고 보면 된다<br>
`const_iterator`로 불리며, `container의 element를 읽기 전용으로 접근`한다<br>

<br>

## 2. programmers

### 예시 1 : lambda
```cpp
#include <algorithm>
#include <cctype>
#include <algorithm>

int main()
{
  std::string s("hello");
  std::transform(s.begin(), s.end(), s.begin(),
                [](unsigned char c) -> unsigned char {return std::toupper(c);});
  
  std::vector<std::size_t> ordinals;
  std::transform(s.begin(), s.end(), std::back_inserter(ordinals),
                [](unsigned char c) -> std::size_t {return c;});
  
  std::cout << s << ':';
  for (auto ord : ordinals) std::cout << ' ' << ord;

  std::transform(ordinals.cbegin(), ordinals.cend(), ordinals.cbegin(),
                ordinals.begin(), std::plus<>{});
  
  std::cout << '\n';
  for (auto ord : ordinals) std::cout << ord << ' ';
  std::cout << '\n';
}
```

### 예시 2
```cpp
string solution(string myString) {
    transform(myString.cbegin(), myString.cend(), myString.begin(), ::tolower);
    return myString;
}
```