- [Avoiding garbage collector performance spikes in Unity](#avoiding-garbage-collector-performance-spikes-in-unity)
- [Memory Allocation in Unity](#memory-allocation-in-unity)
- [Techniques for avoiding GC spikes with managed memory](#techniques-for-avoiding-gc-spikes-with-managed-memory)
  - [1. Avoid unnecessary allocations](#1-avoid-unnecessary-allocations)
    - [1.1. `Favor structs` over classes](#11-favor-structs-over-classes)
    - [1.2. `Be careful with string manipulation`](#12-be-careful-with-string-manipulation)
    - [1.3. `Avoid` creating APIs which `return new arrays/collections`](#13-avoid-creating-apis-which-return-new-arrayscollections)
    - [1.4. `Avoid boxing structs`](#14-avoid-boxing-structs)

<br>

[참고 사이트](https://embrace.io/blog/garbage-collector-spikes-unity/)<br>

# Avoiding garbage collector performance spikes in Unity
`Garbage Collector로 인해 성능이 급상승( spike )하는 경우를 방지`해야 한다.<br>

`spike`란, 성능 또는 frame 그래프를 볼 때, 일정한 수준에서 유지되던 값이 갑자기 급등하는 것을 의미한다.<br>

Garbage Collector를 자주 또는 적절하지 않은 상황에서 실행하면 user의 computer에서 frame이 급증하여 `게임이 끊기는 현상이 발생`할 수 있다.<br>
특히 GC가 많은 memory를 해제할 때, Main Thread가 긴 시간 동안 멈추게 된다. `GC가 memory를 해제할 때는 모든 thread가 안전한 상태에 있는지 확인하면서 모든 작업을 중단`시키기 때문이다.<br>
이를 방지하기 위해서는 `garbage collector의 동작을 간접적으로 제어`하거나, `사용하지 않고 우회`하는 방법이 있다.<br>

<br>
<br>

# Memory Allocation in Unity

`stack memory의 lifetime`은 function scope와 일치하여 함수가 종료하면서 자동으로 memory를 해제하기 때문에 GC가 추적하지 않는다.<br>

`heap memory에 존재하는 객체는 항상 GC가 관리`한다.<br>

<br>

C#의 class는 항상 heap에 저장되지만, `struct는 상황에 따라 stack 혹은 heap에 저장`된다.<br>
local variable로 선언된 struct instance는 stack에 할당되지만, reference type의 member 혹은 object나 interface reference에 할당된 struct instance는 heap에 저장된다( 이를 boxing이라 부른다 ).<br>

GC는 `managed heap의 모든 allocation을 추적`하고, `더 이상 사용되지 않는 heap memory를 해제`한다.<br>

중요한 점은 이러한 `memory 해제 작업이 언제 수행되는지 예측하기 어렵다`.<br>

<br>
<br>

# Techniques for avoiding GC spikes with managed memory

## 1. Avoid unnecessary allocations
GC 최적화의 가장 기본적인 원칙은 필요하지 않는 memory 할당을 피하는 것이다.<br>
`Unity Profiler를 사용해서 필요하지 않은 memory를 할당하고 있지 않는지 파악`한다.<br>

<br>

### 1.1. `Favor structs` over classes
temporary object를 위해 class가 아닌 struct( Memory Allocation in Unity 참고 )를 사용해본다.<br>
class 또는 array가 필요한 경우에는 object를 caching해서 매 frame 마다 재사용해본다.<br>

<br>

### 1.2. `Be careful with string manipulation`
`문자열 조작은 의도치 않은 memory 할당의 일반적인 원인`이다.<br>
C#에서 문자열은 immutable 하기 때문에 문자열을 연결( concatenate )하거나 수정할 때마다 새로운 문자열에 할당한다.<br>
```c#
private StringBuilder builder = new StringBuilder();
public string Vector2ToString(Vector2 vector)
{
  // return "x: " + vector.x + " y: " + vector.y;
  builder.Clear();
  builder.Append("x: ")
         .Append(vector.x)
         .Append(" y: ")
         .Append(vector.y);
  return builder.ToString();
}
```
문자열로 작업할 때는 `StringBuilder를 사용해서 할당 횟수를 줄이는 것`을 권장한다.<br>

<br>

### 1.3. `Avoid` creating APIs which `return new arrays/collections`
```c#
public float[] GetRandomValues()
{
  float[] values = new float[10]; // Allocates a new array every time it is called
  for (int i = 0; i < values.Length; ++i) {
    values[i] = Random.value;
  }
  return values;
}

public void GetRandomValues(float[] values)
{
  if (values == null) return;
  for (int i = 0; i < values.Length; ++i) {
    values[i] = Random.value;
  }
}
```
함수 내부에서 새로운 array 또는 collection을 생성하여 return 하지 않고, 함수의 인자로 받아온다.<br>

<br>

### 1.4. `Avoid boxing structs`
