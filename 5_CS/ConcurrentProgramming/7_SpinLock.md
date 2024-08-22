- [Introduce](#introduce)
    - [장점](#장점)
    - [busy waiting의 단점](#busy-waiting의-단점)
- [Simple SpinLock Implementation](#simple-spinlock-implementation)
- [Exponential Backoff 또는 Randomized Backoff](#exponential-backoff-또는-randomized-backoff)
  - [Exponential( 지수 )](#exponential-지수-)
  - [Randomized](#randomized)
    - [Thread.Sleep(1)](#threadsleep1)
    - [Thread.Sleep(0)](#threadsleep0)
    - [Thread.Yield()](#threadyield)

<br>

[ 참고 ](https://en.wikipedia.org/wiki/Spinlock) <br>

# Introduce
`busy waiting을 사용하여 lock이 available 여부를 반복적으로 확인하는 lock의 한 유형`이다<br>
만약 lock이 not available 하다면, thread가 lock을 사용할 수 있을 때까지 계속 spinning하며 lock을 확인한다<br>

`busy waiting( 특정 조건을 만족할 때까지 대기하는 방식 )`<br>

spinlock은 명시적으로 해제될 때까지 유지되지만, 구현에 따라 lock을 유지 중인 thread가 차단되거나 절전 모드로 전환되면 자동으로 해제시킬 수도 있다<br>

<br>

### 장점
SpinLock은 `OS의 process re-scheduling이나 context-switching으로 인한 overhead를 방지`하기 때문에 `thread가 짧은 시간 동안만 차단( lock 획득을 대기 )될 가능성이 있는 경우에 효율적`이다<br>

### busy waiting의 단점
thread1이 lock을 유지하는 동안 thread2가 계속 spinning하게 되는데, 이 시간 동안 quantum을 낭비할 가능성이 높다.<br>
즉, `thread가 lock을 반복적으로 확인하는 동안 CPU cycle이 낭비`된다<br>

SpinLock을 구현할 때, `하나의 lock에 여러 thread가 대기할 수 있으므로, race-condition이 발생할 가능성을 고려`해야 한다.<br>

이를 해결하기 위해 Exponential Back-off 방식을 사용한다<br>


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

<br>
<br>

# Exponential Backoff 또는 Randomized Backoff
[ 참고 - Spin lock in Modern C++ with atomics, memory barriers and exponential back-off](https://medium.com/@joao_vaz/spin-lock-in-modern-c-with-atomics-memory-barriers-and-exponential-back-off-522798aca817)<br>

여러 thread나 process가 동시에 lock을 획득하려고 할 때, `충돌을 줄이기 위해서 lock을 획득하지 못한 thread가 일정 시간 동안 대기한 후 다시 시도하는 방식`이다<br>

SpinLock에서 busy-waiting으로 인한 resource 낭비를 방지하기 위해 자주 사용한다<br>


## Exponential( 지수 )
`resource를 획득하려는 시도가 실패할 때마다 대기 시간을 점진적으로 늘려가는 방식`이다.<br>
대기 시간은 지수 함수를 이용하여 증가시킨다.<br>
동시성 프로그래밍에서( spin lock )는 lock을 획득하기 위해 loop에서 조건을 반복적으로 확인하는 대신, `lock 획득에 실패할 때마다 thread가 대기하는 시간을 점진적으로 늘린다`<br>

Exponential Backoff는 주로 `network 분야에서 충돌을 줄이기 위해 사용`한다<br>
```cpp
class SpinLock
{
  public:
    SpinLock() {}

    void Acquire() {
      retries = 0;
      while (flag.test_and_set(std::memory_order_acquire)) {
        // spin until the lock is released
        backoff();
        retries++;
      }
    }

    void Release() {
      flag.clear(std::memory_order_release);
    }
  
  private:
    void backoff() {
      const int max_retries = 8;
      if (retries < max_retries) {
        std::this_thread::yield();
      }
      else {
        auto delay = std::chrono::microseconds(1 << (retries - max_retries));
        std::this_thread::sleep_for(delay);
      }
    }

    std::atomic_flag flag = ATOMIC_FLAG_INIT;
    int retires{0};
}
```
여러 thread가 서로 간섭하지 않도록 atomic_flag로 lock을 관리한다<br>

Acquire의 while문에서 lock을 획득한 thread가 이전의 모든 store를 볼 수 있도록 memory barrier를 제공한다<br>

Release의 clear는 lock을 해제한 이후에 lock에서 작업한 write 작업을 모든 thread에게 알리기 위해 memory barrier를 제공한다<br>

<br>

## Randomized
`대기 시간을 무작위`로 설정하는 기법이다<br>
`시스템이 동일한 패턴으로 충돌하는 상황을 피할 수 있도록 돕는다`<br>

Randomized Backoff는 주로 `다른 process나 thread와의 충돌을 방지`하기 위해 사용한다<br>
```c#
public void Acquire()
{
  while (true) {
    int expected = 0;
    int desire = 1;
    if (Interlocked.CompareExchanged(ref _locked, desired, expected) == expected)
      break;
    
    // 3가지 방법 중 하나를 선택
    Thread.Sleep(0);
    Thread.Sleep(1);
    Thread.Yield();
  }
}
```
### Thread.Sleep(1)
OS의 scheduler에게 1ms 쉬고 싶다고 어필한다<br>
OS는 최대한 1ms의 휴식을 맞춰주려고 한다<br>

### Thread.Sleep(0)
현재 thread 보다 우선순위가 낮은 thread에게는 양보하지 않는다.<br>
현재 thread의 우선순위와 같거나 큰 thread가 없으면 다시 현재 thread의 차례로 돌아온다<br>

### Thread.Yield()
우선순위에 관계 없이 현재 실행 가능한 thread가 있으면 양보한다<br>