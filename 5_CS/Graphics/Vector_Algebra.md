- [Vectors](#vectors)
  - [1. Vectors and Coordinate Systems](#1-vectors-and-coordinate-systems)
  - [2. Left-Handed vs Right-Handed Coordinate Systems](#2-left-handed-vs-right-handed-coordinate-systems)
  - [3. Basic Vector Operations](#3-basic-vector-operations)

vector를 기하학적으로, 수치적으로 표현되는 방식을 알아본다.   
vector에 대한 operations와 이에 대한 기하학적 응용을 알아본다.   
vector functions와 DirectXMath library에 익숙해진다.   

# Vectors
**vector는 magnitude( 크기 )와 direction( 방향 )을 표현**한다   

<div>
<img src="Images/VectorAlgebra/vector.png" width=45% />
<img src="Images/VectorAlgebra/VectorsDrawnOn2DPlane.png" width=45% />
</div>

이러한 특성을 기하학적으로 표현한 것이 위의 directed line segment이다.   

**vector가 가진 properties( magnitude, direction )는 location을 이동해도 변하지 않기 때문에 vector를 그리는 location은 중요하지 않다**. 때문에 vector를 평행 이동해도 의미는 같다.   
따라서 두 vector가 같음을 판단하기 위해서는 magnitude와 direction이 같아야 한다. 기하학적으로 두 directed line segment가 완전히 겹치면 두 vector가 동일함을 나타낸다.   

## 1. Vectors and Coordinate Systems
**컴퓨터는 vector의 기하학적 의미를 모르기 때문에 이를 수치적으로 표현하는 방법이 필요**하다.   

<div>
<img src="Images/VectorAlgebra/displacement_position_vector.png" width=50% />
</div>

모든 vector의 tail을 3D coordinate systems의 origin( 원점 )으로 평행 이동한다. 그리고 나서 vector의 head의 corrdinates( 좌표 )를 지정함으로써 각 vector를 식별할 수 있다. 위 그림에서 $\mathbf{p}$는 (x, y, z)로 표현되며, **프로그램은 3개의 `float`를 보고 vector를 표현**할 수 있다.   

<div>
<img src="Images/VectorAlgebra/vector_and_coordinates.png" width=70% />
</div>

하나의 **vector는 frame에 상대적인 좌표를 가진다**.   
표현 방식이 다를 뿐이지 directed line segment에 있는 direction과 magnitude는 변하지 않는다. 이는 Celsius 또는 Fahrenheit에 따라 물의 끓는점에 대한 표현이 다른 것과 비슷하다. 물리적인 물의 끓는 점은 변하지 않지만 표현 방식만 다를 뿐이다.   

3D Computer Graphic에서 **하나 이상의 frame of reference를 사용**하며, **서로 다른 frame을 옮겨다니면서 vector를 표현할 줄 알아야 한다**.   

## 2. Left-Handed vs Right-Handed Coordinate Systems
**Direct3D는 Left-Handed Cooridnate System을 사용**한다.   

<div>
<img src="Images/VectorAlgebra/Left_Right_Handed.png" width=60% />
</div>

Left-Handed Coordinates는 양의 z축이 monitor 안을 향한다. 반면에 Right-Handed Coordinates는 monitor 바깥을 향한다.   

## 3. Basic Vector Operations
벡터의 scalar multiplication, addition, substraction operations에 대해 알아본다.   

![alt text](Images/VectorAlgebra/VectorOperations1.png)   

**a 그림은 두 벡터의 scalar multiplication의 기하학적 의미를 표현**한다.   
$-\frac{1}{2}\mathbf{v}$는 $\mathbf{v}$에 대해 **반대 방향**을 가지고 **길이가 $\frac{1}{2}$이다**.   
즉, **음수 벡터**는 원래 벡터 방향의 **flipping**이고, **scalar multiplication**은 벡터의 길이를 **scaling**한 것이다.   

**b 그림은 두 벡터의 addition의 기하학적 의미를 표현**한다.   
벡터의 덧셈은 $\mathbf{u}$의 tail이 $\mathbf{v}$의 head에 위치하도록 평행이동( 반대도 똑같다 )한다.   
그러면 $\mathbf{v}$의 tail에서 시작하여 평행 이동된 $\mathbf{u}$의 head에서 끝나는 벡터를 얻는다.   

![alt text](Images/VectorAlgebra/VectorOperations2.png)   

이러한 덧셈 규칙( tail과 head 위치 )을 적용하여 두 Forces( vector )를 더해본다.   
**같은 방향으로 향하는 두 Forces를 더하면 더 강한 Force**를 얻지만, **반대 방향으로 향하는 두 Forces를 더하면 더 약한 Force**를 얻는다.   

**c 그림은 두 벡터의 뺄셈의 기하학적 의미를 표현**한다.   
**$\mathbf{v} - \mathbf{u}$는 $\mathbf{u}$의 head에서 $\mathbf{v}$의 head로 향하는 vector**를 반환한다.   
만약 vector를 point로 생각하면, **point(u)에서 point(v)로 향하는 vector를 반환하고, length는 point(u)와 point(v)의 distance**를 나타낸다.   