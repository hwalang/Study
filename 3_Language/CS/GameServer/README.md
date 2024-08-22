- [Index](#index)
- [Synchronization](#synchronization)
    - [1. lock( 또는 Monitor )](#1-lock-또는-monitor-)
    - [2. SpinLock](#2-spinlock)
    - [3. ReaderWriterLockSlim](#3-readerwriterlockslim)
    - [4. AutoResetEvent](#4-autoresetevent)

<br>

# Index
- [Settings](1_Settings.md) : GameServer 구현을 위한 세팅 모음
- [Compiler Optimization](2_CompilerOptimization.md) : 멀티 쓰레드 환경에서 컴파일 최적화( Release 환경 )로 발생하는 문제와 해결하는 방법
- [Thread, ThreadPool, Task](2_Thread.md) 
- [Lock](4_Lock.md) : Lock 사용법, System.Threading.Lock 객체
- [AutoResetEvent](5_AutoResetEvent.md) : signal event
- [ReaderWrtierLockSlim](6_ReaderWriterLockSlim.md)

<br>

# Synchronization 
thread synchronization을 위한 4가지 방식이 존재한다<br>

### 1. lock( 또는 Monitor )
`critical section 보호`를 위해 사용한다<br>

### 2. SpinLock
`보호하는 critical section이 짧고 이를 획득하기에 짧은 기간이 걸릴 때 사용`한다<br>
critical section이 매우 짧아 `context-switching의 overhead가 성능 저하를 일으킬 때 사용`한다<br>

### 3. ReaderWriterLockSlim
`critical section 보호`를 위해 사용하지만, `Read 작업이 많고 Write 작업이 상대적으로 적은 상황에 유용`하다<br>
cache 구조를 구현할 때 유용하다<br>

### 4. AutoResetEvent
`thread 간의 event 기반 동기화`가 필요할 때 사용한다<br>