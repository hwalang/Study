- [sentry class](#sentry-class)
  - [sentry object의 역할](#sentry-object의-역할)
    - [1. check and set stream state](#1-check-and-set-stream-state)
    - [2. I/O 전후의 준비 및 정리 작업](#2-io-전후의-준비-및-정리-작업)
      - [2.1. std::istream](#21-stdistream)
      - [2.2. std::ostream](#22-stdostream)
    - [3. lock stream](#3-lock-stream)
    - [4. error 처리](#4-error-처리)
  - [Example](#example)
- [std::getline - iostream](#stdgetline---iostream)
  - [return value](#return-value)
  - [Example](#example-1)
- [std::getline - basic\_string](#stdgetline---basic_string)
  - [Example](#example-2)

<br>

# sentry class
**[istream sentry class](https://en.cppreference.com/w/cpp/io/basic_istream/sentry) | [ostream sentry class](https://en.cppreference.com/w/cpp/io/basic_ostream/sentry)**   
cpp의 `iostream에서 내부적으로 사용되는 guard( 도우미 ) 객체`다   
sentry object는 stream의 state를 관리하고, I/O 작업 전에 필요한 준비 작업을 수행하며, 작업 후에 정리 작업을 수행하는 역할이다   
이는 stream의 안정성과 효율성을 높이는 데 중요하다   

iostream function( operator>>, operator<<, get(), getline() 등 ) 호출 시 자동으로 생성되는 객체   

## sentry object의 역할
### 1. check and set stream state
sentry object는 stream이 valid한 상태인지 확인   
stream이 이전에 error( failbit, badbit )를 겪었는지, input 또는 output mode로 올바르게 설정됐는지 등을 검사   

### 2. I/O 전후의 준비 및 정리 작업
#### 2.1. std::istream
1. stream의 `skipws` flag가 설정됐는지 확인하고, 필요에 따라 공백 문자를 건너뛰도록 설정
2. input 작업 전에 buffer를 준비

#### 2.2. std::ostream
1. output 작업 후 flush( buffer의 내용을 실제 출력 장치로 전송 )할지 결정

### 3. lock stream
Concurrency( multi-threading ) 환경에서 sentry object는 stream에 대한 lock을 관리하여 여러 thread가 동시에 접근하지 못하게 막는다   

### 4. error 처리
I/O 작업 중 error가 발생하면, sentry object는 stream의 state flag를 업데이트하고, 필요에 따라 exception을 던진다   

## Example
```cpp
#include <iostream>
#include <sstream>

stringstream ss(" 123 456 789 ");
int num;

while (ss >> num) {
  cout << "읽은 숫자: " << num << '\n';
}
```
위 코드에서 `ss >> num` 연산이 호출될 때마다, 내부적으로 sentry object가 생성되어 stream의 state를 검사하고, 필요한 설정을 수행한다   


<br><br>


# std::getline - iostream
```cpp
// 1.
basic_istream& getline(char_type* s, std::streamsize count);

// 2.
basic_istream& getline(char_type* s, std::streamsize count, char_type delim);
```
특정 delimiter 또는 end of line까지 stream으로부터 문자열( characters )을 추출한다   
1번 getline은 `getline(s, count, widen('\n))`와 동일하다   

sentry object를 생성 및 체크 후, 아래 3가지 조건이 발생할 때까지 `*this로부터 문자열을 추출하고 s에 저장`한다   
1. input sequence에서 end of file 발생
2. 다음 선택되는 문자 c가 delimiter인 경우, 이때 c는 s에 저장되지 않는다
3. count( s 문자열의 크기 )가 음수 또는 coount - 1인 경우, setstate(failbit)가 호출

count가 0보다 크면, null 문자라도 s에 추가한다   

## return value
*this

## Example
```cpp
#include <iostream>
#include <sstream>
#include <vector>
#include <array>

istringstream input("abc|def|gh");
vector<array<char, 4>> v;
for (array<char, 4> a; input.getline(&a[0], 4, '|'))
  v.emplace_back(a);    // { abc, def, gh }
```


<br><br>


# std::getline - basic_string
```cpp
#include <string>

template <class CharT, class Traits, class Allocator>
basic_istream<CharT, Traits>& getline(basic_istream<CharT, Traits>& input,
                                      basic_string& str, CharT delim);

template <class CharT, class Traits, class Allocator>
basic_istream<CharT, Traits>& getline(basic_istream<CharT, Traits>& input,
                                      basic_string& str);
```
input stream으로부터 characters를 읽고, 이를 string에 저장   

1. sentry object를 생성하고 체크한 후, 아래 3가지를 수행
   1. str.erase()를 호출
   2. input으로부터 characters를 추출하고, 아래 3가지가 발생할때까지 이를 str에 추가
      1. end-of-file
      2. 다음 input character가 delim인 경우, 이때 str에 이 문자를 저장하지 않는다
      3. str.max_size()인 경우 failbit 반환
   3. delim이 아닌 어떠한 이유로 아무런 characters를 추출하지 않은 경우, failbit
2. 1번 동일하지만 delim이 input.widen('\n')이다   

## Example
```cpp
#include <iostream>
#include <sstream>
#include <string>

istringstream input;
input.str("1\n2\n3\n4\n5\n6\n7\n");
int sum = 0;
for (string line; getline(input, line)) sum += stoi(line);

istringstream input2;
input2.str("a;b;c;d");
for (string line; getline(input2, line, ';')) cout << line << ' ';
```