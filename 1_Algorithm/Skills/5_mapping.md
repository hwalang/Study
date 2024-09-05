- [Introduce](#introduce)
- [1. enum - map](#1-enum---map)
  - [예시 1 : 메뉴와 가격( enum class와 unordered\_map )](#예시-1--메뉴와-가격-enum-class와-unordered_map-)
    - [왜 unordered\_map을 사용했나?](#왜-unordered_map을-사용했나)

<br>

# Introduce
mapping을 이용한 확장성 있는 코드를 작성할 때 유용한 방법을 알아본다<br>

# 1. enum - map
cpp에서 Enumeration은 상수들의 집합을 정의하는 데 사용한다<br>
때문에 정수형 값과 mapping 되며, enum으로 문자열을 직접 저장할 수 없다<br>

하지만 `enum과 string을 mapping하여 사용하여 다양한 데이터를 관리`할 수 있다<br>

<br>

## 예시 1 : 메뉴와 가격( enum class와 unordered_map )
[ Programmers - 커피 심부름 ](https://school.programmers.co.kr/learn/courses/30/lessons/181837)<br>
```cpp
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

enum class Menu : int {
    americano = 4500,
    cafelatte = 5000,
    anything = americano,
};

unordered_map<string, Menu> stringToMenu = {
    {"americano", Menu::americano},
    {"cafelatte", Menu::cafelatte},
    {"anything", Menu::anything}
};

int solution(vector<string> order) {
    // enum과 unordered_map으로 <string, int> mapping을 통해 menu를 관리
    // order의 string과 mapping data를 비교해서 가격을 책정
    int price = 0;
    for (const auto& str : order) {
        // um을 탐색하면서 str의 부분문자열에 um의 key(string)가 있는지 판단
        // 있는 경우, key에 맞는 value를 가져와서 price에 더한다
        for (const auto& [key, value] : stringToMenu) {
            if (str.find(key) != string::npos) {
                price += static_cast<int>(value);
                break;
            }
        }
    }
    return price;
}
```
order에는 가게의 메뉴의 이름 + 고객의 요구 사항을 string으로 가져온다<br>
때문에 메뉴에 따른 가격을 책정해야 하며, 이를 위한 방법으로 enum class과 unordered_map의 mapping을 이용했다<br>

### 왜 unordered_map을 사용했나?
[unordered_map에 대한 내용](/3_Language/CPP/STD/std_map.md/#stdunordered_map)<br>
위 글을 보면 알 수 있듯이 unordered_map은 O(1)으로 Search, Insertion, Removal 작업을 수행한다<br>
메뉴가 많아질수록 빠른 검색이 중요하다<br>

만약 정렬된 순서가 필요한 경우에는 um을 이용할 수 없지만 여기선 순서는 상관없다.<br>
하지만 hash table을 사용하기 때문에 std::map 보다 `추가적인 memory를 더 필요`로 한다<bR>