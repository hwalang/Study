- [std::ceil](#stdceil)
- [Example](#example)
  - [basic](#basic)
  - [피자 나눠 먹기 3](#피자-나눠-먹기-3)

<br>

[ cppreference - std::ceil, std::ceilf, std::ceill ](https://en.cppreference.com/w/cpp/numeric/math/ceil)<br>
# std::ceil
```cpp
#include <cmath>

float ceil(float num);
double ceil(double num);
long double ceil(long double num);
```
`num 보다 작지 않은 가장 작은 정수 값을 계산`한다<br>
symbol: $\lceil num \rceil$<br>

```cpp
std::ceil(num) == std::ceil(static_cast<double>(num))
```
`모든 Integer type에 대해 double로 처리`한다<br>

<br><br>

# Example
## basic
```cpp
#include <cmath>
#include <iostream>

int main()
{
  std::cout << std::fixed
            << "ceil(2.4) = " << std::ceil(2.4) << "\n"     // 3.0
            << "ceil(-2.4) = " << std::ceil(-2.4) << "\n";  // -2.0
}
```

## 피자 나눠 먹기 3
[ Programmers - 피자 나눠 먹기 3 ](https://school.programmers.co.kr/learn/courses/30/lessons/120816)<br>
피자 한 판을 slice 조각으로 잘라주는 가게가 있다<br>
해당 가게에서 n 명의 사람이 최소 한 조각 이상 먹으려면 피자를 최소 몇 판 시켜야 하나?<br>
```cpp
#include <cmath>
using namespace std;

int solution(int slice, int n) {
  return ceil(n * 1.0f / slice);
}
```
ceil()를 이용하면 최소 1판을 보장하며, 사람 수와 조각 수의 비율에 따라 몇 판인지도 판단할 수 있다<br>