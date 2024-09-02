
# std::log2, std::log2f, std::log2l
```cpp
#include <cmath>

/*floating point type*/ log2(/*floating point type*/ num);
float log2f(float num);
long double log2l(long double num);

templace <class Integer>
double log2(Integer num);
```
`num에 대한 binary( base-2 ) logarithm를 계산`한다<br>
return type이 double인 경우, parameter로 모든 Interger Type을 받을 수 있다<br>

<br>
<br>

# return type
기본적으로 $log_2{num}$ 값을 반환한다<br>

만약 num이 0보다 작으면 Domain Error가 발생하며, 이는 NaN을 반환한다<br>
만약 num이 0이라면 Pole Error가 발생하며, 이는 HUGE_VAL( floating point type의 overflow )을 반환한다<br>

<br>
<br>

# Example
[ Programmers - 배열의 길이를 2의 거듭제곱으로 만들기 ](https://school.programmers.co.kr/learn/courses/30/lessons/181857)<br>
```cpp
#include <string>
#include <vector>
#include <cmath>

using namespace std;

// num이 2의 거듭제곱이라면 true
bool two_power(int num) {
  return floor(log2(num)) == log2(num);
}

vector<int> solution(vector<int> arr) {
    while (!two_power(arr.size())) {
        arr.emplace_back(0);
    }
    return arr;
}
```
vector의 크기가 2의 거듭제곱인지 확인하는 방법으로 사용했다<br>