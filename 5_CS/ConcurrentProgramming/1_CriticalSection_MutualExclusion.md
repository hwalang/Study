
- [Introduce](#introduce)
- [Critical Section](#critical-section)
    - [critical section의 필요성](#critical-section의-필요성)
- [Mutual Exclusion](#mutual-exclusion)
    - [동작 방식](#동작-방식)

<br>

# Introduce
동시성 프로그래밍에서 shared resources에 대한 동시 access는 예상치 못한 오류나 잘못된 동작으로 이어진다<br>

따라서 shared resources에 access하는 프로그램 기능은 동시 access를 방지해야 한다<br>

<br>
<br>

# Critical Section
`동시성 프로그래밍에서 shared resources에 access하는 영역`에 대해 critical section 또는 critical region이라 한다<br>

이 영역에는 한 번에 둘 이상의 process 또는 thread가 접근할 수 없고, 첫 process( thread )가 critical section을 벗어날 때까지 다른 process는 일시 중지시킨다<br>

### critical section의 필요성
동일한 변수나 다른 resources에 대해 읽거나 쓰는 작업을 수행하는데, 이는 작업 발생 순서에 따라 결과가 달라진다<br>
```cpp
// Process A
b = x + 5;

// Process B
x = 3 + z;
```
위 코드에서 process A가 x를 읽는 작업과 process B가 x에 쓰는 작업이 동시에 발생하면, process B가 x memory에 데이터를 쓴 시점 전후에 따라 process A가 읽어들이는 x의 값이 달라진다<br>

이처럼 `변수 x는 critical section으로써 process A가 x에 접근할 때, 다른 process가 접근하지 못하도록 보호`해야 한다<br>

<br>
<br>

# Mutual Exclusion
Mutual Exclusion은 `resources를 공유할 때 발생하는 문제를 해결하기 위해 도입된 개념`이다<br>

`critical section에 이미 하나의 thread가 작업 중이라면, 다른 thread는 해당 영역에 접근하지 않아야 한다는 요구 사항`이다<br>

### 동작 방식
Mutual Exclusion Algorithm의 동작 방식은 간단하다<br>

1. process A가 이미 shared resources에 대해 쓰기 작업을 수행
2. 다른 process가 해당 resources에 대해 access 또는 write를 막음
3. process A가 해당 resources에 대한 쓰기를 완료 후 다른 process가 읽고 쓸 수 있도록 lock을 해제

