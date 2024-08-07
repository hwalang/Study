- [std::set](#stdset)
  - [basic](#basic)
  - [Bidirectional Iterator](#bidirectional-iterator)
  - [find](#find)
- [example](#example)

# std::set

associate container인 set에 대해 알아본다.</br>
sequence container와 달리 `key - value` 구조를 가진다.</br>
특정한 key를 넣으면 이에 대응하는 value를 돌려준다.</br>

`특정 key가` associate container에 `존재하는지 유무`를 알려준다.</br>

## basic
sequence container처럼 insert를 이용해서 element를 추가할 수 있다. 하지만 어디에 추가할지에 대한 정보는 없다.</br>
set은 컨테이너 안에 모든 원소들을 `순서를 지키면서` 쑤셔 넣는 방식이다. 컨테이너 안에 `원소가 어디 있는지 중요하지 않고`, 원소가 `있냐/없냐 만이 중요한 정보`이기 때문이다.</br>

set에 element를 추가하거나 지우는 작업은 $O(logN)$ 걸린다. sequence container는 $O(N)$이기 때문에 더 빠르다는 것을 알 수 있다.</br>
cpp의 std::set은 `Red-Black Tree`와 같은 균형 이진 탐색 트리로 이루어져있다.</br>

또한 순서를 지키면서 넣기 때문에 set 내부의 원소들은 `정렬된 상태를 유지`한다.</br>
이러한 특징으로 인해 User-Defined Types( class )를 set에 저장하려면 `operator<`를 정의해야 한다.</br>

set 내부에는 `중복된 원소들이 존재하지 않는다`.</br>
set에 존재하는 원소를 insert하는 경우, 이를 무시하는 성질을 가졌다.</br>

## Bidirectional Iterator
set은 sequence container처럼 임의의 위치에 존재하는 원소에 접근하는 것이 불가능하고, `순차적으로 하나 씩 접근하는 iterator를 제공`한다.</br>

## find
vector의 find는 처음부터 끝까지 비교하면서 찾기 때문에 $O(N)$이 걸린다.</br>
하지만 set의 find는 Red-Black Tree 구조를 가지기 때문에 $O(logN)$이면 key에 대응하는 원소를 찾을 수 있다.</br>
```cpp
auto itr = s.find(key);
if (itr != s.end()) {
  std::cout << "있음" << std::endl;
}
else {
  std::cout << "없음" << std::endl;
}
```

# example
[프로그래머스 - 주사위 게임2](https://school.programmers.co.kr/learn/courses/30/lessons/181930)
```cpp
#include <set>
#include <cmath>

using namespace std;

int solution(int a, int b, int c)
{
  set<int> s{ a, b, c };
  if (s.size() == 3) {
    return a + b + c;
  }
  else if (s.size() == 2) {
    return (a + b + c) * (pow(a, 2) + pow(b, 2) + pow(c, 2));
  }
  else if (s.size() == 1) {
    return (a + b + c) * (pow(a, 2) + pow(b, 2) + pow(c, 2)) * (pow(a, 3) + pow(b, 3) + pow(c, 3));
  }
}
```
주사위를 굴려서 나온 세 가지 숫자 중 몇 개의 숫자가 같은지 판단할 때 set을 이용했다.</br>
set에 a, b, c를 넣었지만 set의 성질에 따르면 기존에 있던 key와 같은 원소를 넣을 수 없기 때문에 set의 크기가 1, 2, 3 중 하나임을 유추할 수 있다.</br>