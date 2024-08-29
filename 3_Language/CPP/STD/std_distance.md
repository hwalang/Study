
[ 참고1 - programmers ](https://devdocs.programmers.co.kr/cpp/iterator/distance)<br>
[ 참고2 - cppreference ](https://en.cppreference.com/w/cpp/iterator/distance)

# std::distance
```cpp
#include <iterator>

template<class InputIt>
typename std::iterator_traits<InputIt>::difference_type 
  distance(InputIt first, InputIt last);
```
`[first에서 last)까지 몇 번 이동해야 갈 수 있는지 반환`한다.<br>
`last에서 first로 도달할 수 있는 경우, 음수 값을 반환`한다.<br>

만약 last까지 갈 수 없다면, 동작하지 않는다.<br>

<br>
<br>

# Possible Implementation
```cpp
// C++17
template<class It>
constexpr typename std::iterator_traits<It>::difference_type
  distance(It first, It last)
{
  using category = typename std::iterator_traits<It>::iterator_category;
  static_assert(std::is_base_of_v<std::input_iterator_tag, category>);

  if constexpr (std::is_base_of_v<std::input_iterator_tag, category>)
    return last - first;
  else
  {
    typename std::iterator_traits<It>::difference_type result = 0;
    while (first != last) {
      ++first;
      ++result;
    }
    return result;
  }
}
```
### 1. template
```cpp
template <class It>
```
It라는 매개변수를 사용하며, It는 iterator type으로써 다양한 유형의 iterator를 처리할 수 있다<br>

### 2. category
```cpp
using category = typename std::iterator_traits<It>::iterator_category;
```
iterator_category는 iterator가 어떤 종류인지 나타낸다.<br>
예시: input_iterator_tag, random_access_iterator_tag 등<br>

### 3. static_assert
```cpp
static_assert(std::is_base_of_v<std::input_iterator_tag, category>);
```
static_assert를 통해서 `compile time에 category가 예상한 값과 일치하는지 검사`한다.<br>
category가 input_iterator_tag를 상속받는지 확인한다<br>

### 4. if constexpr
```cpp
if constexpr (std::is_base_of_v<std::input_iterator_tag, category>)
```
`if constexpr`는 C++17부터 도입된 기능으로, `compile time에 조건을 검사`한다.<br>
만약 iterator_category가 input_iterator_tag( random_access_iterator_tag) 를 상속 받는 경우, last-first연산이 가능하기 때문에 그 결과를 반환한다.<br>
그 외 iterator라면, last에 도달할 때까지 first를 하나씩 증가시키며 거리를 계산한다<br>

<br>
<br>

# Example
```cpp
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

int main()
{
  std::vector<int> vec{3, 1, 4};
  std::cout << "distance(first, last) = "
            << std::distance(vec.begin(), vec.end()) << '\n'
            << "distance(last, first) = "
            << std::distance(vec.end(), vec.begin()) << '\n';
}

// distance(first, last) = 3
// distance(last, first) = -3
```