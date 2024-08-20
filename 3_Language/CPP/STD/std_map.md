- [MAP](#map)
    - [operator\[\] 주의점](#operator-주의점)
- [multimap](#multimap)
    - [key에 대응하는 모든 value 탐색](#key에-대응하는-모든-value-탐색)

# MAP
associative container( 연관 컨테이너 )인 `map과 multimap`, `unordered_map`에 대해 알아본다.</br>
sequence container와 달리 `key - value` 구조를 가진다. 특정한 key를 넣으면 이와 대응되는 value를 돌려준다. </br>

associate container에는 set과 map이 존재한다.</br>
두 자료구조 모두 `중복된 원소를 허용하지 않는다`. </br>
이미 같은 key가 원소로 있는 경우, 나중에 insert되는 key값은 무시한다</br>
key에 대응되는 값을 바꾸고 싶다면 insert가 아니라 operator[]로 값을 바꿀 수 있다. </br>

set과는 달리 key의 존재 유무만 판단하는 것이 아니라 `대응되는 value`를 가져올 수 있다. </br>
하지만 map은 set보다 사용하는 메모리가 많기 때문에 key의 존재 유무만 궁금한 경우 set을 사용한다.

### operator[] 주의점
operator[]로 map에 접근할 때 key에 해당하는 value가 없는 경우, 자동으로 value의 default 생성자를 호출해서 원소를 추가한다.
```cpp
#include <iostream>
#include <map>

std::map<string, double> m;
m["하이"] = 1;

std::cout << m["바이"] << std::endl;    // 0 출력
```
오류가 발생하지 않기 때문에 operator[]를 사용해서 값을 찾을 때는 먼저, find 함수로 key 값이 존재하는지 확인한다.
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
key가 존재하지 않으면 end()를 반환한다.

# multimap
multimap은 중복된 key값을 허용한다. </br>
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
`find() 함수`를 이용하여 multimap의 `key와 대응되는 value 중 랜덤한 값 하나를 반환`한다.</br>

### key에 대응하는 모든 value 탐색
``` cpp
auto range = m.equal_range(1);
for (auto itr = range.first; itr != range.second; ++itr) {
  std::cout << itr->first << " : " << itr->second << " " << std::endl;
}
```
`equal_range`함수는 key에 대응되는 원소들의 iterator 중 `begin()과 end()를 std::pair로 만든 세트로 반환`한다. </br>
이때 iterator의 first는 begin()을 second는 end()를 가리킨다.