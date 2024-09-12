- [std::map](#stdmap)
    - [특징](#특징)
    - [중복 key 처리](#중복-key-처리)
    - [operator\[\] 주의점](#operator-주의점)
- [std::multimap](#stdmultimap)
    - [key에 대응하는 모든 value 탐색](#key에-대응하는-모든-value-탐색)
- [std::unordered\_map](#stdunordered_map)
    - [buckets structure( hash table )](#buckets-structure-hash-table-)
  - [예시](#예시)
    - [1. basic](#1-basic)
    - [2. mapping : enum class - unordered\_map](#2-mapping--enum-class---unordered_map)
    - [3. 빈도수 : counts 배열](#3-빈도수--counts-배열)

<br>

# std::map
associative container( 연관 컨테이너 )인 `map과 multimap`, `unordered_map`에 대해 알아본다.</br>
sequence container와 달리 `key - value` 구조를 가진다. 특정한 key를 넣으면 이와 대응되는 value를 돌려준다. </br>

<br>

### 특징
associate container에는 set과 map이 존재한다.</br>
두 자료구조 모두 `중복된 원소를 허용하지 않는다`. </br>
set과는 달리 `key의 존재 유무만 판단`하는 것이 아니라 `대응되는 value`를 가져올 수 있다. </br>
하지만 map은 set보다 사용하는 메모리가 많기 때문에 key의 존재 유무만 궁금한 경우 set을 사용한다.<br>

```cpp
std::map<int, int, greater<int>> m;     // 내림차순
```
기본적으로 `key를 기준으로 오름차순으로 정렬`<br>

map은 `binary tree 구조`를 사용했기 때문에 `O(logN)의 검색 성능`이다<br>

<br>

### 중복 key 처리
이미 같은 key가 원소로 있는 경우, `나중에 insert되는 key값은 무시`한다</br>
`key에 대응되는 값을 바꾸고 싶다면 insert가 아니라 operator[]로 값을 바꿀 수 있다`. </br>

<br>

### operator[] 주의점
operator[]로 map에 접근할 때 `key에 해당하는 value가 없는 경우, 자동으로 value의 default 생성자를 호출해서 원소를 추가`한다.<br>
```cpp
#include <iostream>
#include <map>

std::map<string, double> m;
m["하이"] = 1;

std::cout << m["바이"] << std::endl;    // 0 출력
```
오류가 발생하지 않기 때문에 operator[]를 사용해서 값을 찾을 때는 `먼저, find 함수로 key 값이 존재하는지 확인`한다.<br>
```cpp
auto itr = m.find(key);
if (itr != m.end()) {
  // 찾음
}
else {
  // 못 찾음
}
```
참고로 find() 함수는 map에서 해당하는 key를 찾아서 이를 가리키는 iterator를 반환한다. </br>
key가 존재하지 않으면 end()를 반환한다.<br>

<br><br>

# std::multimap
multimap은 `중복된 key값을 허용`한다. </br>
```cpp
#include <map>
#include <iostream>

template <typename K, typename V>
void print_map(const std::multimap<K, V>& m) {
  // 맵의 모든 원소 출력
  for (const auto& kv : m) {
    std::cout << kv.first << " " << kv.second << std::endl;
  }
}

int main() {
  std::multimap<int, std::string> m;
  m.insert(std::make_pair(1, "hi"));
  m.insert(std::make_pair(1, "hello"));
  m.insert(std::make_pair(1, "hihi"));

  print_map(m);
  std::cout << m.find(1)->second << std::endl;  // key에 대응되는 value 중 랜덤한 값 반환
                                                // first( key ), second( value )
}

/*
1 hi
1 hello
1 hihi
hi
*/
```

중복된 key 값을 허용하기 때문에 `operator[]를 사용할 수 없다`.</br>
위 예시에서 m[1] 을 했을 때, 어떤 값을 반환해야 할 지 알 수 없기 때문이다.</br>

따라서 `find() 함수`를 이용하여 multimap의 `key와 대응되는 value 중 랜덤한 값 하나를 반환`한다.</br>

<br>

### key에 대응하는 모든 value 탐색
``` cpp
auto range = m.equal_range(1);
for (auto itr = range.first; itr != range.second; ++itr) {
  std::cout << itr->first << " : " << itr->second << " " << std::endl;
}
```
`equal_range`함수는 key에 대응되는 원소들의 iterator 중 `begin()과 end()를 std::pair로 만든 세트로 반환`한다. </br>
이때 iterator의 first는 begin()을 second는 end()를 가리킨다.

<br><br>

# std::unordered_map
[ cppreference - unordered_map ](https://en.cppreference.com/w/cpp/container/unordered_map)<br>
```cpp
#include <unordered_map>

template <class Key, class T,
          class Hash = std::hash<Key>,
          class KeyEqual = std::equal_to<Key>,
          class Allocator = std::allocator<std::pair<const Key, T>>
          >
class unordered_map;
```
unordered_map의 가장 큰 이점은 `elements의 Search, Insertion, Removal 작업을 평균적으로 O(1)에 처리`한다<br>

<br>

### buckets structure( hash table )
`내부적으로 elements는 특정 기준으로 정렬하지 않고, buckets에 존재`한다<br>
이러한 `buckets는 key의 hash 값에 따라 element를 담는다`<br>
만약 hash 값이 같은 key라면 같은 buckets에 담긴다<br>

이러한 buckets 구조는 `hash 값을 계산한 이후, 특정 bucket이 어떤 element를 담고 있는지 참조하기 때문에 각 element에 빠르게 접근`할 수 있다<br>

<br>

## 예시
### 1. basic
unordered_map의 선언 및 초기화 방법<br>
`key-value에 접근하여 순회`하는 방법<br>
새로운 element( key, value )를 추가하는 방법<br>
```cpp
#include <unordered_map>

int main()
{
  std::unordered_map<std::string, std::string> um =
  {
    {"RED", "#FF0000"},
    {"GREEN", "#00FF00"},
    {"BLUE", "#0000FF"}
  };

  // key-value를 출력하는 2가지 방법
  auto print_key_value = [](const auto& key, const auto& value) {
    cout << "key: " << key << " value: " << value << endl;
  }
  for (const pair<const string, string>& n : um)
    print_key_value(n.first, n.second);

  for (const auto& [key, value] : um)     // since C++17
    print_key_value(key, value);  

  // Add two new entries
  um["BLACK"] = "#000000";
  um["WHITE"] = "#FFFFFF";

  print_key_value("new_key", u["new_key"]);   // key: [new_key] value:[]
}
```
`operator[]를 사용`하면, std::map과 마찬가지로 `unordered_map에 해당 key가 없는 경우 새로운 key-value를 추가`한다<br>
이때 value는 빈 값이다<br>

<br>

### 2. mapping : enum class - unordered_map
[mapping 예시](/1_Algorithm/Skills/5_mapping.md/#예시-1--메뉴와-가격-enum-class와-unordered_map-)<br>
위 글을 보면 알 수 있듯이 enum과 map을 이용한 mapping은 자주 사용한다<br>

<br>

### 3. 빈도수 : counts 배열
[ frequency 기록하는 예시 ](/1_Algorithm/Skills/7_frequency.md/#2-unordered_map)<br>
내가 말하는 counts 배열이란, index를 value( Integer )로 삼고 각 value가 몇 번 등장했는지 기록하는 자료 구조이다<br>
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

```cpp
unordered_map<int, int> counts;   // freq라고 지어도 괜찮음
for (int i = 0; i < array.size(); ++i) {
  counts[array[i]]++;
}
```
`값의 범위가 불특정하고 빈도수를 효율적으로 관리`하고 싶을 때, unordered_map을 사용한다<br>
