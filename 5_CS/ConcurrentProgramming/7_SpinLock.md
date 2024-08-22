- [Introduce](#introduce)
    - [장점](#장점)
    - [단점](#단점)
- [Simple SpinLock Implementation](#simple-spinlock-implementation)

<br>

[ 참고 ](https://en.wikipedia.org/wiki/Spinlock) <br>

# Introduce
`lock 권한을 획득하는 방법`<br>
`SpinLock은 다른 thread가 lock을 보유하고 있을 때, 그 lock을 반환할 때까지 계속 확인하며 기다리는 방법`이다<br>
반복적으로 lock을 획득하려는 시도를 보고 thread가 spinning( 빙빙도는것 )하고 있다고 본다<br>


thread가 실질적인 작업을 하지 않기 때문에 spinlock을 사용하는 것은 `busy waiting( 특정 조건을 만족할 때까지 대기하는 방식 )`이다.<br>

spinlock은 명시적으로 해제될 때까지 유지되지만, 구현에 따라 lock을 유지 중인 thread가 차단되거나 절전 모드로 전환되면 자동으로 해제시킬 수도 있다<br>

### 장점
SpinLock은 `OS의 process re-scheduling이나 context-switching으로 인한 overhead를 방지`하기 때문에 `thread가 짧은 시간 동안만 차단( lock 획득을 대기 )될 가능성이 있는 경우에 효율적`이다<br>

### 단점
thread1이 lock을 유지하는 동안 thread2가 계속 spinning하게 되는데, 이 시간 동안 quantum을 낭비할 가능성이 높다.<br>
즉, `lock을 획득하기 위해 기다리는 행위가 thread를 낭비`시킨다<br>

SpinLock을 구현할 때, `하나의 lock에 여러 thread가 대기할 수 있으므로, race-condition이 발생할 가능성을 고려`해야 한다.<br>


<br>
<br>

# Simple SpinLock Implementation
```c#
class SpinLock
{
  private volatile int _locked = 0; // memory visibility

  public void Acquire()
  {
    // lock을 습득할 때까지 대기
    while (true) {
      int expected = 0;
      int desire = 1;
      if (Interlocked.CompareExchanged(ref _locked, desired, expected) == expected)
        break;
    }
  }

  public void Release()
  {
    _locked = 0;
  }
}

// -----

static SpinLock _lock = new SpinLock();
static void Func()
{
  _lock.Acquire();
  num++;
  _lock.Release();
}
```
lock을 습득하는 기능이 핵심이다.<br>
CompareExchanged()와 같은 `Compare-And-Swap( CAS ) 연산을 사용해서 memory visibility를 지킬 수 있다`<br>


```c#
public void Acquire()
{
  while (true) {
    int expected = 0;
    int desired = 1;
    int original = Interlocked.Exchanged(ref _locked, desired);
    if (original == expected) break;
  }
}
```
위 코드처럼 작성할 수 있지만, 일반적인 방법은 아니다.<br>
여기서 의문은 `original의 값을 비교하는 것은 왜 안전 장치를 마련하지 않았는지`이다<br>

`original은 stack에 있는 값`이다. 각 thread의 영역에 있는 값이기 때문에 race condition이 발생할 일이 없기 때문이다.<br>