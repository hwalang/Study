- [Geometric Sequence( 등비수열 )](#geometric-sequence-등비수열-)
  - [1. 개념](#1-개념)
  - [2. Geometric Sequence의 일반항](#2-geometric-sequence의-일반항)
  - [3. Geometric Sequence Properties](#3-geometric-sequence-properties)
    - [3.1. common ratio 증가 또는 감소 수열](#31-common-ratio-증가-또는-감소-수열)
    - [3.2. common ratio의 부호](#32-common-ratio의-부호)
  - [4. Geometric Sequence Sum](#4-geometric-sequence-sum)
    - [4.1. 유한 등비수열의 합](#41-유한-등비수열의-합)
    - [4.2. 무한 등비수열의 합](#42-무한-등비수열의-합)
- [활용](#활용)
  - [1. 등차 또는 등비수열 구분](#1-등차-또는-등비수열-구분)
    - [항의 개수 확인](#항의-개수-확인)
    - [common difference 확인](#common-difference-확인)
    - [common ratio 확인](#common-ratio-확인)

<br><br>

# Geometric Sequence( 등비수열 )
## 1. 개념
Geometric Sequence는 `연속하는 두 항의 비율이 일정한 수열`을 말한다   

## 2. Geometric Sequence의 일반항
등비수열의 n번째 항은 다음과 같이 계산한다   
$$a_n = a \times r^{n - 1}$$
```
첫 번째 항( initial term )이 2이고, common ratio가 3인 geometric sequence의 첫 5개 항은 다음과 같다
[ 2, 6, 18, 54, 162 ]
```

## 3. Geometric Sequence Properties
### 3.1. common ratio 증가 또는 감소 수열
```
r > 1, 항이 지수적으로 증가하는 수열

0 < r < 1, 항이 지수적으로 감소하는 수열
```
common ratio에 따라 수열이 기하급수적으로 증가하거나 감소하며, 이를 발산 또는 수렴이라 말한다   

### 3.2. common ratio의 부호
```
양수: 수열의 항들이 모두 같은 부호
음수: 수열의 항들이 부호가 번갈아가며 나타남
```

## 4. Geometric Sequence Sum
### 4.1. 유한 등비수열의 합
$$S_n = a \times \frac{1 - r^n}{1 - r} (r \neq 1)$$
$$S_n = a \times n (r = 1)$$
```
initial term이 2이고, common ratio가 3인 geometric sequence의 첫 5개 항은 다음과 같다
[ 2, 6, 18, 54, 162 ]

이들의 합은 242
```

### 4.2. 무한 등비수열의 합
$$\textnormal{if |r| < 1, } S = \frac{a}{1 - r}$$
`위 조건을 만족하지 않으면, 무한 등비수열의 합은 무한대로 발산`한다   

initial term이 1이고, common ratio가 1/2인 무한 등비수열의 합   
$$S = \frac{1}{1 - \frac{1}{2}} = \frac{1}{\frac{1}{2}} = 2$$
즉, 이 `무한 등비수열의 합은 2로 수렴`한다   

<br><br>

# 활용
## 1. 등차 또는 등비수열 구분
주어진 vector가 Arithmetic Sequence인지 Geometric Sequence인지 구분하는 방법   
```
1. 항의 개수 확인
2. 등차수열 여부 확인
3. 등비수열 여부 확인
```
### 항의 개수 확인
항의 개수가 1인 경우, 등차수열과 등비수열 모두 만족할 수 있기 때문에 구분이 불가능하다   
### common difference 확인
모든 연속된 항에 대해 $a_i - a_{i - 1} = d$인지 확인   
### common ratio 확인
첫 common ratio를 계산했을 때, $a_1 \neq 0$이어야 한다   
이후 모든 연속된 항에 대해 $\frac{a_i}{a_{i - 1}} = r$인지 확인   

```cpp
#include <vector>
#include <string>
#include <cmath>

using namespace std;

string identifySequence(const vector<long long>& seq) {
  int n = seq.size();
  // 등차수열과 등비수열 모두 만족
  if (n <= 2) return "Both Arithmetic and Geometric";

  bool isArithmetic = true;
  bool isGeometric = true;

  // 등차수열 확인
  long long common_diff = seq[1] - seq[0];
  for (int i = 2; i < n; ++i) {
    if (seq[i] - seq[i - 1] != common_diff) {
      isArithmetic = false;
      break;
    }
  }

  // 등비수열 확인
  if (seq[0] == 0) {    // common_ratio를 정의할 수 없음
    // 모든 항이 0이어야 등비수열
    for (int i = 1; i < n; ++i) {
      if (seq[i] != 0) {
        isGeometric = false;
        break;
      }
    }
  }
  else {                // common ratio를 정의할 수 있음
    double common_ratio = static_cast<double>(seq[1] / seq[0]);
    for (int i = 2; i < n; ++i) {
      // 연속된 항 중 이전 항이 0이면 등비수열이 아님
      if (seq[i - 1] == 0) {
        isGeometric = false;
        break;
      }

      double ratio = static_cast<double>(seq[i] / seq[i - 1]);
      if (abs(ratio - common_ratio) > 1e-9) {
      isGeometric = false;
      break;
    }
    }
  }

  if (isArithmetic && isGeometric) return "Both Arithmetic and Geometric";
  else if (isArithmetic) return "Arithmetic";
  else if (isGeometric) return "Geometric";
  return "Unknown";
}
```