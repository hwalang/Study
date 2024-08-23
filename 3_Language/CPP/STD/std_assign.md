- [std::vector::assign](#stdvectorassign)
  - [예시](#예시)

<br>

# std::vector::assign
[cppreference - std::vector::assign](https://en.cppreference.com/w/cpp/container/vector/assign)<br>
```cpp
#include <vector>

// 1
void assign(size_type count, const T& value);

// 2
template <class InputIt>
void assign(InputIt first, InputIt last);

// 3
void assign(std::initializer<T> ilist);
```
Container의 contents를 대체한다<br>

1. value 값을 복제하여 count 만큼 가지는 content로 대체
2. [first, last) 범위의 복제본으로 content를 대체
3. 초기화된 list의 elements로 content를 대체

## 예시
```cpp
#include <vector>
#include <string>

int main()
{
  std::vector<char> characters;

  characters.assign(5, 'a');    // a, a, a, a, a

  const std::string extra(6, 'b');
  characters.assign(extra.begin(), extra.end());  // b, b, b, b, b, b

  characters.assign({'C', '+', '+', 'L'});  // C, +, +, L
}
```