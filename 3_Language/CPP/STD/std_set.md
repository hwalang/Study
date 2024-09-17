- [std::set](#stdset)
  - [1. basic](#1-basic)
  - [2. Bidirectional Iterator](#2-bidirectional-iterator)
  - [3. find](#3-find)
  - [4. example](#4-example)
- [std::unordered\_set](#stdunordered_set)
  - [1. key 또는 value를 수정할 수 없는 이유](#1-key-또는-value를-수정할-수-없는-이유)
  - [2. 안전한 element 수정 방법](#2-안전한-element-수정-방법)
  - [3. Example](#3-example)

<br>

여기서 말하는 element는 container에 저장된 데이터 단위를 의미하며, container의 종류에 따라 달라진다   
unordered_set과 set에서는 `element가 key를 의미`한다. 참고로 set은 value가 없다   

# std::set
[ cppreference - set ](https://en.cppreference.com/w/cpp/container/set)   

associate container인 set에 대해 알아본다.   
sequence container와 달리 `key - value` 구조를 가진다.   
특정한 key를 넣으면 이에 대응하는 value를 돌려준다.   

`특정 key가` associate container에 `존재하는지 유무`를 알려준다.   


## 1. basic
sequence container처럼 insert를 이용해서 element를 추가할 수 있다. 하지만 어디에 추가할지에 대한 정보는 없다.   
set은 컨테이너 안에 모든 원소들을 `순서에 상관 없이` 데이터를 저장하는 방식이다. 컨테이너 안에 `원소가 어디 있는지 중요하지 않고`, 원소가 `있냐/없냐 만이 중요한 정보`이기 때문이다.   
하지만 key compare 함수를 통해 `내부적으로 key를 정렬해서 저장`한다   
이러한 특징으로 인해 User-Defined Types( class )를 set에 저장하려면 `operator<`를 정의해야 한다.   

set에 `element를 search, insert, remove 작업은 O(logN)`걸린다. sequence container는 $O(N)$이기 때문에 더 빠르다는 것을 알 수 있다.   

cpp의 std::set은 `Red-Black Tree`와 같은 균형 이진 탐색 트리로 이루어져있다.   

set 내부에는 `중복된 원소들이 존재하지 않는다`.   
set에 존재하는 원소를 insert하는 경우, 이를 무시하는 성질을 가졌다.   


## 2. Bidirectional Iterator
set은 sequence container처럼 임의의 위치에 존재하는 원소에 접근하는 것이 불가능하고, `순차적으로 하나 씩 접근하는 iterator를 제공`한다.   

이때 Bidirectional Iterator를 지원하는데, 한 방향으로만 전진할 수 있는 Forward Iterator와 달리, 반대 방향( 후진 )으로도 이동할 수 있다   
때문에 `set의 iterator는 양방향으로 이동 가능`하다   


## 3. find
```cpp
auto itr = s.find(key);
if (itr != s.end()) {
  std::cout << "있음" << std::endl;
}
else {
  std::cout << "없음" << std::endl;
}
```
vector의 find는 처음부터 끝까지 비교하면서 찾기 때문에 $O(N)$이 걸린다.   
하지만 set의 find는 Red-Black Tree 구조를 가지기 때문에 $O(logN)$이면 key에 대응하는 원소를 찾을 수 있다.   


## 4. example
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
주사위를 굴려서 나온 세 가지 숫자 중 몇 개의 숫자가 같은지 판단할 때 set을 이용했다.   
set에 a, b, c를 넣었지만 set의 성질에 따르면 기존에 있던 key와 같은 원소를 넣을 수 없기 때문에 set의 크기가 1, 2, 3 중 하나임을 유추할 수 있다.   

   

[ Programmers - 무작위로 K개의 수 뽑기 ](https://school.programmers.co.kr/learn/courses/30/lessons/181858#)   
```cpp
#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> arr, int k) {
    set<int> temp;
    vector<int> results;
    for (auto ele : arr) {
        if (results.size() == k) break;
        
        if (temp.find(ele) == temp.end()) {
            results.emplace_back(ele);
            temp.insert(ele);
        }
    }

    if (results.size() < k) {
        results.insert(results.end(), k - results.size(), -1);
    }

    return results;
}
```
문제에서는 results에 저장하는 elements가 정렬된 상태를 원하지 않는다   
그렇기 때문에 set을 중복 여부를 판단하는 용도로만 사용했다   


<br><br>


# std::unordered_set
`Search, Insertion, Removal 작업이 일반적으로 O(1)`이다   

`내부적으로 element( 데이터 단위, key )를 정렬하지 않으며, bucket( hash table )에 저장`한다   
hash table에 저장했기 때문에 각 element에 O(1) 속도로 접근할 수 있다   
동일한 hash 값을 가진 value는 같은 bucket에 저장된다   
value의 중복을 허용하지 않는다   
이러한 `key를 수정하면 hash가 변경되어 container가 손상되므로 element를 수정할 수 없다`   


## 1. key 또는 value를 수정할 수 없는 이유
`element를 변경하면 hash 함수에 의해 계산되는 hash 값도 변경`될 수 있다   
cpp에서 hash 값을 결정하는데 element가 사용되기 때문이다   

hash 값이 변경되면 `수정된 key를 찾을 수 없거나, 존재하지 않는 element를 찾았다고 잘못 판단`할 수 있다   

`hash 값이 변경된 element를 다시 container에 삽입하면 중복된 element가 생길 수 있다`   

때문에 cpp에서는 `key를 const로 취급하여 수정을 불가능`하게 만들었다   

## 2. 안전한 element 수정 방법
```cpp
string data = "기존 데이터";
um.erase(data);

data = "수정 데이터";
um.insert(data);
```
기존 element를 수정해야 하는 경우, 해당 element를 container에서 제거하고 수정된 값을 가진 새로운 element를 삽입한다   

## 3. Example
```cpp
void print(const auto& set) {
  for (const auto& ele : set) std::cout << ele << ' ';
  std::cout << '\n';
}

int main()
{
  std::unordered_set<int> mySet{ 2, 7, 1, 8, 2, 8 };
  print(mySet);     // 8 1 7 2
}
```
**[ Programmers - 모음 제거 ](/1_Algorithm/Programmers/240917_모음제거.md)**   
