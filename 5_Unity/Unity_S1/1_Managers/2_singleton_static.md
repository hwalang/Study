- [Singleton과 Static으로 Managers를 구현하는 이유](#singleton과-static으로-managers를-구현하는-이유)
  - [1. 유일성 보장](#1-유일성-보장)
  - [2. Lazy Initialization](#2-lazy-initialization)
  - [3. Global State 관리](#3-global-state-관리)
  - [4. 개발 편의성](#4-개발-편의성)
  - [5. MonoBehaviour와 Singleton의 시너지](#5-monobehaviour와-singleton의-시너지)
- [Managers가 관리하는 Manager 멤버 변수를 static으로 관리하지 않는 이유](#managers가-관리하는-manager-멤버-변수를-static으로-관리하지-않는-이유)
  - [1. Memory 효율성](#1-memory-효율성)
  - [2. Dependency Injection](#2-dependency-injection)
  - [3. Multi-Thread](#3-multi-thread)
  - [4. 어려운 Test](#4-어려운-test)

</br></br></br>

# Singleton과 Static으로 Managers를 구현하는 이유
먼저 `static`으로 정의된 변수는 `application 내 어디에서든 쉽게 접근`할 수 있다. 이는 singleton pattern의 핵심이다.</br>

`singleton pattern`으로 Managers.Instance를 관리한다는 의미는 `프로그램 전체에서 하나의 Instance만 생성되고 사용할 수 있도록 보장`하기 위함이다.</br>

외부 시스템이랑 상호 작용하는 경우, 유일성을 보장해야 하기 때문에 singleton pattern을 사용한다.</br>

</br></br></br>

## 1. 유일성 보장
singleton pattern으로 관리하면 `resource( memory )를 절약`하고, 여러 instance가 동시에 존재하면서 발생할 수 있는 `데이터 불일치 문제를 피할 수 있다`.</br>

</br></br></br>

## 2. Lazy Initialization
Init() 메소드를 통해 `필요할 때만 Instance를 초기화`한다.</br>
Instance가 필요할 때까지 객체를 생성하지 않음으로써 `초기 loading 시간을 단축`하고, `memory를 효율적으로 사용`할 수 있다.</br>

`하지만` 전투 중에 Lazy Initialization을 통해 초기화가 이뤄진다면, 게임 전투에 버벅임이 생길 수 있다.</br>

</br></br></br>

## 3. Global State 관리
Managers 클래스는 다양한 Manager를 포함한다.</br>
static Instance를 통해 `관리하는 Manager들은 게임의 어느 곳에서든 동일한 상태를 공유`한다.</br>

</br></br></br>

## 4. 개발 편의성
Managers.Instance.Data로 표현하는 DataManager 인스턴스를 Managers.Data로 편리하게 사용하고 가독성을 높일 수 있다.</br>

</br></br></br>

## 5. MonoBehaviour와 Singleton의 시너지
Managers 클래스는 Unity Object의 생명 주기를 따른다.</br>
일반적인 singleton 구현과 달리 MonoBehaviour 클래스는 직접 생성자를 사용할 수 없기 때문에 Unity Object로서 Instance의 생명 주기를 적절히 다룬다.</br>


</br>
</br>
</br>


# Managers가 관리하는 Manager 멤버 변수를 static으로 관리하지 않는 이유

## 1. Memory 효율성
Manager 변수들을 static으로 관리하면 프로그램 전체에서 하나의 instance만 유지된다.</br>
이는 `memory를 직접적으로 제어할 수 없기에` memory 낭비가 발생할 수 있다.</br>
하지만 instance로 관리하면 `필요에 따라 memory를 사용하고 해제`한다.</br>

</br></br></br>

## 2. Dependency Injection
singleton pattern은 class 간 `높은 결합도( coupling )를 초래`할 수 있다.</br>
class가 singleton instance에 의존한다면, `모듈화 및 테스트가 어려워`진다.</br>

</br></br></br>

## 3. Multi-Thread
singleton instance 초기화 과정이 `multi-thread 환경`에서 동시에 발생하는 경우, 동기화 문제가 발생할 수 있다.</br>
Dead lock이나 Race Condition을 방지하는 추가적인 동기화 처리가 필요하기 때문에 `성능이 저하`된다.</br>

</br></br></br>

## 4. 어려운 Test
깅한 coupling은 단위 테스트를 수행하기 어려워진다.</br>
Managers 로직을 테스트하기 위해서는 Data, Resource 등 관리하는 모든 Manager를 함께 초기화할 필요가 있다.</br>
singleton과 static으로 관리하지 않으면 `특정 기능에 대해 mocking` 할 수 있다.</br>


</br>
</br>
</br>