- [Special Folder Name : Resources](#special-folder-name--resources)
  - [사용 예시](#사용-예시)
  - [사용하는 이유](#사용하는-이유)
  - [문제점](#문제점)
    - [1. path 관리](#1-path-관리)
    - [2. built-in](#2-built-in)
    - [3. memory leak](#3-memory-leak)
    - [4. Load 시간이 느리다](#4-load-시간이-느리다)

</br>

# Special Folder Name : Resources
Resources, Scripts, Scenes 폴더는 Unity에서 `Special Folder Name으로 지정한 폴더`다. cpp의 keyword와 같은 개념이다.</br>
Resources 폴더에 파일을 저장하면, `동적 로드를 지원하는 기능`을 제공한다.</br>
이러한 파일들은 동적 로드로 인해 파일을 건드리지 않기 때문에 개발을 진행할 때 특정 메소드를 호출하여 가져올 수 있다.</br>

</br>
</br>

## 사용 예시
```c#
// Object Load
GameObject bullet;
bullets = Resources.Load("Prefabs/Bullet") as GameObject; // == (GameObject)Resources.Load("Prefabs/Bullet");
```
Load() 메소드는 `Object Type을 리턴`하며, Asset Path를 string으로 판단한다.</br>
내부적으로 `Resources/Prefabs/Bullet` 경로에 저장된 Asset을 `메모리로 Load` 한다.</br>

즉, `path를 이용하여 memory로 load하고 필요하면 이를 instance 화` 한다.</br>

Bullet은 GameObject Type으로 선언했기 때문에, Load() 메소드의 반환 값인 Object Type을 GameObject로 Casting 해야 한다.</br>

</br>
</br>

## 사용하는 이유
1. 앱을 실행하고 이용하는데 `필수적인 Resource`인 경우
2. `Update가 빈번하지 않고`, `Remote로 Update할 필요가 없는 경우`

</br>
</br>

## 문제점

</br>

### 1. path 관리
Client에서 string으로 path를 관리하기 때문에 `Resources에 있는 Asset의 경로가 변경되면 코드 상의 path도 수정`해야 한다.</br>

</br>

### 2. built-in
Resource 폴더를 사용하면 프로젝트를 빌드하면서 `c# 코드와 resource 파일들이 apk에 묶어서 배포( built-in )`한다.</br>
즉, `Resources 폴더에 존재하는 모든 Asset이 최종 실행 파일에 포함`된다.</br>
이에 따른 `게임 용량 증가` 문제도 있다.</br>

Resources 폴더 내부의 Asset이 build 과정에서 모두 포함되기 때문에 대용량 Asset이 많은 게임 특성상, `build 시간이 길어진다`.</br>

모바일 게임의 경우 스토어에 게임을 올릴 때 심사 기간이 필요하다.</br>
Resources 폴더를 사용한 Asset에 수정사항이 발생하면 다시 배포해야 하기 때문에 `심사 기간만큼 실제 게임에 적용하는 기간이 늘어난다`.</br>
패치와 배포는 다른 개념이다.</br>

</br>

### 3. memory leak
Load()를 통해 Asset을 불러오면 Memory에 저장한다.</br>
`memory에서 해제되기 전까지 남아있는데, 이를 신경쓰지 않으면 memory leak가 발생`한다.</br>

실제로 Lost Taste, 던전처리기사 게임을 만들면서 Effect를 Resources 폴더에 저장하고, 이를 memory에 load 하여 사용한 적이 있다.</br>
여기서 effect를 직접 삭제하지 않으면 memory에 남아있는 현상이 발생했다.</br>

</br>

### 4. Load 시간이 느리다
Resources.Load()를 통해 Asset을 가져올 때, 이를 `디스크에서 찾아 Load` 해야 한다.</br>
Resource의 용량이 많을수록 Load 시간이 길어질 수 있다.</br>