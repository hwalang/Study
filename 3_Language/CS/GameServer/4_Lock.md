- [Introduce](#introduce)
- [lock 주의점](#lock-주의점)
- [.NET 9 및 C# 13](#net-9-및-c-13)
  - [1. 이전 버전](#1-이전-버전)
  - [2. 최신 버전](#2-최신-버전)
- [예시 1 : lock 내부 로직](#예시-1--lock-내부-로직)

<br>

# Introduce
lock 문은 `지정된 object에 대한 mutual-exclusion( 상호 배제 ) 잠금`을 획득하고, `lock 문을 실행한 뒤에 잠금을 해제`한다.<br>

lock을 획득한 thread는 lock을 다시 획득하거나 해제할 수 있다<br>
`lock문은 한 번에 하나의 thread만 lock문을 실행하도록 보장`한다.<br>

일반적으로 lock은 class 내부에 존재한다<br>

<br>
<br>

# lock 주의점
[참고 - Lock Problem](/5_CS/7_LockProblem.md) <br>
lock 전용 object가 shared resource에 사용된다면, `예상치 못한 문제( DeadLock, Lock Contention )를 초래`할 수 있다<br>
```c#
readonly object _sharedLock = new object(); // System.Threading.Lock 객체도 마찬가지
static int A = 0;
static int B = 0;

lock (_sharedLock) { 
  // A에 대한 작업
}

lock (_sharedLock) {
  // B에 대한 작업
}
```
위 코드는 `하나의 lock object instance`가 thread 간의 `서로 다른 공유 데이터에 대한 접근을 제어`하는데 사용한다.<br>
`현재 A에 대한 작업이 완료되지 않으면, B를 사용하려는 thread는 기다려야 한다`.<br>
이로 인해 불필요한 lock contention( 락 경쟁 )이 발생할 수 있으며, DeadLock도 유발될 수 있다.<br>

따라서 `각 shared resources에 대해 별도의 lock instance를 사용`하는 것이 더 안전하고 효율적이다.<br>

<br>
<br>

# .NET 9 및 C# 13
```c#
readonly object _lock = new object();            // .NET 9 및 C# 13 이전
readonly System.Threading.Lock _lock = new();    // .NET 9 및 C# 13 이후
```
이전 버전에서는 전용 객체 TYPE이 존재하지 않았다.<br>
최신 버전에서는 성능을 위해서 `System.Threading.Lock 유형의 전용 object instance를 사용해서 lock을 걸도록 권장`한다.<br>

<br>

## 1. 이전 버전
```c#
readonly object _lockObj = new object();
lock (_lockObj) {}
```
object type의 객체를 사용해서 lock을 걸었는데, `lock을 사용하는 object는 오직 lock을 걸기 위한 용도로만 사용`했다.<br>

<br>

## 2. 최신 버전
```c#
System.Threading.Lock _lockObj = new();   // readonly가 아닌 경우
object obj = _lockObj;
lock (obj) {}
```
System.Threading.Lock 타입이 다른 타입으로 casting 된 후에 lock에 사용되는 경우, 컴파일러가 경고를 준다.<br>

casting을 통해 원래의 lock 타입의 정보가 손상되기 때문이다<br>
S`ystem.Threading.Lock 타입은 최적화된 락 관리 기능을 제공`하는데, `casting으로 인해 최적화 기능을 활용할 수 없다`.<br>



<br>
<br>

# 예시 1 : lock 내부 로직
아래 코드는 lock이 어떻게 동작하는지 나타내는 코드이다.<br>
```c#
object _lockObj;
bool _lockWasTaken = false;

try {
  System.Threading.Monitor.Enter(_lockObj, ref _lockWasTaken);
  // TODO
}
finally {
  if (_lockWasTaken)
    System.Threading.Monitor.Exit(_lockObj);
}
```
`DeadLock을 방지`하기 위해서 Monitor.Enter()와 Monitor.Exit() 사이에 예상치 못하게 빠져나가거나( exception ), return으로 나가도 `항상 Monitor.Exit()를 실행해서 잠금을 해제하도록 유도`한다.<br>

일반적으로 lock은 object 타입의 참조를 사용되며, ref type이라면 어떤 객체든 사용할 수 있다.<br>

