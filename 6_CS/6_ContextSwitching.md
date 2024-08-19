- [Introduce](#introduce)
    - [용어 정리](#용어-정리)
    - [multi- tasking, processing, threading 개념](#multi--tasking-processing-threading-개념)
    - [발생하는 경우](#발생하는-경우)
- [Cost](#cost)
    - [부작용 1 : Cache Pollution](#부작용-1--cache-pollution)
    - [부작용 2 : overhead](#부작용-2--overhead)

<br>

# Introduce
multi-tasking에서의 context-switching은 `CPU에서 실행 중이던 process 또는 thread의 상태를 저장하여 작업을 일시 중지하고, 다른 process 또는 thread로 교체`하는 과정이다.<br>

Context Switching이 발생할 때, CPU는 이전에 실행 중이던 작업( process, thread )의 context( state )를 저장하고, 새로 실행할 작업의 context를 load한다.<br>
이처럼 여러 작업을 번갈아 가며 실행하기 때문에 각 `process나 thread의 상태를 기억`해야 한다.<br>

<br>

### 용어 정리
`Context`
  - state( 실행 상태, memory 상태 ), register, program counter, stack pointer 등

`Process Context Switching`
  - 서로 다른 process 간의 context switching.
  - 예시: process1 thread1 &rarr; process2 thread2

`Thread Context Switching`
  - 동일한 process 내에서 thread 간의 context switching.
  - 예시: process1 thread1 &larr; process1 thread2<br>

`IO Bound 작업`
  - `실행 중인 작업이 IO 연산에 많은 시간을 소비하는 경우`
  - `IO Bound 작업에서 병목이 발생하는 이유는 CPU 보다 상대적으로 느린 IO 장치에 의존하기 때문`이다
  - IO 작업을 기다리는 동안 놀고 있는 CPU를 OS가 다른 작업에 보낸다( context-switching )
  - 예시: disk, network, keyboard, mouse 등 입출력 장치에 데이터를 주고 받는 작업, file write/read, database query, web 요청 등

<br>

### multi- tasking, processing, threading 개념
`multi-tasking`
  - `OS가` 여러 task( process 단위 )를 동시에 처리하는 것처럼 보이도록 관리하는 방식
  - 일반적으로 Time-Slicing( 시간 분할 )을 적용하여 `하나의 CPU가 여러 process를 짧은 시간 간격으로 번갈아가며 처리`
  - 예시: 컴퓨터에 여러 앱을 동시에 실행하는 상황

`multi-processing`
  - `여러 CPU( CPU core )를 활용하여 동시에 여러 process를 병렬로 처리`하는 방식
  - 각 process가 별도의 CPU core에서 독립적으로 실행

`multi-threading`
  - `하나의 process 내에서 여러 thread를 생성하여 동시에 여러 task를 수행`하는 방식

<br>

### 발생하는 경우
하나의 cpu core가 여러 process나 thread를 담당한다.<br>

`IO Bound 작업( interrupt, 병목 )이 발생`하면 CPU가 IO 작업을 기다리는 동안 Waiting 상태가 되므로, 다른 process나 thread로 전환한다.<br>

Scheduler가 process 또는 thread에게 `주어진 quantum( time slice ) 시간( CPU 시간 )이 끝나면`, 다른 작업으로 전환한다.<BR>

`높은 우선순위의 process나 thread가 준비되면`, 현재 실행 중인 작업을 중단하고 우선적으로 실행한다.<br>

<br>
<br>

# Cost
자주 context-switching이 발생하는 경우 cpu core가 효율적으로 분배되지만, `context-switching 자체에 소모되는 overhead로 인해 성능에 부정적인 영향`을 미칠 수 있다.<br>

<br>

### 부작용 1 : Cache Pollution
`Cache Pollution( 캐시 오염 )이 발생`한다.<br>
Cache memory는 용량이 매우 작기 때문에 모든 process가 같이 사용한다.<br>
Context Switching이 일어나면, 이전 process, thread에서 사용한 데이터가 cache에 남아있기 때문에 새 process나 thread에서는 이를 사용하지 않아 `cache 낭비 및 cache miss가 발생`한다.<br>

context switching 직후에는 cache에 필요한 데이터가 없기 때문에 `memory에 접근해서 데이터를 받아`온다. &rarr; 성능 저하<br>


<br>

### 부작용 2 : overhead
overhead( 간접 비용 )은 프로그램 실행 흐름에서 나타난다.<br>
`프로그램 실행 도중에 동떨어진 위치의 코드를 실행시켜야 할 때, 추가적으로 시간, memory, resource가 사용되는 현상`이다.<br>
현재 프로그램과 상관 없는 작업을 하는 것이다.<br>

10초가 걸리는 기능이 간접적인 원인으로 20초가 걸렸다면 overhead는 10초이다.<br>

context-switching 과정에서 process나 thread의 상태를 저장하고, 새로운 process나 thread의 상태를 복원하는 작업이 추가되기 때문에 `CPU 시간이 context-switching에 소모되어 실제 작업 처리 시간이 줄어들 수 있다`.<br>

<br>