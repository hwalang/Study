- [vector](#vector)
- [Dot product](#dot-product)
    - [특징](#특징)
    - [사용처](#사용처)
- [Cross product](#cross-product)
    - [특징](#특징-1)

<BR>

# vector
scalar 끼리 연산을 할 때는 dot, cross 연산자에 차이가 없이 곱셈을 의미한다<br>
하지만 vector 끼리 연산은 다르다<br>
![alt text](Images/vector.png)<br>
`vector는 magnitude( 크기 )와 direction( 방향 )을 표현`한다<br>

<br>
<br>

# Dot product
[ Dot product ](https://www.mathsisfun.com/algebra/vectors-dot-product.html)<br>
![alt text](dot_product.png)<br>
$A \cdot B$ <br>

`연산 결과가 scalar`이기 때문에 scalar product라고도 불린다<br>
inner product 또는 projection product라는 용어도 있다<br>

`하나의 vector에 투영( projection )한다는 의미`를 가진다<br>

### 특징
`두 vector가 서로 직각일 때, dot product 결과는 0`이다<br>
`두 vector가 같은 방향을 가리키면 $a \times b$이다<br>

### 사용처
`두 vector가 직각인지 확인할 때 유용`하다<br>
직각 삼각형에서 두 변의 길이를 알면, 피타고라스 정의를 이용해서 나머지 한 변의 길이를 구할 수 있다<br>

![alt text](dot_product_physics.png)<br>
`물리학에서 Work를 판단할 때 사용`한다<br>
$Work = Force \cdot Distance$ <br>
$Work = Force \times Distance \times \cos \theta$ <br>
Work가 Force times Distance인 경우는 물건에 힘을 주는 방향과 이동 방향이 같은 경우이다<br>


<br>
<br>

# Cross product
[ Cross product ](https://www.mathsisfun.com/algebra/vectors-cross-product.html)<br>

![alt text](cross_product.png)<br>
$A \times B$ <br>

Dot product와 달리 `vector 값을 반환`하기 때문에 vector product라는 이름도 있다<br>
`3차원에서 사용`한다<br>

Cross product를 나타내는 `"Right Hand Rule"`도 존재한다<br>

### 특징
`두 vector가 같은 방향 또는 반대 방향을 가리킬 때 길이가 0`이다<br>
`두 vector가 직각일 때 최대 길이`이다<br>