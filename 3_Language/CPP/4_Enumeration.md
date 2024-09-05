- [Underlying Type( 기저 타입 )](#underlying-type-기저-타입-)
    - [개념](#개념)
    - [특징](#특징)
- [1. Unscoped Enumerations](#1-unscoped-enumerations)
    - [1.1. Global namespace](#11-global-namespace)
    - [1.2. Underlying Type is Not Fixed](#12-underlying-type-is-not-fixed)
    - [1.3. Empty Enumerator List](#13-empty-enumerator-list)
    - [1.4. overflow](#14-overflow)
    - [1.5. enumerator value](#15-enumerator-value)
    - [1.6. Non-name Enumeration](#16-non-name-enumeration)
    - [1.7. class member](#17-class-member)
- [Enumeration에 이름을 붙이지 않으면 Linkage 과정에서 발생하는 일](#enumeration에-이름을-붙이지-않으면-linkage-과정에서-발생하는-일)
- [2. Scoped Enumerations](#2-scoped-enumerations)
    - [2.1. static\_cast](#21-static_cast)
- [3. 기타 사용법](#3-기타-사용법)
  - [3.1. list initialization](#31-list-initialization)
    - [조건](#조건)
    - [예시](#예시)
  - [3.2. using enum declaration](#32-using-enum-declaration)
    - [3.2.1. Non-dependent type](#321-non-dependent-type)
    - [3.2.2. type only lookup](#322-type-only-lookup)
    - [3.2.3. class member](#323-class-member)

<br>

[cppreference - Enumeration Declaration](https://en.cppreference.com/w/cpp/language/enum)<br>

# Underlying Type( 기저 타입 )
enum에 대해 얘기할 때 자주 등장하는 type이다<br>

enum 외에도 추상화된 데이터 타입에 적용할 수 있다<br>
```cpp
using Integer = int;    // underlying type: int
Integer num = 5;
```
예를 들어, typedef, using keyword를 이용한 TYPE 별칭의 underlying type은 원래 TYPE을 의미한다<br>

### 개념
cpp에서 `enum type이 내부적으로 사용하는 정수형 데이터 타입`을 의미한다<br>
enum은 프로그래머에게 열거된 상수들의 이름을 제공하지만, `compiler는 enum 상수들을 하나의 정수 값으로 처리`한다<br>
이때 사용되는 정수형이 바로 underlying type이다<br>

```cpp
enum Color : unsigned char { Red, Green, Blue };
```
Color enum에서 Red, Green, Blue를 compiler가 보기엔 0, 1, 2로 취급한다<br>
`이러한 0, 1, 2가 어떤 정수형으로 저장되는지가 underlying type`이다<br>
위 예시에서는 unsigned char가 underlying type이다<br>

### 특징
enum의 underlying type은 기본적으로 `int`를 사용한다<br>
만약 enum value가 `int 범위를 벗어나면 compiler는 더 큰 정수형 타입( unsigned int, long 등 )을 자동으로 선택`한다<br>

C++11 이후 `enum을 선언할 때, underlying type을 명시적으로 지정할 수 있다`<br>

<br>
<br>

# 1. Unscoped Enumerations
enum-specifier를 사용한다<br>
```cpp
enum name(optional) {
  enumerator = constant_expression, 
  enumerator = constant_expression,
  ... 
};

// since C++11
enum name(optional) : type { enumerator = constant_expression, ... };
enum name : type;
```

<br>

### 1.1. Global namespace
```cpp
enum Color { red, green, blue };
Color color = red;

if (color == red) cout << "red\n";
```
이름처럼 `enum 값이 global namespace에 노출`된다<br>
즉, Color::Red뿐만 아니라 Red로 사용할 수 있다<br>

<br>

### 1.2. Underlying Type is Not Fixed
underlying type이 고정되지 않으며, 일반적으로 int type이 사용된다<br>
`underlying type이 특정되지 않으면 compiler는 enum의 모든 값이 표현될 수 있는 TYPE을 선택`한다<br>

memory 효율성 측면에서 안 좋다.<br>

<br>

### 1.3. Empty Enumerator List
```cpp
enum Empty {};
cout << Empty() << endl;  // print 0

enum Empty;
cout << Empty() << endl;  // print 0
```
`enum이 비어있으면 compiler는 0으로 취급`한다<br>

<br>

### 1.4. overflow
enum value가 `어떤 정수형 타입으로도 표현할 수 없는 값을 포함`하면, 해당 enum은 잘못된 형식으로 간주되어 `compile error`가 발생한다<br>

<br>

### 1.5. enumerator value
```cpp
enum Foo { a, b, c = 10, d, e = 1, f, g = f + c };
//a = 0, b = 1, c = 10, d = 11, e = 1, f = 2, g = 12
```
각 enumerator는 underlying type과 관련된다.
만약 enum에서 operator=으로 constant-expressions를 정의하지 않았다면, 0부터 시작하는 값을 자동으로 할당받는다<br>
이후에도 = 로 값을 정하지 않았다면, 이전 value에 +1을 한다<br>

<br>

### 1.6. Non-name Enumeration
```cpp
enum { a, b, c = 0, d = a + 2 };
// defines a = 0, b = 1, c = 0, d = 2

int number = a;   // 0
```
enum-name을 생략한 경우, { } 내부에 있는 `enumerators는 일반 상수처럼 사용`된다<br>

이름이 불필요하거나 상수를 단순하게 정의하고 싶을 때 이용한다<br>

<br>

### 1.7. class member
```cpp
struct X {
  enum direction { left = 'l', right = 'r' };
};

X x;
X* p = &x;

int a = X::direction::left;   // since C++11
int b = X::left;
int c = x.left;
int d = p->left;
```
class의 멤버 변수로 존재하는 enumeration의 enumerators는 `operator.과 operator->로 접근`할 수 있다<br>

<br>
<br>

# Enumeration에 이름을 붙이지 않으면 Linkage 과정에서 발생하는 일
Linkage 과정은 Compile된 여러 객체 파일들이 결합되어 최종 실행 파일이 만들어진다<br>
`이 과정에서 변수, 함수, enum 같은 이름들을 어떻게 연결할지 결정하는 과정이 필요`하다<br>
이때 이름이 없는 enumeration은 어떻게 다루는지 살펴본다<br>

```cpp
enum { red, green, blue };
```
위 코드의 이름 없는 enumeration은 typedef( 타입 별칭 )이 없다<br>
enumeration 자체의 이름이 없기 때문에 특별한 방식으로 구분한다<br>

이때, Non-name Enumeration이 하나 이상의 Enumerator를 포함한다면, `Linkage 과정에서 해당 enumeration을 구분하기 위해 underlying type과 첫 번째 enumerator를 사용`한다<br>
즉, 첫 번째 열거형 상수와 underlying type이 이름처럼 취급되어 enumeration을 구분하는데 사용한다<br>

<br>
<br>

# 2. Scoped Enumerations
```cpp
enum struct|class name { enumerator = constant-expression, ... };
enum struct|class name : type { enumerator = constant-expression, ... };

enum struct|class name;
enum struct|class name : type;
```
대부분 Unscoped Enumeration과 같기 때문에 다른 점을 살펴본다<br>

### 2.1. static_cast
```cpp
enum class Color : int { red, green = 20, blue };
Color color = Color::blue;

int n = static_cast<int>(color);
int n = color;                      // error
```
Scoped Enumeration은 `implicit( 암시적 ) conversion을 지원하지 않는다`<br>
Underlying Type을 명시적으로 알려줘도 Type 안전성을 위해 implicit conversion을 할 수 없다<br>
대신 `static_cast를 이용`하여 Color::blue를 정수형으로 변환할 수 있다<br>

<br>
<br>

# 3. 기타 사용법
## 3.1. list initialization
list-initialization을 통해 정수형으로부터 Enumeration Type으로 변환할 수 있다<br>
`INT TO ENUM`<BR>
```cpp
// Direct-List-Initialization
enum class Color : int { red, green, blue };    // Underlying type을 int로 고정
Color color = { 1 };
Color error_color = { 1, 2 };     // compile error
```
list-initialization을 통해 `Integer 1을 Color Type의 green으로 변환`한다<br>

### 조건
하지만 이 방법으로 변환하려면 아래의 조건을 만족해야 한다<br>

<br>

1. list-initialization을 사용할 때, `하나의 값`만 있어야 한다
2. `Scoped Enum` 또는 `고정된 Underlying Type을 가진 Unscoped Enum`이어야 한다
3. `Non-narrowing conversion`이어야 한다

<br>

list-initialization에 2개 이상의 element로 초기화 할 수 없으며, Underlying Type을 명시하거나 Scoped Enum을 사용해야 한다<br>
narrowing conversion으로 더 큰 범위를 가진 TYPE이 더 작은 범위를 가진 TYPE으로 casting 할 수 없다<br>

### 예시
```CPP
// byte is a new integer type
enum byte : unsigned char {};

byte b{ 42 };
byte c = byte{ 42 };      // C++17

struct A { byte b; }
A a1 = { byte{ 42 } };    // C++17

enum class Handle : std::uint32_t { Invalid = 0 };
Handle h{ 42 };           // C++17
```
```cpp
// error 예시
byte d = { 42 };
byte e{ -1 };
A a2 = { { 42 } };

void f(byte);
f( { 42 } );    // copy-list-initialization of a function parameter
```
이 방식은 `새로운 정수형 타입을 정의`할 때, `기존의 정수 타입과 동일한 호출 규칙을 사용`할 수 있게 한다<BR>
특정한 ABI( application binary interface )struct를 값으로 전달하거나 반환할 때 발생할 수 있는 성능 저하를 방지할 수 있다<br>
정수형 값을 기반으로 한 enum은 호출 규칙과 관련된 성능 패널티 없이 기존의 정수형 타입처럼 사용할 수 있다<br>

<br>

## 3.2. using enum declaration
```cpp
using enum using-enum-declarator;   // since C++20
```
`using namespace std;`를 생각하면 된다<br>
using enum을 통해 특정 Enumeration을 현재 범위로 가져와서 사용한다<br>
```cpp
enum class Color { red, green, blue, };

void foo() {
  using enum Color;   // Color의 enumerators를 현재 범위로 가져온다

  int color = red;    // Color::red에 직접 접근한다
}
```
이러면 `enum name( Color )을 생략하고 Enumerator에 직접 접근`할 수 있다<br>

<br>

### 3.2.1. Non-dependent type
하지만 `이러한 enum type이 compile time에 이미 결정`되야 한다<br>
이를 `Non-dependent enumeration type`이라 한다<br>
```cpp
template <typename T>
void foo() {
  using enum T;     // compile time에 어떤 type인지 확정되지 않는다
}
```
T는 template parameter로 compile time에 type을 확정하지 않는다<br>
이러한 `T를 dependent type( 종속적 타입 )`이라 한다<br>

하지만 using enum을 사용하기 위해선 compiler가 enum type을 이미 알고 있어야 한다<br>

<br>

### 3.2.2. type only lookup
using enum은 `TYPE만을 기준으로 검색`한다<br>
enum-declarator가 범위 내에 정의됐거나, 다른 범윙에서 참조할 수 있으면 된다<br>
```cpp
namespace Colors {
  enum class Color { red, green, blue };
}

void foo() {
  using enum Colors::Color;   // qualified lookup( 명시적 범위를 통해 검색 )
  using enum Color;           // Unqualified lookup( 현재 범위에서 검색 )
}
```
compiler가 enum-declarator를 찾는 방법은 qualified lookup과 un-qualified lookup, 두 가지 방법이 있다<br>
명시적으로 범위를 지정하거나 지정하지 않는 방식이다<br>
범위를 지정하지 않으면, 현재 범위 내에서 enum-declarator를 찾는다<br>

<br>

### 3.2.3. class member
`class 내에서 사용된 enum-declarator는 자신의 enumerators를 class의 멤버 변수로 접근`할 수 있다<Br>
```cpp
enum class fruit { orange, apple };
enum class color { red, green, orange };

struct S {
  using enum fruit;   // introduces orange and apple into S
  // using enum color;  // error: conflict orange
};

void f() {
  S s;
  s.orange;
  S::orange;
}
```
하지만 `2개 이상의 using enum을 사용할 때는 같은 Enumerators를 보유하지 않아야 에러가 발생하지 않는다`<br>