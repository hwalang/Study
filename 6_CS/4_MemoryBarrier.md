- [Introduction](#introduction)
  - [필요한 이유](#필요한-이유)
  - [필요 없는 경우](#필요-없는-경우)
- [예시 1](#예시-1)
    - [발생하는 문제](#발생하는-문제)
    - [memory barrier의 적절한 위치](#memory-barrier의-적절한-위치)
- [예시 2 : Memory Barrier from C#](#예시-2--memory-barrier-from-c)
  - [1. Full Memory Barrier](#1-full-memory-barrier)
  - [2. Memory Visibility](#2-memory-visibility)
  - [3. 일반적으로 Memory Barrier를 명시적으로 사용하지 않는다](#3-일반적으로-memory-barrier를-명시적으로-사용하지-않는다)
- [예시 3 : memory visiblity](#예시-3--memory-visiblity)

<br>

# Introduction
memory barrier는 membar, memory fence, fence instruction로 알려져 있다.<br>
memory barrier는 `CPU 또는 Compiler가 barrier 명령어 전후에 실행되는 memory 연산( load / store )을 순서에 맞게 실행하도록 강제`한다.<br>
`barrier 이전에 나온 연산이 barrier 이후에 나온 연산보다 먼저 실행되는 것을 보장`한다.<br>

`memory visibility를 보장`한다.<br>
이는 2번 예제를 통해 설명한다.<br>

<br>

## 필요한 이유
`대부분의 최신 CPU는 성능 최적화를 수행하는데, 이는 out-of-order( 순서를 벗어난 ) 실행을 초래`할 수 있다.<br>
memory operation( load / store )의 순서 변경은 single thread 환경에서는 눈에 띄지 않지만, multi thread 환경과 같은 동시 실행 프로그램에서 예상치 못한 행동을 할 수 있다.<br>

multi-thread 환경처럼 `공유 memory에서 작동하는 저수준 프로그램을 구현할 때 사용`한다.<br>
single process( multi-thread가 데이터 영역을 공유하는 상황 )에서 실행되는 두 개 이상의 thread에서 적용한다.<br>

<br>

## 필요 없는 경우
`single thread 환경`에서의 HW는 개발자가 지정한 순서( program order )에 따라 모든 memory operation이 수행된 것처럼 행동한다.<br>
`서로 다른 process`는 memory 공간을 공유하지 않는다.<br>

<br>
<br>

# 예시 1
```c#
static int x = 0;
static int f = 0;

// thread1
{
  while (f == 0);
  // Memory fence requirement here( Thread.MemoryBarrier(); )
  Console.WriteLine(x);
}

// thread2
{
  x = 42;
  // Memory fence requirement here( Thread.MemoryBarrier(); )
  f = 1;
}
```
memory x와 f는 처음에 0 값을 가진다.<br>

thread1은 f 값이 0인 동안 반복한 다음 x 값을 출력( load x )한다.<br>
thread2는 x에 42를 저장( store x )한 다음에 f에 1을 저장( store f )한다.<br>

### 발생하는 문제
Console에서 출력되는 값은 항상 42를 예상하지만, thread2의 memory operation의 순서가 다르게 실행되면, f가 x보다 먼저 수정될 수 있기 때문에 0을 출력하는 경우가 발생한다.<br>

마찬가지로 thread1의 load operation이 순서와 다르게 실행하면, f를 확인하기 전에 x를 읽는 상황이 발생한다.<br>

이를 방지하기 위해서 memory barrier를 적절한 위치에 삽입해야 한다.<br>

### memory barrier의 적절한 위치
```c#
`prepare data` for a hardware module
// Memory Barrier
trigger the hardware module to process the data
```
memory에 data가 준비된 이후에 data와 관련된 작업을 수행한다.<br>

<br>
<br>

# 예시 2 : Memory Barrier from C#

## 1. Full Memory Barrier
```c#
internal class Program
{
  static int x = 0;
  static int y = 0;
  static int result1 = 0;
  static int result2 = 0;

  static void Thread_1()
  {
    y = 1;          // Store y
    Thread.MemoryBarrier();
    result1 = x;    // Load x
  }

  static void Thread_2()
  {
    x = 1;          // Store x
    Thread.MemoryBarrier();
    result2 = y;    // Load y
  }

  static void Main(string[] args)
  {
    int count = 0;
    while (true) {
      ++count;
      x = y = result1 = result2 = 0;

      Task task1 = new Task(Thread_1);
      Task task2 = new Task(Thread_2);
      task1.Start();
      task2.Start();

      Task.WaitAll(task1, task2);

      if (result1 == 0 && result2 == 0)
        break;
    }
    Console.WriteLine($"{count}에 빠져나옴");
  }
}
```
Full Memory Barrier는 CPU 또는 Compiler의 `Store와 Load의 순서 재배치를 막는다`.<br>
Memory Barrier를 적용하지 않으면, Main Thread의 while문을 빠져나온다.<br>

<br>

## 2. Memory Visibility
Thread.MemoryBarrier()는 코드 순서의 재배치를 막는 역할도 있지만, `이전 작업을 memory에 올리는 역할`도 있다.<br>
y = 1; 이후에 Thread.MemoryBarrier()를 넣었기 때문에 y 값을 memory에 올라갔음을 보장한다.<br>
공유 memory에 올리기 때문에 예상치 못한 값을 load 할 일은 없다.<br>

<br>

## 3. 일반적으로 Memory Barrier를 명시적으로 사용하지 않는다
일반적으로 multi-thread programming에서 사용하는 primitive 기능( volatile, lock, atomic 등 )들은 memory visibility를 적용하기 위해 memory barrier를 내부적으로 사용하고 있다.<br>
때문에 C#, JAVA와 같은 고급 프로그래밍 환경에서는 `memory barrier를 명시적으로 사용할 필요가 없다`.<br>

<br>
<br>

# 예시 3 : memory visiblity
```c#
static int _answer;
static bool _complete;

// store
void A()
{
  _answer = 123;
  Thread.MemoryBarrier();
  _complete = true;
  Thread.MemoryBarrier();
}

// load
void B()
{
  Thread.MemoryBarrier();
  if (_complete) {
    Thread.MemoryBarrier();
    Console.WriteLine(_answer);
  }
}
```
A에서는 마지막에 작성한 이유는 Store 작업으로 끝났기 때문이다.<br>
memory에 저장하는 작업을 했기에 memory visibility를 지키기 위해 barrier를 사용했다.<br>

B에서 처음에 작성한 이유는 Load 작업 전에 memory에 올려두는 것이 안전하기 때문이다.<br>
memory에서 데이터를 가져오기 전에 memory에 올려두는 작업이 필요하다.<br>