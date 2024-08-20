- [Thread](#thread)
    - [1. BackGround Thread VS ForeGround Thread](#1-background-thread-vs-foreground-thread)
      - [`1.1.` BackGround Thread](#11-background-thread)
      - [`1.2.` ForeGround Thread](#12-foreground-thread)
      - [`1.3.` IsBackGround](#13-isbackground)
    - [2. Thread Constructors](#2-thread-constructors)
    - [3. `Join`](#3-join)
      - [`3.1.` Exception : Unstarted State, Infinitly Waiting](#31-exception--unstarted-state-infinitly-waiting)
- [Thread Pooling](#thread-pooling)
    - [1. `Thread Pool 특징`](#1-thread-pool-특징)
    - [2. `QueueUserWorkItem(callback method)`](#2-queueuserworkitemcallback-method)
    - [3. `QueueUserWorkItem(callback method, Object)`](#3-queueuserworkitemcallback-method-object)
- [Task](#task)
    - [1. 특징](#1-특징)
    - [2. TaskCreationOptions](#2-taskcreationoptions)
    - [3. Start VS Run](#3-start-vs-run)
      - [`3.1.` Start](#31-start)
      - [`3.2.` Run : 비동기 대기, blocking](#32-run--비동기-대기-blocking)

<br>
<br>

**`C#에서는 Thread를 직접 관리하지 않고 ThreadPool 또는 Task를 이용`한다.**<br>
직접 Thread를 사용하는 것은 legacy이거나 MMO 등 특정 상황에 알맞은 방식이다.<br>
보통 C#에서는 ThreadPool을 이용해 직접 Thread를 관리하지 않고, 일감만 등록해서 분배 실행하는 식으로 작업한다.<br>

<br>
<br>

# Thread
```c#
#include System.Threading;

class Program
{
  static void OtherThread()
  {
    whiel (true)
      Console.WriteLine("Hello World");
  }

  static void Main(string[] args)
  {
    Thead t = new Thread(OtherThread);
    t.Name = "Thread Name";
    t.IsBackGround = true;
    t.Start();

    Console.WriteLine("Before Join");
    t.Join();
    Console.WriteLine("After Join");
  }
}
```

### 1. BackGround Thread VS ForeGround Thread
#### `1.1.` BackGround Thread
BackGround Thread는 process의 종료를 막지 못한다.<br>
`process에 속한 모든 ForeGround Thread가 종료되면 process가 종료되고, 나머지 BackGround Thread는 수행 중간에 종료`된다.<br>

`ThreadPool` class는 BG Thread이다.<br>

<br>

#### `1.2.` ForeGround Thread
`Main Application Thread와 Thread class는 기본적으로 ForeGround Thread`이다.<br>

#### `1.3.` IsBackGround
Thread class를 통해 기능을 배정받은 Thread Instance는 기본적으로 false( ForeGround Thread )이다.<br>

--- 
### 2. Thread Constructors
```c#
using System.Threading;

public class Work
{
  public static void Main()
  {
    // 1. static method
    Thread newThread = new Thread(Work.DoWork);
    newThread.Start(42);

    // 2. static method
    Thread newThread = new Thread(new ThreadStart(Work.DoWork));
    newThread.Start(42);


    // 1. instance method
    Work w = new Work();
    newThread = new Thread(w.DoMoreWork);
    newThread.Start("The answer.");

    // 2. instance method
    Work threadWork = new Work();
    Thread newThread = new Thread(new ThreadStart(threadWork.DoWork));
    newThread.Start("The answer.");
  }

  public static void DoWork(object data)
  {
    Console.WriteLine("Static thread procedure. Data = '{0}'", data);
  }

  public void DoMoreWork(object data)
  {
    Console.WriteLine("Instance thread procedure. Data = '{0}'", data);
  }
}
```
static method와 instance method를 할당하고 인자를 넘겨주는 방식으로 Thread를 생성한다.<br>

`Visual Basic 환경`에서는 ThreadStart를 Thread 생성자에서 자동으로 호출하기 때문에 생략해도 된다.<br>

---

### 3. `Join`
`Join()` Instance가 나타내는 thread가 종료될 때까지 `calling thread를 차단`한다.<br>
`Join(int 또는 TimeSpan)`은 Instance가 나타내는 `thread가 종료` 혹은 `지정된 시간`까지 calling thread를 차단한다.<br>

calling thread( method를 호출하는 thread )를 차단하는 synchronization method이다.<br>
`thread가 종료됐는지 확인할 때 유용한 기능`이다.<br>

<br>

#### `3.1.` Exception : Unstarted State, Infinitly Waiting
```c#
static Thread thread1, thread2;

// static void Main()
thread1 = new Thread(ThreadPoc);
thread1.Name = "Thread1";
thread1.Start();

thread2 = new Thread(ThreadPoc);
thread2.Name = "Thread2";
thread2.Start();

static void ThreadPoc()
{
  Console.WriteLine("\nCurrent Thread: {0}", Thread.CurrentThread.Name);
  if (Thread.CurrentThread.Name == "Thread1" && thread2.ThreadState != ThreadState.Unstarted) {
    thread2.Join();
  }

  Thread.Sleep(4000);
  Console.WriteLine("\nCurrent Thread: {0}", Thread.CurrentThread.Name);
  Console.WriteLine("Thread1: {0}", thread1.ThreadState);
  Console.WriteLine("Thread2: {0}", thread2.ThreadState);
}
```
`Unstarted state한 thread에 적용하면 에러`가 발생한다.<br>

`현재 Thread에서 현재 Thread에 대한 Join()를 호출하면 무한정 대기`하게 된다.<br>


<br>
<br>

# Thread Pooling
```c#
#include System.Threading;

public static void Main()
{
  ThreadPool.QueueUserWorkItem(ThreadProc);   // stateInfo default = null
  Thread.Sleep(1000);

  Console.WriteLine("Main thread exits.");
}

static void ThreadProc(Object stateInfo)
{
  Console.WriteLine("Hello from the thread pool");
}
```
### 1. `Thread Pool 특징`
1. `BackGround Thread`<br>
2. `Object Pooling과 비슷한 개념`으로써 thread pool을 제공한다.<br>
3. `process 당 하나의 thread pool이 존재`한다.<br>
4. process는 `GetMaxThreads()를 호출하여 thread 수를 확인`할 수 있다.<br>
5. `각 thread는 기본 stack 크기를 사용`하고 기본 우선순위를 적용한다.<br>
6. `thread pool을 최대치까지 사용하면`, 추가 thread를 생성하거나 일부 작업이 완료될 때까지 기다린다.

thread pool은 system thread pool 중에서 대기 상태인 thread를 application에 제공하여 thread를 효율적으로 사용할 수 있다.<br>
`현재 작업에 맞춰서 thread pool 크기를 자동으로 줄이거나 키운다`.<br>
때문에 CPU Core와 Thread 개수를 맞추는 작업을 하지 않아도 된다.<br>

<br>

### 2. `QueueUserWorkItem(callback method)`
실행을 위해 method를 queue에 넣어 대기하고, thread pool에서 thread가 준비되면 method를 실행시킨다.<br>
thread가 호출할 method 또는 delegate에 대한 참조를 인자로 받으며, Queue에 추가된 이후에는 취소할 수 없다.<br>

`Task 정보를 전달할 수 없기 때문에 ThreadProc method에서 사용할 수 있는 정보는 method가 속한 객체( class, instance )로 제한`된다.<br>

<br>

### 3. `QueueUserWorkItem(callback method, Object)`
method를 실행 대기열에 추가하고, `method에서 사용할 데이터가 포함된 object를 지정`한다.<br>

```c#
public class Other
{
  public void ThreadPoolCallback(Object threadContext)
  {
    int threadIndex = (int)threadContext;
    // TODO
  }
}

public class Example
{
  static void Main()
  {
    Other other = new Other();
    ThreadPool.QueueUserWorkItem(other.ThreadPoolCallback, 10);
    Thread.Sleep(1000);
  }
}
```

<br>
<br>

# Task
`Task`는 thread pool에서 thread를 받아와 실행된다<br>

### 1. 특징
`Task 객체는 한 번만 실행`될 수 있다.<br>
Task 객체를 여러 번 실행하려고 하면 예외가 발생한다.<br>

Task는 내부적으로 상태( running, complete, cancel 등 )를 가진다. 한 번 작업이 시작되면 해당 Task 객체는 그 상태를 유지하고, 해당 상태에 따라 동작한다.<br>
`다시 Task 객체를 재사용하여 작업하려고 하면, 이미 완료됐거나 진행 중이기 때문에 Exception이 발생`한다.<br>

Task가 생성되면 ready state로 존재한다.<br>

<br>

### 2. TaskCreationOptions
```c#
using System.Threading.Tasks;

for (int i = 0; i < 5; ++i) {
  Task t = new Task(() => { while (true) { } }, TaskCreationOptions.LongRunning);
  t.Start();
}
```
Task는 ThreadPool에서 관리되지만 `특정 Option을 활용하여 오래 걸리는 작업을 한다는 것을 알려줄 수 있다`<br>
그러면 ThreadPool이 아닌 별도의 Thread에서 관리할 수 있다<br>

위 코드에서 OtherThread 작업은 Thread를 할당받아 정상적으로 동작한다.<br>
TaskCreationOptions.LongRunning을 인자로 전달하지 않으면 남은 thread가 없어서 프로그램이 멈춘다.<br>

<br>

### 3. Start VS Run

#### `3.1.` Start
`비동기 함수가 아니다`.<br>
단순히 Task를 thread pool에 queue로 넣고, 작업이 실행되도록 하는 method이다.<br>

```c#
public static void Main()
{
  // Task 생성
  Task task = new Task( () => {
    Console.WriteLine("Task {0} running on thread {1}",
    Task.CurrentId, Thread.CurrentThread.ManagedThreadId);
    for (int i = 1; i <= 10; ++i)
      Console.WriteLine("Iteration {0}", i);
  });

  ...

  // Task 실행
  task.Start();
  task.Wait();
}
```
`Task의 생성과 실행을 분리해서 사용할 때`, Start() method를 사용한다.<br>
Task를 바로 실행하지 않고, 특정 조건에서 실행할 필요가 있을 수 있다.<br>

Start()는 Run()과는 다르게 `즉시 반환되므로 작업이 완료될 때까지 기다리지 않는다`.<br>

비동기 함수가 아니기 때문에 await를 사용할 수 없는 대신, `Wait()를 통해 작업이 완료될 때까지 기다린다`.<br>

<br>

#### `3.2.` Run : 비동기 대기, blocking
`비동기 함수`이다.<br>
```c#
static async Task Main(string[] args)
{
  await Task.Run( () => {
    Console.WriteLine("Task is Running...");
  });
}
```
일반적으로 Run() method를 사용하는 것이 간편하고 권장한다.<br>
Run()은 `Task를 생성하면서 동시에 실행`한다.<br>

`Task가 완료될 때까지 Main Thread가 blocking되지 않도록 비동기로 대기`한다.<br>

1. 비동기 대기란, Main Thread가 해당 작업을 기다리면서 다른 작업을 수행할 수 있다.<br>
2. `blocking`이란, 어떤 작업이 완료될 때까지 프로그램의 실행 흐름( 특정 thread )이 멈추는 것이다.
   - blocking이 발생하면 해당 작업이 완료되기 전까지, 다른 작업을 수행할 수 없다.

