# std::count, std::count_if
```cpp
#include <algorithm>

// 1.
template <class InputIt, class T>
typename std::iterator_traits<InputIt>::difference_type
  count(InputIt first, InputIt last, const T& value);

// 2.
template <class InputIt, class UnaryPred>
typename std::iterator_traits<InputIt>::difference_type
  count(InputIt first, InputIt last, UnaryPred p);
```
특정 기준( criteria )을 만족하는 [first, last) 범위의 elements 수를 반환한다.   
1. value와 같은 elements의 수를 Counting
2. p가 true인 elements의 수를 Counting

## Return Value
[first, last) 범위에서 `*it == value` 또는 `p(*it) != false`를 만족하는 iterator의 수를 반환한다   

## Possible Implementation
```cpp
template <class InputIt, class T = std::iterator_traits<InputIt>::value_type>
typename std::iterator_traits<InputIt>::difference_type
  count(InputIt first, InputIt last, const T& value)
{
  typename std::iterator_traits<InputIt>::difference_type ret = 0;
  for (; first != last; ++first)
    if (*first == value)
      ++ret;
  return ret;
}
```

```cpp
template <class InputIt, class UnaryPred>
typename std::iterator_traits<InputIt>::difference_type
  count_if(InputIt first, InputIt last, UnaryPred p)
{
  typename std::iterator_traits<InputIt>::difference_type ret = 0;
  for (; first != last; ++first)
    if (p(*first))
      ++ret;
  return ret;
}
```

## Example
