- [Introduce](#introduce)
- [placement-new의 역할](#placement-new의-역할)
    - [malloc](#malloc)
    - [new](#new)
- [일반적인 new의 역할](#일반적인-new의-역할)
    - [memory allocation](#memory-allocation)
    - [instance 생성](#instance-생성)
    - [return pointer](#return-pointer)

<br>

# Introduce
cpp에서 placement-new로 객체를 생성하는 방법과 그렇지 않은 방법을 살펴보던 중 operator new의 역할을 살펴봤다.<br>

<br>
<br>

# placement-new의 역할
```cpp
// 메모리 할당과 객체 생성을 분리한 예시
struct Foo {
  Foo() { std::cout << "Foo()\n"; }
  ~Foo() { std::cout << "~Foo()\n"; }
}

int main() {
  Foo* foo = (Foo*)malloc(sizeof(Foo)); // memory 할당
  new (foo) Foo;                        // foo->memory에 Foo 객체 생성

  foo->~Foo();                          // Foo 객체 해제
  free(foo);                            // foo->memory 해제
}
```
### malloc
sizeof(Foo) bytes 만큼의 memory를 heap 영역에 할당한다<br>
malloc은 `memory 할당만 가능`하며, 이를 통해 `할당된 memory 주소를 foo pointer에서 참조`한다<br>

free를 통해 foo가 가리키는 memory를 해제한다<br>

### new
placement-new 문법을 사용해서 `이미 할당된 memory( foo pointer가 가리키는 위치 )에 Foo 객체를 생성`한다.<br>
객체를 생성하면서 Foo의 Constructor를 호출한다<br>
이 단계는 memory를 새로 할당하지 않고, 기존의 foo->memory에 객체를 placement한다<br>

Destructor를 이용해서 Foo 객체를 소멸시킨다<br>

<br>
<br>

# 일반적인 new의 역할
```cpp
Foo* foo = new Foo();   // Foo 객체를 heap memory에 생성
delete foo;             // Foo 객체 소멸자 호출, memory 해제
```
### memory allocation
operator new는 `heap 영역에 지정된 크기만큼 memory를 동적으로 할당`한다<br>
예를 들면, new int는 sizeof(int) 크기의 memory를 할당한다<br>

### instance 생성
`할당된 memory 위치에 객체를 생성`하기 위해서 해당 객체의 생성자를 호출한다<br>

### return pointer
`할당된 memory 시작 주소를 pointer로 반환`한다<br>
반환된 pointer는 `객체 타입`에 맞게 type casting한다<br>