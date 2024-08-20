- [Debug와 Release는 다른 환경](#debug와-release는-다른-환경)
- [해결하는 방법](#해결하는-방법)
  - [1. volatile keyword](#1-volatile-keyword)

<br>

# Debug와 Release는 다른 환경
멀티 쓰레드로 게임 서버를 구현할 때, Debug에서는 잘 작동하던 코드가 Release( 배포 )에서는 버그를 불러일으키는 경우가 많다.<br>

최신 컴파일러에서는 해당 문제가 발생하지 않는 경우가 있다.<br>
따라서 `컴파일러 버전에 따라 문제가 발생할 수 있음`을 알아둔다.<br>

```c#
static bool _stop = false;    // data segment

// Debug
while (_stop == false)
{
  // stop 신호를 대기
}

// Release
if (_stop == false)
{
  while (true) {}
}
```
`Release 모드에서는 Compiler가 코드를 최적화`한다.<br>
어떻게 최적화 했는지 파악하려면, assembly code를 살펴보는 것이 가장 직관적이다.<br>

<br>
<br>

# 해결하는 방법

## 1. volatile keyword
```c#
volatile static bool _stop = false;
```
volatile( 휘발성 ) keyword는 `compile 최적화에서 제외`한다.<br>

c++에서는 위 기능만 있지만 c#에서는 추가 기능이 존재한다.<br>
대표적인 기능이 cache를 무시하고, 최신 값을 가져오는 것이다.<br>
이 외에도 다양한 기능이 있기 때문에 `c# 전문가들은 volatile keyword를 권장하지 않는다`.<br>