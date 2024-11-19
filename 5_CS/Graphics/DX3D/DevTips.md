- [외부 HW를 사용하는 경우](#외부-hw를-사용하는-경우)
- [Windows Programming: 부모 클래스에서 해당 인스턴스의 포인터를 전역 변수로 선언하는 이유](#windows-programming-부모-클래스에서-해당-인스턴스의-포인터를-전역-변수로-선언하는-이유)

<br><br>

# 외부 HW를 사용하는 경우
API를 이용하여 외부 HW를 사용하는 경우 호환성, 기기 결함 등 다양한 문제로 인해 같은 코드를 작성하더라도 작동하지 않는 경우가 있다.   
이를 파악 또는 방지하기 위해서 특정 변수를 초기화하거나 기능을 수행하는 경우, 각 작업마다 확인을 거친다.   
```cpp
TestApp app;
app.Initialze();
```
일반적인 코드 작성법은 초기화할 때, 아무런 문제가 없기 때문에 따로 확인을 거치지 않는다.   
```cpp
int main() {
  if (!app.Initialize()) {
    cout << "Initialization Failed" << endl;
    return -1;
  }

  return app.Run();
}
```
하지만 다양한 그래픽 카드를 사용하는 DirectX 같은 경우, 각 단계마다 확인 작업이 필요하다.   
작업도 마찬가지다. `app.Run()`이 수행 중 비정상적으로 종료되면, Run()이 -1을 반환하여 문제가 있음을 알려준다.   

<br>

# Windows Programming: 부모 클래스에서 해당 인스턴스의 포인터를 전역 변수로 선언하는 이유
`Windows Programming에서 class의 멤버 함수는 callback 함수로 등록할 수 없다`.   
non-static 멤버 함수는 숨겨진 this pointer를 매개변수로 받기 때문에, `C 스타일의 callback 함수와 cignature와 맞지 않다`. 때문에 우회해서 이를 처리한다.   
```cpp
// Base.cpp
Base *g_base = nullptr;

// WNDCLASSEX 객체를 생성할 때 등록하는 callback 함수
LRESULT WINAPI WndProc(...) {
  return g_base->MsgProc(...);
}

Base::Base() : ... {
  g_base = this;
}

bool Base::Init() {
  WNDCLASSEX wc = {
    ...
    WndProc,    // callback 함수 등록
    ...
  };
}
```
클래스 내부에 멤버 함수가 아닌 일반적인 함수를 구현한 후, `함수 내부에서 자신(*this)에게 간접적으로 접근하여 class member function을 호출`한다.   
class member function에서 원하는 로직을 구현할 수 있으며, 이를 `상속받는 자식 클래스의 멤버 함수도 영향`을 받는다.   

이는 windows programming에서 메시지를 처리하기 위한 방법 중 하나다.   