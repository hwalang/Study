- [Introduce](#introduce)
- [Checking the Lower/Upper Triangular Matrix](#checking-the-lowerupper-triangular-matrix)

<br>

# Introduce
Problem Solving을 하던 중 생각하기 어려운 방법으로 matrix를 사용하여 문제를 푸는 방법을 기록한다.<br>

<br>

# Checking the Lower/Upper Triangular Matrix
`행렬의 대각선 아래쪽 또는 위쪽만 검사하는 방법`을 알아본다<br>

[ Programmers - 특별한 이차원 배열 2 ](https://school.programmers.co.kr/learn/courses/30/lessons/181831)<br>
`[r][c] == [c][r]`에 대해 조건을 제시한 문제<br>
```cpp
#include <vector>
using namespace std;

int solution(vector<vector<int>> arr)
{
  for (int r = 0; r < arr.size(); ++r) {
    for (int c = 0; c < r; ++c) {
      if (arr[r][c] != [c][r]) return 0;
    }
  }
  return 1;
}
```
![alt text](Images/triangular_matrix.png)<br>
위 이미지는 어떤 면을 계산하는지 보여주는 용도이다<br>
중복 연산을 피하기 위해서 2차원 배열 대각선을 기준으로 왼편( lower triangular matrix )에 대해서만 연산을 수행한다<br>
