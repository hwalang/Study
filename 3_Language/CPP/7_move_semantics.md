- [1. Move Semantics( 이동 의미론 )](#1-move-semantics-이동-의미론-)
  - [1.1. Copy](#11-copy)
  - [1.2. Move](#12-move)
    - [1.2.1. Moved-From State](#121-moved-from-state)
    - [1.2.2. 주의점](#122-주의점)
    - [1.2.3. 사용처](#123-사용처)
- [2. Example](#2-example)
  - [2.1. Basic Class](#21-basic-class)
  - [2.2. Move Constructor : Container](#22-move-constructor--container)
  - [2.3. std::move](#23-stdmove)
    - [2.3.1. std::move Logic](#231-stdmove-logic)

<br>

# 1. Move Semantics( 이동 의미론 )
객체의 resource를 효율적으로 이동시켜 복사에 비해 성능을 향상시킨다.   

대용량 데이터를 복사하지 않아 overhead를 줄이고, pointer만 이동하기 때문에 복사에 비해 빠르다.   
불필요한 복사를 줄이고 메모리 사용을 최적화한다   

## 1.1. Copy
`객체의 모든 memeber를 복사( Deep Copy )하여 새로운 객체를 생성`한다   

## 1.2. Move
```cpp
#include <utility>

std::move(T&& t)    // t: the object to be moved
```
`객체의 resource( dynamic memory, file handle 등 )를 다른 객체로 이동`시킨다   
`이동 후 원본 객체는 resource를 잃는다( Moved-From State )`   
여기서 원본 객체란, from-to에서 from을 의미한다. 즉, 데이터를 전달해주는 객체가 원본 객체다   

이러한 Move Operation에는 Move Constructor와 Move Assignment Operation이 존재한다   

### 1.2.1. Moved-From State
Move Operation 이후 original 객체는 resource를 잃게 되어, 마치 비어있는 것처럼 보이기 때문에 이동 대상이 된 객체들은 사실상 제거된 것과 같은 효과가 있다   
즉, 원본 객체는 `moved-from state`를 가진다   

### 1.2.2. 주의점
원본 객체의 resource 이동 후, 원본 객체는 valid 하지만 내부 resource는 특정되지 않은 상태라서 재사용하려면 초기화가 필요하다   

resource 이동 후에는 원본 객체의 resource를 안전하게 초기화하여 중복 해제 등의 문제가 발생하지 않도록 한다   

Move Constructor와 Move Assignment Operation에 onexcept를 지정하여 Container 최적화를 돕는다   

### 1.2.3. 사용처
Function에서 local 객체를 반환할 때   
Container에서 객체를 insertion 또는 Move할 때   
resource 소유권을 이전할 때   


<br><br>


# 2. Example
## 2.1. Basic Class
앞으로 Move Assignment Operation, Move Constructor를 사용하는 클래스를 정의   
```cpp
#include <iostream>
#include <cstring>

// Dynamic Memory 관리 클래스
class MyString {
private: 
  char* data;
  size_t size;

public:
  MyString() : data(nullptr), size(0) {
    std::cout << "기본 생성자 호출\n";
  }

  MyString(const char* str) {         // 기존 문자열을 받아들이는 생성자
    std::cout << "복사 생성자 호출\n";
    size = std::strlen(str);
    data = new char[size + 1];
    std::strcpy(data, str);
  }

  MyString(const MyString& other) {   // 다른 객체의 member 데이터를 복사하는 생성자
    std::cout << "복사 생성자 호출\n";
    size = other.size;
    data = new char[size + 1];
    std::strcpy(data, other.data);
  }

  MyString(MyString&& other) noexcept { // 이동 생성자
    std::cout << "이동 생성자 호출\n";
    data = other.data;
    size = other.size;

    other.data = nullptr;
    other.size = 0;
  }

  MyString& operator=(const MyString& other) {  // 복사 할당 연산자
    std::cout << "복사 할당 연산자 호출\n";
    if (this != &other) {
      delete[] data;

      size = other.size;
      data = new char[size + 1];
      std::strcpy(data, other.data);
    }
    return *this;
  }

  MyString& operator=(MyString&& other) noexcept {  // 이동 할당 연산자
    std::cout << "이동 할당 연산자 호출\n";
    if (this != &other) {
      delete[] data;

      data = other.data;
      size = other.size;

      other.data = nullptr;
      other.size = 0;
    }
    return *this;
  }

  ~MyString() {
    std::cout << "소멸자 호출\n";
    delete[] data;
  }

  void print() const {
    if (data) std::cout << data << "\n";
    else std::cout << "(null)\n";
  }
}
```
`Copy Constructor`와 `Copy Assignment Operation`은 Deep-Copy를 수행하여 새로운 메모리를 할당한다   

`Move Constructor`는 원본 객체의 data **pointer**를 이동하고, 원본 객체 포인터를 nullptr로 설정한다   
`Move Assignment Operation`은 기존( 원본 ) 메모리를 해제하고, 원본 객체의 resource를 이동한다   
memory leak를 방지하기 위해 기존 resource를 해제한다   

```cpp
MyString str1("Hello, World");
MyString str2(std::move(str1));   // Move Constructor
str1.print();                     // Moved-From State
str2.print();

MyString str3;
str3 = std::move(str2);
str2.print();                     // Moved-From State
str3.print();
```

## 2.2. Move Constructor : Container
```cpp
std::vector<MyString> vec;
vec.push_back(MyString("First"));
vec.push_back(MyString("Second"));

std::cout << "Print Vector\n";
for (const auto& str : vec) {
  str.print();
}
```
Move Constructor를 이용하여 Container에 새로운 객체를 insertion한다   
```cpp
복사 생성자 호출
이동 생성자 호출
소멸자 호출
복사 생성자 호출
이동 생성자 호출
소멸자 호출
Print Vector
First
Second
소멸자 호출
소멸자 호출
```
**[ push_back 내부 동작 ](1_pushback_emplaceback.md/#push_back-과정)**   
1. push_back()은 임시 객체( MyString("First") )가 생성된다   
2. 임시 객체는 vector 내부로 이동하는데, 이때 이동 생성자가 호출되어 임시 객체의 resource가 vector에 저장   
3. 임시 객체 소멸   

## 2.3. std::move
object를 rvalue 참조로 변환하여 Move Semantics를 적용한다   
```cpp
MyString a("Hello");
MyString b;

b = a;              // Copy Assignment
b = std::move(a);   // Move Assignment
```

### 2.3.1. std::move Logic
```
1. Pointer 이동
    객체가 소유한 resource를 다른 객체로 이동

2. Original Object 초기화
    이동 후 Original Object는 resource를 잃게 되며, 이를 nullptr 또는 기본값으로 초기화

3. noexcept 지정자
    Move Constructor와 Move Assignment Operation에 noexcept를 지정하여 예외 안전성을 높인다
    Container들은 내부적으로 element의 Move Constructor가 noexcept인지 확인하고 최적화를 수행
```