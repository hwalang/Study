
- [사용하는 이유](#사용하는-이유)
- [단점과 장점](#단점과-장점)
- [예시 1 : Simple](#예시-1--simple)
- [예시 2 : Better](#예시-2--better)
- [예시 3 : 멀티 쓰레드 환경](#예시-3--멀티-쓰레드-환경)
  - [3.1. lock과 volatile](#31-lock과-volatile)
  - [3.2. static instance를 미리 생성](#32-static-instance를-미리-생성)
- [예시 4 : Generic](#예시-4--generic)

</br>

# 사용하는 이유

1. `class가 자체의 instance 하나만을 instance화 하도록 보장`
2. `하나의 instance에 대한 global access 제공`

전체 Scene에서 행동을 조정하는 Object가 하나만 필요할 때 유용하다.</br>
Scene에 main game loop를 총괄하는 Game Manager가 하나만 필요한 경우, 한 번에 하나의 File Manager만 파일 시스템에 작성하기를 원하는 경우가 있다.</br>
이러한 `관리자 레벨의 Object`는 대체로 singleton을 적용하기 좋은 대상이다.</br>

</br>

`하지만` 엔터프라이즈 수준의 게임을 제작할 예정이라면, singleton은 적절한 선택이 아니다.</br>
계속 확장하는 게임이 아니라면 singleton을 적용해도 된다.</br>

예시: 상태창, 게임 매니저, 오디어 매니저, 파일 관리자, UI Setting</br>

</br>
</br>

# 단점과 장점

Singleton은 여러 이유로 SOLID 원칙을 위반한다는 점에서 많은 개발자들이 호의적이지 않는다.</br>

1. `Global Access가 필요`
   - global instacne를 사용하기 때문에 `Dependency를 숨길 수 있다`.
   - 이 때문에 `해결하기 어려운 버그를 유발`한다.
2. `Test의 복잡성`
   - Unit Test는 반드시 서로 독립적으로 수행한다.
   - Singleton은 `Scene 전반에서 많은 Object의 상태를 변경`할 수 있기에 Test에 방해될 수 있다.
   - 생성 시점이 명확하지 않다.
3. `High Coupling 유발`
   - Coupling이 높으면 Refactoring이 힘들다.
   - `Component 하나를 변경하면 연결된 Component에 영향`을 줄 수 있기 때문이다.

</br>

확장성이 필요하지 않은 소규모 게임 개발에 유용하다.</br>

1. Learning Curve
   - `Core Pattern이 직관적`이다.
2. 사용자 친화적
   - 다른 Component에서 singleton을 사용할 때, `static instance만 참조`하면 된다.
3. 성능 보장
   - static instance에 항상 global access가 가능하기 때문에, `속도가 느린 GetComponent, Find 연산의 결과를 Cache하지 않아도 된다`.


</br>
</br>

# 예시 1 : Simple
```c#
// 1. Unity의 경우
using UnityEngine;

public class SimpleSingleton : MonoBehaviour
{
  public static SimpleSinglton Instance;

  private void Awake()
  {
    if (Instance == null) Instance = this;
    else                  Destroy(gameObject);
  }
}

// 2. 일반 C#의 경우
public class SimpleSingleton
{
  public static SimpleSinglton Instance;

  public static SimpleSingleton Instance
  {
    get {
      if (instance == null) instance = new Singleton();
    }
    return instance;
  }
}
```
class에서 `static 변수는 여러 instance가 생기더라도 하나의 memory 공간`만 사용한다.</br>

runtime에 Hierarchy view에서 둘 이상의 gameObject에 Script를 연결하는 경우, Awake()로 인해 첫 Object만 유지하고 나머지는 파괴한다.</br>

`현재 예시의 3가지 문제점`</br>
1. 새로운 Scene을 Load하면 `Object가 파괴`된다.
2. 사용하기 전에 Hierarchy view에서 singleton을 설정해야 한다.
   - Awake() 호출 전에 Singleton에 접근하면 `null 문제`가 발생한다.
3. 일반 c#의 경우 `쓰레드 세이프가 적용되지 않는다`.
   - 멀티 쓰레드 환경에서 Instance에 2개의 쓰레드가 동시에 접근하면 문제가 발생한다.

DontDestroyOnLoad() 사용, Lazy Initialization 사용( singletone이 처음으로 필요할 때 만든다 )</br>

</br>
</br>

# 예시 2 : Better
```c#
public class Singleton : MonoBehaviour
{
  private static Singleton instance;
  public static Singleton Instance
  {
    get {
      if (instance == null) SetupInstance();
      return instance;
    }
  }

  private void Awake()
  {
    if (instance == null) {
      instance == this;
      DontDestroyOnLoad(this.gameObject);
    }
    else {
      Destroy(gameObject);
    }
  }

  private static void SetupInstance()
  {
    instance = FindObjectOfType<Singleton>();   // Scene에 존재하는지 확인
    if (instance == null) {
      GameObject gameObj = new GameObject();
      gameObj.name = "Singleton";
      instance = gameObj.AddComponent<Singleton>();
      DontDestroyOnLoad(gameObj);
    }
  }
}
```
Instance를 참조할 때 가져오려는 Instance가 존재하는지 확인하고, 없는 경우 Setup() 메서드가 Singleton Object를 생성한다ㅣ</br>
Scene Load로 인한 오브젝트 파괴를 막는다.</br>

</br>
</br>

# 예시 3 : 멀티 쓰레드 환경

## 3.1. lock과 volatile
Unity는 싱글 쓰레드 환경이기 때문에 문제가 없지만, 일반 c#은 멀티 쓰레드 환경을 적용할 수 있다.</br>

```c#
public class SimpleSingleton
{
  private static volatile SimpleSinglton instance = null;
  private static readonly object padlock = new object(); 

  public static SimpleSingleton Instance
  {
    get {
      if (instance == null) {
        lock (padlock) {
          if (instance == null) instance = new Singleton();
        }
      }
    }
    return instance;
  }
}
```
lock을 사용하면 critical session이 되면서 A 쓰레드가 사용할 때, 다른 쓰레드가 해당 구문에 접근할 수 없다.</br>
</br>

`instance null 체크를 2번하는 이유`</br>
1. A 쓰레드가 Singleton 객체를 생성하는 도중에 첫 번째 if문에 B 쓰레드가 접근하면, lock (padlock)에서 B 쓰레드가 대기한다.
2. A 쓰레드가 객체를 생성하고 lock을 빠져나가면, B 쓰레드가 `instance = new Singleton();`에 접근하여 또 instance를 생성한다.
3. 위 과정을 막기 위해서 instance null 체크를 두 번 수행한다.

</br>

`volatile을 사용하는 이유`</br>
멀티 쓰레드 환경에서 사용함을 알려준다.</br>
멀티 쓰레드 환경에서 CPU의 cache에 있는 데이터와 memory에 있는 데이터가 miss matching 하는 경우가 발생할 수 있다.</br>
volatile을 사용하면 cache 최적화에서 제외하지만, 위 문제가 발생할 여지가 없다.</br>

</br>
</br>

## 3.2. static instance를 미리 생성
```c#
public class SimpleSingleton
{
  private static readonly SimpleSinglton instance = new SimpleSingleton();

  private SimpleSingleton() {}

  public static SimpleSingleton Instance { get => instance; }
}
```
static 멤버 변수는 class script가 생성될 때 함께 생성된다.</br>
처음부터 존재하기 때문에 `멀티 쓰레드 환경에서 완벽하게 안전`하다.</br>

Lazy Initailzation의 이점은 없다.</br>

</br>
</br>

# 예시 4 : Generic
AudioManager로서 작동하는 Singleton과 GameManager로 작동하는 다른 Singleton이 필요한 경우, 이 두 Singleton은 공존할 수 없다.</br>
관련 코드를 복제하고 로직을 각 클래스로 붙여 넣어야 한다.</br>

```c#
public class Singleton<T> : MonoBehaviour where T : Component
{
  private static T instance;
  public static T Instance
  {
    get {
      if (instance == null) {
        instance = (T)FindObjectOfType(typeof(T));
        if (instance == null) SetupInstance();
      }
      return instance;
    }
  }

  private virtual void Awake()
  {
    RemoveDuplicates();
  }

  private static void SetupInstance()
  {
    instance = (T)FindObjectOfType(typeof(T));
    if (instance == null) {
      GameObject gameObj = new GameObject();
      gameObj.name = typeof(T).Name;
      instance = gameObj.AddComponent<T>();
      DontDestroyOnLoad(gameObj);
    }
  }

  private void RemoveDuplicates()
  {
    if (instance == null) {
      instance == this as T;
      DontDestroyOnLoad(this.gameObject);
    }
    else {
      Destroy(gameObject);
    }
  }
}
```
위 코드를 이용하여 어떤 class라도 singleton으로 변환할 수 있다.</br>
```c#
public class GameManager : Singleton<GameManager> { ... }
```
