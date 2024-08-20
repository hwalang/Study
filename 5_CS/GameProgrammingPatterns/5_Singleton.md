
- [사용하는 이유](#사용하는-이유)
- [단점과 장점](#단점과-장점)
    - [`단점`](#단점)
    - [`장점`](#장점)
- [static class가 아니라 singleton인 이유](#static-class가-아니라-singleton인-이유)
- [예시 1 : Unity, C# singleton 구현 및 문제점](#예시-1--unity-c-singleton-구현-및-문제점)
- [예시 2 : Unity Singlton 개선 : Lazy Initialization](#예시-2--unity-singlton-개선--lazy-initialization)
    - [`Lazy Initialization`](#lazy-initialization)
- [예시 3 : 멀티 쓰레드 환경](#예시-3--멀티-쓰레드-환경)
  - [3.1. lock과 volatile](#31-lock과-volatile)
    - [`instance null 체크를 2번하는 이유`](#instance-null-체크를-2번하는-이유)
    - [`volatile을 사용하는 이유`](#volatile을-사용하는-이유)
  - [3.2. static instance를 미리 생성](#32-static-instance를-미리-생성)
- [예시 4 : Generic](#예시-4--generic)
  - [4.1. 간단한 Generic](#41-간단한-generic)
  - [4.2. 실전 Generic](#42-실전-generic)
    - [`중복된 Instance를 파괴한다는 의미`](#중복된-instance를-파괴한다는-의미)
    - [`중복된 Instance를 파괴한다는 의미 2`](#중복된-instance를-파괴한다는-의미-2)
    - [`Instance 동작 과정`](#instance-동작-과정)
- [예시 5 : 다른 Manager를 관리하는 Managers](#예시-5--다른-manager를-관리하는-managers)

</br>

# 사용하는 이유

1. `class가 자체의 instance 하나만을 instance화 하도록 보장`
2. `하나의 instance에 대한 global access 제공`

<br>

전체 Scene에서 행동을 조정하는 Object가 하나만 필요할 때 유용하다.</br>
여러 instance가 동시에 존재하면서 발생할 수 있는 `데이터 불일치 문제를 피할 수 있다`.<br>

<br>

`관리자 레벨의 Object`가 대체로 singleton을 적용하기 좋은 대상이다.</br>

</br>

`하지만` 엔터프라이즈 수준의 게임을 제작할 예정이라면, singleton은 적절한 선택이 아니다.</br>
계속 확장하는 게임이 아니라면 singleton을 적용해도 된다.</br>

</br>

`사용 예시`: 상태창, 게임 매니저, 오디어 매니저, 파일 관리자, UI Setting</br>

Scene에 main game loop를 총괄하는 Game Manager가 하나만 필요한 경우, 한 번에 하나의 File Manager만 파일 시스템에 작성하기를 원하는 경우가 있다.</br>



</br>
</br>

# 단점과 장점

### `단점`
Singleton은 여러 이유로 SOLID 원칙을 위반한다는 점에서 많은 개발자들이 호의적이지 않는다.</br>

1. `Global Access가 필요`
   - global instacne를 사용하기 때문에 `Dependency를 숨길 수 있다`.
   - 이 때문에 `해결하기 어려운 버그를 유발`한다.
2. `Test의 복잡성`
   - Unit Test는 반드시 서로 독립적으로 수행한다.
   - Singleton은 `Scene 전반에서 많은 Object의 상태를 변경`할 수 있기에 Test에 방해될 수 있다.
   - 생성 시점이 명확하지 않다.
   - 특정 기능에 대해 mocking( mock 객체, 모의 객체 )을 하기 어렵다.
3. `High Coupling 유발`
   - Coupling이 높으면 Refactoring이 힘들다.
   - `Component 하나를 변경하면 연결된 다른 Component에 영향`을 줄 수 있기 때문이다.

</br>

### `장점`
확장성이 필요하지 않은 소규모 게임 개발에 유용하다.</br>

1. Learning Curve
   - `Core Pattern이 직관적`이다.
2. 사용자 친화적
   - 다른 Component에서 singleton을 사용할 때, `static instance만 참조`하면 된다.
3. 성능 보장
   - static instance에 항상 global access가 가능하기 때문에, `속도가 느린 GetComponent, Find, FindObjectOfType과 같은 연산의 결과를 Cache하지 않아도 된다`.

<br>

```c#
// cacing 예시
private GameObject player;

// Start에서 처음에만 Find 연산을 수행하고 이후에는 player 변수를 이용
void Start() { player = GameObject.Find("Player"); }
void Update() { player.transform.position = new Vector3(0, 0, 0); }
```
caching 한다는 의미는 `속도가 느린 기능을 수행하여 찾아낸 결과를 memory에 저장`해두고, 이후에 동일한 객체나 컴포넌트에 접근할 때 반복적으로 Find 연산을 수행하지 않고, `이미 저장된 결과를 재사용`하는 것이다.

대표적으로 Find 연산은 게임 오브젝트나 컴포넌트를 Scene 내에서 탐색하여 반환한다.<br>
이는 전체 Scene이나 특정 부모 객체 내의 모든 자식 객체를 순회해야 하기 때문에 성능에 영향을 준다.<br>


<br>
<br>

# static class가 아니라 singleton인 이유
static class에는 static 변수와 함수만 선언할 수 있다.<br>
singleton class는 static한 성격을 가지지 않는다. 다만, static 변수를 이용해서 global access를 유도한다.<br>


</br>
</br>

# 예시 1 : Unity, C# singleton 구현 및 문제점
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

DontDestroyOnLoad() 사용, Lazy Initialization 사용( singletone이 처음으로 필요할 때 만든다 ), thread safe 환경 세팅</br>

</br>
</br>

# 예시 2 : Unity Singlton 개선 : Lazy Initialization
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

### `Lazy Initialization`

Lazy Initialzation으로 Instance가 필요할 때 생성할 수 있다.</br>
Instance에 접근할 때, SetupInstance를 이용해서 Scene에 존재하지 않는 경우 Instance를 생성한다.</br>
즉, `필요할 때만 Instance를 초기화`한다.</br>

Instance가 필요할 때까지 생성하지 않음으로써 `초기 loading 시간을 단축`하고, 필요할 때부터 memory에 올리면 된다.</br>

`하지만`
전투 중에 Lazy Initialization을 통해 초기화가 이뤄진다면, `게임 전투에 끊김 현상`이 생길 수 있다.<br>
또한 게임 로딩 시점에서 Managers.Resource가 수행되어 데이터를 가져오기 때문에 큰 성능 차이는 없다고 판단한다.<br>


</br>
</br>

# 예시 3 : 멀티 쓰레드 환경

## 3.1. lock과 volatile
`Unity는 싱글 쓰레드 환경`이기 때문에 문제가 없지만, `일반 c#은 멀티 쓰레드 환경을 적용할 수 있다`.</br>

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

### `instance null 체크를 2번하는 이유`
1. A 쓰레드가 Singleton 객체를 생성하는 도중에 첫 번째 if문에 B 쓰레드가 접근하면, lock (padlock)에서 B 쓰레드가 대기한다.
2. A 쓰레드가 객체를 생성하고 lock을 빠져나가면, B 쓰레드가 instance = new Singleton();에 접근하여 또 instance를 생성한다.
3. 위 과정을 막기 위해서 instance null 체크를 두 번 수행한다.

</br>

### `volatile을 사용하는 이유`
멀티 쓰레드 환경에서 사용함을 알려준다.</br>
멀티 쓰레드 환경에서 CPU의 cache에 있는 데이터와 memory에 있는 데이터가 miss matching 하는 경우가 발생할 수 있다.</br>
`volatile을 사용하면 cache 최적화에서 제외`하지만, 위 문제가 발생할 여지가 없다.</br>

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

## 4.1. 간단한 Generic
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
Singleton을 상속받은 GameManager이다.</br>

<br>
<br>

## 4.2. 실전 Generic
```c#
public class SingletonBehaviour<T> : MonoBehaviour where T : SingletonBehaviour<T>
{
  protected bool m_IsDestroyOnLoad = false;

  protected static T m_Instance;
  public static T Instance { get { return m_Instance; }}

  private void Awake()
  {
    Init();
  }

  protected virtual void Init()
  {
    if (m_Instance == null)
    {
      m_Instance = (T)this;
      if (!m_IsDestroyOnLoad)
      {
        DontDestroyOnLoad(this);
      }
    }
    else
    {
      Destroy(gameObject);
    }
  }

  protected virtual void OnDestroy()
  {
    Dispose();
  }

  protected virtual void Dispose()
  {
    m_Instance = null;
  }
}
```
bool 값으로 singleton instance가 scene 전환 시 삭제 여부를 결정한다.<br>


### `중복된 Instance를 파괴한다는 의미`
`m_Instance는 static 변수이기 때문에 memory를 하나만 차지`한다.<br>
따라서 Init() 함수에서 `m_Instance가 Scene에 존재하면( memory에 존재 ) 현재 Singleton instance를 삭제`한다.<br>

m_Instance는 최초로 설정된 instance는 계속 유지된다.<br>
Init() 함수는 기존 instance가 이미 존재함을 감지하고 새로 생성된 게임 오브젝트를 파괴한다.<br>
`중요한 포인트는 static 변수인 m_Instance가 이미 참조하고 있는 객체는 memory에 남아있고, 이후 중복 생성된 객체는 memory에서 해제`된다.<br>

<br>

### `중복된 Instance를 파괴한다는 의미 2`
현재 게임 오브젝트가 파괴될 때, m_Instance를 null 처리한다.<br>
`중복 생성된 객체를 파괴할 때 기존 m_Instance에 영향을 미칠 것 같지만, OnDestroy()가 호출되는 시점에서 파괴되는 객체는 이미 중복 생성된 객체이기 때문에 영향을 미치지 않는다`.<br>

<br>

### `Instance 동작 과정`

1. `첫 번째 singleton 객체가 생성되어 m_Instance memory 공간에서 이를 참조`한다.
2. 두 번째로 동일한 singleton 객체가 생성되면, Init() 메서드에서 m_Instance가 존재하기 때문에 `중복 객체는 파괴`된다.
3. `이때 중복 객체의 OnDestory()가 호출`된다.
4. `기존 m_Instance는 첫 번째 객체를 참조`하고 있다. 따라서 Dispose()에서 m_Instance를 null로 설정하더라도 `기존의 m_Instance에는 영향을 주지 않는다`.
5. null로 세팅한 후에 해당 게임 오브젝트는 Scene에서 사라진다.

<br>

기존 m_Instance에 영향을 주지 않는 이유는 참조의 일관성 때문이다.<br>
```c#
protected virtual void OnDestroy()
{
    if (m_Instance == this)
    {
        Dispose();
    }
}
```
그럼에도 불안하다면, `현재 instance가 singleton instance와 동일한지 확인 후에 null 처리`를 수행한다.<br>

`하지만 Dispose() 의도`는 child class에서 자신만의 파괴 로직을 넣기 위함이기 때문에 기존 코드로 유지해도 된다.<br>


<br>
<br>

# 예시 5 : 다른 Manager를 관리하는 Managers
```c#
public class Managers : MonoBehaviour
{
  private static Managers _instance;
  private static Managers Instance { get { Init(); return _instance; }}

  private ResourceManager _resource = new ResourceManager();
  public static ResourceManager Resource { get { return Instance?._resource; } }

  public static void Init()
  {
    if (_instance == null) {
      GameObject go = GameObject.Find("Managers");
      if (go == null) {
        go = new GameObject { name = "Managers" };
        go.AddComponent<Managers>();
      }

      DontDestroyOnLoad(go);

      _instance = go.GetComponent<Managers>();
    }
  }
}
```

`Managers 내부의 Manager는 왜 static으로 관리 안 하는 이유`<br>
Managers의 Instance가 만들어질 때, `각 Manager의 객체 생성과 초기화 순서를 제어`할 수 있다.<br>
PoolManager가 ResourceManager에 Dependency하고 있다면, 두 객체가 올바른 순서로 초기화되는 것을 보장한다.<br>

