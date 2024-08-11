- [Singleton과 Static으로 Managers를 구현하는 이유](#singleton과-static으로-managers를-구현하는-이유)
  - [1. singleton 클래스를 중점으로 다른 클래스 간의 데이터 공유](#1-singleton-클래스를-중점으로-다른-클래스-간의-데이터-공유)
  - [2. 유일성 보장](#2-유일성-보장)
  - [3. Lazy Initialization와 memory 절약](#3-lazy-initialization와-memory-절약)
  - [4. Global State 관리](#4-global-state-관리)
  - [5. 개발 편의성](#5-개발-편의성)
  - [5. MonoBehaviour와 Singleton의 시너지](#5-monobehaviour와-singleton의-시너지)
- [Managers가 관리하는 Manager 멤버 변수를 static으로 관리하지 않는 이유](#managers가-관리하는-manager-멤버-변수를-static으로-관리하지-않는-이유)
  - [1. Instance의 Life-Cycle 관리](#1-instance의-life-cycle-관리)
  - [2. Dependency 관리](#2-dependency-관리)
  - [3. Multi-Thread](#3-multi-thread)
  - [4. 어려운 Test](#4-어려운-test)

</br></br></br>

# Singleton과 Static으로 Managers를 구현하는 이유

## 1. singleton 클래스를 중점으로 다른 클래스 간의 데이터 공유
먼저 `static`으로 정의된 변수는 `application 내 어디에서든 쉽게 접근`할 수 있다. 이는 singleton pattern의 핵심이다.</br>

</br></br></br>

## 2. 유일성 보장
`singleton pattern`으로 Managers.Instance를 관리한다는 의미는 `프로그램 전체에서 하나의 Instance만 생성되고 사용할 수 있도록 보장`하기 위함이다.</br>

singleton pattern으로 관리하면 `resource( memory )를 절약`하고, 여러 instance가 동시에 존재하면서 발생할 수 있는 `데이터 불일치 문제를 피할 수 있다`.</br>

외부 시스템이랑 상호 작용하는 경우, 유일성을 보장해야 하기 때문에 singleton pattern을 사용한다.</br>

```c#
public static void Init()
{
  if (s_instance == null)
  {
    GameObject go = GameObject.Find("@Managers");
    if (go == null)
    {
      go = new GameObject { name = "@Managers" };
      go.AddComponent<Managers>();
    }
    DontDestroyOnLoad(go);

    s_instance = go.GetComponent<Managers>();
  }
}
```
Find()를 활용해서 Hierarchy view에서 @Managers가 있는지 판단한다.</br>
```c#
Instance = this;
```
Find() 함수로 게임 오브젝트를 찾으면 성능 부하가 발생하지만, 위 코드로 Managers Instance를 초기화하면 Hierarchy view에서 @Managers Object를 복붙할 수 있는 문제가 발생할 수 있다.</br>

</br></br></br>

## 3. Lazy Initialization와 memory 절약
```c#
// 에시 코드
private static Managers s_instance;
private static Managers Instance { get { Init(); return s_instance; } }

private DataManager _data = new DataManager();
public static DataManager Data { get { return Instance?._data; } }      // Instance를 호출하면서 Init()이 수행
```
Init() 메소드는 Singleton Instance가 존재하지 않을 때만, Instance를 생성한다.</br>
이는 곧 다른 클래스에서 Instance에 접근하는 일이 발생하지 않는다면, Managers.Instance가 생성되지 않음을 의미한다. 즉, `필요할 때만 Instance를 초기화`한다.</br>

Instance가 필요할 때까지 객체를 생성하지 않음으로써 `초기 loading 시간을 단축`하고, `memory를 효율적으로 사용`할 수 있다.</br>

`하지만` 전투 중에 Lazy Initialization을 통해 초기화가 이뤄진다면, 게임 전투에 버벅임이 생길 수 있다.</br>
또한 게임 로딩 시점에서 Managers.Resource가 수행되어 데이터를 가져오기 때문에 큰 성능 차이는 없다고 판단한다.</br>

</br>

Instance가 하나만 존재하도록 제한하기 때문에 `여러 개의 Instance가 생성되지 않는다`.</br>
특히 Managers class는 다양한 Manager 멤버 변수를 가지며, 이는 `memory 사용량이 큰 것`을 알 수 있다.</br>
또한 `여러 곳에서 사용`된다는 특징도 있다.</br>

이를 하나만 생성하게 제한하면 `메모리를 절약`할 수 있다.</br>

</br></br></br>

## 4. Global State 관리
Managers 클래스는 다양한 Manager를 포함한다.</br>
static Instance를 통해 `관리하는 Manager들은 게임의 어느 곳에서든 동일한 상태를 공유`한다.</br>

따라서 singleton Managers를 활용해서 `게임 내 상태를 서로 공유`할 수 있다.</br>

</br></br></br>

## 5. 개발 편의성
Managers.Instance.Data로 표현하는 DataManager 인스턴스를 Managers.Data로 편리하게 사용하고 가독성을 높일 수 있다.</br>

</br></br></br>

## 5. MonoBehaviour와 Singleton의 시너지
Managers 클래스는 Unity Object의 생명 주기를 따른다.</br>
일반적인 singleton 구현과 달리 MonoBehaviour 클래스는 직접 생성자를 사용할 수 없기 때문에 Unity Object로서 Instance의 생명 주기를 적절히 다룬다.</br>

`하지만` Managers Instance는 Start()에서 생성되기 때문에 Instance 할당 시점 이전에 다른 클래스에서 접근하면 null 오류가 발생할 수 있다.</br>

또한 Scene이 변경될 경우 Managers 클래스가 파괴되기 때문에 이전 Scene의 데이터가 소실된다.</br>
이를 `DontDestroyOnLoad()로 방지`해야한다.</br>


</br>
</br>
</br>


# Managers가 관리하는 Manager 멤버 변수를 static으로 관리하지 않는 이유

## 1. Instance의 Life-Cycle 관리
Manager 변수들을 static으로 관리하면 프로그램 전체에서 하나의 instance만 유지된다.</br>
이는 `memory를 직접적으로 제어할 수 없기에` memory 낭비가 발생할 수 있다.</br>

따라서 일반적인 instance로 관리하면 `필요에 따라 memory를 사용하고 해제`할 수 있다.</br>


</br></br></br>

## 2. Dependency 관리
Managers의 Instance가 만들어질 때 각 `Manager의 객체 생성과 초기화 순서를 제어`할 수 있다.</br>
`예를 들면`, PoolManager가 ResourceManager에 의존하고 있다면, 이 두 객체가 올바른 순서로 초기화되는 것을 보장할 수 있다.</br>

</br></br></br>

## 3. Multi-Thread
singleton instance 초기화 과정이 `multi-thread 환경`에서 동시에 발생하는 경우, `동기화 문제`가 발생할 수 있다.</br>
동기화를 위한 추가 작업( overhead )가 발생하고 이는 `성능 저하`로 나타난다.</br>


</br></br></br>

## 4. 어려운 Test
깅한 coupling은 `단위 테스트`를 수행하기 어려워진다.</br>
Managers 로직을 테스트하기 위해서는 Data, Resource 등 관리하는 모든 Manager를 함께 초기화할 필요가 있다.</br>

이때 테스트 환경에 맞는 객체를 임의로 지정할 수 있다.</br>
즉, `특정 기능에 대해 mocking( 모의<mock> 객체)` 할 수 있다.</br>


</br>
</br>
</br>