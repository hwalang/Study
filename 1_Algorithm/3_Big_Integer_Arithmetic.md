- [Arbitrary-Precision Arithmetic](#arbitrary-precision-arithmetic)
- [Example](#example)
  - [1. 더하기](#1-더하기)

### Big Integer Arithmetic
매우 큰 정수를 다루는 연산을 말한다.<br>
제목을 보고 내용을 바로 판단할 수 있도록 Big Integer Arightmetic이라 했다<br>
원래 내용은 Arbitrary-Precision Arithmetic이다<br>

<br>
<br>

# Arbitrary-Precision Arithmetic
`정수의 크기에 제한 없이 원하는 만큼의 정밀도로 계산할 수 있는 연산`을 말한다<br>
컴퓨터가 제공하는 Integer TYPE는 한계가 있기 때문에 생겨난 개념이다<br>

<br>
<br>

# Example
예제를 통해 다양한 유형의 Arbitrary-Precision Arithmetic에 대해 알아본다<br>

## 1. 더하기
[ Programmers - 두 수의 합 ](https://school.programmers.co.kr/learn/courses/30/lessons/181846)<BR>
cpp의 long long으로도 표현할 수 없는 숫자를 더하고 싶다.<br>
```cpp
#include <string>
#include <algorithm>

using namespace std;

string solution(string a, string b) {
    string result = "";

    int a_idx = a.length() - 1;     // 마지막 자릿수부터 시작
    int b_idx = b.length() - 1;
    int carry = 0;

    while (a_idx >= 0 || b_idx >= 0 || carry) {
        int digit1 = (a_idx >= 0) ? a[a_idx] - '0' : 0;
        int digit2 = (b_idx >= 0) ? b[b_idx] - '0' : 0;
        int sum = digit1 + digit2 + carry;
        result += to_string(sum % 10);
        carry = sum / 10;
        a_idx--;
        b_idx--;
    }
    
    reverse(result.begin(), result.end());
    
    return result;
}
```
컴퓨터 구조에서 `cpu의 덧셈 연산을 이용한 방법`이다<BR>

각 문자열의 마지막 자리를 더하면 최대 두 자릿수의 정수가 나온다<BR>
여기서 일의 자릿수는 result에 저장하고, 십의 자릿수는 carry에 담아서 다음 연산에 이용한다<br>
각 문자열의 순회가 끝났으면 carry가 0인지 확인하여 자릿수를 증가시킬지 결정한다<br>
문자열의 마지막 자릿수에서 첫 번째 자릿수로 이동하며 덧셈을 수행했기 때문에 마지막에 result 문자열의 순서를 뒤집는다<br>