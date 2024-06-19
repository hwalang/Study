# m by n matrix
행렬의 헷갈리는 개념을 정확히 짚고 넘어간다.
</br>2차원 배열을 for문을 이용해서 탐색할 때, row와 col 변수를 사용하면서 발생하는 헷갈림을 잡는다.

## row( 행 )와 column( 열 )

row는 `가로줄`, column은 `세로줄`을 의미한다.
</br>
![alt text](images/m_by_n_matrix.png)
</br>

따라서 m * n 행렬의 m과 n은 
</br>m은 `row의 크기`
</br>n은 `column의 크기`

## for문 순회
데이터가 row-major 방식으로 저장되는 경우( c/c++ )에는 row-major order가 효율적이다.

```cpp
// row-major order
for (int row = 0; row < m; ++row) {
  for (int col = 0; col < n; ++col) {
    arr[row][col];
  }
}
```

row를 행 전체라고 생각하지 않는다.
</br>row는 행에 존재하는 하나의 원소를 뜻한다.
</br>예로 들면, arr = {1, 2, 3}; 중에서 arr 자체가 아닌 1, 2, 3을 의미한다.

```cpp
// column-major order
for (int col = 0; col < m; ++col) {
  for (int row = 0; row < n; ++row) {
    arr[row][col];
  }
}
```