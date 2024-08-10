# std::reverse
```cpp
// BidirIt: LagacyBidirectionalIterator에 속함
template< class BidirIt >
void reverse( BidirIt first, BidirIt last );                            // #1

template< class ExecutionPolicy, class BidirIt >
void reverse( ExecutionPolicy&& policy, BidirIt first, BidirIt last );  // #2
```
1. `[first, last) 범위 내의 elements 순서를 바꾼다`.</br>[0, std::distance(first, last) / 2)의 각 정수 i에 대해 모든 iterator first + i와 (last - i) - 1 쌍에 std::iter_swap을 적용하는 방식으로 동작한다.
2. 1번과 동일한 효과지만 policy에 맞춰서 수행한다.

</br>
</br>
</br>

## Complexity
내부 동작을 보면 알 수 있듯이 `std::distance(first, last) / 2 swaps` 복잡도를 가진다.

</br>
</br>
</br>

## Possible Implementation
```cpp
template<class BidirIt>
constexpr
void reverse(BidirIt first, BidirIt last)
{
  using iter_cat = typename std::iterator_traits<BidirIt>::iterator_category;

  if constexpr (std::is_base_of_v<std::random_access_iterator_tag, iter_cat>)
  {
    if (first == last) return;

    for (--last; first < last; (void)++first, --last)
      std::iter_swap(first, last);
  }
  else
  {
    while (first != last && first != --last)
      std::iter_swap(first++, last);
  }
}
```

</br>
</br>
</br>

## Example
```cpp
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

void println(auto rem, auto const& list)
{
  for (std::cout << rem; auto e : list)
    std::cout << e << ' ';
  std::cout << '\n';
}

int main()
{
  std::vector<int> vec {1, 2, 3};
  std::reverse(vec.begin(), vec.end());
  println("after reverse, vec = ", vec);      // 3 2 1

  int a[] = {4, 5, 6, 7};
  std::reverse(std::begin(a), std::end(a));   // 7 6 5 4
  println("after reverse, a = ", a);
}
```



</br>
</br>
</br>

# 참고 자료
[cppreference-reverse](https://en.cppreference.com/w/cpp/algorithm/reverse)

