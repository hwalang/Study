- [Place Value( Digit )](#place-value-digit-)
  - [place value VS digit](#place-value-vs-digit)
  - [숫자 이어 붙이기](#숫자-이어-붙이기)
    - [1. INTEGER TO STRING](#1-integer-to-string)
    - [2. MATH](#2-math)

<br>

# Place Value( Digit )
`숫자의 자릿수를 다루는 방법`을 알아본다<br>

<br>

## place value VS digit
먼저 place value와 digit의 의미 차이를 알아보자.<br>
```cpp
1234 has four digits.                 // 1234는 네 자릿수이다.
The digit in the hundreds place is 2. // 백의 자리에 있는 숫자는 2이다.
The place value of 5 in 352 is 50.    // 352에서 5의 자리값은 50이다.
```
`digit`: 숫자를 구성하는 개별 숫자를 의미한다.<br>
`place value`: 숫자의 위치나 자리값을 의미한다.<br>

<br>

## 숫자 이어 붙이기
[프로그래머스 - 이어붙인수](https://school.programmers.co.kr/learn/courses/30/lessons/181928)<br>

### 1. INTEGER TO STRING
```cpp
int solution(vector<int> num_list)
{
  string str_odd = "";
  string str_even = "";
  for (auto num : num_list) {
    if (num % 2 == 0) str_even += to_string(num);
    else              str_odd.append(to_string(num));
  }
  return stoi(str_even) + stoi(str_odd);
}
```
각 digit이 짝수/홀수 인지 판단하여 짝수만 이어 붙인 수와 홀수만 이어 붙인 수를 더한 값을 반환하는 함수이다.<br>
`정수를 문자열로 변환하고 문자열 연산을 이용하여 직관적으로 수를 다룬다`<br>

### 2. MATH

```cpp
int solution(vector<int> num_list)
{
  int odd = 0;
  int even = 0;
  for (auto num : num_list) {
    if (num % 2 == 0) {
      even *= 10;
      even += num;
    }
    else {
      odd *= 10;
      odd += num;
    }
  }

  return odd + even;
}
```
`수학을 이용하여 정수 연산을 수행`한다<br>
