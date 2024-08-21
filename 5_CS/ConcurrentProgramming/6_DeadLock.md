- [Introduce](#introduce)
- [DeadLock( 교착 상태 )](#deadlock-교착-상태-)
  - [1. 영원히 Lock이 된 경우](#1-영원히-lock이-된-경우)
  - [2. Lock에 cycle이 생긴 경우](#2-lock에-cycle이-생긴-경우)
  - [3. Lock Wrapper Class](#3-lock-wrapper-class)

<br>

# Introduce
Lock과 관련된 문제를 살펴본다.<br>

<br>
<br>

# DeadLock( 교착 상태 )
`call stack 추적으로 각 thread가 어디서 waiting하고 있는지 파악`할 수 있다<br>
일반적으로 개발 단계에서는 발생하지 않지만, 배포했을 때 문제가 발생한다.<br>

<br>

## 1. 영원히 Lock이 된 경우
```c#
static object _lockObj = new object();
static int num = 0;

Monitor.Enter(_lockObj);

num / 0   // exception
return;   // exit

Monitor.Exit(_lockObj);
```
위 코드는 _lockObj를 이용하여 lock을 건 상황에서 예상치 못한 상황이나 `lock을 해제하지 않고 빠져나오는 경우`를 나타낸다.<br>
만약 `해당 코드에 접근한 다른 thread가 있는 경우, 영원히 기다리는 상황이 발생`한다<br>

이런 문제는 `lock() 문법을 사용함으로써 간단히 해결`할 수 있다<br>

<br>

## 2. Lock에 cycle이 생긴 경우
```c#
class SessionManager
{
  static object _lock = new object();

  public static void TestSession() { lock (_lock) { } }
  public static void TestSession2() { lock (_lock) { UserManager.TestUser2(); } }
}

class UserManager
{
  static object _lock = new object();

  public static void TestUser() { lock (_lock) { SessionManager.TestSession(); } }
  public static void TestUser2() { lock (_lock) { } }
}
```
<br>

| Thread 1 Task | Thread 2 Task |
|:---:|:---:|
| UserManager.TestUser() 호출 | SessionManager.TestSession2() 호출 |
| UserManager._lock 획득 | SessionManager._lock 획득 |
| SessionManager.TestSession() 호출 | UserManager.TestUser2() 호출 |
| SessionManager._lock 획득 실패 후 대기 | UserManager._lock 획득 실패 후 대기 |

<br>
Thread 1과 Thread 2는 각자 _lock을 소유하고 있으며, 이로 인해 `서로 상대방이 보유한 lock을 기다리며 DeadLock이 발생`한다.<br>

<br>

## 3. Lock Wrapper Class
DeadLock을 피하기 위해서 lock을 그대로 사용하지 않고, Wrapper Class를 만들어서 이를 활용하는 방식으로 사용할 수 있다<br>
하지만 DeadLock은 완전히 방지할 수 없다<br>
```c#
class LockWrapper
{
  int id;     // 각 클래스가 사용하는 lock의 id
}
```
