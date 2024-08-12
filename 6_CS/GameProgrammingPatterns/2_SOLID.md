- [요약](#요약)
- [Single Responsibility ( 단일책임원칙 )](#single-responsibility--단일책임원칙-)
  - [예시](#예시)
    - [Single Responsibility 적용 이전](#single-responsibility-적용-이전)
    - [Single Responsibility 적용 이후](#single-responsibility-적용-이후)
- [Open-Closed ( 개방폐쇄원칙 )](#open-closed--개방폐쇄원칙-)
  - [예시](#예시-1)
    - [Open-closed 적용 이전](#open-closed-적용-이전)
    - [Open-closed 적용 이후](#open-closed-적용-이후)
- [Liskov Subsitution ( 리스코프치환 )](#liskov-subsitution--리스코프치환-)
  - [예시](#예시-2)
    - [Liskov substitution 적용 이전](#liskov-substitution-적용-이전)
    - [Liskov substitution 적용 이후](#liskov-substitution-적용-이후)
- [Interface Segregation ( 인터페이스분리원칙 )](#interface-segregation--인터페이스분리원칙-)
  - [예시](#예시-3)
    - [Interface Segregation 적용 이전](#interface-segregation-적용-이전)
    - [Interface Segregation 적용 이후](#interface-segregation-적용-이후)
- [Dependency Inversion ( 의존역전원칙 )](#dependency-inversion--의존역전원칙-)
  - [예시](#예시-4)
    - [Dependency Inversion 적용 이전](#dependency-inversion-적용-이전)
    - [Dependency Inversion 적용 이후](#dependency-inversion-적용-이후)

</br>

# 요약

모든 Design Pattern은 SOLID 원칙을 지키려고 노력한다.</br>

1. Single Responsibility
   - class는 `하나의 작업만 수행`, `변경할 이유는 하나`만
2. Open-closed
   -  `이미 작동하는 방식을 변경하지 않고도 class 기능을 확장` 가능
3. Liskov substitution
   -  하위 클래스는 기본 클래스를 대체할 수 있어야 한다. `기본 클래스의 방향성을 유지`
4. interface segregation
   -  `interface를 작게 유지`, `client는 필요한 것만 interface를 가져와서 사용`
5. Dependency inversion
   -  추상화에 의존, `하나의 구체 클래스에서 다른 클래스로 직접 의존 금지`

</br>
</br>

# Single Responsibility ( 단일책임원칙 )
`모든 클래스는 하나의 책임`만 가진다.</br>


1. Readability( 가독성 )
   - `짧은 분량의 클래스`( 200 ~ 300 lines )
2. Extensibility( 확장성 )
   - `상속이 쉬움`
3. Re-usability( 재사용성 )
   - 모듈식 설계로 `재사용 가능`

</br>

## 예시

### Single Responsibility 적용 이전
![alt text](Images/SOLID/S_Player.png)</br>
```c#
// Not Single Responsibility
public class UnrefactoredPlayer : MonoBehaviour
{
  [SerializeField] private string inputAxisName;
  [SerializeField] private float positionMultiplier;
  private float yPosition;
  private AudioSource bounceSfx;

  private void Start() {
    bounceSfx = GetComponent<AudioSource>();
  }

  private void Update() {
    float delta = Input.GetAxis(inputAxisName) * Time.deltaTime;
    yPosition = Mathf.Clamp(yPosition + delta, -1, 1);
    transform.position = new Vector3(transform.position.x, yPosition * positionMultiplier, transform.position.z);
  }

  private void OnTriggerEnter(Collider other) {
    bounceSfx.Play();
  }
}
```
Player 클래스가 Audio, Input, Movement 3가지 기능을 담당한다.</br>

</br>

### Single Responsibility 적용 이후
![alt text](Images/SOLID/S_Player2.png)</br>
```c#
// Single Responsibility
[RequireComponent(typeof(PlayerAudio), typeof(PlayerInput), typeof(PlayerMovement))]
public class Player : MonoBehaviour
{
  [SerializeField] private PlayerAudio playerAudio;
  [SerializeField] private PlayerInput playerInput;
  [SerializeField] private PlayerMovement playerMovement;

  private void Start() {
    playerAudio = GetComponent<PlayerAudio>();
    playerInput = GetComponent<PlayerInput>();
    playerMovement = GetComponent<PlayerMovement>();
  }

  // 외부 클래스
  public class PlayerAudio : MonoBehaviour {}
  public class PlayerInput : MonoBehaviour {}
  public class PlayerMovement : MonoBehaviour {}
}
```
Player 클래스는 외부 모듈을 활용한다.</br>
이러면 PlayerMovement와 같은 모듈은 NPC의 movement를 구현할 때도 사용할 수 있다.</br>

</br>
</br>

# Open-Closed ( 개방폐쇄원칙 )

1. `확장( 상속 )`에 대해 열려있다.
   - 모듈의 동작을 확장할 수 있다.
   - `요구 사항이 변경될 때, 새로운 동작을 추가해 모듈을 확장`할 수 있다.
   - 즉, `모듈이 하는 일을 변경할 수 있다`.
2. 수정에 대해 닫혀있다.
   - `기존 코드를 수정하지 않아도 모듈의 기능을 확장하거나 변경`할 수 있다.
   - `모듈의 라이브러리( ex. DLL )의 수정이 필요 없다`.

</br>

## 예시

### Open-closed 적용 이전
![alt text](Images/SOLID/O_Shape.png)</br>
```c#
public class Rectangle { public float width; public float height; }
public class Circle { public float radius; }

public class AreaCalculator
{
  public float GetRectangleArea(Rectangle rectangle)
  {
    return rectangle.width * rectangle.height;
  }

  public float GetCircleArea(Circle circle)
  {
    return circle.radius * circle.radius * Mathf.PI;
  }
}
```
도형이 늘어날수록 AreaCalculator에서 관리하는 GetArea() 함수가 증가한다.</br>

</br>

### Open-closed 적용 이후
![alt text](Images/SOLID/O_Shape2.png)</br>
```c#
public abstract class Shape
{
  public abstract float CalculateArea();
}

public class Rectangle : Shape
{ 
  public float width; 
  public float height; 
  public override float CalculateArea() { return width * height; }
}
public class Circle 
{ 
  public float radius; 
  public override float CalculateArea() { return radius * radius * Mathf.PI; }
}

// Shape의 Area를 구하는 클래스
public class AreaCalculator
{
  public float GetArea(Shape shape) { return shape.CalculateArea(); }
}
```
도형을 추가하더라도 AreaCalculator 클래스의 수정은 필요하지 않다.</br>

</br>
</br>

# Liskov Subsitution ( 리스코프치환 )

**`interface로 역할에 맞는 기능을 가져다 사용하는 것을 권장`한다.**</br>

child class는 parent class의 방향성을 지켜줘야 한다.</br>
하위 클래스를 강력하고 유연하게 만드는 원칙이다.</br>
`OOP 상속을 사용하면 하위 클래스를 통해 기능을 추가할 수 있지만`, `복잡성이 증가`할 수 있다.</br>

parent class에서 상속을 요구하는 메소드를 child class에서 사용했을 때, 내용이 비어있으면 안 된다.</br>
부모 클래스에서 자식 클래스에게 무조건 상속을 요구하는 메소드가 있다. 이를 자식 클래스에서 override 한 뒤, 아무런 내용을 채우지 않는 것을 의미한다.</br>

![alt text](Images/SOLID/L_inheritance_composition.png)</br>
이 때문에 abstraction을 단순하게 유지하기 위해 `inheritance 보다 composition을 권장`한다.</br>
이는 `abstract로 상속을 받는 구조( inheritance )`보다는 `interface를 가져다 사용하는 것( composition )`을 의미한다.</br>

</br>

## 예시

### Liskov substitution 적용 이전
![alt text](Images/SOLID/L_Before.png)</br>
```c#
public class Vehicle
{
  public float speed = 100;
  public Vector3 direction;

  public void GoForward() {}
  public void Reverse() {}
  public void TurnRight() {}
  public void TurnLeft() {}
}
```
자동차와 기차는 모두 Vehicle 기능을 가진다.</br>
문제는 자동차는 도로에 따라 움직이고, 기차는 레일에 따라 움직인다.</br>
이 때문에 `기차는 GoForward() 기능만` 있으면 움직이는데 지장이 없고, `나머지 기능은 상속만 받고 내용을 채우지 않게 된다`.</br>

이를 `interface를 이용해서 수정`한다.

</br>

### Liskov substitution 적용 이후
![alt text](Images/SOLID/L_After.png)</br>
```c#
public interface ITurnable { 
  public void TurnRight();
  public void TurnLeft();
}
  
public interface IMovable { 
  public void GoForward();
  public void Reverse();
}

public class RoadVehicle : IMovable, ITurnable {
  public float speed = 100f;
  public float turnSpeed = 5f;

  public virtual void GoForward() {}
  public virtual void Reverse() {}
  public virtual void TurnRight() {}
  public virtual void TurnLeft() {}
}

public class RailVehicle : IMovable {
  public float speed = 100f;

  public virtual void GoForward() {}
  public virtual void Reverse() {}
}
```
방향 전환과 직진 후진 기능을 interface로 분리한다.</br>
이러한 관계는 is-a가 아니라 `has-a` 관계를 가진다.</br>



</br>
</br>

# Interface Segregation ( 인터페이스분리원칙 )

`많은 기능을 가진 interface를 구체적이고 작은 단위로 분리`한다.</br>
의존성을 약화하고 유연성을 강화한다.</br>

</br>

## 예시
![alt text](Images/SOLID/I_interface.png)</br>

### Interface Segregation 적용 이전
```c#
public interface IUnitStats
{
  public float Health { get; set; }
  public int Defence { get; set; }
  public void Die();
  public void TakeDamage();
  public void RestoreHealth();
  public float MoveSpeed { get; set; }
  public float Acceleration { get; set; }
  public void GoForward();
  public void Reverse();
  public void TurnLeft();
  public void TurnRight();
  public int Strength { get; set; }
  public int Dexterity { get; set; }
  public int Endurance { get; set; }
}
```
Unit Stat에 대한 기능을 한 곳에 모은 상황이다.</br>

</br>

### Interface Segregation 적용 이후
```c#
public interface IMovable {
  public float MoveSpeed { get; set; }
  public float Acceleration { get; set; }
  public void GoForward();
  public void Reverse();
  public void TurnLeft();
  public void TurnRight();
}
public interface IDamageable() { }
public interface IUnitStats() { }
public interface IExplodable() { }

public class ExplodingBarrel : MonoBehaviour, IDamageable, IExplodable {}
public class EnemyUnit : MonoBehaviour, IDamageable, IMovable, IUnitStats {}
```
Unit Stat interface를 분리하여 다양한 클래스에서 `각자 필요한 기능을 사용`할 수 있다.</br>

</br>
</br>

# Dependency Inversion ( 의존역전원칙 )

SW Module을 분리하는 특정 형식이다.</br>

하나의 클래스는 `다른 클래스와 직접적인 관계가 있으면 안 된다`.</br>
`dependency(종속성) 또는 coupling(결합)이 발생`하기 때문이다.</br>

A class와 B class 간의 dependency 또는 coupling이 클수록 하나의 class를 수정할 때, 다른 클래스도 수정해야 하는 상황이 발생한다.</br>

</br>

## 예시

### Dependency Inversion 적용 이전
![alt text](Images/SOLID/D_1.png)
```c#
public class Switch : MonoBehaviour {
  public Door door;
  public bool isActivated;
  public void Toggle() {
    if (isActivated) {
      isActivated = false;
      door.Close();
    } else {
      isActivated = true;
      door.Open();
    }
  }
}

public class Door : MonoBehaviour {
  public void Open() {}
  public void Close() {}
}
```
게임의 기믹에 대한 switch를 살펴보자.</br>
switch class는 door에 의존하고 있다.</br>

door만 있는 상황에서는 문제가 없다. 하지만 함정 기믹이 추가된다면 문제가 발생한다.</br>
이 경우에는 switch class에서 각 함정과 문에 대한 기능( method )를 추가해야 한다.</br>

### Dependency Inversion 적용 이후
![alt text](Images/SOLID/D_2.png)
```c#
public interface ISwitchable {
  public bool isActive { get; }
  public void Activate();
  public void Deactivate();
}

public class Door : MonoBehaviour, ISwitchable {
  private bool isActive;
  public bool IsActive => isActive;

  public void Activate() { isActive = true; }
  public void Deactivate() { isActive = false; }
}

public class Switch : MonoBehaviour {
  public ISwitchable client;

  public void Toggle() {
    if (client.isActive) {
      client.Deactivate();
    } else {
      client.Activate();
    }
  }
}
```
Door가 아닌 함정 class를 생성할 때 ISwitchable를 사용하여 함정 기능을 추가한다.</br>
이러한 interface를 사용하는 class는 Switch 클래스에서 모두 판단하여 발동시킬 수 있다.</br>