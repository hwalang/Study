
# 2차원 배열의 index를 1차원 배열 index로 표현하는 방법
cpp이 OS에게 요청해서 받는 `memory는 내부적으로 1차원 배열 구조`다<br>
computer vision 또는 graphics에서는 2차원 배열을 많이 다룬다<br>

즉, OS는 무조건 1차원 memory를 할당만 하는 역할이고, 이를 개발자가 1, 2차원 중 하나를 선택해서 사용한다<br>

<br>

## 1차원을 2차원으로 바꾸는 과정
[ Row and Column major order ](https://en.wikipedia.org/wiki/Row-_and_column-major_order)<br>
먼저 `c와 cpp은 다차원 배열을 표현할 때, row-major order` 방식이다<br>
![alt text](Images/row_column_major_order.png)<br>

$$
\text{allocated memory} = 
\begin{matrix}
  0 & 1 & 2 & 3 & 4 \\
  \hline
  5 & 6 & 7 & 8 & 9 \\
  \hline
  10 & 11 & 12 & 13 & 14 \\
  \hline
  15 & 16 & 17 & 18 & 19
\end{matrix}
$$

$$
\text{2D matrix} = 
\begin{array}{c|c|c|c|c} 
  (0, 0) & (0, 1) & (0, 2) & (0, 3) & (0, 4) \\
  \hline
  (1, 0) & (1, 1) & (1, 2) & (1, 3) & (1, 4) \\
  \hline
  (2, 0) & (2, 1) & (2, 2) & (2, 3) & (2, 4) \\
  \hline
  (3, 0) & (3, 1) & (3, 2) & (3, 3) & (3, 4)
\end{array}
$$

<br>

(0, 3)의 위치는 1차원 배열에서 3이다<br>
(1, 3)의 위치는 1차원 배열에서 8이다<br>
(2, 3)의 위치는 1차원 배열에서 13이다<br>

따라서 (3, 3) 위치는 1차원 배열에서 18이다<br>
`row에 width를 곱한 후 column을 더하면` 1차원 배열의 각 위치를 알 수 있다<br>

따라서 (i, j)를 1차원 배열로 표현하면<br>

$$
\boldsymbol{index = i * column + j}
$$

## 예시
```
2차원 배열이 3 * 4 크기이고, 위치 (i, j)가 (2, 3)이라면,
이 위치를 1차원 배열의 index로 변환해본다.

index = 2 * 4 + 3 = 2행 * width + 3열
```

