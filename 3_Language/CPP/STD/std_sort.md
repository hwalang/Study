- [std::sort](#stdsort)
    - [comp](#comp)
- [Complexity](#complexity)
    - [IntroSort Algorithm](#introsort-algorithm)
- [Example](#example)
  - [basic](#basic)
  - [compare pair\<Type, Type\>](#compare-pairtype-type)

<BR>

[cppreference - std::sort](https://en.cppreference.com/w/cpp/algorithm/sort)<br>

# std::sort
```cpp
#include <algorithm>

// 1.
template <class RandomIt>
void sort(RandomIt first, RandomIt last);

// 2.
template <class RandomIt, class Compare>
void sort(RandomIt first, RandomIt last, Compare comp);
```
`[first, last) 범위의 elements를 ascending order 방식으로 정렬한`다<br>
`값이 같은 element의 순서가 유지되는 것은 보장하지 않는다`<br>

<br>

1. elements의 정렬 방식은 `operator< 또는 std::less{}`에 따른다.
2. elements의 정렬 방식은 `comp`에 따른다

<br>

### comp
comparison function object이다<br>
만약 `첫 번째 인자( element )가 두 번째 인자보다 작으면 true를 반환`한다<br>
```cpp
bool cmp(const Type1& a, const Type2& b);
```

<br>
<br>

# Complexity
N은 정렬할 요소의 개수( last - first )이다<br>
"operator<, std::less{}"와 comp를 사용한 비교를 포함하면, `O(N * logN)`이다<br>

과거에는 내부적으로 QuickSort만 사용하여 O(N * N)이었지만, 지금은 `IntroSort 알고리즘을 사용`한다<br>

### IntroSort Algorithm
`QuickSort, HeapSort, InsertionSort를 조합한 하이브리드 알고리즘`이다<br>

기본적으로 QuickSort를 사용하여 O(N * logN)을 추구하지만, 최악의 경우 O(N * N)이 걸린다.<br>
최악의 상황에 다가가면 HeapSort로 전환한다<br>

HeapSort는 항상 O(N logN) 시간 복잡도를 가지기 때문에 최악의 경우를 방지한다<br>

InsertionSort는 O(N * N)이지만, 크기가 작은 배열에서는 다른 알고리즘보다 더 빠를 수 있기 때문에 작은 크기의 배열에 적용한다<BR>

<BR>
<BR>

# Example
## basic
```cpp
#include <algorithm>
#include <functional>
#include <array>

std::array<int, 10> s{5, 7, 4, 2, 8, 6, 1, 9, 0, 3};

// 1. default operator<
std::sort(s.begin(), s.end());

// 2. compare function object
std::sort(s.begin(), s.end(), std::greater<int>());

// 3. custom function object
struct {
  bool operator() (int a, int b) const {return a < b;}
} customLess;
std::sort(s.begin(), s.end(), customLess);

// 4. lambda expression
std::sort(s.begin(), s.end(), [](int a, int b) {
  return a > b;
});
```

## compare pair<Type, Type>
[전국 대회 선발 고사](https://school.programmers.co.kr/learn/courses/30/lessons/181851)<br>
```cpp
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> rank, vector<bool> attendance) {
    vector<pair<int, int>> attend_rank;
    for (int i = 0; i < attendance.size(); ++i) {
        if (attendance[i]) {
            attend_rank.emplace_back(make_pair(i, rank[i]));
        }
    }
    
    sort(attend_rank.begin(), attend_rank.end(), [](pair<int, int> a, pair<int, int> b) {
        return a.second < b.second;
    });
    
    int a = attend_rank[0].first;
    int b = attend_rank[1].first;
    int c = attend_rank[2].first;
    
    return 10000 * a + 100 * b + c;
}
```
lambda expression에 pair<int, int> element를 비교했다<br>
`기본적으로 std::sort는 first를 기준으로 비교`하지만, 여기선 second로 비교했다<br>