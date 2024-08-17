- [들어가기 전에](#들어가기-전에)
    - [`process`](#process)
    - [CPU `Scheduling`](#cpu-scheduling)
    - [`Context Switching`](#context-switching)
      - [사용하는 이유](#사용하는-이유)
      - [부작용 1 : Cache Pollution](#부작용-1--cache-pollution)
      - [부작용 2 : overhead](#부작용-2--overhead)
      - [용어 정리](#용어-정리)
    - [`thread`](#thread)
      - [Shared Segment](#shared-segment)
      - [Thread-Specific Segment](#thread-specific-segment)
- [Server에서 적절한 Thread 수](#server에서-적절한-thread-수)
    - [`SW thread를 HW thread로 제한`](#sw-thread를-hw-thread로-제한)
    - [`왕도는 없다`](#왕도는-없다)
  - [과도한 Thread가 성능에 미치는 점](#과도한-thread가-성능에-미치는-점)
    - [Overhead](#overhead)

<br>

# 들어가기 전에

### `process`
`실행 파일이 실행되어 memory에 올라간 instance( program )`이다.<br>
process는 반드시 하나 이상의 thread가 담당한다<br>

process는 CPU를 할당받아 Task를 수행한다.<br>
process는 여러 state( new, ready, waiting, running, terminated )를 가진다.
이때, `CPU가 처리 중인 Process가 I/O를 기다리며 waiting state가 되는 경우`, 아주 유능한 `CPU를 사용하지 못하는 엄청난 비효율이 발생`한다.<br>

CPU가 노는 상황을 방지하기 위해서 CPU Scheduling이 필요하다.<br>

<br>

### CPU `Scheduling`
CPU의 효율성을 높이기 위해 `OS가 CPU를 사용하려고 하는 process 사이의 우선순위를 관리하는 작업`이다<br>
한정된 Resource를 어떤 process에 얼마나 할당하는지 policy를 만드는 것이다<br>

다양한 policy가 존재하지만 개념만 알고 간다.<br>

<br>

### `Context Switching`
`CPU에서 실행 중이던 thread가 다른 thread로 교체`되는 것이다.<br>
이때, `이전/이후 thread는 같거나 다른 process에 속한다`.<br>
OS의 kernel에 의해 수행된다.<br>

<br>

#### 사용하는 이유
1. 여러 process 또는 thread가 `동시에 실행되는 것처럼` 보이기 위함
2. `interrupt가 발생`할 때 context의 일부를 다른 process에 할당
3. `높은 우선순위의 Task를 빠르게 처리`하기 위함
4. 주어진 quantum( time slice ) 시간이 다 된 경우

<br>

#### 부작용 1 : Cache Pollution
`Cache Pollution( 캐시 오염 )이 발생`한다.<br>
Cache memory는 용량이 매우 작기 때문에 모든 process가 같이 사용한다.<br>
Context Switching이 일어나면, 다시 사용할 것이라고 예상하여 cache에 저장한 데이터가 의미 없어진다.<br>
`이전 process에서 실행된 정보`를 가지기 때문이다<br>

때문에 context switching 직후에는 cache에 필요한 데이터가 없기 때문에 memory에 접근해서 데이터를 받아온다. => 성능 저하<br>

<br>

#### 부작용 2 : overhead
overhead( 간접 비용 )은 프로그램 실행 흐름에서 나타난다.<br>
`프로그램 실행 도중에 동떨어진 위치의 코드를 실행시켜야 할 때, 추가적으로 시간, memory, resource가 사용되는 현상`이다.<br>
현재 프로그램과 상관 없는 작업을 하는 것이다.<br>

10초가 걸리는 기능이 간접적인 원인으로 20초가 걸렸다면 overhead는 10초이다.<br>

<br>

#### 용어 정리
`Context` : process, thread의 memory state를 의미한다.<br>
`Process Context Switching`: process1 thread1 => process2 thread2<br>
`Thread Context Switching`: process1 thread1 => process1 thread2<br>

<br>
<br>

### `thread`
`OS에서 CPU가 시간을 할당하는 기본 단위` 또는 `process 내에서 작업을 수행하는 기본 단위`이다<BR>
OS는 Multi-Tasking을 지원하기 위해 여러 process를 동시에 실행하는데, 이 과정에서 각 process는 하나 이상의 thread를 가질 수 있다<br>

OS의 schedulr는 CPU 시간을 효율적으로 사용하기 위해 각 thread에 시간을 분배하여 실행한다<br>
이때 `CPU가 실제로 시간을 할당하는 단위가 thread`이다.<br>

<br>

#### Shared Segment
하나의 process는 여러 개의 thread를 가질 수 있으며, 같은 process에 있는 threads는 code, data, heap 영역을 공유한다.<br>
각 thread는 고유의 stack 영역을 할당받는다.<br>

- `code segment`: process가 실행할 코드
- `data segment`: global 혹은 static 변수가 저장되는 영역
- `heap segment`: dynamic memory

<br>

#### Thread-Specific Segment
- `stack segment`: 각 thread는 독립된 stack을 가진다.
- `registers`: thread 상태를 관리하기 위한 CPU register이다.
  - Program Counter, Stack Pointer 등은 각 thread마다 독립적으로 관리한다.

<br>
<br>

# Server에서 적절한 Thread 수
[How Many Threads Is Too Many?](https://www.baeldung.com/cs/servers-threads-number)<br>

### `SW thread를 HW thread로 제한`
program은 SW thread를 생성하고, HW thread는 실제 물리적인 resource이다.<br>

따라서 `실행 가능한 thread 수를 HW thread 수로 제한하는 것을 권장`한다.<br>
HW thread 수는 다 다르기 때문에 SW thread 제한을 하드 코딩하지 않는다.<br>

<br>

### `왕도는 없다`
thread 수를 조절해서 코드를 실행한 뒤, 결과를 평가한 후에 결정을 내리는 것이 정석이다.<br>
측정하지 않고는 좋은 solution에 도달할 수 없기 때문이다.<br>

특히 부하가 걸린 상태에서 동시에 실행되는 최대 thread 수는 측정 시 주의 깊게 살펴야 한다.<br>
왜냐하면 이를 기준으로 안전 margin으로 20% 늘리기 때문이다.<br>

<br>

## 과도한 Thread가 성능에 미치는 점

### Overhead
한정된 작업량에 너무 많은 thread를 할당하면 각 thread가 할당 받는 작업량이 너무 적어 `thread 시작 및 중단과 관련된 overhead가 생산적인 작업을 압도`한다.<br>

과도한 수의 thread를 실행하면 `제한된 hardware resource에 대한 경쟁`으로 인해 overhead가 발생한다.<br>

`각 thread에 대한 memory overhead는 크지 않지만`, `thread schedulr가 이를 관리해야 하는 overhead가 존재`한다.<br>

<br>

