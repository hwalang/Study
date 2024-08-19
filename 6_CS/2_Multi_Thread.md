- [들어가기 전에](#들어가기-전에)
    - [`process`](#process)
    - [CPU `Scheduling`](#cpu-scheduling)
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

