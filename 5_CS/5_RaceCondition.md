- [Introduce](#introduce)
- [예시 1 : increase](#예시-1--increase)
- [예시 2 : atomic increase in C#](#예시-2--atomic-increase-in-c)

<br>

# Introduce
같은 시간에 동시에 실행되는 code가 있을 때, race condition이 발생할 수 있다.<br>
특히 `여러 thread가 공유 데이터에 동시에 접근할 때 race condition이 발생`한다.<br>
race condition이 발생함으로써 공유 데이터에 손상이 발생한다.<br>

multi-thread 환경에서 race condition은 상대적인 타이밍에 따라 달라지기 때문에 재현 및 디버깅이 어렵다.<br>

<br>
<br>

# 예시 1 : increase
공유 데이터를 증가시키는 2개의 thread가 있는 경우<br>
```c#
static int num = 0;

static void Func()
{
  for (int i = 0; i < 100000; ++i)
    num++;
}

static void Main()
{
  Task task1 = new Task(Func);
  Task task2 = new Task(Func);

  task1.Start();
  task2.Start();

  Task.WaitAll(task1, task2);

  Console.WriteLine(num);
}
```
예상되는 num의 값은 200000이지만, 실제로는 200000보다 낮은 값이 나온다.<br>
assembly code를 보면 알 수 있는데, 실제로 num++은 3단계로 나눠진다.<br>
```c#
int temp = num;
temp += 1;
num = temp;
```
위처럼 lock 또는 동기화 작업 없이 `task1과 task2가 동시에 num = temp에 접근하면 race condition이 발생`한다.<br>

아래는 위 코드의 진행 과정을 표로 나타낸다.<br>

|Thread1|Thread2||num value|
|:---:|:---:|:---:|:---:|
|read value| | &larr; |0|
||read value| &larr; |0|
|increase value|| |0|
||increase value| |0|
|write back| | &rarr; |1|
||write back| &rarr; |1|

이 경우에는 num은 2가 아니라 1이다.<br>
이는 `한 번에 하나의 thread만 memory에 접근할 수 있도록 보장하지 않아서 생긴 문제`이다.<br>

<br>
<br>

# 예시 2 : atomic increase in C#
`atomic( 원자성, 더 이상 쪼개지지 않음 ) operation을 이용`한다.<br>
원래 num++ 작업은 3가지 순서로 동작됐지만, atomic을 보장하여 이 3가지 동작을 수행하는 동안 다른 thread가 접근하지 못하게 막는다.<br>
```c#
static void Func()
{
  for (int i = 0; i < 100000; ++i)
    int result = Interlocked.Increment(ref num);
}
```
Interlocked.Increament()와 같은 `atomic operation은 메모리 일관성을 보장하기 위해서 내부적으로 memory barrier를 사용`한다.<br>
barrier는 CPU가 memory 접근 순서를 재배치하거나, `cache를 통해 데이터를 최적화하는 것을 제한`한다.<br>
이로 인해 CPU는 데이터를 cache에서 읽는 대신에 main memory에서 읽고 쓰게 된다.<br>

`성능에 손해( cache 접근 X, memory 접근 O )`가 있지만, 항상 200000이 나온다.<br>


