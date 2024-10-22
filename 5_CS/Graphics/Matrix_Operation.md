- [Matrix](#matrix)
  - [1. Vector로 Matrix를 표현하는 방법](#1-vector로-matrix를-표현하는-방법)
    - [1.1. 표기법: row vector, column vector](#11-표기법-row-vector-column-vector)
    - [1.2. 표기법: Matrix to row vector](#12-표기법-matrix-to-row-vector)
    - [1.3. 표기법: Matrix to column vector](#13-표기법-matrix-to-column-vector)
  - [2. Matrix Multiplication](#2-matrix-multiplication)
    - [2.1. Matrix Multiplication : Formula( Math Expression )](#21-matrix-multiplication--formula-math-expression-)
    - [2.2. Matrix Multiplication : Properties](#22-matrix-multiplication--properties)
    - [2.2. Vector-Matrix Multiplication](#22-vector-matrix-multiplication)
      - [Linear Combination](#linear-combination)
  - [3. Transpose( 전치 행렬 )](#3-transpose-전치-행렬-)

<br>

#### 핵심 요약
```cpp
u` = uT     // DirectXMath는 Row-major Matrix 사용
u` = Tu     // HLSL은 Column-major Matrix 사용

u : vector 또는 point
T : Transformation[ Translation, Rotation, Scaling ] Matrix
```
Transformation을 행렬로 표현   
즉, 어떠한 vector나 point를 변환하고 싶으면 Matrix를 곱한다   

<br><br>

# Matrix
matrix는 `vector를 여러 개 묶은 것` 또는 `2차원 배열 형태`를 가진다   
![alt text](Images/Matrix/row_column_major_order.png)   
2차원 배열 형태이므로 row-major order로 vector를 묶었거나 column-major order로 vector를 묶은 것으로 판단할 수 있다( [m_by_n_matrix.md](/2_Math/matrix/m_by_n_matrix.md/#1-row-col-용어) )   

## 1. Vector로 Matrix를 표현하는 방법

### 1.1. 표기법: row vector, column vector
$$\mathbf{u} = \begin{bmatrix}
  u_1, u_2, u_3
\end{bmatrix} \space \mathbf{v} = \begin{bmatrix}
  1 \\
  2 \\
  3 \\
  4
\end{bmatrix}$$

위 수식은 벡터 u, v를 행렬로 나타내는 방법이다   
왼쪽 수식은 `row 하나로 벡터를 표현( row vector )`하고, 오른쪽 수식은 `column 하나로 벡터를 표현( column vector )`한다   
DirectX는 row vector를 선호한다   

### 1.2. 표기법: Matrix to row vector
*( Asterisk, Star )   

$$\begin{bmatrix}
  A_{11} & A_{12} & A_{13} \\
  A_{21} & A_{22} & A_{23} \\
  A_{31} & A_{32} & A_{33}
\end{bmatrix} = \begin{bmatrix}
  \leftarrow \mathbf{A_{1,*}} \rightarrow \\
  \leftarrow \mathbf{A_{2,*}} \rightarrow \\
  \leftarrow \mathbf{A_{3,*}} \rightarrow
\end{bmatrix}$$

$$\mathbf{A_{1,*}} = \begin{bmatrix}
  A_{11}, A_{12}, A_{13}
\end{bmatrix} \\ \mathbf{A_{2,*}} = \begin{bmatrix}
  A_{21}, A_{22}, A_{23}
\end{bmatrix} \\ \mathbf{A_{3,*}} = \begin{bmatrix}
  A_{31}, A_{32}, A_{33}
\end{bmatrix}$$

하나의 matrix를 `여러 개의 row vector가 모여있는 것`으로 볼 수 있다   

### 1.3. 표기법: Matrix to column vector

$$\begin{bmatrix}
  A_{11} & A_{12} & A_{13} \\
  A_{21} & A_{22} & A_{23} \\
  A_{31} & A_{32} & A_{33}
\end{bmatrix} = \begin{bmatrix}
  \uparrow & \uparrow & \uparrow \\
  \mathbf{A_{*, 1}}, & \mathbf{A_{*, 2}}, & \mathbf{A_{*, 3}} \\
  \downarrow & \downarrow & \downarrow
\end{bmatrix}$$

$$\mathbf{A_{*, 1}} = \begin{bmatrix}
  A_{11} \\ A_{12} \\ A_{13}
\end{bmatrix} \quad \mathbf{A_{*, 2}} = \begin{bmatrix}
  A_{21} \\ A_{22} \\ A_{23}
\end{bmatrix} \quad \mathbf{A_{*, 3}} = \begin{bmatrix}
  A_{31} \\ A_{32} \\ A_{33}
\end{bmatrix}$$

하나의 matrix를 `여러 개의 column vector가 모여있는 것`으로 볼 수 있다   

<br>

## 2. Matrix Multiplication
### 2.1. Matrix Multiplication : Formula( Math Expression )
고등학생 때는 `a11*b11 + a12*b12 + a13*b13`처럼 행렬을 곱했는데, 이는 `Dot product와 같은 방식`이다   

$$
A = \begin{bmatrix} 1 & 2 & 3 \\ 4 & 5 & 6 \end{bmatrix} \quad 
B = \begin{bmatrix} 2 & 1 \\ 0 & -1 \\ -1 & 2 \end{bmatrix}
\\
AB = \begin{Bmatrix}
  (1, 2, 3) \cdot (2, 0, -1) & (1, 2, 3) \cdot (1, -1, 2) \\
  (4, 5, 6) \cdot (2, 0, -1) & (4, 5, 6) \cdot (1, -1, 2)
\end{Bmatrix}
\\
= \begin{bmatrix}
  -1 & 5 \\ 2 & 11
\end{bmatrix}
$$

따라서 Graphics에서는 A( 2 * 3 matrix )와 B( 3 * 2 matrix )를 곱할 때, Dot product를 이용한다   

$$
C_{ij} = A_{i, *} \cdot B_{*, j}
$$

이를 수식으로 정리하면, `A의 row vector와 B의 column vector를 Dot product한 결과가 결과 행렬의 한 element( C-ij )를 결정`한다   
또한 `row vector와 column vector의 elements 갯수가 같아야 곱할 수 있다`   

### 2.2. Matrix Multiplication : Properties

$$1. \space AB \neq BA$$

일반적으로 Matrix Multiplication은 곱하는 순서에 따라 결과가 달라지며, 이는 3D space에서 회전을 적용할 때 사용되는 개념이다   

$$2. \space (AB)C = A(BC)$$

### 2.2. Vector-Matrix Multiplication

$$
\mathbf{uA} = \begin{bmatrix} x, y, z \end{bmatrix} \begin{bmatrix}
  \uparrow & \uparrow & \uparrow \\
  \mathbf{A_{*, 1}}, & \mathbf{A_{*, 2}}, & \mathbf{A_{*, 3}} \\
  \downarrow & \downarrow & \downarrow
\end{bmatrix}
$$

$$
\mathbf{uA} = \begin{bmatrix} 
  \mathbf{u \cdot A_{*, 1}} & \mathbf{u \cdot A_{*, 2}} & \mathbf{u \cdot A_{*, 3}}
\end{bmatrix}
\\
= x\mathbf{A_{1, *}} + y\mathbf{A_{2, *}} + z\mathbf{A_{3, *}}
$$

vector와 matrix의 multiplication의 결과는 vector이다   
`vector를 matrix를 이용해서 Transformation한다는 개념`이기 때문이다   

uA는 vector의 elements 수와 matrix의 row( line )의 수가 같아야 곱할 수 있다   
또한 uA의 내부를 전개하고 Matrix의 Property를 이용하면 vector-matrix multiplication을 scalar * row-vector 형태로 정리할 수 있다   

<hr>

#### Linear Combination

$$
\mathbf{uA} = x\mathbf{A_{1, *}} + y\mathbf{A_{2, *}} + z\mathbf{A_{3, *}}
$$

vector-matrix multiplication 형식을 Linear Combination( 선형 결합 )이라 한다   
<hr>

$$
\mathbf{Au} = \begin{bmatrix}
  \leftarrow & \mathbf{A_{*, 1}} & \rightarrow \\ 
  \leftarrow & \mathbf{A_{*, 2}} & \rightarrow \\ 
  \leftarrow & \mathbf{A_{*, 3}} & \rightarrow
\end{bmatrix} 
\begin{bmatrix} x \\  y \\ z \end{bmatrix}
$$

uA를 Au로 표현할 수 있다   
이때 A는 column-vector가 아니라 row-vector이며, u는 row-vector가 아닌 column-vector로 나타낸다   

<br>

## 3. Transpose( 전치 행렬 )
