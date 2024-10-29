- [std::basic\_stringstream](#stdbasic_stringstream)
  - [1. stringstream STATE](#1-stringstream-state)
- [사용법](#사용법)
  - [1. read/write stream](#1-readwrite-stream)
  - [2. operator\>\>](#2-operator)
    - [2.1. token( split )](#21-token-split-)
      - [공백 문자 단위](#공백-문자-단위)
      - [Data Type 단위](#data-type-단위)
      - [string::getline()과 delimiter](#stringgetline과-delimiter)
    - [2.2. automatically type casting](#22-automatically-type-casting)
  - [3. stringstream::str(), clear()](#3-stringstreamstr-clear)

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

## 1. stringstream STATE
`cpp stream은 내부적으로 아래와 같은 state flag를 유지`한다   
```
Good( goodbit ): stream이 정상적으로 작동 중
EOF( eofbit ): stream이 끝에 도달했음
Fail( failbit ): input fail 또는 format error( 형식 오류 )가 발생
Bad( badbit ): serious I/O error 발생
```
`while 문에서` stringstream을 loop 반복 조건에 사용할 경우, `stream이 GOOD STATE일 때만 TRUE`를 반환하고, `그렇지 않으면 FALSE`를 반환한다   
이는 stream에 아직 읽을 데이터가 있고, error가 발생하지 않았을 때 반복을 계속한다는 의미다   


<br><br>

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
  std::cout << result << std::endl;   // Hello, World!
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

## 2. operator>>
```cpp
basic_istream& operator>>( unsigned short& value );
basic_istream& operator>>( unsigned int& value );
...
```
input stream으로부터 값을 추출한다   
기본적으로 `whitespace를 기준으로 값을 추출`한다   
### 2.1. token( split )
#### 공백 문자 단위
```cpp
std::string data = "apple orange banana";
std::stringstream ss(data);

std::string word;
// ss >> word >> word2 >> word3; 도 가능
while (ss >> word) {
  std::cout << word << std::endl;
}
```
operator>>를 이용하여 공백 문자를 제거하면서 문자열을 나눈다<br>

#### Data Type 단위
[Programmers - 다트 게임(memo)](/1_Algorithm/Programmers_level_1/241029_다트게임.md/#gpt-2-string-stream)   
```cpp
std::string data = "1D2S#10S";
std::stringstream ss(data);

for (int round = 0; round < 3; ++round) {
  int score = 0;
  char bonus = ' ';
  char option = ' ';

  ss >> score;
  ss >> bonus;
  if (ss.peek() == '#' || ss.peek() == '*') {   // peek()은 get()과는 달리 보기만 한다
    ss >> option;
  }
}
```
stringstream의 operator>>는 입력을 저장하는 memory의 Data Type에 맞춰서 string buffer에서 가져올 수 있다   
즉, `공백 단위 뿐만 아니라 Data Type 단위로 나눠서 입력 받을 수 있다`   

참고로 for문 내부의 변수를 초기화하지 않으면, option에 이전 값이 유지될 수 있다   
왜냐하면 `C++은 local variable을 초기화하지 않으면 Garbage Value 또는 이전 round의 값이 유지`되기 때문이다   

#### string::getline()과 delimiter
```cpp
#include <iostream>
#include <sstream>
#include <string>

istringstream input;
input.str("1\n2\n3\n4\n5\n6\n7\n");
int sum = 0;
for (string line; getline(input, line)) sum += stoi(line);

// ;을 기준으로 split
istringstream input2;
input2.str("a;b;c;d");
for (string line; getline(input2, line, ';')) cout << line << ' ';
```
[basic_string의 getline()](std_getline.md/#stdgetline---basic_string)을 이용하면 문자열을 특정 구분자를 기준으로 나눌 수 있다   

<br>

### 2.2. automatically type casting
```cpp
string input = "41 3.14 false hello world";
stringstream ss(input);

int n;
double f;
bool b;

ss >> n >> f >> std::boolalpha >> b;
cout  << "n = " << n << '\n'
      << "f = " << f << '\n'
      << "b = " << std::boolalpha << b << '\n';

// extract the rest using the streambuf overload
ss >> std::cout.rdbuf();
```
이처럼 string을 입력 받아서 공백을 기준으로 나누되, `Implicit Type Casting이 가능`하다   

<br>

## 3. stringstream::str(), clear()
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