- [Introduce](#introduce)
    - [특징](#특징)
- [Example](#example)
  - [1. Bitwise AND : 짝수? 홀수?, bit mask](#1-bitwise-and--짝수-홀수-bit-mask)
    - [1.1. 짝수? 홀수?](#11-짝수-홀수)
    - [1.2. bit mask](#12-bit-mask)
      - [응용 : Flag](#응용--flag)
      - [응용 : 사용됐는지 여부를 추적](#응용--사용됐는지-여부를-추적)
  - [2. Bitwise Left-Shift : 2배](#2-bitwise-left-shift--2배)
    - [2.1. 모든 elements를 2배씩 증가](#21-모든-elements를-2배씩-증가)
    - [2.2. T시간에 2배씩 증가](#22-t시간에-2배씩-증가)
  - [3. Bitwise Right-Shift : 2나누기](#3-bitwise-right-shift--2나누기)
    - [3.1. Adding Binary Strings Using Bitwise Operations Code](#31-adding-binary-strings-using-bitwise-operations-code)

<br>

# Introduce
[ Bitwise operation ](https://en.wikipedia.org/wiki/Bitwise_operation)<br>
유용한 bitwise operation에 대해 알아본다<br>

### 특징
`빠르고 간단한 연산`<br>
과거 또는 저가형 processors에서 일반적으로 bitwise operation이 나눗셈, 곱셈, 덧셈에 대해 `훨씬 빠른 속도`를 가진다<br>
최신 processors는 덧셈과 곱셈을 bitwise operation만큼 빠르게 수행하지만, resource 사용을 줄이기 때문에 `전력 사용량이 적다`<br>

<br>
<br>

# Example
## 1. Bitwise AND : 짝수? 홀수?, bit mask
```
    0101  (decimal 5)
AND 0011  (decimal 3)
---------
    0001
```
`두 operand는 같은 크기의 bit를 가져야 한다`<br>
`두 operand의 bit에 대해 logical AND 연산을 수행`한다<br>

### 1.1. 짝수? 홀수?
[ Programmers - 주사위 게임1 ](https://school.programmers.co.kr/learn/courses/30/lessons/181839/solution_groups?language=cpp)<br>
```cpp
int solution(int a, int b) {
  if ((a & 1) && (b & 1)) return a*a + b*b;
  else if ((a & 1) || (b & 1)) return 2 * (a + b);

  return abs(a - b);
}
```
`Bitwise AND를 이용`하여 숫자가 짝수인지 홀수인지 간단히 판단할 수 있다   

홀수라면 `least significant bit( LSB )`가 1이며, 짝수는 0이다   

### 1.2. bit mask
bit mask는 특정 bit를 선택하거나 조작하기 위해 사용되는 binary 값이다   
mask는 1 또는 0으로 구성되며, `bit 1은 관심 있거나 조작하려는 bit`를 나타낸다   
```cpp
unsigned int number = 0b10101010;   // 170 in decimal
unsigned int mask = 0b00001000;     // 8 in decimal( 확인하려는 bit 위치 )
if (number & mask) {
  // TODO
}
```
number의 4번째 bit가 활성화됐다면 if문 조건이 true이다   
```cpp
if (number & mask) {
  number |= mask;       // OR 연산으로 특정 bit 활성화
  number &= ~mask;      // AND와 NOT 연산으로 특정 bit 비활성화
}
cout << bitset<8>(number) << endl;
```
일반적으로 `특정 bit에 접근하여 |( OR ) 또는 ~( NOT )연산을 통해 해당 bit를 활성화하거나 비활성`화한다   

```cpp
if ((number & mask) == mask) {
  // TODO
}
```
`여러 bit가 동시에 활성화됐는지 확인`한다   
#### 응용 : Flag
```cpp
#include <iostream>
using namespace std;

// flag definition
const unsigned int FLAG_READ = 0b0001;
const unsigned int FLAG_WRITE = 0b0010;
const unsigned int FLAG_EXECUTE = 0b0100;
const unsigned int FLAG_DELETE = 0b1000;

int main() {
  unsigned int permissions = 0;

  // set flag( READ, WRITE )
  permissions |= FLAG_READ;
  permissions |= FLAG_WRITE;

  // current permission
  cout << "현재 권한: " << bitset<4>(permissions) << endl;    // 0011

  // check WRITE
  if (permissions & FLAG_WRITE) cout << "WRITE 권한이 설정" << endl;

  // set flag
  permissions |= FLAG_EXECUTE;
  cout << "EXECUTE 권한 설정 후: " << bitset<4>(permissions) << endl; // 0111
  // remove flag
  permissions &= ~FLAG_EXECUTE;
  cout << "EXECUTE 권한 제거 후: " << bitset<4>(permissions) << endl; // 0011

  // check READ & WIRTE
  if ((permissions & (FLAG_READ | FLAG_WIRTE | FLAG_EXECUTE | FLAG_DELETE) == (FLAG_READ | FLAG_EXECUTE))) {
    cout << "READ, WRITE 권한만 설정" << endl;
  }
}
```

#### 응용 : 사용됐는지 여부를 추적
[ Programmers - 옹알이(1) ](https://school.programmers.co.kr/learn/courses/30/lessons/120956)   
```cpp
#include <string>
#include <vector>

using namespace std;

// 허용된 발음 리스트
const vector<string> allowed = {"aya", "ye", "woo", "ma"};

// 주어진 문자열이 발음 리스트로만 구성될 수 있는지 확인하는 함수
bool can_babble(const string& s, int index, int used) {
  // 문자열 끝에 도달하면 성공
  if (index == s.size()) return true;

  // 모든 허용된 발음에 대해 시도
  for (int i = 0; i < allowed.size(); ++i) {
    // 해당 발음이 아직 사용되지 않았는지 확인
    if ( !(used & (1 << i)) ) {
      const string& sub = allowed[i];
      // 현재 인덱스에서 발음이 일치하는지 확인
      if (index + sub.size() <= s.size() && s.substr(index, sub.size()) == sub) {
        // 발음이 사용한 상태로 다음 부분 문자열을 검사
        if ( can_babble(s, index + sub.size(), used | (1 << i)) ) {
          return true;
        }
      }
    }
  }
  return false;   // 모든 발음이 실패하면 불가능
}

int solution(vector<string> babbling) {
  int cnt = 0;
  for (const string& s : babbling) {
    if (can_babble(s, 0, 0)) ++cnt;
  }
  return cnt;
}
```
used 변수는 bitmask로 사용해서, 각 bit는 allowed에 있는 특정 발음이 이미 사용됐는지 나타낸다   
```
bit 0 ( 1 << 0 ): "aya"의 사용 여부
bit 1 ( 1 << 1 ): "ye"의 사용 여부
bit 2 ( 1 << 2 ): "woo"의 사용 여부
bit 3 ( 1 << 3 ): "ma"의 사용 여부
```
즉, used 변수는 4 bit( 0 ~ 3 bit )를 사용하여 각 발음의 사용 여부를 추적한다   

<br><br>

## 2. Bitwise Left-Shift : 2배
```
    00010111 (decimal 23) LEFT-SHIFT
=   00101110 (decimal 46)
```
left-shift를 수행한 뒤, rightmost position에 `새롭게 생기는 bit 값은 0`이다<br>
`기존 값을 2배로 증가`시켜준다<br>
```
1 << i: 1을 왼쪽으로 i번 shift 하는 연산
a << 1: bit a를 왼쪽으로 1번 shift 하는 연산
```

### 2.1. 모든 elements를 2배씩 증가
```cpp
#include <vector>
#include <algorithm>

std::vector<int> vec { 1, 2, 3, 4, 5 };
std::transform(vec.cbegin(), vec.cend(), vec.begin(), [](int ele) {
  ele = ele << 1;
  return ele;
});
```

### 2.2. T시간에 2배씩 증가
```cpp
int solution(int n, int t) { return n << t; }
```

<br><br>

## 3. Bitwise Right-Shift : 2나누기
### 3.1. Adding Binary Strings Using Bitwise Operations Code
```cpp
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

string addBinary(string a, string b) {
  string result = "";
  int carry = 0;

  int i = a.size() - 1;
  int j = b.size() - 1;
  while (i >= 0 || j >= 0 || carry) {
    int sum = carry;
    if (i >= 0) sum += a[i--] - '0';
    if (j >= 0) sum += a[j--] - '0';

    carry = sum >> 1;   // Equal to (sum / 2)
    sum = sum & 1;      // Equal to (sum % 2)
    result += to_string(sum);
  }
  reverse(result.begin(), result.end());
  return result;
}
```
`carry = sum >> 1`은 right shift 연산이며, 이는 2로 나누는 효과가 있다   
`sum = sum & 1`은 AND 연산이며, 0001처럼 1bit 자리에 있는 bit가 0 또는 1인지 판단한다   

<br><br>