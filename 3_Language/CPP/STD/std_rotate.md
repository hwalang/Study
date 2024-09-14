- [std::rotate](#stdrotate)
    - [1. `범위에 있는 elements는 left rotation을 수행`](#1-범위에-있는-elements는-left-rotation을-수행)
    - [return value](#return-value)
- [Possible Implementation](#possible-implementation)
    - [first == middle](#first--middle)
    - [write, next\_read](#write-next_read)
    - [for문](#for문)
    - [rotate(write, next\_read, last);](#rotatewrite-next_read-last)
- [Example](#example)

<br>

# std::rotate
```cpp
#include <algorithm>

// 1. since C++20
template <class ForwardIt>
ForwardIt rotate(ForwardIt first, ForwardIt middle, ForwardIt last);

// 2. since C++17
template <class ExecutionPolicy, class ForwardIt>
ForwardIt rotate(ExecutionPolicy&& policy,
                 ForwardIt first, ForwardIt middle, ForwardIt last);
```

### 1. `범위에 있는 elements는 left rotation을 수행`
```cpp
vector<int> v{ 1, 2, 3, 4, 5, 6 };

// [first, middle): [1, 2]
// [middle, last): [3, 4, 5, 6]
// pivot: 3
auto it = std::rotate(v.begin(), v.begin() + 2, v.end());

// [first, last): [3, 4, 5, 6, 1, 2]
// *it = 1
```
- [first, last) 범위의 elements를 2 부분으로 나눠서 swap 한다.
- `[first, middle)은 첫 범위`로서 middle은 회전할 지점을 가리키며, first부터 middle까지의 elements가 swap 이후 두 번째 부분에 해당
- `[middle, last)는 두 번째 범위`로서 middle부터 last까지의 elements가 swap 이후 첫 번째 부분에 해당

`각 구간의 elements의 순서는 보존`되며, `각 구간이 서로 자리를 바꾸는 효과`다<br>

<br>

### return value
originally *first iterator<br>
`rotate를 수행하기 전의 *first를 가리키던 iterator를 반환`한다<br>
즉, first에서 distance(middle, last)만큼 next 이동한 위치를 가리키는 iterator이다<br>

<br>

# Possible Implementation
```cpp
template <class ForwardIt>
constexpr
ForwardIt rotate(ForwardIt first, ForwardIt middle, ForwardIt last)
{
  if (first == middle) return last;
  if (middle == last) return first;

  ForwardIt write = first;
  ForwardIt next_read = first;    // read position for when "read" hits "last"
  for (ForwardIt read = middle; read != last; ++write, ++read) {
    if (write == next_read) 
      next_read = read;   // track when "first" went
    std::iter_swap(write, read);
  }

  // rotate the remaining sequence into place
  rotate(write, next_read, last);
  return write;
}
```
### first == middle
first와 middle이 같다면, [first, middle) 구간이 비어 있기 때문에 회전할 필요가 없다<br>
이 경우 회전 후 첫 번째 원소가 마지막 원소 뒤로 가기 때문에 last를 반환한다<br>

middle == last 또한 이러한 이유에서 first를 반환한다.<br>

### write, next_read
wirte는 회전 작업에서 현재 쓰기 작업을 할 위치를 가리킨다<br>
next_read는 원래 first가 가리키던 element가 새롭게 이동된 위치를 추적하는 역할이다<br>

### for문
for문을 통해 read 위치의 element를 write 위치로 이동시키는 역할이다<br>

write가 next_read와 같은 위치에 도달하면, 원래 first에 있던 값이 새로운 위치로 이동한 시점이다<br>
이때 next_read가 이제부터 회전할 남은 부분을 추적하기 때문에 현재의 read 위치로 갱신된다<br>
이후 회전의 남은 구간을 다시 처리하기 위한 준비다<br>

### rotate(write, next_read, last);
for문이 끝나면 일부 구간이 회전된 상태이다<br>
남은 구간을 처리하기 위해 재귀를 호출하여 회전을 수행한다.

<br>

# Example
**[ Programmers - 배열 회전시키기 ](https://school.programmers.co.kr/learn/courses/30/lessons/120844)**<br>

```cpp
#include <algorithm>

std::vector<int> v{0, 1, 2, 2, 3, 4, 5, 7, 7, 10};

// rotation to the left
std::rotate(v.begin(), v.begin() + 1, v.end()); // 1 2 2 3 4 5 7 7 10 0

// rotation to the right
std::rotate(v.rbegin(), v.rbegin() + 1, v.rend()); // 0 1 2 2 3 4 5 7 7 10
```
