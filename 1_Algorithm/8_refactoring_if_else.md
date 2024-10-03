- [Refactoring Code to Eliminate If-Else Statements](#refactoring-code-to-eliminate-if-else-statements)
  - [1. Adding Binary Strings using Bitwise Operations](#1-adding-binary-strings-using-bitwise-operations)
    - [Adding Binary Strings Using Bitwise Operations Code](#adding-binary-strings-using-bitwise-operations-code)

<br><br>

# Refactoring Code to Eliminate If-Else Statements

refactoring을 통해 if-else 문을 제거하는 사례를 소개한다   

<br>

## 1. Adding Binary Strings using Bitwise Operations
[Programmers - 이진수 더하기](https://school.programmers.co.kr/learn/courses/30/lessons/120885)   
binary 덧셈 로직을 간결하게 처리한다   
```cpp
// params : string bin1, string bin2
// return : string
// while loop
int sum = operand1 + operand2 + carry;
if (sum == 3) {
  stk_result.push('1');
  carry = 1;
}
else if (sum == 2) {
  stk_result.push('0');
  carry = 1;
}
else if (sum == 1) {
  stk_result.push('1');
  carry = 0;
}
else {    // sum == 0
  stk_result.push('0');
  carry = 0;
}
```
문자열로 주어진 binary 숫자를 bit operation을 통해 더하는 코드의 일부분이다   
반복문에서 bin1과 bin2의 binary 문자를 더하는 방식으로 구현했다   
해당 코드의 if-else 문을 제거하면서 원래 기능을 유지하도록 refactoring 해본다   
```cpp
int sum = operand1 + operand2 + carry;
carry = sum / 2;
char bit = (sum % 2) + '0';
stk_result.push(bit);
```
carry가 sum이 2 또는 3인 경우 1을 가지기 때문에 sum / 2를 수행   
binary는 0 또는 1을 가지기 때문에 sum % 2로 0 또는 1값을 추출하고, 이를 + '0'으로 문자로 변환   

### Adding Binary Strings Using Bitwise Operations Code
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