- [Arithmetic Sequence( 등차수열, 또는 Arithmetic Progression\[AP\] )](#arithmetic-sequence-등차수열-또는-arithmetic-progressionap-)
  - [1. 개념](#1-개념)
  - [2. 등차수열 구하기](#2-등차수열-구하기)
  - [3. 공차( common difference ) 구하기](#3-공차-common-difference--구하기)
  - [4. 등차수열의 합](#4-등차수열의-합)
- [활용](#활용)
  - [1. 연속된 수의 합을 이용한 **첫 번째 항 구하기**](#1-연속된-수의-합을-이용한-첫-번째-항-구하기)

<br><br>

# Arithmetic Sequence( 등차수열, 또는 Arithmetic Progression[AP] )

## 1. 개념
연속하는 두 항의 차이가 모두 일정한 수열을 뜻한다.   
두 항의 차이는 이 수열의 모든 연속하는 두 항들에 대해서 <b>공</b>통으로 나타나는 <b>차</b>이므로, <b>공차( common difference )</b>라고 한다. </br>

## 2. 등차수열 구하기
`arithmetic sequence의 n번째 항의 숫자를 구하는 방법`이고, 이를 `일반항`으로 나타낸다. </br>
일반항이란, arithmetic sequence의 임의의 n 번째 항을 n에 관한 식으로 나타낸 것을 뜻한다. </br>
```
수열 A = {5, 7, 9, 11, ... }

공차 = 2
초항 = 5

n에 1을 넣었을 때 5가 나와야 한다.
공차 * n으로 2n이고, 여기에 1을 넣은 후 5를 만들기 위해 3을 더한다.
즉, 2n + 3
위 식이 수열 A의 일반항이다.
```

x번째 항을 $a_{x}$, 공차가 d인 arithmetic sequence의 일반항은

$$a_{n} = a_{x} + (n - x)d$$

만약 x = 1이라면 

$$a_n = a_1 + (n - 1)d$$


## 3. 공차( common difference ) 구하기
$$ d = a(n + 1) - a_n ( n >= 2 ) $$

$$ \frac{a_x - a_y}{x - y} $$

위 두가지 식으로 common difference를 구할 수 있다.</br>
```
[ 1, 3, 5, 7, 9, ... ]
- 첫째항: 1
- 공차: 2

(9 - 5 / 5 - 3) = (4 / 2) = 2
```

## 4. 등차수열의 합
$$S = \frac{n}{2} \times [ 2a + (n - 1)d] \textnormal{ 또는 } S = \frac{n}{2} \times (a + l)$$
```
n: 항의 개수
a: 첫 번째 항
l: 마지막 항( a + (n - 1)d )
d: 공차
```


<br><br>

# 활용
## 1. 연속된 수의 합을 이용한 **첫 번째 항 구하기**
[ Programmers - 연속된 수의 합 ](https://school.programmers.co.kr/learn/courses/30/lessons/120923)   
`연속된 num개의 정수의 합이 total`이어야 한다   
공차( d )는 1이며, 첫 번째 정수를 x라고 하면, 마지막 정수는 x + (n - 1)이다   

$$total = \frac{n}{2} \times (2x + n - 1)$$

등차수열의 합 공식에 의해 total을 구할 수 있는데, 이를 이용해서 `첫 번째 항을 구할 수 있다`   

$$x = \frac{total - \frac{n \times (n - 1)}{2}}{n}$$

```
// num = 3, total = 12
x = (12 - (3 * (3 - 1)/2) / 3) = 3

=> 3 + 4 + 5 = 12
```
```cpp
#include <vector>

using namespace std;

vector<int> solution(int num, int total) {
  vector<int> result;

  // 첫 번째 항
  int x = (total - (num * (num - 1) / 2)) / num;

  // x부터 x + num - 1까지의 연속된 정수를 배열에 추가
  for (int i = 0; i < num; ++i) {
    result.emplace_back(x + i);
  }
  return result;
}
```