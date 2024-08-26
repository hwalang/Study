- [Introduce](#introduce)
  - [왜 stack을 사용하지 않나?](#왜-stack을-사용하지-않나)
    - [1. stack](#1-stack)
    - [2. TLS](#2-tls)
  - [사용하는 상황](#사용하는-상황)

<br>

# Introduce
`thread 별 저장 공간`<br>

Thread-Local Storage(TLS)는 multi-thread에서 사용하는 기법으로, `static 또는 global memory에서 각 thread가 자신만의 독립된 데이터를 가질 수 있게 하는 방법`이다<br>

`thread가 공유하는 영역에서 모든 thread가 동일한 값을 갖는 것이 아니라 각 thread 마다 개별적으로 값을 관리`한다<br>
즉, 각 thread에는 TLS 변수의 복사본을 가지며, 해당 변수에 대한 변경 사항은 thread에 local로 적용된다<br>

```cpp
// cpp
#include <threads.h>
thread_local int counter = 0;

// c# 2가지 사용법
using System.Threading;
static ThreadLocal<int> counter = new ThreadLocal<int>(() => { return 0; });

[ThreadStatic]
static int counter = 0;
```

<br>

## 왜 stack을 사용하지 않나?
thread 고유의 정보를 원한다면 stack 영역을 사용하면 될 텐데, 왜 TLS라는 특별한 영역을 사용할까?<br>

### 1. stack
stack은 `함수의 실행 흐름`과 밀접하게 관련되고, 함수가 호출되고 종료될 때마다 `stack에 데이터가 할당되고 해제`된다<br>

stack은 local variables를 저장하기 적합하지만, thread 전체에서 접근하는 공유 데이터를 저장하기에는 적합하지 않다<br>
또한 thread 고유 영역인 stack은 많은 시스템에서 제한된 규칙을 적용하기 때문에 stack overflow가 발생할 수 있다<br>

### 2. TLS
TLS는 `모든 thread에서 지속적으로 유지되는 데이터를 저장`할 수 있다<br>
함수의 실행 흐름과 무관하게 thread 생명 주기 동안 접근 가능한 데이터를 저장한다<br>
즉, `thread가 종료될 때까지 TLS에 저장된 변수가 유지`된다<br>
stack 처럼 함수 호출에 의존적이지 않기 때문에 많은 곳에서 `데이터를 공유`할 수 있다<br>

<br>

## 사용하는 상황
첫 번째는 `multi-thread 환경에서는 thread 별 static( 또는 global ) 변수를 사용하고 싶을 때`가 있다.<br>

두 번째는 `최근에는 static variables를 사용하지 않는 추세`다.<br>

세 번째는 race condition을 피하면서 thread의 global variable을 관리하기 위함이다<br>
lock을 사용하는 이유는 race condition을 피하기 위함이다<br>
하지만 lock은 잠그고 해제하는 과정에서 overhead가 발생해 성능을 떨어뜨린다<br>
때문에 `race conditon 발생 가능성을 없애고 lock 필요성을 제거하기 위해 사용`한다<br>