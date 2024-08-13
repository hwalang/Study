# std::basic_string::substr
[cppreference - substr](https://en.cppreference.com/w/cpp/string/basic_string/substr)

```cpp
#include <string>

basic_string substr(size_type pos = 0, size_type count = npos) const;
```
`[pos, pos + count) 범위의 부분 문자열을 반환`한다.</br>
만약 요청된 범위 내의 부분 문자열이 기존 문자열보다 크기가 크다면(`count > size() - pos`), `[pos, size()) 범위의 부분 문자열을 반환`한다.

basic_string.substr()로 호출되는데, const로 인해서 basic_string의 상태는 변하지 않는다.</br>
즉, `return 값은 원본 문자열에서 일부를 추출한 새로운 문자열`이고, `원본 문자열은 변하지 않음`을 의미한다.</br>

</br>
</br>

## Complexity
`O(count)`

</br>
</br>

## Example
```cpp
#include <string>

std::string solution(std::string original, int size)
{
  return original.substr(0, size);
}
```

</br>

```cpp
int solution(string str, string is_prefix) {
  return str.substr(0, is_prefix.size()) == is_prefix;
}

int solution(string str, string is_prefix) {
  return (str.find(is_prefix) == 0);
}
```
[Programmers - 접두사 확인](https://school.programmers.co.kr/learn/courses/30/lessons/181906)</br>
생각지도 못한 방법이라서 메모한다.</br>
접두사는 앞에 붙는 단어이기 때문에 is_prefix.size() 만큼만 조회한다.</br>
find()를 통해서 is_prefix를 찾은 뒤에 시작 index가 0이면 1을 리턴한다.</br>