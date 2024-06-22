# prefix sum( 구간 합 )
prefix sum은 배열의 부분 합을 빠르게 찾을 수 있는 방법이다.
</br>prefix sum 배열을 채우면 특정 구간의 합을 O(1) 시간에 구할 수 있다.

# 원리
0-based indexing을 사용할 때의 원리
- `prefix[i]`는 grid의 첫 번째 원소부터 i번째 원소까지의 합을 저장한다.
- `prefix[i][j]`는 (0, 0) ~ (i, j)까지의 부분 합을 저장한다.

특정 구간의 합을 계산할 때마다 모든 요소를 다시 더하지 않아도 된다.

## 1차원 배열
```cpp
prefix[0] = grid[0];
prefix[1] = grid[0] + grid[1];
prefix[2] = grid[0] + grid[1] + grid[2];

// 점화식
prefix[i] = prefix[i - 1] + grid[i];

// grid의 [i, j] 구간의 합
sum[i, j] = prefix[j] - prefix[i - 1];  // i > 0인 경우
sum[i, j] = prefix[j];                  // i == 0인 경우
```
[i, j] 구간의 합은 `j까지의 구간합 - (i-1)까지의 구간합`이다. 

( i - 1 )인 이유는 i부터 j까지의 합을 구하므로 grid[i] 값은 필요하기 때문이다.

## 2차원 배열
임의의 직사각형 영역의 합을 효율적으로 구할 수 있다.

```cpp
// 기준
grid = [
  [6, 5, 4, -3],
  [3, -4, -4, 14],
  [6, 1, -3, 15],
  [3, -5, 1, 16]
]

// 계산 과정( 직사각형 모양 )
prefix[0][0] = arr[0][0] = 6
prefix[0][1] = arr[0][0] + arr[0][1] = 6 + 5 = 11

prefix[1][0] = arr[0][0] + arr[1][0] = 6 + 3 = 9
prefix[1][1] = arr[0][0] + arr[0][1] + arr[1][0] + arr[1][1] = 6 + 5 + 3 - 4 = 10

prefix[2][0] = arr[0][0] + arr[1][0] + arr[2][0] = 6 + 3 + 6 = 15
prefix[2][1] = arr[0][0] + arr[0][1] + arr[1][0] + arr[1][1] + arr[2][0] + arr[2][1] = 6 + 5 + 3 - 4 + 6 + 1 = 17


// 결과
prefix = [
  [6, 11, 15, 12],
  [9, 10, 10, 21],
  [15, 17, 14, 40],
  [18, 15, 13, 54]
]
```
1차원 배열의 구간 합과 다르게 2차원 배열은 직사각형 영역을 생각해야 이해하기 쉽다.

```cpp
// 점화식
prefix[i][j] = grid[i][j] + prefix[i - 1][j] + prefix[i][j - 1] + prefix[i - 1][j - 1];

// 구간 합 계산[ (1, 1) ~ (2, 3) ]
sum((y1, x1), (y2, x2)) = prefix[y2][x2] - prefix[y1 - 1][x2] - prefix[y2][x1 - 1] + prefix[y1 - 1][x1 - 1];

prefix[2][3] - prefix[0][3] - prefix[2][0] + prefix[0][0]
```
`prefix[i][j]`는 (0, 0)에서 (i, j)까지의 구간 합을 저장한다.
</br>임의의 직사각형 영역의 합을 효율적으로 구할 수 있다.

### prefix 연산
```cpp
// prefix 채우기
void InitPrefix(const vector<vector<int>>& grid, const vector<vector<int>>& prefix)
{
  int n = grid.size();
  int m = grid[0].size();
  prefix.assign(n, vector<int>(m, 0));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      prefix[i][j] = grid[i][j];
      if (i > 0) prefix[i][j] += prefix[i-1][j];
      if (j > 0) prefix[i][j] += prefix[i][j-1];
      if (i > 0 && j > 0) prefix[i][j] -= prefix[i-1][j-1];
    }
  }
}
```

(y, x)까지의 구간 합을 구하기 위해 prefix[y][x]를 채운다.
</br>`(y, x - 1)까지의 구간합 + (y - 1, x)까지의 구간합 - (y - 1, x - 1)까지의 구간합`이 prefix[y][x]값이다.
</br>(y - 1, x - 1)까지의 구간합이 두 번 더해지기 때문에 한 번 빼야한다.

```cpp
// prefix[y2][x2] 구하기
int GetSum(const vector<vector<int>>& prefix, int y1, int x1, int y2, int x2)
{
	int sum = prefix[y2][x2];
	if (y1 > 0) sum -= prefix[y1 - 1][x2];
	if (x1 > 0) sum -= prefix[y2][x1 - 1];
	if (y1 > 0 && x1 > 0) sum += prefix[y1 - 1][x1 - 1];
	return sum;
}
```

(y1, x1) ~ (y2, x2) 사이의 구간 합을 구한다.