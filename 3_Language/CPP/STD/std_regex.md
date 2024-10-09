- [std::regex](#stdregex)
  - [1. std::regex\_replace](#1-stdregex_replace)
    - [1.1. regex\_replace 동작 방식](#11-regex_replace-동작-방식)
    - [1.2. regex\_replace example](#12-regex_replace-example)
    - [1.3. 복잡한 대체 작업 예시](#13-복잡한-대체-작업-예시)

<br><br>

std::regex를 사용하기 전, 복잡한 문자를 처리하려면 cpp의 regular expression 문법에 대한 링크가 필요   

# std::regex
cpp의 regular expression에 대해 알아보자   
```cpp
#include <regex>
```



<br><br>

## 1. std::regex_replace
`regex를 사용하여 string 내의 특정 pattern을 찾아 대체하는 용도`   
주어진 pattern에 일치하는 모든 부분을 지정된 형식( fmt )으로 대체하여 새로운 문자열을 생성하며, 다양한 문자열 처리 작업을 간결하게 구현할 수 있다   

**문제점**   
regex_replace는 고정된 대체 문자열( fmt )을 사용하기 때문에 `복잡한 동적 대체가 필요한 경우 직접 matching을 순회하여 대체하는 방법`을 사용한다   
```cpp
template<...>
std::string regex_replace(const std::string& s,
                          const std::regex& re,
                          const CharT* fmt,
                          std::regex_constants::match_flag_type flags = 
                            std::regex_constants::match_default );
```
regular expression을 사용하여 문자열( a sequence of characters ) 치환을 수행한다   

**arguments**   
s는 원본 문자열로서, regex와 일치하는 부분을 찾을 때 쓰이는 문자열이다   
re는 정의한 regular expression pattern이다   
fmt는 대체할 문자열 형식이다. regex의 capture group을 참조할 수 있다.   
flags는 검색 및 대체 동작의 세부 사항을 조정할 수 있다. 예를 들면, 대소문자 구분 등   



### 1.1. regex_replace 동작 방식
1. 원본 문자열( s )에서 regex와 일치하는 모든 부분을 찾는다
2. 비어 있는 문자열( result )를 생성하고, 여기에 각 일치 부분을 fmt 형식에 따라 대체 문자열로 변환하여 저장한다
3. result를 반환한다

### 1.2. regex_replace example
```cpp
#include <iostream>
#include <string>
#include <regex>

int main() {
  std::string s = "The cat sat on the cat mat.";
  std::regex re("cat");
  std::string fmt = "dog";

  std::string result = std::regex_replace(s, re, fmt);
  std::cout << result << std::endl;   // The dog sat on the dog mat.
}
```
문자열 내의 모든 "cat"을 "dog"로 대체한다   
```cpp
#include <iostream>
#include <string>
#include <regex>

int main() {
  std::string s =  "Contact us at support@example.com or sales@example.com.";
  std::regex re("(\\w+)@(\\w+\\.\\w+)");
  std::string fmt = "$1@newdomain.org";

  std::string result = std::regex_replace(s, re, fmt);
  std::cout << result << std::endl;   // Contact us at support@newdomain.org or sales@newdomain.org.
}
```
capture group을 사용해서 복잡한 대체 작업을 수행할 수 있다   
위 예시는 이메일 주소에서 사용자 이름과 도메인을 capture하여 형식을 변경했다   

### 1.3. 복잡한 대체 작업 예시
regex_replace를 chainning 기법으로 이어서 사용하여 여러 단어를 동시에 대체할 수 있지만, 비효율적이다   
`std::regex_iterator나 std::sregex_iterator를 사용하여 matching된 단어를 순회하면서 동적으로 대체하는 방식`이 더 효율적이다   
```cpp
#include <iostream>
#include <string>
#include <regex>
#include <unordered_map>

int main() {
  std::string numbers = "one4seveneight";
  std::unordered_map<std::string, std::string> num_map = {
    {"zero", "0"}, {"one", "1"}, {"two", "2"}, {"three", "3"}, {"four", "4"},
    {"five", "5"}, {"six", "6"}, {"seven", "7"}, {"eight", "8"}, {"nine", "9"}
  };

  // regular expression pattern 생성
  std::string pattern = "(zero|one|two|three|four|five|six|seven|eight|nine)";
  std::regex re(pattern);

  // 결과 문자열 초기화
  std::string result;
  std::string::const_iterator searchStart(numbers.cbegin());
  std::smatch match;

  // 모든 matching을 순회하며 대체
  while (std::regex_search(searchStart, numbers.cend(), match, re)) {
    // matching된 부분 이전의 문자열을 결과에 추가
    result += match.prefix().str();
    // matching된 단어를 숫자로 대체하여 결과에 추가
    result += num_map[match.str()];
    // 다음 검색 시작 위치 업데이트
    searchStart = match.suffix().first;
  }
  
  // 마지막 matching 이후의 남은 문자열을 결과에 추가
  result += std::string(searchStart, numbers.cend());

  std::cout << result << std::endl; // 출력: 1478
}
```
영어로 표기된 숫자를 수( digit )으로 바꾸는 코드이다   

std::regex_match, std::regex_match   
std::regex_search   