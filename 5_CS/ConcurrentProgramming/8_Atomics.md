- [Introduce](#introduce)
- [Example In C++11](#example-in-c11)

<br>

[ 참고 - Spin lock in Modern C++ with atomics, memory barriers and exponential back-off](https://medium.com/@joao_vaz/spin-lock-in-modern-c-with-atomics-memory-barriers-and-exponential-back-off-522798aca817)<br>

# Introduce
Atomics는 `동시성 프로그래밍에서 여러 thread가 thread-safe 방식으로 shared resource에 access하고 modify 할 수 있도록 한다`.<br>

일반적으로 atomic을 지원하는 언어에서 `atomic template은 모든 thread가 shared memory를 일관되게 볼 수 있도록 필요한 동기화 및 memory barrier를 제공`한다<br>

<br>
<br>

# Example In C++11
```cpp
#include <atomic>
#include <thread>

std::atomic<int> counter{0};      // shared memory

// critical section
void increment_counter() { counter++; }

int main() 
{
  std::thread t1(increment_counter);
  std::thread t2(increment_counter);

  t1.join();
  t2.join();
}
```
atomic method는 atmoic variable에 대해 원자성을 보장하고, memory barrier를 사용해서 thread간의 일관성을 보장한다<br>