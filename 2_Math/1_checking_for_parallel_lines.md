- [Checking for parallel lines](#checking-for-parallel-lines)
  - [1. Slope Comparsion( 기울기 비교 )](#1-slope-comparsion-기울기-비교-)
  - [2. Vector Method](#2-vector-method)
  - [3. Matrix Method](#3-matrix-method)

<br><br>

# Checking for parallel lines
네 개의 점이 주어졌을 때, 두 개씩 점을 연결하여 두 직선을 만들고, 이 두 직선이 평행한지 판단하는 방법을 알아본다   

## 1. Slope Comparsion( 기울기 비교 )
두 직선의 기울기를 계산하여 비교한 뒤, 기울기가 같다면 두 직선은 평행하다   

$$\textnormal{직선 AB의 기울기: }m_{AB} = \frac{y_2 - y_1}{x_2 - x_1}$$
$$\textnormal{직선 CD의 기울기: }m_{CD} = \frac{y_4 - y_3}{x_4 - x_3}$$

문제는 `분모가 0인 경우`가 존재할 수 있다   
이를 해결하기 위해 `교차 곱을 이용하여 비교`한다   
$$(y_2 - y_1) \times (x_4 - x_3) == (y_4 - y_3) \times (x_2 - x_1)$$

## 2. Vector Method
두 직선의 방향 벡터를 구한 후, 이 벡터들이 scalar 배수 관계에 있는지 확인한다   
scalar 배수 관계라면 두 직선은 평행하다   


## 3. Matrix Method
두 직선의 방향 벡터로 행렬을 구성하고, 그 행렬의 행렬식을 계산한다   
행렬식이 0이면, 두 직선은 평행하다   
