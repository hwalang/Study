- [operator\[\]와 at()의 차이점](#operator와-at의-차이점)
  - [1. Basic Concept](#1-basic-concept)
  - [2. Difference](#2-difference)
    - [2.1. vector](#21-vector)
      - [operator\[\]](#operator)
      - [at()](#at)
    - [2.2. map, unordered\_map](#22-map-unordered_map)
      - [operator\[\]](#operator-1)
      - [at()](#at-1)
  - [3. const container 접근](#3-const-container-접근)
    - [3.1. vector](#31-vector)
    - [3.2. map](#32-map)

<br>

# operator[]와 at()의 차이점
```cpp
const unordered_map<string, pair<int, int>> command {
  {"up", {0, 1}}, {"down", {0, -1}}, {"left", {-1, 0}}, {"right", {1, 0}}
};

...

for (auto& key : keyinput) {
  pair<int, int> operand = command[key];    // error
  pair<int, int> operand = command.at(key); // good
}
```
no viable overloaded operator[] for type 'const unordered_map<string, pair<int, int>>'   
pair<int, int> operand = command[key];에서 command[key]에서 에러가 발생   

이러한 error를 겪고, operator[]와 at()의 차이점을 구분해본다   

<br>

## 1. Basic Concept
operator[]와 at()은 연산자 또는 멤버 함수로써, `container의 특정 element에 접근`한다   
하지만 container 별로 차이점이 존재한다   

<br>

## 2. Difference
### 2.1. vector
#### operator[]
지정된 index의 element를 반환   
`index valid 검사를 하지 않는다` 때문에 유효하지 않은 index에 접근하면, Undefined Behaviour가 발생   
#### at()
```cpp
#include <exception>

try {
  vec.at(1);
}
catch (const std::out_of_range& e) {
  std::cerr << e.what() << std::endl;
}
```
지정된 index의 element를 반환   
`index valid를 체크`하여, 유효하지 않으면 std::out_of_range 예외를 던진다   
`valid 검사를 하기 때문에 operator[]보다 약간 느리다`   

### 2.2. map, unordered_map
#### operator[]
지정된 key의 value를 반환   
존재하지 않는 key에 접근하면, `새로운 element를 추가`하고 `해당 key에 대한 default 값을 반환`   

#### at()
지정된 key의 const value를 반환   
존재하지 않는 key에 접근하면, `std::out_of_range 예외`를 던진다   
`valid 검사를 하기 때문에 operator[]보다 약간 느리다`   

<br>

## 3. const container 접근
const container의 index 또는 key에 접근하면 `const element를 반환`한다   
### 3.1. vector
operator[]와 at() 둘 다 사용할 수 있다   
하지만 `operator[]로 element를 수정할 수 없다`   

### 3.2. map
const container는 `operator[]를 사용하지 않는다`   
때문에 처음 말했던 코드의 const unordered_map은 at()만 사용하여 접근할 수 있다   

const로 선언된 container는 수정이 불가능하기 때문에 `operator[]를 사용하여 container를 수정할 수 없도록 막는다`   
때문에 index 또는 key에 접근만 하는 at()만 사용할 수 있다   