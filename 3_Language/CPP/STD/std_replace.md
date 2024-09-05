- [std::basic\_string::replace](#stdbasic_stringreplace)
  - [return](#return)
  - [Exception](#exception)
  - [Example](#example)
    - [1. basic](#1-basic)
    - [2. chaining](#2-chaining)

<br>

[ cppreference - std::basic_string::replace ](https://en.cppreference.com/w/cpp/string/basic_string/replace)<br>

# std::basic_string::replace
보통 `부분 문자열을 다른 문자열로 대체할 때 사용`한다<br>
```cpp
// 1.
basic_string& replace(size_type pos, size_type count, const basic_string& str);

// 2.
basic_string& replace(const_iterator first, const_iterator last, const basic_string& str);
```
`주어진 문자열에서 [begin() + pos, begin() + std::min(pos + count, size())) 또는 [first, last) 범위 내의 문자열을 대체`한다<br>

1. 교체를 시작할 위치( pos )와 교체할 기존 문자열 길이( count ), 대체할 새로운 문자열( str )로 구성


<br><br>

## return 
`*this` <br>
문자열을 변경한 후 변경된 문자열 객체의 참조를 반환한다<br>
*this를 반환하면 `chaning 방식으로 다른 연산과 결합`할 수 있다<br>

<br><br>

## Exception
pos가 size()보다 큰 경우 std::out_of_range를 던진다<br>
만약 replace 결과의 size()가 max_size()를 초과하면, std::length_error를 던진다<br>

<br><br>

## Example
### 1. basic
```cpp
std::string str = "Hello, World";

// 1. 
str.replace(7, 5, "C++");   // "World" to "C++"



```


### 2. chaining
```cpp
std::string str = "Hello, World";

str.replace(0, 5, "Hi").replace(4, 3, "C++");   // Hi, C++!
```
*this를 반환하기 때문에 chaning 방식으로 다른 연산과 결합할 수 있다<br>