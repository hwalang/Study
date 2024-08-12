# Abstract class VS Interface

## 1. abstract class
![alt text](Images/ab_interface/abstract_concrete.png)
concrete class는 abstract class를 상속 받아서 기능을 구현한다.</br>
Light와 Door, NPC는 Switchable이다.( is-a 관계 )</br>

</br>

### 1.1. inheritance의 문제점을 해결하기 위한 c#의 설계
![alt text](Images/ab_interface/inheritance_problem.png)
cpp은 다중 상속이 가능하지만, C class에서 Func() 함수를 호출했을 때, A, B1, B2 중에서 어떤 Func()를 상속받는지 판단할 수 없다.</br>

이 때문에 c#은 하나의 abstract class만 상속 받을 수 있다.</br>

### 1.2. is-a, has-a
![alt text](Images/ab_interface/result.png)
NPC는 Robot이다.</br>
NPC는 Switchable 할 수 있는 Robot이다.</br>

## 2. 차이점
| abstract class | interface |
| :---: | :---: |
| method를 완전히 또는 일부만 구현 | method 선언만 가능 |
| field 선언 및 사용 | method, property 선언만 가능( field 제외 ) |
| static 멤버 가능 | static 멤버 불가 |
| constructor 가능 | constructor 불가 |
| 모든 access modifier 가능 | public로만 취급 및 가능 |
