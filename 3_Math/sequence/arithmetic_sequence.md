# Arithmetic Sequence( 등차수열, 또는 Arithmetic Progression[AP] )

## 개념
연속하는 두 항의 차이가 모두 일정한 수열을 뜻한다. </br>
두 항의 차이는 이 수열의 모든 연속하는 두 항들에 대해서 <b>공</b>통으로 나타나는 <b>차</b>이므로, <b>공차( common difference )</b>라고 한다. </br>

## 등차수열 구하기
arithmetic sequence의 n번째 항의 숫자를 구하는 방법이고, 이를 일반항으로 나타낸다. </br>
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


## 공차 구하기
$$ d = a(n + 1) - a_n ( n >= 2 ) $$
$$ \frac{a_x - a_y}{x - y} $$
위 두가지 식으로 common difference를 구할 수 있다.
