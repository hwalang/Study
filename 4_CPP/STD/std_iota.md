# std::iota
```cpp
#include <numeric>

template <class ForwardIt, class T>
void iota(ForwardIt first, ForwardIt last, T value);
```
`[first, last) 범위`를 점차적으로 증가한 값으로 채운다.</br>
`시작 값은 value`이며, `++value`가 반복적으로 수행된다.</br>

std::iota를 사용하기 위해서는 `container의 크기를 미리 지정`해야 한다.</br>
지정된 범위 내의 iterator를 통해 연속된 값을 채우기 때문이다.</br>


## Possible Implementation
```cpp
template <class ForwardIt, class T>
constexpr
void iota(ForwardIt first, Forward last, T value) 
{
  for (; first != last; ++first, ++value) {
    *first = value;
  }
}
```

## Example
```cpp
#include <vector>
#include <numeric>

std::vector<int> solution(int start_num, int end_num) 
{
  std::vector<int> vec(end_num - start_num + 1);
  std::iota(vec.begin(), vec.end(), start_num);
  return vec;
}
```