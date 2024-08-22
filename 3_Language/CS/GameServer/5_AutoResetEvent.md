- [Introduce](#introduce)
- [사용법](#사용법)
  - [signal](#signal)
    - [1. Signaled](#1-signaled)
    - [2. Non-Signaled](#2-non-signaled)
  - [WaitOne()](#waitone)
  - [Set()](#set)
- [예제](#예제)

<br>

# Introduce
thread synchronization( 동기화 )를 위해 사용한다<br>
`하나의 thread가 다른 thread에게 작업이 끝났으니 이제 접근해도 좋다는 신호를 보내는데 사용`한다<br>

이러한 작업을 `Thread Interaction, or Thread signaling`이라 부르며, `thread가 계속 진행하기 위해 하나 이상의 thread에서 notification 또는 signal을 기다려야 한다`<br>

Thread Interaction한 기능을 c#에서는 EventWaitHandle, AutoResetEvent, ManualResetEvent, ManualResetEventSlim으로 제공한다<br>

이러한 Event는 OS의 Kernel에 접근하기 때문에 속도가 느리다<br>


<br>
<br>

# 사용법

## signal
```c#
public AutoResetEvent (bool initialState);
```
AutoResetEvent는 2가지 상태인, `signal이 있는 상태와 없는 상태를 가진다`<br>
`signal은 thread가 작업을 진행해도 되는지를 결정`한다<br>

### 1. Signaled
signaled state는 `특정 thread가 WaitOne()을 호출할 때, 대기하지 않고 바로 통과하여 다음 작업을 수행할 수 있는 상태`를 말한다<br>

### 2. Non-Signaled
`특정 thread가 WaitOne()을 호출하면 signal을 받을 때까지 대기`한다<br>

<br>

## WaitOne()
`thread는 WaitOne()을 호출하여 signal을 기다린다`<br>
만약 AutoResetEvent가 non-signaled인 경우, AutoResetEvent.Set()이 호출될 때까지 thread가 차단된다<br>

한 번 signal을 보내서 하나의 thread가 깨어나면, 자동으로 다시 닫힌다( Reset() )<br>
즉, `WaitOne() 메소드 내부에서 AutoResetEvent.Reset()이 포함`된다<br>

## Set()
AutoResetEvent.Set()을 호출하면 WaitOne()으로 `대기 중인 하나의 thread를 해제하도록 signal을 보낸다`<br>

<br>
<br>

# 예제
```c#
static AutoResetEvent autoEvent = new AutoResetEvent(false);  // non-signaled

static void Main()
{
  Thread thread = new Thread(Worker);
  thread.Start();

  Thread.Sleep(1000);

  autoEvent.Set();    // thread가 WaitOne()으로 대기 중이므로 Set()으로 signal을 보냄

  thread.Join();
}

static void Worker()
{
  autoEvent.WaitOne();  // signal 대기
}
```