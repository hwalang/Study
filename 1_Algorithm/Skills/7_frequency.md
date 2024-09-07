- [Introduce](#introduce)
- [1. array, vector](#1-array-vector)
- [2. unordered\_map](#2-unordered_map)
  - [Example](#example)

<br>

# Introduce
빈도수를 기록해야 하는 상황에서 `어떤 자료 구조를 이용하면 좋은지`에 대한 내용<br>

여기서 말하는 counts 배열이란, index를 value( Integer )로 삼고 각 value가 몇 번 등장했는지 기록하는 자료 구조이다<br>

<br><br>

# 1. array, vector
```cpp
// 0 ~ 1000 사이의 값
int counts[1001];                       // 0은 dummy
for (int i = 0; i < array.size(); ++i) {
  counts[array[i]]++;
}
```
이 방법으로 각 value에 대한 빈도수를 저장하기 위해선 `value의 범위를 미리 알아야 한다`<br>
counts의 index에 접근하려면 미리 크기를 지정해야 하기 때문이다<br>
하지만 `value의 범위가 넓으면 0을 저장하는 공간이 늘어나며, 이는 memory를 비효율적으로 사용하게 만든다`<br>

<br><br>

# 2. unordered_map
`값의 범위가 불특정하고 빈도수를 효율적으로 관리`하고 싶을 때, unordered_map을 사용한다<br>
```cpp
unordered_map<int, int> counts;   // freq라고 지어도 괜찮음
for (int i = 0; i < array.size(); ++i) {
  counts[array[i]]++;
}
```
map 자료구조 특성상 operator[]를 사용하여 key에 접근했을 때, 해당 key가 없으면 map에 해당 key를 생성한다<br>
이를 이용하여 `key( Integer )가 몇 번 등장했는지 기록`할 수 있다<br>

## Example
[ Programmers - 최빈값 구하기 ](https://school.programmers.co.kr/learn/courses/30/lessons/120812)<br>
```cpp
#include <vector>
#include <unordered_map>

using namespace std;

int solution(vector<int> array) {
  unordered_map<int, int> freq;
  for (const auto& num : array) {   // 기록
    freq[num]++;
  }

  int result = 0;
  int mode = 0;
  for (const auto& f : freq) {
    if (f.second == mode) {
      result = -1;
    }
    else if (f.second > mode) {
      mode = f.second;
      result = f.first;
    }
  }
  return result;
}
```
배열에 몇 개의 num이 있는지 freq에 저장한다.<br>

현재 mode( 최빈값 )와 freq에 저장된 key의 빈도수가 같으면 -1을 반환한다<br>
그렇지 않고 key의 빈도수가 mode보다 큰 경우에는 mode를 갱신하고 해당 key를 반환한다<br>

만약 mode 값이 중복됐을 때 가장 처음 나온 mode를 가져오려면, max_element로 mode를 추출하면 된다<br>