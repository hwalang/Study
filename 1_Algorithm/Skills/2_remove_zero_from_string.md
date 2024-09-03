
# 문자열의 가장 왼쪽에 있는 0을 제거하는 방법
[Programmers - 0빼기](https://school.programmers.co.kr/learn/courses/30/lessons/181847)<br>

문제의 조건을 있는 그대로 적용하기 위해서 for문을 사용했지만, 더 간단한 방법이 있었다<br>
string을 int로 변환하면 가장 왼쪽에 있는 0이 자동으로 사라진다<br>

### 내가 적용한 방법
```cpp
#include <string>

using namespace std;

string solution(string n_str) {
    if (n_str[0] != '0') return n_str;

    for (auto it = n_str.begin(); it != n_str.end();) {
        if (*it == '0') {
            it = n_str.erase(it);
        }
        else {
            break;
        }
    }

    return n_str;
}
```

### 간단한 방법
```cpp
#include <string>

using namespace std;

string solution(string n_str)
{
  return to_string(stoi(n_str));
}
```