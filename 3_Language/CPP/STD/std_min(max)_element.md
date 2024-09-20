# std::min_element, std::max_element

[cppreference - std::min_element](https://en.cppreference.com/w/cpp/algorithm/min_element)<br>
[cppreference - std::max_element](https://en.cppreference.com/w/cpp/algorithm/max_element)<br>
```cpp
#include <algorithm>

template <class ForwardIt>
ForwardIt min_element( ForwardIt first, ForwardIt last );

template <class ForwardIt, class Compare>
ForwardIt min_element( ForwardIt first, ForwardIt last, Compare comp );
```

`[first, last) 범위 내에서 가장 작은 element를 찾는다`.</br>
`operator<` 와 `std::less{}`를 이용하여 elements를 비교한다.</br>

max_element는 min_element의 반대 결과가 나온다<br>

<br>

# Return
`[first, last) 범위 내의 가장 작은 element`를 return 한다.</br>
만약 가장 작은 element가 여러 개 존재한다면, `가장 처음 발견한 element`를 return 한다.</br>
`비어있는 범위라면 last를 반환`한다.</br>

<br>

# Complexity
std::distance(first, last)로써 `O(N)`이다.</br>

<br>

# Posible implementation
```cpp
template<class ForwardIt>
ForwardIt min_element(ForwardIt first, ForwardIt last)
{
  if (first == last) return last;

  ForwardIt smallest = first;

  while (++first != last) {
    if (*first < *smallest) {
      smallest = first;
    }
  }

  return smallest;
}
```

```cpp
template<class ForwardIt, Compare comp>
ForwardIt min_element(ForwardIt first, ForwardIt last, Compare comp)
{
  if (first == last) return last;

  ForwardIt smallest = first;

  while (++first != last) {
    if (comp(*first, *smallest)) {
      smallest = first;
    }
  }

  return smallest;
}
```

<br>

# Example

## min_element
[주사위 게임3](/2_Algorithm/Programmers/240809_주사위게임3.md) : min_element 사용 예시

```cpp
#include <algorithm>

std::vector<int> vec {3, 1, -4, 1, 5, 9};
std::vector<int>::iterator result = std::min_element(vec.begin(), vec.end());

// *result = -4
// result : 2 ( index )
```

## max_element
[Programmers - 문자열 묶기](https://school.programmers.co.kr/learn/courses/30/lessons/181855)<br>
```cpp
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<string> strArr) {
    vector<int> len(31, 0);         // 0은 dummy
    for (string str : strArr) {
        len[str.size()]++;
    }
    
    return *max_element(len.cbegin(), len.cend());
}
```
[Programmers - 가장 큰 수 찾기](https://school.programmers.co.kr/learn/courses/30/lessons/120899)   
```cpp
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> array) {
    auto max_index = max_element(array.cbegin(), array.cend());
    return vector<int>{ *max_index, static_cast<int>((max_index - array.cbegin())) };
}
```