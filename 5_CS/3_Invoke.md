- [Introduce](#introduce)
- [cpp](#cpp)

<br>

# Introduce
Invoke라는 개념이 Unity, cpp 등 다양한 분야에서 사용된다<br>
Invoke는 일반적으로 `호출하다` 라는 의미로 사용된다<br>

<br>
<br>

# cpp
cpp에서 invoke란, `function object( 특정 함수나 함수 객체 )를 호출하는 것을 의미`한다<br>
```cpp
int main()
{
  std::vector<int> v { 1, 2, 3, 4, 5 };

  struct Sum
  {
    void operator() (int n) { sum += n; }
    int sum {0};
  };

  // invoke Sum::operator() for each element
  Sum s = std::for_each(v.cbegin(), v.cend(), Sum());

  std::cout << s.sum << std::endl;
}
```
[ 코드 설명 ](/3_Language/CPP/STD/std_for_each.md/#1-stateful-function-object)<br>