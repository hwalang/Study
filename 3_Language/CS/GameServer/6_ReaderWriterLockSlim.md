- [Introduce](#introduce)
    - [주의점](#주의점)
- [Lock States](#lock-states)
    - [1. Not Entered](#1-not-entered)
    - [2. Read](#2-read)
    - [3. Upgrade( 업그레이드 가능 모드 )](#3-upgrade-업그레이드-가능-모드-)
    - [4. Write](#4-write)
- [예시](#예시)

<br>

[ 참고 - System.Threading.ReaderWriterLockSlim class ](https://learn.microsoft.com/en-us/dotnet/fundamentals/runtime-libraries/system-threading-readerwriterlockslim)<br>

# Introduce
shared resources에 접근을 관리하는 lock을 나타내며, `read 작업에는 여러 thread를 허용하고 write 작업에는 하나의 thread만 허용`한다.<br>

memory read 작업이 99%로 이뤄지고, memory write 작업은 1%만 수행하는 기능에 적합한 lock이다<br>

`내부적으로 DeadLock을 방지하는 기능`이 있다<br>

### 주의점
ReaderWriterLockSlim은 Thread 중단에 안전하지 않다<br>
.NET에서는 `Thread.Abort()를 사용해서 thread를 중단( .NET5이후 안전한 중단 기능이 생김 )`시킬 수 있다<br>
ReaderWriterLockSlim에서 thread가 강제로 중단되는 경우, 3가지 문제가 발생할 수 있다<br>

1. `lock이 해제되지 않아 다른 thread들이 계속 대기 상태`에 빠질 수 있다. 이는 `DeadLock`을 유발한다.
2. Dispose()와 같은 thread resource 정리 작업이 수행되지 않아 `resource leak가 발생`한다
3. lock으로 보호하는 데이터가 thread 중단으로 인해 비정상적인 상태로 남을 수 있다. `데이터 무결성 문제`가 발생한다.

ReaderWriterLockSlim는 `thread가 정상적으로 lock을 획득하고 해제하는 것을 가정하고 설계`됐다.<br>

<br>

# Lock States
ReaderWriterLockSlim은 4가지 상태를 가진다<br>

### 1. Not Entered
thread가 lock에 진입하지 않았거나, 모든 thread가 잠금에서 빠져나온 상태이다<br>

### 2. Read
하나 이상의 thread가 protected resource에 대한 read access를 위해 lock 상태에 진입한다<br>

### 3. Upgrade( 업그레이드 가능 모드 )
하나의 thread가 write access로 업그레이드 할 수 있는 option이 있는 read access를 위한 lock에 진입한다.<br>
이때 한 번에 하나의 thread만 upgrade option이 있는 lock에 들어갈 수 있다.<br>

### 4. Write
하나의 thread가 protected resource에 write access를 위해 lock 상태에 진입한다<br>
해당 thread는 lock을 독점적으로 소유한다<br>


<br>
<br>

# 예시
```c#
public class SynchronizedCache
{
  private ReaderWriterLockSlim cacheLock = new ReaderWriterLockSlim();
  private Dictionary<int, string> innerCache = new Dictionary<int, string>();

  public int Count { get => innerCache.Count; }

  public string Read(int key)
  {
    cacheLock.EnterReadLock();
    try {
      return innerCache[key];
    }
    finally {
      cacheLock.ExitReadLock();
    }
  }

  public void Add(int key, string value)
  {
    cacheLock.EnterWriteLock();
    try {
      innerCache.Add(key, value);
    }
    finally {
      cacheLock.ExitWriteLock();
    }
  }

  // Status Enum { Added, Updated, Unchanged }
  public Status AddOrUpdate(int key, string value)
  {
    cacheLock.EnterUpgradeableReadLock();
    try
    {
      string result = null;
      if (innerCache.TryGetValue(key, out result)) {
        if (result == value) return Status.Unchanged;
        else {
          cacheLock.EnterWriteLock();
          try {
            innerCache[key] = value;
          }
          finally {
            cacheLock.ExitWriteLock();
          }
          return Status.Updated;
        }
      }
      else
      {
        cacheLock.EnterWriteLock();
        try {
          innerCache.Add(key, value);
        }
        finally {
          cacheLock.ExitWriteLock();
        }
        return Status.Added;
      }
    }
    finally
    {
      cacheLock.ExitUpgradeableReadLock();
    }
  }

  public void Delete(int key)
  {
    cacheLock.EnterWriteLock();
    try {
      innerCache.Remove(key);
    }
    finally {
      cacheLock.ExitWriteLock();
    }
  }

  ~SynchronizedCache() { if (cacheLock != null) cacheLock.Dispose(); }
}
```
Read, Upgrade, Write 상태를 모두 사용해본 예시이다<br>