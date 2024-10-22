
- [**문자열의 가장 왼쪽에 있는 0을 제거하는 방법**](#문자열의-가장-왼쪽에-있는-0을-제거하는-방법)
    - [내가 적용한 방법](#내가-적용한-방법)
    - [간단한 방법](#간단한-방법)
- [**문자 반복 출력**](#문자-반복-출력)
    - [1. 별 찍기](#1-별-찍기)
    - [2. 문자 반복 출력 - string(cnt, char) 생성자](#2-문자-반복-출력---stringcnt-char-생성자)
- [**문자열 token 및 parsing**](#문자열-token-및-parsing)
- [char to string | string to char](#char-to-string--string-to-char)
  - [1. string(cnt, char);](#1-stringcnt-char)
  - [2. string\[0\];](#2-string0)
- [**문자열 비교**](#문자열-비교)
  - [1. 같은지 비교하는 방법](#1-같은지-비교하는-방법)
  - [2 shift 연산으로 같아질 수 있는지 비교하는 방법](#2-shift-연산으로-같아질-수-있는지-비교하는-방법)
    - [2.1. 직접 밀기](#21-직접-밀기)
    - [2.2. string doubling](#22-string-doubling)
- [Alphabet Operation](#alphabet-operation)
  - [1. Alphabet Shift](#1-alphabet-shift)
    - [1.1. Modular Operation](#11-modular-operation)
      - [Logic](#logic)
    - [1.2. String Doubling](#12-string-doubling)

<br><br>

# **문자열의 가장 왼쪽에 있는 0을 제거하는 방법**
[Programmers - 0빼기](https://school.programmers.co.kr/learn/courses/30/lessons/181847)<br>

문제의 조건을 있는 그대로 적용하기 위해서 for문을 사용했지만, 더 간단한 방법이 있었다<br>
string을 int로 변환하면 가장 왼쪽에 있는 0이 자동으로 사라진다<br>

### 내가 적용한 방법
```cpp
#include <string>

using namespace std;

string solution(string n_str) {
    if (n_str[0] != '0') return n_str;

    for (auto it = n_str.begin(); it != n_str.end();) {
        if (*it == '0') {
            it = n_str.erase(it);
        }
        else {
            break;
        }
    }

    return n_str;
}
```

### 간단한 방법
```cpp
#include <string>

using namespace std;

string solution(string n_str)
{
  return to_string(stoi(n_str));
}
```

<br><br>

# **문자 반복 출력**
```cpp
#include <string>
basic_string( size_type count, CharT ch, const Allocator& alloc = Allocator());
```
`ch 문자를 count만큼 복사하여 string을 생성`한다<br>

### 1. 별 찍기
[ Programmers - 직각삼각형 출력 ](https://school.programmers.co.kr/learn/courses/30/lessons/120823)<br>
```cpp
#include <string>
#include <iostream>
using namespace std;

int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cout << string(i, '*') << '\n';
}
```

### 2. 문자 반복 출력 - string(cnt, char) 생성자
[ Programmers - 문자 반복 출력 ](https://school.programmers.co.kr/learn/courses/30/lessons/120825)<br>
```cpp
#include <string>
#include <algorithm>

using namespace std;

string solution(string my_string, int n) {
    string result = "";
    for_each(my_string.cbegin(), my_string.cend(), [&result, n](char ch) {
        result += string(n, ch);
    });
    return result;
}
```

<br><br>

# **문자열 token 및 parsing**
[programmers - 다항식 더하기](/1_Algorithm/Programmers/240923_다항식더하기.md/#풀이)   
[token과 parsing이란](/5_CS/4_token_parsing.md)   
문자열을 whitespace 또는 delimiter를 기준으로 token화 하는 방법을 메모했다   

<br><br>

# char to string | string to char
## 1. string(cnt, char);
cpp에서 char를 string으로 변환하는 방법이 없다   
```cpp
to_string('a');     // "97"
```
`to_string(char)를 하는 경우, ASCII code로 변환 후, string으로 casting`하기 때문에 의도치 않은 값이 나온다   
```cpp
string(1, 'a');     // "a"
```
때문에 `string(1, char)를 이용해서 string을 생성`한다   
[문자 반복 출력](#2-문자-반복-출력---stringcnt-char-생성자)에서 string(cnt, char) 생성자에 대한 설명이 있다   

## 2. string[0];
string의 첫 번째 index만 가져오면 된다   
```cpp
string s = "a";
s[0];
```

<br><br>


# **문자열 비교**
## 1. 같은지 비교하는 방법
일반적으로 문자열 길이와 처음 주어진 두 문자열이 같은지 비교하여 불필요한 연산을 피한다   
```cpp
#include <string>
#include <algorithm>
using namespace std;

bool is_same(string A, string B) {
    if (A.size() != B.size()) return false;
    if (A == B) return true;

    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    return A == B;
}
```
두 문자열을 같은 기준( 여기선 사전순 )으로 정렬하면 `같은 위치에 같은 문자`가 있는 원리를 이용했다   

<br>

## 2 shift 연산으로 같아질 수 있는지 비교하는 방법
두 문자열 중 하나의 문자열을 왼쪽( 또는 오른쪽 )으로 최소 몇 번 밀어야 같아지는지 판단하는 방법   

### 2.1. 직접 밀기
```cpp
#include <string>
using namespace std;

int is_same(string A, string B) {
    if (A.size() != B.size()) return -1;
    if (A == B) return 0;

    string shifted = A;
    for (int shift = 1; shift <= A.size(); ++ shift) {
        char last = shifted.back();
        shifted.pop_back();
        shifted.insert(0, 1, last);         // last + shifted.substr(0, shifted.size() - 1);
        if (shifted == B) return shift;
    }
    
    return -1;
}
```
문자열을 오른쪽으로 한 칸씩 밀면서 확인한다   


### 2.2. string doubling
두 문자열 중 하나의 문자열을 오른쪽으로 최소 몇 번 밀어야 같아지는지 판단하는 방법   
```cpp
#include <string>
using namespace std;

int is_same(string A, string B) {
    if (A.size() != B.size()) return -1;

    string doubled = B + B;
    return doubled.find(A);
}
```
```
A = "hello"
B = "ohell"

BB = "ohellohell"
B.find(A) = 1
```
문자열 A를 오른쪽으로 밀면서 B로 변환하는 과정은 B를 A로 되돌리는 것과 동일한 작업이다   
따라서 B + B에서 A를 찾는 것은 A가 B의 몇 번 밀린 결과인지 정확히 알 수 있다   

<br><br>

# Alphabet Operation
std::string의 각 문자를 변환하는 다양한 방법을 기록한다.   

## 1. Alphabet Shift
[ Programmers - 시저 암호 ](https://school.programmers.co.kr/learn/courses/30/lessons/12926)   
[ 풀이 ](/1_Algorithm/Programmers_level_1/241022_시저암호.md/#other)   

어떤 문장의 알파벳을 n만큼 민 거리만큼 이동한 알파벳으로 변환하는 방법을 알아본다   
'Z' 또는 'z' 이후는 'A' 또는 'a'로 돌아오며, n은 1이상 25이하인 자연수이다   

### 1.1. Modular Operation
```cpp
#include <string>
using namespace std;

string solution(string s, int n) {
  string answer = "";
  for (char c : s) {
    if ('A' <= c && c <= 'Z') {
      c = 'A' + (c - 'A' + n) % 26;
    }
    else if ('a' <= c && c <= 'z') {
      c = 'a' + (c - 'a' + n) % 26;
    }

    // spaces remain unchanged
    answer += c;
  }
  return answer;
}
```
#### Logic
1. current_char를 'A' 또는 'a' 문자로 제거해서 `0 ~ 25 사이의 정수`를 가져온다
2. 1번에서 구한 정수에 n을 더하여 `shift 연산`을 적용한다
3. `% 26`을 통해 'Z' 또는 'z'를 넘어가면 'A' 또는 'a'로 돌아오게 한다
4. 현재 0 ~ 25 사이의 정수를 가지고 있기에 `+ 'A'` 또는 `+ 'a'`를 통해 ASCII 문자로 변환한다
5. space character라면, answer 문자열에 그냥 추가한다

### 1.2. String Doubling
```cpp
#include <string>
using namespace std;

string solution(string s, int n) {
    string lower_set = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";
    string upper_set = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == ' ') continue;
        
        int pos = 0;
        if (islower(s[i])) {
            pos = lower_set.find(s[i]);
            s[i] = lower_set[pos + n];
        }
        else {
            pos = upper_set.find(s[i]);
            s[i] = upper_set[pos + n];
        }
    }
    return s;
}
```
n이 1 ~ 25 사이의 자연수라서 적합한 풀이   