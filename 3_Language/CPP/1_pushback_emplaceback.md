- [push\_back](#push_back)
    - [push\_back 과정](#push_back-과정)
- [emplace\_back](#emplace_back)
- [객체 생성 방법 2가지](#객체-생성-방법-2가지)
  - [1. 일반적인 객체 생성](#1-일반적인-객체-생성)
  - [2. placement-new 방식의 객체 생성](#2-placement-new-방식의-객체-생성)
- [공통점](#공통점)
- [차이점](#차이점)
- [Move Constructor](#move-constructor)
  - [1. COPY](#1-copy)
  - [2. MOVE](#2-move)
  - [3. std::move](#3-stdmove)
    - [예시](#예시)
    - [이동 후 기존 객체의 상태](#이동-후-기존-객체의-상태)

<br>

vector의 push_back과 emplace_back의 차이점을 알아본다.<br>

# push_back
```cpp
// std::vector<T, Allocator>::push_back
void push_back(const T& value);
void push_back(T&& value);
```
container의 마지막에 value를 추가한다.<br>

### push_back 과정
1. 새로운 element를 생성( constructor, 임시 객체 생성 )
2. element에 value를 복사( move )
3. 임시 객체( element )를 vector에 추가
4. push_back이 끝나면 임시 객체( element )를 삭제( destructor )

<br>
<br>

# emplace_back
```cpp
// std::vector<T, Allocator>::emplace_back
template <class... Args>
void emplace_back(Args&&... args);

template <class... Args>
reference emplace_back(Args&&... args);
```
container의 마지막에 새로운 element를 추가한다.<br>
전달된 인자들을 placement-new( vector 내부 메모리 공간에 바로 생성 )로 불필요한 임시 객체나 이동 작업 없이 효율적으로 container에 element를 추가한다.<br>

emplace_back을 이해하기 위해선 객체 생성이 이뤄지는 방법을 알아야 한다.<br>

<br>
<br>

# 객체 생성 방법 2가지
## 1. 일반적인 객체 생성
```cpp
Example* obj = new Example();
```
1. `memory allocation `
2. `call constructor`

new 연산자를 통해 memory를 할당하고, 그 위치에 constructor를 이용하여 객체를 초기화( 생성 )한다.<br>
위 코드는 memory 할당과 객체 생성이 동시에 이뤄진다.<br>

<br>

## 2. placement-new 방식의 객체 생성
```cpp
// memory만 할당, 객체 생성 X
void* buffer = operator new(sizeof(Example));

std::vector<Example> vec;
vec.reserve(10);

Example* example = (Example*)malloc(sizeof(Example));

// 이미 할당된 memory에 객체를 생성
Example* obj = new(buffer) Example();

vec.emplace_back(1, 2, 3);             // vector의 capacity 내에서 객체 생성

new (Example) Example;                 // 여기서 new는 memory를 할당하지 않고, 이미 할당된 memory에 객체를 생성
```
placement-new는 `이미 할당된 memory에 객체를 생성`한다.<br>
new에 대한 자세한 설명은 [new - 참고](/3_Language/CPP/3_new.md)<br>

<br>

- **`memory 효율성`**
  - 대규모 메모리 할당 또는 메모리를 미리 예약하는 상황인 경우, 미리 할당한 메모리 내에서 객체를 생성하여 불필요한 메모리 재할당을 피할 수 있다
- **`특정 위치에 객체 생성`**
  - 임베디드 시스템에서는 정해진 메모리 영역에서만 객체를 생성할 수 있다
  - `vector 또한 내부에 메모리 블록`이 있으며, 새로 메모리를 할당하는 대신 `이미 할당된 메모리( vector의 capacity 내부 )에서 placement-new를 통해 객체를 생성`한다.


<br>
<br>

# 공통점
만약 `new element를 추가한 후 vector의 size가 기존 capacity를 초과`하면, 더 큰 memory 공간에 vector를 할당( 생성 )하고 기존 elements를 그곳으로 옮긴다( 재할당 ).

<br>
<br>

# 차이점
move 연산의 차이<br>
```cpp
#include <vector>
#include <iostream>
#include <string>

struct President
{
  std::string name;
  std::string country;
  int year;

  President(std::string p_name, std::string p_country, int p_year) 
    : name(std::move(p_name)), country(std::move(p_country)), year(p_year)
  {
    std::cout << "I am being constructed.\n";
  }

  // 이동 생성자( move constructor )
  President(President&& other)
    : name(std::move(other.name)), country(std::move(other.country)), year(other.year)
  {
    std::cout << "I am being moved.\n";
  }

  ~President()
  {
    std::cout << "I am being destructed.\n";
  }
};

int main()
{
  std::vector<President> elections;
  std::cout << "emplace_back:\n";
  elections.emplace_back("Nelson Mandela", "South Africa", 1994);

  std::vector<President> reElections;
  std::cout << "\npush_back:\n";
  reElections.push_back(President("Franklin", "USA", 1936));
}
```
위 코드를 실행하면
```cpp
emplace_back:
I am being constructed.
 
push_back:
I am being constructed.
I am being moved.
I am being destructed.
// 여기는 vector가 소멸될 때, elements들도 소멸되기 때문
I am being destructed.
I am being destructed.
```
이 출력된다.<br>

즉, emplace_back은 생성자만 호출되는 반면에 push_back은 move 연산도 발생한다.<br>

<br>
<br>

# Move Constructor
```cpp
// 이동 생성자( move constructor )
President(President&& other)
  : name(std::move(other.name)), country(std::move(other.country)), year(other.year)
{
  // year와 같은 정수는 복사해도 성능에 큰 영향을 주지 않는다
  std::cout << "I am being moved.\n";
}
```
`객체를 복사하는 대신`, `기존 객체의 자원을 이동하는 목적으로 사용`한다.<br>

복사 생성자는 deep copy하기 때문에 resource가 큰 객체일수록 성능에 안 좋지만, `이동 생성자는 기존 resource의 소유권을 넘겨주기 때문에 빠른 성능`을 가진다.<br>

추가로 새로운 memory를 할당하지 않기 때문에 `memory 효율성`이 높다.<br>
특히 수명이 짧은 임시 객체를 반환하거나 전달할 때 유용하다.<br>


<br>

## 1. COPY
```cpp
std::string str1 = "hello";
std::string str2 = str1;      // copy, str2에 memory 할당 후 str1 데이터를 복사
```
1. 새로운 memory를 할당
2. 전달받은 value( object )를 할당한 memory에 초기화( 복사 )

<br>

## 2. MOVE
`기존 object의 memory 소유권을 새로운 object에게 넘겨준다`<br>

move는 `참조의 개념이 아니`라 `기존 객체의 memory의 소유권을 새로운 객체로 넘기고, 기존 객체는 비워지거나 더 이상 유효한 자원을 갖지 않는다`.<br>

```cpp
std::string str1 = "hello";
std::string str2 = std::move(str1);   // move, str1 자원을 str2로 이동
```
1. str1은 "hello"를 저장하기 위해 memory를 할당( memory["hello"] )
2. memory resource(`"hello"를 저장한 memory block의 주소 + memory block을 관리하는 소유권`)를 str1으로 옮긴다
3. str2는 "hello"를 가리키는 memory 자원을 소유, str1은 비어있거나 초기화되지 않은 상태

<br>

## 3. std::move
Move Constructor의 핵심이며, std::move는 객체를 rvalue 참조로 casting해서 move constructor가 호출되게 만든다.<br>

President move contructor에서 std::move는 기존 객체(other)의 name을 rvalue 참조로 변환하여 move constructor를 호출한다.<br>
other.name의 소유권이 새 객체로 이전된다.<br>

### 예시
```cpp
presidents.push_back(President("kdh", "korea", 2024));

President p1("kdh", "korea", 2024);
President p2 = std::move(p1);
```

### 이동 후 기존 객체의 상태
자원 소유권을 넘겨준 기존 객체는 더 이상 유효한 데이터를 갖지 않으며, 일반적으로 비어 있는 상태이다<br>
`이 객체는 파괴는 가능하지만, 사용해서는 안 된다`.<br>
`안전한 방식으로 재사용하거나 소멸시킨다`.<br>