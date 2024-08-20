[cppreference - erase](https://en.cppreference.com/w/cpp/string/basic_string/erase)

# std::basic_string::erase
```cpp
#include <string>

// 1
basic_string& erase(size_type index = 0, size_type count = npos);

// 2
iterator erase(iterator position); 

// 3
iterator erase(iterator first, iterator last);
```
문자열에서 특정한 문자를 제거한다.<br>

1. `index에서 시작해서 count 만큼 제거`
   1. 제거된 후의 문자열 참조를 반환
2. `position에 있는 문자를 제거`
   1. 제거된 position 뒤를 가리키는 iterator를 반환
   2. 만약 2.1.번의 position이 없는 경우 end()를 반환
3. [`first, last) 범위의 문자들을 제거`
   1. 제거된 position 뒤를 가리키는 iterator를 반환
   2. 만약 3.1.번의 position이 없는 경우 end()를 반환


<br>
<br>

# 1번 예시
```cpp
#include <string>
#include <iostream>
using namespace std;

int main()
[
  string s = "This is An Example";
  cout << s.erase(std::find(7, 3) << endl;   // This is Example -- 1
  cout << s.erase(s.find(' ')) << endl;      // This            -- 2
]
```
1번 코드는 7번 index에서 시작하여 3개의 문자를 제거하고, 이 연산을 수행한 뒤의 문자열 참조값을 반환한다<br>

2번 코드는 ' ' 문자를 처음 발견한 위치에서 문자열 끝까지 제거한 뒤, 문자열 참조값을 반환한다<br>

<br>
<br>

# 2번 예시
```cpp
int main()
{
  string s = "This is An Example";
  auto ret = s.erase(find(s.begin(), s.end(), ' '));

  cout << s << endl;      // Thisis An Example
  cout << *ret << endl;   // i
}
```
만약 마지막 문자를 제거했다면, end()를 반환하기 때문에 프로그램이 멈춘다<br>

<br>
<br>

# 3번 예시
```cpp
int main()
{
  string s = "Example";

  auto ret = s.erase(s.begin() + 1, s.begin() + 3);
  cout << s << endl;        // Emple
  cout << *ret << endl;     // m
}
```
[first, last) 범위 내의 문자들은 [x, a]이다.<br>
이 문자들을 제거하고, 제거된 문자의 뒷 문자를 반환한다<br>
```cpp
// std::next()를 이용하는 방법
int main()
{
  string s = "Example";
  auto it = std::next(s.begin(), 1);    // s의 시작점에서 1칸 뒤( 'x' )

  s.erase(it, std::next(it, 2));
  cout << *it << endl;            // x
  cout << s << endl;              // Emple
}
```