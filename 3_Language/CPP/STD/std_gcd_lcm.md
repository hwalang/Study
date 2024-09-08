- [std::gcd](#stdgcd)
  - [return value](#return-value)
- [std::lcm](#stdlcm)
  - [return value](#return-value-1)

<br>

[ standard library를 안 쓰고 GCD와 LCM을 구하는 방법 ](/2_Math/number/README.md)<br>

# std::gcd
[ Greatest Commond Divisor ](/2_Math/number/3_GCD.md)<br>
[ cppreference - gcd ](https://en.cppreference.com/w/cpp/numeric/gcd)<br>
```cpp
#include <numeric>

template <class M, class N>
constexpr std::common_type_t<M, N> gcd(M m, N n);
```
`M과 N 둘 중 하나라도 Integer가 아니거나 bool인 경우, 잘못된 문법`이기 때문에 runtime-error가 발생한다<br>

## return value
둘 중 하나라도 0이 존재하면, 0을 반환<br>
그렇지 않다면, $|M|$과 $|N|$의 gcd를 반환<BR> 

<br><br>

# std::lcm
[ Least Common Multiple ](/2_Math/number/4_LCM.md)<br>
[ cppreference - lcm ](https://en.cppreference.com/w/cpp/numeric/lcm)<br>
```cpp
#include <numeric>

template <class M, class N>
constexpr std::common_type_t<M, N> lcm(M m, N n);
```
`M과 N 둘 중 하나라도 Integer가 아니거나 bool인 경우, 잘못된 문법`이기 때문에 runtime-error가 발생한다<br>

## return value
둘 중 하나라도 0이 존재하면, 0을 반환<br>
그렇지 않다면, $|M|$과 $|N|$의 lcm을 반환<BR> 