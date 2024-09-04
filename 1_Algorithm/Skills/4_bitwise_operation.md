- [Introduce](#introduce)
    - [특징](#특징)
- [Example](#example)
  - [1. Bitwise AND : 짝수, 홀수 판단](#1-bitwise-and--짝수-홀수-판단)

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
## 1. Bitwise AND : 짝수, 홀수 판단
[ Programmers - 주사위 게임1 ](https://school.programmers.co.kr/learn/courses/30/lessons/181839/solution_groups?language=cpp)<br>
```cpp
int solution(int a, int b) {
  if ((a & 1) && (b & 1)) return a*a + b*b;
  else if ((a & 1) || (b & 1)) return 2 * (a + b);

  return abs(a - b);
}
```
`Bitwise AND를 이용`하여 숫자가 짝수인지 홀수인지 간단히 판단할 수 있다<br>
```
    0101  (decimal 5)
AND 0011  (decimal 3)
---------
    0001
```
`두 operand는 같은 크기의 bit를 가져야 한다`<br>
`두 operand의 bit에 대해 logical AND 연산을 수행`한다<br>
