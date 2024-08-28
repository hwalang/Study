- [용어 살펴보기](#용어-살펴보기)
    - [1. `closure`란](#1-closure란)
    - [2. `first-class function`란](#2-first-class-function란)
    - [3. `record`란](#3-record란)
- [Introduce](#introduce)
- [Examples](#examples)
  - [1. Mutable](#1-mutable)


<br>

# 용어 살펴보기
### 1. `closure`란
[ 참고 wiki ](https://en.wikipedia.org/wiki/Closure_(computer_programming))<br>
first-class function을 가진 프로그래밍 언어에서 사용되는 기법으로, `function과 그 function가 선언된 environment( free variables )를 함께 묶어서 보관하는 구조`이다.<br>

여기서 environment란, 함수가 생성될 때 `함수의 외부 scope에서 정의된 변수들과 그 값`들을 의미한다<br>
이러한 변수들을 free varaibles라고 부르며, `함수 내에서 자유롭게 사용`할 수 있다<br>

closure는 function과 environment를 capture한다<bR>
`capture된 environment 덕분에 함수의 외부 변수( free variables )를 참조`할 수 있다<br>
일반적인 함수는 함수 외부 변수에 접근할 수 없지만, closure는 이 변수를 capture해서 다른 scope에서 사용할 수 있다<br>

closure는 `함수가 선언된 시점의 변수들을 캡쳐해서, 나중에 그 함수가 호출될 때 해당 변수들을 참조`할 수 있다<br>

<br>

### 2. `first-class function`란
`함수를 하나의 값으로 다룰 수 있는 성질`이다.<br>
예를 들면, 함수를 변수에 할당, 다른 함수의 인자로 전달, 반환값으로 사용, Anonymous function으로 사용 등이 있다<br>

이러한 특성이 function programming의 기반을 제공한다<br>

<br>

### 3. `record`란
[ 참고 wiki ](https://en.wikipedia.org/wiki/Record_(computer_science))<br>
`composite data structure( 복합 데이터 구조 )`으로써, 다양한 데이터 type의 field들의 모음이다.<br>
예를 들면, 날짜는 숫자와 문자를 field로 포함하는 record로 저장할 수 있다.<br>

<br>
<br>

# Introduce
[ cppreference - lambda expression ](https://en.cppreference.com/w/cpp/language/lambda)<br>
lambda expression으로 closure를 생성한다<br>

중요한 특징 중 하나는 lambda가 정의된 시점의 변수들을 capture해서 함수 내부에서 사용할 수 있으며, 이러한 free variables는 closure의 일부로 저장된다<br>
`capture list( "[ ]" )를 통해 value 또는 reference로 capture할지 지정`할 수 있다<br>
```cpp
int main()
{
  int x = 10;
  auto lambda = [x]() { std::cout << "Captured x: " << x << std::endl; };
  lambda();
}
```
x는 value capture이다<br>

<br>
<br>

# Examples
lambda expression은 많은 규칙이 있기 때문에, 사용할 때마다 다양한 유형의 lambda expression을 예시로써 메모한다<br>

## 1. Mutable
mutable keyword는 `capture variables를 수정할 수 있는 기능`이다<br>
기본적으로 lambda expression에서 `capture된 변수는 read-only( 상수 취급 )`이기 때문에 mutable을 사용해야 해당 변수의 값을 수정할 수 있다<br>
```cpp
#include <numeric>

std::vector<int> nums = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
int sum = std::accumulate(nums.begin(), nums.end(), 0, [i = 0](int sum, int value) mutable {
  if (i % 2 == 0) sum += value;
  ++i;
  return sum;
});
```
만약 mutable을 사용하지 않으면 `++i`에서 compile error가 발생한다<br>