[ 참고1 - programmers ](https://devdocs.programmers.co.kr/cpp/algorithm/find)<br>
[ 참고2 - cppreference ](https://en.cppreference.com/w/cpp/algorithm/find)

# std::find | std::find_if | std::find_if_not

```cpp
#include <algorithm>

// 1
template<class InputIt, class T>
InputIt find(InputIt first, InputIt last, const T& value);

// 2
template<class InputIt, class UnaryPred>
InputIt find_if(InputIt first, InputIt last, UnaryPred p);

// 3
template<class InputIt, class UnaryPred>
InputIt find_if_not(InputIt first, InputIt last, UnaryPred q);
```
[first, last) 범위 내에서 특정 조건을 만족하는 첫 번째 element의 iterator를 반환한다.<br>
만약 만족하는 element가 없는 경우, last( end() )를 반환한다<br>

### condition
1. `*it == value` is true
2. `p(*it)` is true
3. `q(*it)` is false

<br>

### UnaryPred
UnaryPred는 단항 조건자를 의미하는 template 매개 변수이다<br>
이 매개 변수는 `단항 함수 또는 함수 객체로써 하나의 인자를 받아 bool 값을 반환`한다<br>

```cpp
// function pointer
bool is_even(int n) { return n % 2 == 0; }
auto it = std::find_if(v.begin(), v.end(), is_even);

// lambda
auto it = std::find_if_not(v.begin(), v.end(), [](int n) { return n % 2 == 0; });
```
이때 UnaryPred는 하나의 인자만 받아야 하며, bool 값을 반환해야 한다.<br>
참고로 `find()에서 container 안에 있는 element가 매개 변수로 들어간다`<br>

<br>
<br>

# Possible Implementation
### find
```cpp
template <class It, class T>
It find(It first, It last, const T& value)
{
    for (; first != last; ++first)
        if (*first == value)
            return first;

	return last;
}
```
### find_if
```cpp
template <class It, class UnaryPred>
It find_if(It first, It last, UnaryPred p)
{
    for (; first != last; ++first)
        if (p(*first))
            return first;

	return last;
}
```
### find_if_not
```cpp
template <class It, class UnaryPred>
It find_if(It first, It last, UnaryPred q)
{
    for (; first != last; ++first)
        if (!q(*first))
            return first;

	return last;
}
```

<br>
<br>

# 예시1 - find
[ Programmers - 가까운 1 찾기](https://school.programmers.co.kr/learn/courses/30/lessons/181898)<br>
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int solution(std::vector<int> arr, int idx) {
    // find 함수로 범위 [arr.begin() + idx, arr.end())에서 1을 찾는다.
    auto it = std::find(arr.begin() + idx, arr.end(), 1);
    
    // 1이 없으면 -1을 반환
    if (it == arr.end())
        return -1;
    
    // 1이 있으면 해당 위치의 인덱스를 반환
    return std::distance(arr.begin(), it);
}
```

<br>

# 예시2 - find_if
[Programmers - 첫 번째로 나오는 음수](https://school.programmers.co.kr/learn/courses/30/lessons/181896) <br>
```cpp
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int solution(vector<int> num_list)
{
    auto it = find_if(begin(num_list), end(num_list), [](int n) { return n < 0; });
    return if (it == end(num_list)) ? -1 : distance(begin(num_list), it);
}
```