- [std::remove](#stdremove)
  - [1. Logic](#1-logic)
  - [2. Stable Algorithm](#2-stable-algorithm)
  - [3. return value](#3-return-value)
  - [4. Possible Implementation](#4-possible-implementation)
  - [5. std::remove Incompatibility with Associate Container](#5-stdremove-incompatibility-with-associate-container)
- [Example](#example)

<br>

# std::remove
```cpp
#include <algorithm>

template <class ForwardIt, class T>
ForwardIt remove( ForwardIt first, ForwardIt last, const T& value );

template <class ForwardIt, class UnaryPred>
ForwardIt remove_if( ForwardIt first, ForwardIt last, UnaryPred p );
```
`[first, last) 범위의 특정 기준을 만족하는 모든 elements를 제거`하고, `기존 end iterator를 remove 작업이 끝난 후에는 새로운 범위의 past-the-end iterator로 바꾼다`.   
즉, `past-the-end iterator`는 remove 또는 remove_if 함수가 반환하는 새로운 유효 범위 끝을 나타내는 iterator이다   

1. `value와 같은` 모든 elements를 제거한다. ( using operator== )
2. `p가 true`를 반환하는 모든 elements를 제거한다.

<br>

## 1. Logic
`조건을 만족하지 않는 elements는 [first, last) 범위의 앞 부분으로 이동`하고, `조건을 만족하는 elements는 range의 뒷 부분에 위치`된다.   
이후 기존 [first, last)범위의 `end()를 [first, result) 범위의 past-the-end iterator로 바꾼다`   

```cpp
string str("Hello, World");
auto new_end = str.remove(str.begin(), str.end(), 'o');   // Hell, Wrld

index: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
value: H, e, l, l, ,     W, r, l, d, ?,   ?
```
remove 작업을 수행한 뒤에 `실제로 underlying sequence of [first, last)가 줄어들지 않는다`   
[result, last) 범위의 elements는 여전히 valid 하지만, 불특정한 상태( unspecified state )가 된다   
**일반적으로 기존의 값이 남아있을 수 있지만, 이를 신뢰하면 안 된다**   

이는 [ Move Assignment ](../7_move_semantics.md) 때문인데, 이동 연산자는 원본 객체의 resource를 목표 객체로 이동시킨다.   
이동 후 original 객체는 resource를 잃게 되어, 마치 비어있는 것처럼 보이기 때문에 이동 대상이 된 객체들은 사실상 제거된 것과 같은 효과가 있다   
unspecified state를 정확히 말하면, [moved-from state](../7_move_semantics.md/#121-moved-from-state)이다   
`객체가 move operation에 의해 자신의 resource를 다른 객체로 이동시킨 후 남게 되는 상태`를 말한다.   
즉, 이동 후 원본 객체는 valid 하지만 unspecified state가 된다   

## 2. Stable Algorithm
stable Algorithm 이란, `데이터 처리 과정에서 동일한 key를 가진 elements의 상대적인 순서가 유지`되는 알고리즘을 말한다   

std::remove는 값 또는 조건에 해당하지 않은 elements를 앞으로 이동시켜 원하는 elements를 제거하는 연산이다   
이 과정에서 `제거되지 않는 elements의 순서가 변경되지 않는다`   
```cpp
std::vector<int> numbers = {1, 2, 3, 2, 4, 2, 5};

auto new_end = std::remove(numbers.begin(), numbers.end(), 2);
for (auto it = numbers.begin(); it != new_end; ++it) {    // 1, 3, 4, 5
  std::cout << *it << ' ';
}
```
2에 해당하지 않는 elements를 앞으로 이동시키는 과정에서 기존 elements의 순서를 보장한다   

## 3. return value
Past-the-end iterator for the new range of values   
즉, `새로운 범위의 end()를 반환`한다   
이는 곧 값 또는 조건에 맞는 elements의 begin()을 가리키며, 이를 이용하여 `일반적으로 erase와 함께 사용`한다   

## 4. Possible Implementation
```cpp
template<class ForwardIt, class T = typename std::iterator_traits<ForwardIt>::value_type>
ForwardIt remove(ForwardIt first, ForwardIt last, const T& value)
{
  first = std::find(first, last, value);        // 값과 같은 element의 위치
  if (first != last) {
    for (ForwardIt i = first; ++i != last;) {
      if (!(*i == value)) {                     // 값과 같지 않다면
        *first++ = std::move(*i);               // 앞으로 이동
      }
    }
  }
  return first;
}
```
```cpp
template<class ForwardIt, class UnaryPred>
ForwardIt remove_if(ForwardIt first, ForwardIt last, UnaryPred p)
{
  first = std::find_if(first, last, p);
  if (first != last) {
    for (ForwardIt i = first; ++i != last) {
      if (!p(*i)) {                             // 조건에 맞지 않다면
        *first++ = std::move(*i);
      }
    }
  }
  return first;
}
```

## 5. std::remove Incompatibility with Associate Container
`std::remove는 associate container와 함께 사용할 수 없다`   

Container들의 iterator가 가리키는 값들이 수정 불가능하며, 이러한 container의 elements는 MoveAssignable하지 않는다   
Associate Container는 key의 고유성을 유지하기 위해서 value에 대응하는 key를 수정하는 것을 허용하지 않는다   
따라서 std::set<int>::iterator는 const int&를 반환하며, 이는 key를 수정할 수 없음을 나타낸다   


<br><br>

# Example
```cpp
#include <string_view>
#include <algorithm>

std::string str1{"Text with some   spaces"};
auto noSpaceEnd = std::remove(str1.begin(), str1.end(), ' ');

std::cout << std::string_view(str1.begin(), noSpaceEnd) << " size: " << str1.size() << '\n';
str1.erase(noSpaceEnd, str1.end());
std::cout << str1 << " size: " << str1.size() << '\n';


std::string str2 = "Text\n with\tsome \t  whitespaces\n\n";
str2.erase(std::remove_if(str2.begin(), str2.end(), [](unsigned char x) { 
  return std::isspace(x); 
  }), str2.end());
std::cout << str2 << '\n';
```