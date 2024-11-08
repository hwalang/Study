- [Manhattan Distance](#manhattan-distance)
  - [1. 상하좌우 이동으로 제한](#1-상하좌우-이동으로-제한)
  - [2. MD : 공식](#2-md--공식)
- [Euclidean Distance( 유클리드 거리 )](#euclidean-distance-유클리드-거리-)
  - [1. UD : 공식](#1-ud--공식)

<br><br>

# Manhattan Distance
`matrix 기반의 구조에서 두 점 사이의 거리를 측정할 때 사용되는 거리 계산 방법`이다   

## 1. 상하좌우 이동으로 제한
`상하좌우로만 이동`할 수 있으며 `한 번에 한 칸씩 이동`하는 경우, 두 점 사이의 거리를 상하좌우 이동의 합으로 표현할 수 있다   
```
1 2 3
4 5 6
```
1과 6사이의 거리는 1이 오른쪽으로 두 칸, 아래로 한 칸 이동하기 때문에 총 거리가 3이다   

이처럼 대각선으로 이동할 수 없으면 두 elements 사이의 실제 이동 거리는 `가로 이동 거리 + 세로 이동 거리`로 계산한다   

## 2. MD : 공식
```
(x1, y1)과 (x2, y2) 사이의 거리: |x1 - x2| + |y1 - y2|
```

<br><br>

# Euclidean Distance( 유클리드 거리 )
Manhattan Distance와 다르게 `대각선 이동이 가능한 경우`, 두 점사이의 거리를 계산하는 방법이다   
두 점 사이의 "직선 거리"를 나타내기 때문이다   

## 1. UD : 공식
2차원, 3차원 공간에서의 공식은 같다   

$$
\text{(x1, y1)과 (x2, y2) 사이의 거리 = } \sqrt{(x1 - x2)^2} + \sqrt{(y1 - y2)^2}
$$