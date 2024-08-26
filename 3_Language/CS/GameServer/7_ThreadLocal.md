- [Introduce](#introduce)
    - [간단한 사용 예시](#간단한-사용-예시)
  - [Constructor](#constructor)
  - [Properties](#properties)
    - [1. IsValueCreated](#1-isvaluecreated)
    - [2. Value](#2-value)
  - [Methods](#methods)
    - [1. Dispose()](#1-dispose)

<br>

# Introduce
[Thread Local Storage 개념](/5_CS/ConcurrentProgramming/9_ThreadLocalStorage.md)<br>
[ c# reference - ThreadLocal<T> ](https://learn.microsoft.com/ko-kr/dotnet/api/system.threading.threadlocal-1?view=net-8.0)<br>

ThreadLocal은 thread 별로 데이터를 관리하기 때문에 thread가 많아질수록 memory 사용량이 증가할 수 있다<br>

### 간단한 사용 예시
```c#
using System.Threading;

class ThreadLocalDemo
{
  static void Main()
  {
    ThreadLocal<string> ThreadName = new ThreadLocal<string>(() => {
      return $"Thread {Thread.CurrentThread.ManagedThreadId}";
    });

    Action action = () => {
      bool repeat = ThreadName.IsValueCreated;
      Console.WriteLine($"ThreadName = {ThreadName.Value} {(repeat ? "(repeat)" : "")}");
    };

    Parallel.Invoke(action, action, action, action, action, action);
    ThreadName.Dispose();
  }
}
```

<br>

## Constructor
```c#
ThreadLocal<T>();                   // 1.
ThreadLocal<T>(Boolean);            // 2.
ThreadLocal<T>(Func<T>);            // 3.
ThreadLocal<T>(Func<T>, Boolean);   // 4.
```

1. default 값으로 false가 들어간다.
2. `모든 thread에서 모든 값에 access 할 수 있는지 여부를 결정`한다
   - `true`: thread instance가 종료된 후에도 ThreadLocal.Values를 통해 사용할 수 있다
3. `Func<T>는 초기화 함수로써, lazy initialization 기법`을 이용한다
   - `특정 thread에서 처음으로 ThreadLocal.Value 호출되면 Func<T>를 이용하여 값을 생성`한다
   - 해당 thread의 `ThreadLocal에 한 번 초기화되면 다시 Func<T>가 호출되지 않는다`.
4. 2번과 3번이 합쳐진 constructor이다

<br>

## Properties
### 1. IsValueCreated
`현재 thread의 ThreadLocal.Value가 초기화 됐는지 확인`한다<br>

### 2. Value
`현재 thread의 ThreadLocal의 값을 가져오거나 세팅`한다<br>

<br>

## Methods
### 1. Dispose()
`ThreadLocal 객체를 사용할 수 없는 상태로 만들고, memory와 resources를 정리`한다<br>
이는 `해당 객체가 관리하는 모든 thread의 데이터와 관련된 resources가 해제`된다는 뜻이다<br>

ThreadLocal<T> 사용이 끝나면 Dispose()를 호출해야 한다<br>
GC가 더 이상 사용되지 않는 객체를 memory에서 회수하기 전에, 객체가 차지하던 resource는 직접 해제해야 한다.<br>
ThreadLocal은 내부적으로 많은 resource를 사용하기 때문에 이를 Dispose()로 해제하는 것이다<br>