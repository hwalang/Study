
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
  - [1. sort](#1-sort)
  - [2. string doubling](#2-string-doubling)
    - [2.1. 직접 밀기](#21-직접-밀기)
    - [2.2. find](#22-find)

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
일반적으로 문자열 길이와 처음 주어진 두 문자열이 같은지 비교하여 불필요한 연산을 피한다   

## 1. sort
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


## 2. string doubling
두 문자열 중 하나의 문자열을 오른쪽으로 최소 몇 번 밀어야 같아지는지 판단하는 방법   
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


### 2.2. find
```cpp
#include <string>
using namespace std;

int is_same(string A, string B) {
    if (A.size() != B.size()) return -1;

    string doubled = B + B;
    return doubled.find(A);
}
```
문자열 A를 오른쪽으로 밀면서 B로 변환하는 과정은 B를 A로 되돌리는 것과 동일한 작업이다   
따라서 B + B에서 A를 찾는 것은 A가 B의 몇 번 밀린 결과인지 정확히 알 수 있다   
