- [std::basic\_stringstream](#stdbasic_stringstream)
- [사용법](#사용법)
  - [1. read/write stream](#1-readwrite-stream)
  - [2. stringstream::str(), clear()](#2-stringstreamstr-clear)
  - [3. token( split )](#3-token-split-)

<br>

# std::basic_stringstream
[ cpp reference ](https://en.cppreference.com/w/cpp/io/basic_stringstream)<br>
```cpp
#include <sstream>

template <class CharT,
          class Traits = std::char_traits<CharT>,
          class Allocator = std::allocator<CharT> >
class basic_stringstream : public basic_iostream<CharT, Traits>
```
class template인 std::basic_stringstream은 문자열 기반 stream에 대해 I/O operation을 구현한다.<br>
std::basic_string 객체를 효과적으로 저장할 수 있으며, 이러한 객체에 대해 I/O operation을 수행한다.<br>

파일이나 표준 I/O처럼 `문자열을 읽고 쓸 수 있다`.<br>

<br>
<br>

# 사용법
## 1. read/write stream
```cpp
#include <iostream>
#include <sstream>
#include <string>

int main()
{
  // write
  std::stringstream ss;
  ss << "Hello, ";
  ss << "World!";

  std::string result = ss.str();
  std::cout << result << std::endl;
}
```
```cpp
int main()
{
  std::string data = "42 3.14 Hello";
  std::stringstream ss(data);

  int i;
  double d;
  std::string s;

  ss >> i >> d >> s;
}
```
`operator<<로 문자열을 string based stream에 작성`하고, `operator>>를 사용하여 문자열을 string based stream에서 읽는다`.<br>

`std::cin을 통해 입력을 받는 방식과 유사`하다<br>

<br>

## 2. stringstream::str(), clear()
```cpp
std::stringstream ss;
ss << "12345";

int num;
ss >> num;    // 12345

ss.str("");
ss.clear();
```
`str()` : stringstream 객체에 있는 문자열을 get 또는 set 한다.<br>
`clear()` : stringstream 상태를 초기화<br>

<br>

## 3. token( split )
```cpp
std::string data = "apple orange banana";
std::stringstream ss(data);

std::string word;
// ss >> word >> word2 >> word3; 도 가능
while (ss >> word) {
  std::cout << word << std::endl;
}
```
문자열을 특정 구분자를 기준으로 나눌 수 있다<br>
operator>>를 이용하여 공백 문자를 제거하면서 문자열을 나눈다<br>