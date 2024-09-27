- [Sweep Line Algorithm](#sweep-line-algorithm)
  - [1. 겹치는 선분의 길이](#1-겹치는-선분의-길이)
    - [1.1. Event 정의](#11-event-정의)
    - [1.2. Sort Event](#12-sort-event)
    - [1.3. Sweep Line 적용](#13-sweep-line-적용)
    - [1.4. Code](#14-code)

<br><br>

# Sweep Line Algorithm
**[LeetCode - Line Sweep Algorithm](https://leetcode.com/discuss/study-guide/2166045/line-sweep-algorithms)**   

Line Sweep( 또는 Sweep Line ) Algorithm은 `가상의 선( x축 또는 y축 )을 sweep`하여 다양한 문제를 해결하는 알고리즘 기법이다   

Event( 또는 Entry )가 발생하고 이를 기반으로 정보를 업데이트한 다음 결과를 반환한다   

## 1. 겹치는 선분의 길이
**[Programmers - 겹치는 선분의 길이](https://school.programmers.co.kr/learn/courses/30/lessons/120876)**   
선분의 시작과 끝을 이벤트로 처리하여, 현재 활성화된 선분의 개수를 추적하고, 겹치는 부분의 길이를 계산한다   
### 1.1. Event 정의
각 line의 시작점과 끝점을 Event로 정의    
시작점은 `+1`, 끝점은 `-1`로 표시   

### 1.2. Sort Event
모든 Event를 좌표를 기준으로 정렬   
동일한 좌표에서는 시작 Event가 끝 Event보다 먼저 온다   

### 1.3. Sweep Line 적용
정렬된 Event를 순차적으로 처리하면서 현재 활성화된 line의 수를 업데이트   
두 개 이상의 선분이 활성화된 구간의 길이를 누적   

### 1.4. Code
```cpp
#include <vector>
#include <algorithm>

using namespace std;

// Event
struct Event {
  int position;   // Event Position
  int type;       // 시작점: 1, 끝점: -1

  // 정렬 기준: 위치가 작을수록 먼저, 같은 위치일 경우 시작점이 먼저
  bool operator<(const Event& other) const {
    if (position != other.position) return position < other.position;
    return type > other.type;
  }
};

int solution(vector<vector<int>> lines) {
  // 모든 line에 대해 시작점과 끝점을 Event로 추가
  vector<Event> events;
  for (auto& line : lines) {
    int start = line[0];
    int end = line[1];
    events.push_back(Event{start, 1});
    events.push_back(Event{end, -1});
  }
  sort(events.begin(), events.end());

  // sweep line 적용
  int total_overlap = 0;
  int active = 0;           // 현재 활성화된 line 수
  int prev_position = 0;    // 이전 event 위치
  for (auto& event : events) {
    if (active >= 2) {
      // 이전 위치부터 현재 위치까지는 두 개 이상의 선분이 겹침
      total_overlap += (event.position - prev_position);
    }

    // 현재 event 처리
    active += event.type;
    prev_position = event.position;
  }
  return total_overlap;
}
```
선분의 시작과 끝을 이벤트로 처리하여 겹치는 구간을 정확히 추적할 수 있다   